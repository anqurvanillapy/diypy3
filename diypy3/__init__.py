#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""\
This is a formatting module for input data and transfering to the C extension
module _diypy3.

Functions:

binary_tree() -- format arguments for _diypy3._binary_tree() function to create
                 and initialize a binary tree.
array_stack() -- format arguments for _diypy3._array_stack() function to create
                 and initialize an array stack.
"""

import _diypy3

class Diypy3(object):

    def __init__(self):

        self.PREORDER = 0
        self.INORDER = 1
        self.POSTORDER = 2

    def check_args_type(self, args):

        argtp = type(args).__name__
        if argtp not in ['list', 'tuple']:
            tperr = 'A list or tuple is required, not {0}'
            raise TypeError(tperr.format(argtp))

    def array_stack(self, size, inc, args):

        """Convert an args tuple or list to C string in specific format
        to _diypy3._array_stack() function. User can create a array
        stack whose size can be customized, but types of data can only be
        string.

        A value in stack cannot be spaces, and spaces within a string will
        be removed. A good formatted C string can be 'foo bar ', which
        will create an array stack with 2 values.

        The first argument defines the max size of the stack, and the
        second defines the increment of stack pushing.
        """

        self.check_args_type(args)

        intargs = (size, inc)
        for i in intargs:
            argtp = type(i).__name__
            if argtp != 'int':
                tperr = 'An integer is required, not {0}'
                raise TypeError(tperr.format(argtp))

        arrstk_str = ''
        for arg in args:
            arg = str(arg).replace(' ', '')
            if not arg:
                arg = '0'
            arrstk_str += '{0} '.format(arg)

        print('max size: {0}'.format(size))
        print('increment: {0}'.format(inc))
        print('stack size: {0}'.format(len(arrstk_str.split())))
        _diypy3._array_stack(size, inc, arrstk_str)

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

        self.check_args_type(args)

        bt_str = ''
        for node in args:
            node = str(node).replace(' ', '')
            if not node:
                node = '0'
            bt_str += '{0} '.format(node)

        nodes = len([n for n in bt_str.split() if n != '0'])
        depth = len(bt_str.split('0')[0].split())

        print('nodes: {0}'.format(nodes))
        print('depth: {0}'.format(depth))
        _diypy3._binary_tree(flag, bt_str)
