import os
import sys
import subprocess
import shutil

def deepCopy(path, out):
    for files in os.listdir(path):
        name = os.path.join(path, files)
        back_name = os.path.join(out, files)
        if os.path.isfile(name):
            if not os.path.isfile(back_name):
                shutil.copy(name, back_name)
        else:
            if not os.path.isdir(back_name):
                os.makedirs(back_name)
            deepCopy(name, back_name)

def copyDepends():
    shadowBin = os.path.join('.', 'shadow', 'bin')
    if not os.path.isdir(shadowBin):
        os.makedirs(shadowBin)
   
    dependsPath = os.path.join('.', 'depends')
    for files in os.listdir(dependsPath):
        name = os.path.join(dependsPath, files, 'bin')
        if os.path.isdir(name):
            deepCopy(name, shadowBin)
            
def copyConfig():
    shadowBin = os.path.join('.', 'shadow', 'bin')
    if not os.path.isdir(shadowBin):
        os.makedirs(shadowBin)
    
    configPath = os.path.join('.', 'config')
    deepCopy(configPath, os.path.join(shadowBin, 'debug'))
    deepCopy(configPath, os.path.join(shadowBin, 'release'))

def generateSln():
    rootProPath = os.path.join('..', 'cpp', 'src.pro')
    commandList = [
       'qmake',
        '-tp',
        'vc',
        '-r',
        rootProPath 
    ]
    
    slnDir = 'shadow'
    if os.path.exists(slnDir):
        shutil.rmtree(slnDir)
        
    os.makedirs(slnDir)
    
    result = subprocess.call(commandList, cwd=slnDir)

if __name__ == '__main__':
    generateSln()
    copyDepends()
    copyConfig()
