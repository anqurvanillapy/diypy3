#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""\
This is a formatting module for input data and transfering to the C extension
module _diypy3.

Functions:

binary_tree() -- format arguments for _diypy3._binary_tree() function to create
                 and initialize a binary tree.
"""

import _diypy3

class Diypy3(object):

    def __init__(self):

        self.PREORDER = 0
        self.INORDER = 1
        self.POSTORDER = 2

    def binary_tree(self, flag, args):

        """Convert an args tuple or list to C string in specific format
        to _diypy3._binary_tree() function. User can only create a binary
        tree with less than 1023 nodes, whose types of data can only be
        string.

        A node value cannot be spaces, and spaces within a string will
        be removed. A good formatted C string can be 'foo bar ', which
        will create a binary tree with 2 nodes.

        The first flag defines the order of output data, which includes:
            PREORDER -- pre-order
            INORDER -- in-order
            POSTORDER -- post-order
        """

        argtp = type(args).__name__
        if argtp not in ['list', 'tuple']:
            tperr = 'A list or tuple is required, not {0}'
            raise TypeError(tperr.format(argtp))

        bt_str = ''
        for node in args:
            node = str(node).replace(' ', '')
            if not node:
                node = '0'
            bt_str += '{0} '.format(node)
        _bt_str = bt_str.replace(' ', '')
        nodes = len([n for n in _bt_str if n != '0'])
        depth = len(_bt_str.split('0')[0])

        print('nodes: {0} depth: {1}'.format(nodes, depth))
        _diypy3._binary_tree(flag, bt_str)
