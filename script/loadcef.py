#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
import sys
import time
import hashlib
import os
import json
import re
import logging


def timestamp() -> str:
    return str(int(time.time() * 1000))


def readcookies(file_name) -> list:
    if not os.path.exists(file_name):
        logging.info('%s is null', file_name)
        raise OSError(file_name + ' 不存在')

    with open(file_name, 'r', encoding='utf-8') as f:
        json_str = f.read()

    try:
        # 将字符串转换为字典
        cookies_dict = eval(json_str)
        cookies = cookies_dict['cookies']
    except Exception:
        raise Exception('转换「' + file_name + '」为字典时出现错误')
    return cookies


class LoginError(ValueError):
    pass


class YoudaoNoteSession(requests.Session):
    """ 继承于 requests.Session，能像浏览器一样，完成一个完整的 Session 操作"""

    # 类变量，不随着对象改变
    WEB_URL = 'https://note.youdao.com/web/'
    SIGN_IN_URL = 'https://note.youdao.com/signIn/index.html?&callback=https%3A%2F%2Fnote.youdao.com%2Fweb%2F&from=web'  # 浏览器在传输链接的过程中是否都将符号转换为 Unicode？
    LOGIN_URL = 'https://note.youdao.com/login/acc/urs/verify/check?app=web&product=YNOTE&tp=urstoken&cf=6&fr=1&systemName=&deviceType=&ru=https%3A%2F%2Fnote.youdao.com%2FsignIn%2F%2FloginCallback.html&er=https%3A%2F%2Fnote.youdao.com%2FsignIn%2F%2FloginCallback.html&vcode=&systemName=&deviceType=&timestamp='
    COOKIE_URL = 'https://note.youdao.com/yws/mapi/user?method=get&multilevelEnable=true&_=%s'
    ROOT_ID_URL = 'https://note.youdao.com/yws/api/personal/file?method=getByPath&keyfrom=web&cstk=%s'
    DIR_MES_URL = 'https://note.youdao.com/yws/api/personal/file/%s?all=true&f=true&len=50&sort=1&isReverse=false&method=listPageByParentId&keyfrom=web&cstk=%s'
    FILE_URL = 'https://note.youdao.com/yws/api/personal/sync?method=download&keyfrom=web&cstk=%s'

    # 莫有类方法

    def __init__(self):

        # 使用父类的构造函数初始化 self
        requests.Session.__init__(self)

        self.headers = {
            'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36',
            'Accept': '*/*',
            'Accept-Encoding': 'gzip, deflate, br',
            'Accept-Language': 'zh-CN,zh;q=0.9,en;q=0.8',
        }

        # 属于对象变量
        self.cstk = None
        self.local_dir = None
        self.smms_secret_token = None

    def checklogin(self, username, password) -> str:
        try:
            cookies = readcookies('cookies.json')
        except Exception as err:
            logging.info('readcookies error: %s', format(err))
            cookies = None

        # 如果 cookies 不为 null，使用 cookies 登录
        if cookies is not None:
            # 如果 Cookies 被修改或过期等原因导致 Cookies 登录失败，改用使用账号密码登录
            try:
                root_id = self.cookieslogin(cookies)
                print('本次使用 Cookies 登录')
            except KeyError as err:
                logging.info('cookie 登录出错：%s', format(err))
                root_id = self.login(username, password)
                print('本次使用账号密码登录，已将 Cookies 保存到「cookies.json」中，下次使用 Cookies 登录')
        else:
            root_id = self.login(username, password)
            print('本次使用账号密码登录，已将 Cookies 保存到「cookies.json」中，下次使用 Cookies 登录')

        return root_id

    def login(self, username, password) -> str:
        """ 模拟浏览器用户操作，使用账号密码登录，并保存 Cookie """

        # 模拟打开网页版
        self.get(self.WEB_URL)
        # 模拟设置上一步链接
        self.headers['Referer'] = self.WEB_URL
        # 模拟重定向跳转到登录页
        self.get(self.SIGN_IN_URL)
        # 模拟设置上一步链接
        self.headers['Referer'] = self.SIGN_IN_URL
        # 模拟跳转到登录页后的请求连接
        self.get('https://note.youdao.com/login/acc/pe/getsess?product=YNOTE&_=%s' % timestamp())
        self.get('https://note.youdao.com/auth/cq.json?app=web&_=%s' % timestamp())
        self.get('https://note.youdao.com/auth/urs/login.json?app=web&_=%s' % timestamp())

        data = {
            'username': username,
            'password': hashlib.md5(password.encode('utf-8')).hexdigest()
        }

        logging.info('cookies: %s', self.cookies)

        # 模拟登陆
        self.post(self.LOGIN_URL,
                  data=data, allow_redirects=True)

        # 登录成功后的链接，里面包含可用于登录的最新 Cookie: YNOTE_CSTK
        self.get(self.COOKIE_URL % timestamp())

        logging.info('new cookies: %s', self.cookies)

        # 设置 cookies
        cstk = self.cookies.get('YNOTE_CSTK')

        if cstk is None:
            logging.info('cstk: %s', cstk)
            raise LoginError('请检查账号密码是否正确！也可能因操作频繁导致需要验证码，请切换网络（改变 ip）或等待一段时间后重试！')

        self.cstk = cstk

        self.savecookies()

        return self.get_root_id()

    def savecookies(self) -> None:
        """ 将 Cookies 保存到 cookies.json """

        cookies_dict = {}
        cookies = []

        # cookiejar 为 RequestsCookieJar，相当于是一个 Map 对象
        cookiejar = self.cookies
        for cookie in cookiejar:
            cookie_eles = [cookie.name, cookie.value, cookie.domain, cookie.path]
            cookies.append(cookie_eles)

        cookies_dict['cookies'] = cookies

        with open('cookies.json', 'wb') as f:
            f.write(str(json.dumps(cookies_dict, indent=4, sort_keys=True)).encode())

    def cookieslogin(self, cookies_dict) -> str:
        """ 使用 Cookies 登录，其实就是设置 cookies """

        cookiejar = self.cookies
        for cookie in cookies_dict:
            cookiejar.set(cookie[0], cookie[1], domain=cookie[2], path=cookie[3])

        self.cstk = cookies_dict[0][1]

        return self.getrootid()

    def getrootid(self) -> str:
        """
        获取有道云笔记 root_id
        root_id 始终不会改变？可保存？可能会改变，几率很小。可以保存，保存又会带来新的复杂度。只要登录后，获取一下也没有影响
        """

        data = {
            'path': '/',
            'entire': 'true',
            'purge': 'false',
            'cstk': self.cstk
        }
        response = self.post(self.ROOT_ID_URL % self.cstk, data=data)
        json_obj = json.loads(response.content)
        try:
            return json_obj['fileEntry']['id']
        # Cookie 登录时可能错误
        except KeyError:
            raise KeyError('Cookie 中没有 cstk')
            # parsed = json.loads(response.content.decode('utf-8'))
            # raise LoginError('请检查账号密码是否正确！也可能因操作频繁导致需要验证码，请切换网络（改变 ip）或等待一段时间后重试！接口返回内容：',
            #                  json.dumps(parsed, indent=4, sort_keys=True))
    
    def downloadfile(self, filename, outdir, root_id) -> None:
        """ 下载文件 """
        url = self.DIR_MES_URL % (root_id, self.cstk)

        response = self.get(url)
        json_obj = json.loads(response.content)
        
        try:
            json_obj['count']
        # 如果 json_obj 不是 json，退出
        except KeyError:
            logging.info('json_obj: %s', json_obj)
            raise KeyError('有道云笔记修改了接口地址，此脚本暂时不能使用！请提 issue')
            
        for entry in json_obj['entries']:
            file_entry = entry['fileEntry']
            id = file_entry['id']
            name = file_entry['name']
            logging.info('name: %s', name)
            # 如果是目录，继续遍历目录下文件
            if file_entry['dir']:
                self.downloadfile(filename, outdir, id)
            elif name == filename:
                self.savefile(id, os.path.join(outdir, filename) , 'zip')
                
    def checkpathname(self, name):
        """ 避免 open() 函数失败（因为目录名错误），修改文件名 """

        regex = re.compile(r'[\\/:\*\?"<>\|]')  # 替换 \ / : * ? " < > | 为 _
        name = regex.sub('_', name)
        return name

    def savefile(self, file_id, file_path, youdao_file_suffix) -> None:
        """ 下载文件。先不管什么类型文件，均下载。如果是 .note 类型，转换为 Markdown """

        data = {
            'fileId': file_id,
            'version': -1,
            'convert': 'true',
            'editorType': 1,
            'cstk': self.cstk
        }
        url = self.FILE_URL % self.cstk
        response = self.post(url, data=data)

        with open(file_path, 'wb') as f:
            f.write(response.content)  # response.content 本身就是字节类型

