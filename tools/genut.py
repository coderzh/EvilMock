#!/usr/bin/python

import sys
import os
import argparse
import CppHeaderParser
from mako.template import Template


def get_root_path():
    current_dir = os.path.dirname(__file__)
    root_file = os.path.join(current_dir, 'BLADE_ROOT')

    while not os.path.exists(root_file):
        current_dir = os.path.join(current_dir, os.path.pardir)
        if not os.path.exists(current_dir):
            return None
        root_file = os.path.join(current_dir, 'BLADE_ROOT')

    return os.path.abspath(current_dir)


def gen_code(root_path, source, template_file, target):
    source_filepath = os.path.realpath(source)
    target_filepath = os.path.realpath(target)
    target_filename = os.path.basename(target_filepath)
    ##source_filename = os.path.basename(source_filepath)
    ##target_filepath = os.path.join(os.path.dirname(source_filepath), "hook_" + source_filename)

    try:
        cpp_header = CppHeaderParser.CppHeader(source)
    except CppHeaderParser.CppParseError as e:
        print(e)
        sys.exit(1)

    #print('CppHeaderParser view of %s' % cpp_header)

    headerFilePath = os.path.relpath(cpp_header.headerFileName, root_path)
    headerFileName = os.path.basename(headerFilePath)

    template = Template(filename=template_file)
    result_code = template.render(classList=cpp_header.classes,
            functions=cpp_header.functions,
            headerFileName=headerFileName,
            headerFilePath=headerFilePath,
            includes=cpp_header.includes,
            FILENAME_H=target_filename.replace('.', '_').upper())

    if os.path.exists(target_filepath):
        overwrite = raw_input(target_filepath + ' exists. Overwrite it? (Y or N) ')
        if overwrite != 'y' and overwrite != 'Y':
            return

    with open(target_filepath, 'w') as f:
        f.write(result_code)

    print('Generate file: ' + target_filepath)



if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate UnitTest.')
    parser.add_argument('-t', '--template', default='tmock_template.h', help='etc: tmock_template.h')
    parser.add_argument('source', help='source .h file')
    parser.add_argument('target', help='output file path')
    args = parser.parse_args()

    template_file = os.path.join(os.path.split(os.path.realpath(__file__))[0], args.template)

    gen_code(get_root_path(), args.source, template_file, args.target)
