#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""\
This script creates a triplet sparse matrix
"""

import diypy3

d = diypy3.Diypy3()
d.triplet_sparse_matrix((1, 1, 'hello'),
                        (2, 1, 'how'),
                        (1, 2, 'are'),
                        (2, 2, 'you'))
