import os
import sys
import subprocess
import shutil

def deepcopy(path, out):
    for files in os.listdir(path):
        name = os.path.join(path, files)
        back_name = os.path.join(out, files)
        if os.path.isfile(name):
            if not os.path.isfile(back_name):
                shutil.copy(name, back_name)
        else:
            if not os.path.isdir(back_name):
                os.makedirs(back_name)
            deepcopy(name, back_name)

def copy_cef():
    debug_path = os.path.join('.', 'bin', 'debug')
    release_path = os.path.join('.', 'bin', 'release')
    
    if not os.path.isdir(debug_path):
        os.makedirs(debug_path)
    if not os.path.isdir(release_path):
        os.makedirs(release_path)
    '''
    cef_debug_path = os.path.join('.', 'cef', 'bin', 'debug')
    cef_release_path = os.path.join('.', 'cef', 'bin', 'release')
    deepcopy(cef_debug_path, debug_path)
    deepcopy(cef_release_path, release_path)
    '''
    
    resources_path = os.path.join('.', 'cef', 'resources')
    deepcopy(resources_path, debug_path)
    deepcopy(resources_path, release_path)

def generate_sln():
    root_pro_path = os.path.join('..', 'src', 'pcutil.pro')
    command_list = [
       'qmake',
        '-tp',
        'vc',
        '-r',
        root_pro_path 
    ]
    
    sln_dir = 'shadow'
    if os.path.exists(sln_dir):
        shutil.rmtree(sln_dir)
        
    os.makedirs(sln_dir)
    
    result = subprocess.call(command_list, cwd=sln_dir)

if __name__ == '__main__':
    copy_cef()
    generate_sln()
