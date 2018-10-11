#!/usr/bin/env python
'''
Mantis shader export script
'''

import sys
import os
import platform
import subprocess
import tempfile
import argparse
import re

ProjectDirectory = os.path.dirname(os.path.abspath(__file__)) + '/..'

#-------------------------------------------------------------------------------
def error(msg) :
    print("ERROR: {}".format(msg))
    sys.exit(10)

#-------------------------------------------------------------------------------
def getToolsBinPath() :
    path = os.path.dirname(os.path.abspath(__file__))
    if platform.system() == 'Windows' :
        path += '/win32/'
    elif platform.system() == 'Linux' :
        path +=  '/'
    else :
        error("Unknown host system {}".format(platform.system()))
    return path

def toSPIRV(srcPath, dstPath, dstLanguage) :
    '''
    Compile a shader to SPIR-V
    '''
    glslangTool = getToolsBinPath() + 'glslangvalidator'
    mantisSpirvCross = getToolsBinPath() + 'mantis-spirv-cross'

    dstPath, dstFilename = os.path.split(dstPath)
    tmpFilename, ext = os.path.splitext(dstFilename)
    tmpFilename += '.temp'
    tmpFile  = tempfile.gettempdir() + '/' + tmpFilename

    print('=== toSPIRV: {} => {}:'.format(srcPath, tmpFile))

    cmdLine = [glslangTool, '-H', '-V', '-o', tmpFile, srcPath ]
    subprocess.call(args=cmdLine)

    cmdLine = [mantisSpirvCross, '--input', tmpFile, '--output', dstFilename, '--lang', dstLanguage]
    subprocess.call(args=cmdLine)

def findAllSubstrings(substring, text) :
    return [m.end() for m in re.finditer(substring, text)]

#-------------------------------------------------------------------------------
if __name__ == '__main__' :
    print("{}".format(__file__))

    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-i', '--input', required=True, help='Input file')
    parser.add_argument('-o', '--output', required=True, help='Output file')
    parser.add_argument('-l', '--lang', required=True, help='Output shader language')

    args = parser.parse_args()

    file = open(args.input, 'r')
    print(findAllSubstrings(r"\s@shader_program\s", file.read()))

    #toSPIRV(args.input, args.output, args.lang)