#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension

_diypy = Extension('_diypy', sources=['diypy/ext/diypymodule.c'])
description = 'Data-structure Interface Yourself using Python'
try:
    with open('README.md', 'r') as filehandle:
        long_description = filehandle.read()
except:
    long_description = description

setup(name='diypy',
      version='0.1',
      description=description,
      long_description=long_description,
      author='AnqurVanillapy',
      author_email='anqurvanillapy@gmail.com',
      url='https://github.com/anqurvanillapy/diypy',
      packages=['diypy'],
      ext_modules=[_diypy])
