#!/usr/bin/env python
# -*- coding: utf-8 -*-

from distutils.core import setup, Extension

_diypy3 = Extension('_diypy3', sources=['diypy3/ext/diypy3module.c'])
description = 'Data-structure Interface Yourself using Python 3'
try:
    with open('README.md', 'r') as filehandle:
        long_description = filehandle.read()
except:
    long_description = description

setup(name='diypy3',
      version='0.1',
      description=description,
      long_description=long_description,
      author='AnqurVanillapy',
      author_email='anqurvanillapy@gmail.com',
      url='https://github.com/anqurvanillapy/diypy3',
      packages=['diypy3'],
      ext_modules=[_diypy3])
