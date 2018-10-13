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

def convertShader(shader_program, type, dstLanguage) :
    glslangTool = getToolsBinPath() + 'glslangvalidator'
    mantisSpirvCross = getToolsBinPath() + 'mantis-spirv-cross'

    tmpFileInput = tempfile.gettempdir() + '/' + "input." + type
    tmpFileSpirv  = tempfile.gettempdir() + '/' + "spirv"
    tmpFileOutput = tempfile.gettempdir() + '/' + "output"

    file = open(tmpFileInput, "w")
    file.write(shader_program)
    file.close()

    cmdLine = [glslangTool, '-H', '-V', '-o', tmpFileSpirv, tmpFileInput ]
    subprocess.call(args=cmdLine)

    cmdLine = [mantisSpirvCross, '--input', tmpFileSpirv, '--output', tmpFileOutput, '--lang', dstLanguage]
    subprocess.call(args=cmdLine)

    file = open(tmpFileOutput, 'r')
    file_str = file.read()
    file.close()
    return file_str

def ExtractVertexShader(shader_name, text) :
    return ExtractShader("@vert_shader", shader_name, text)

def ExtractFragmentShader(shader_name, text) :
    return ExtractShader("@frag_shader", shader_name, text)

def ExtractShader(shader_type, shader_name, text) :
    vert_shader_begin = re.search(r"(^|\s)" + re.escape(shader_type) + r"\s" + re.escape(shader_name) + r"\s", text)

    if not vert_shader_begin:
        error("Unable to find '" + shader_type + " " + shader_name + "'")

    vert_shader_end = re.search(r"(^|\s)@end\s", text[vert_shader_begin.end():])

    if not vert_shader_end:
        error("Unable to find '@end' for '" + shader_type + " " + shader_name + "'")

    return file_str[vert_shader_begin.end():vert_shader_begin.end() + vert_shader_end.start()]

#-------------------------------------------------------------------------------
if __name__ == '__main__' :
    print("{}".format(__file__))

    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('-i', '--input', required=True, help='Input file')
    parser.add_argument('-o', '--output', required=True, help='Output file')
    parser.add_argument('-l', '--lang', required=True, help='Output shader language')

    args = parser.parse_args()

    file = open(args.input, 'r')
    file_str = file.read()
    file.close()

    for shader_program in re.finditer(r"(^|\s)@shader_program\s", file_str):
        parameters = file_str[shader_program.end():].split(None, 2)
        if len(parameters) < 3:
            error("@shader_program requires three arguments.")
        print(parameters)

        shader_program_name = parameters[0]

        vertex_shader_source = ExtractVertexShader(parameters[1], file_str)
        fragment_shader_source = ExtractFragmentShader(parameters[2], file_str)

        vertex_shader = convertShader(vertex_shader_source, "vert", args.lang)
        fragment_shader = convertShader(fragment_shader_source, "frag", args.lang)

        shader_header = r"""#pragma once

#include <string>

namespace Mantis {
namespace GFX {
namespace Shaders {

    struct """ + shader_program_name + r""" {
        static const std::string vertex_shader;
        static const std::string fragment_shader;
    };

}
}
}"""

        file = open("shaders.h", "w")
        file.write(shader_header)
        file.close()

        shader_source = r"""#include "shaders.h"
        
namespace Mantis {
namespace GFX {
namespace Shaders {

        const std::string """ + shader_program_name + r"""::vertex_shader = R"(""" + vertex_shader + r""")";
        
        const std::string """ + shader_program_name + r"""::fragment_shader = R"(""" + fragment_shader + r""")";

}
}
}"""

        file = open("shaders.cpp", "w")
        file.write(shader_source)
        file.close()


    # dstPath, dstFilename = os.path.split(dstPath)
    # tmpFilename, ext = os.path.splitext(dstFilename)
    # tmpFilename += '.temp'