DIYPy3
======

> **D**ata-structure **I**nterface **Y**ourself using **Py**thon 3.

This is a C extension module for Python 3 which provides homemade and
basic data types for your Python 3 interpreter. In the module there
are Python 3 functions for formatting input data, transfering to C
program and visualizing output data, and C functions for creating data
types, traversal and manipulating exceptions, etc.

**Attention**, this project is experimental and inspired by my current
professional course *Data Structure*. Just treat this as my learning
notes.

Requirements
------------

- `Python 3.4.x` or higher versions
- `Graphviz (DOT)` for visualizing *graphs*

Installation
------------

Clone and setup!

```bash
git clone git@github.com:anqurvanillapy/diypy3.git
cd diypy3
python3 setup.py install
```

Examples
--------

```python
import diypy3

d = diypy3.Diypy3()

# create a stack with array implementation and pop it,
# 100 for stack max size and 10 for stack pushing increment if oversized
d.array_stack(100, 10, [1, 2, 3, 4, 5])

# create a binary tree and traverse in pre-order
d.binary_tree(d.PREORDER, [1, 2, 3, 0, 0, 4, 0, 0, 0])

# and then see what will happen!
```

License
-------

CC0 1.0
