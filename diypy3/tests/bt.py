#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""\
This script creates a simple full binary tree
"""

import diypy3

d = diypy3.Diypy3()
bt = (1, 2, 4, 0, 0, 5, 0, 0, 3, 6, 0, 0, 7, 0, 0)
d.binary_tree(d.PREORDER, bt)