def download():
    start_time = int(time.time())

    try:
        username = 'zhouxingbang92@163.com'
        password = ''
        session = YoudaoNoteSession()
        root_id = session.checklogin(username, password)
        print('正在下载，请稍后 ...')
        session.downloadfile('cef_bin.zip', '.', root_id)

    except requests.exceptions.ProxyError as proxyErr:
        print('请检查网络代理设置；也有可能是调用有道云笔记接口次数达到限制，请等待一段时间后重新运行脚本，若一直失败，可删除「cookies.json」后重试')
        print('错误提示：' + format(proxyErr))
        print('已终止执行')
        sys.exit(1)
    except requests.exceptions.ConnectionError as connectionErr:
        print('网络错误，请检查网络是否正常连接。若突然执行中断，可忽略此错误，重新运行脚本')
        print('错误提示：' + format(connectionErr))
        print('已终止执行')
        sys.exit(1)
    except LoginError as loginErr:
        print('错误提示：' + format(loginErr))
        print('已终止执行')
        sys.exit(1)
    # 链接错误等异常
    except Exception as err:
        print('错误提示：' + format(err))
        print('已终止执行')
        sys.exit(1)

    end_time = int(time.time())
    print('运行完成！耗时 %s 秒' % str(end_time - start_time))


if __name__ == '__main__':
    download()
