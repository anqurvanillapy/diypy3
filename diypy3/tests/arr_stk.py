#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""\
This script creates a stack array
"""

import diypy3

d = diypy3.Diypy3()
arr_stk = (1, 2, 3, 4, 5)
max_size = 100
inc = 10
d.array_stack(max_size, inc, arr_stk)
