#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension

diypy = Extension('diypy', sources=['diypy/diypymodule.c'])
with open('README.md', 'r') as filehandle:
    long_description = filehandle.read()

setup(name='diypy',
      version='0.1',
      description='Data-structure Interface Yourself using Python',
      long_description=long_description,
      author='AnqurVanillapy',
      author_email='anqurvanillapy@gmail.com',
      url='https://github.com/anqurvanillapy/diypy',
      ext_modules=[diypy])