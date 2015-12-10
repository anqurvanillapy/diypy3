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

    """A formatting module for C extension module _diypy3"""

    def __init__(self):

        self.PREORDER = 0
        self.INORDER = 1
        self.POSTORDER = 2

    def check_args_type(self, args):

        """Checkout whether the input args are valid. Only tuple and list
        are required."""

        argtp = type(args).__name__
        if argtp not in ['list', 'tuple']:
            tperr = 'A list or tuple is required, not {0}'
            raise TypeError(tperr.format(argtp))

    def formatter(self, args):

        """Convert an args tuple or list to C string in specific format
        to data structrue creation functions. User can create a data type
        whose size can be customized, but types of data can only be string.
        """

        fmtstr = ''
        for node in args:
            node = str(node).replace(' ', '')
            if not node:
                node = '0'
            fmtstr += '{0} '.format(node)

        return fmtstr

    def array_stack(self, size, inc, args):

        """Create and initialize a stack implemented by array.

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
        arrstk_str = self.formatter(args)
        print('max size: {0}'.format(size))
        print('increment: {0}'.format(inc))
        print('stack size: {0}'.format(len(arrstk_str.split())))
        _diypy3._array_stack(size, inc, arrstk_str)

    def link_queue(self, args):

        """Create and initialize a linked list queue.

        A value in queue cannot be spaces, and spaces within a string will
        be removed. A good formatted C string can be 'foo bar ', which
        will create a linked list queue with 2 values.
        """

        self.check_args_type(args)
        lnkq_str = self.formatter(args)
        print('nodes: {0}'.format(len(lnkq_str.split())))
        _diypy3._link_queue(lnkq_str)

    def binary_tree(self, flag, args):

        """Create and initialize a binary tree. The values of the binary
        tree should be input in pre-order.

        A node value cannot be spaces, and spaces within a string will
        be removed. A good formatted C string can be 'foo bar ', which
        will create a binary tree with 2 nodes.

        The first flag defines the order of output data, which includes:
            PREORDER -- pre-order
            INORDER -- in-order
            POSTORDER -- post-order
        """

        self.check_args_type(args)
        bt_str = self.formatter(args)
        nodes = len([n for n in bt_str.split() if n != '0'])
        depth = len(bt_str.split('0')[0].split())
        print('nodes: {0}'.format(nodes))
        print('depth: {0}'.format(depth))
        _diypy3._binary_tree(flag, bt_str)
