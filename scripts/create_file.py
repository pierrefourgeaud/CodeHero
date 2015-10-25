#!/usr/bin/env python

import argparse
import os
import sys

from datetime import date

SOURCE_ROOT = os.path.abspath(os.path.dirname(os.path.dirname(__file__)))

def main():
  args = parse_args()
  create_file(args.file_path)

def parse_args():
  parser = argparse.ArgumentParser(description='Create a new source file with the right license')
  parser.add_argument('file_path',
                      help='The path of the file you want to create relative to the root of the project.'
                      'I.E: src/main.cpp')
  return parser.parse_args()

def create_file(path):
  print('Creating ' + path)
  target_file = os.path.join(SOURCE_ROOT, path)

  with open(os.path.join(SOURCE_ROOT, 'source_template.h'), 'r') as f:
    template = f.read()
  content = template.replace('{YEAR}', str(date.today().year))

  with open(target_file, 'w') as f:
    f.write(content)

if __name__ == '__main__':
  sys.exit(main())