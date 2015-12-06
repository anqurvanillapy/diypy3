#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""\
This is a formatting module for input data and transfering to the C extension
module _diypy.

Functions:

binary_tree() -- format arguments for _diypy._binary_tree() function to create
                 and initialize a binary tree.
"""

import _diypy

class Diypy(object):

    def __init__(self):

        self.PREORDER = 0

    def binary_tree(self, flag, *args):

        """Convert an args tuple to C string in a specific format to
        _diypy._binary_tree() function. User can only create a binary
        tree with less than 1023 nodes, whose types of data can only be
        string.

        A node value cannot be spaces, and spaces within a string will
        be removed. A good formatted C string can be 'foo bar ', which
        will create a binary tree with 2 nodes.

        The first flag defines the order of input data, which includes:
            LEVELORDER -- level-order
            PREORDER -- pre-order
        """

        bt_str = ''
        for node in args:
            node = str(node).replace(' ', '')
            if not node:
                node = '0'
            bt_str += '{0} '.format(node)

        _diypy._binary_tree(flag, bt_str)
