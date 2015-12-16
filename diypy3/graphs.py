#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import subprocess
from jinja2 import *

env = Environment(loader=PackageLoader('graphs', '.'))
graphs_tmpl = env.get_template('graphs.dot')

def generate_graph_img(imgfmt='png'):

    dotout = graphs_tmpl.render(hello='fuck', world='you')
    with open('temp.dot', 'w') as filehandle:
        filehandle.write(dotout)
    prompt = ['dot', '-T' + imgfmt, 'temp.dot', '-o', 'graph.' + imgfmt]
    subp = subprocess.run(prompt)
    cwd = os.path.getcwd
    print("graph image generated at '{0}'".format(cwd))
    subp = subprocess.run(['rm', 'temp.dot'])