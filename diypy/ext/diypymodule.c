/**
 *  This module provides homemade data types for Python 3
 *  interpreter, including:
 *      - binary tree
 *          + Threaded binary tree
 */

 #include "Python.h"

/**
 *  Binary tree methods
 *      split_str(): -- replaces the spaces in the pre-order
 *                      binary tree string with null characters
 *                      and use a pointer array to allocate every
 *                      string.
 *      pre_order_create(): -- creates a binary tree by pre-order
 *                             recursion
 *
 */

typedef struct binary_tree_node {
    char *node_value;
    struct binary_tree_node *left_child;
    struct binary_tree_node *right_child;
} BTNODE, *BT;
char **temp_rec;
int indent = 0;

void
split_str(char *str, char **rec)
{
    char *ptr = str;
    int i = 0;

    while (*ptr != '\0') {
        rec[i] = ptr;
        while (*ptr != ' ')
            ptr++;
        *ptr = '\0';
        ptr++;
        i++;
    }
}

void
pre_order_create(BT *T)
{
    if (strcmp(*temp_rec, "0") == 0) {
        *T = NULL;
        temp_rec++;
    } else {
        *T = (BT)malloc(sizeof(BTNODE));
        (*T)->node_value = *temp_rec;
        temp_rec++;
        pre_order_create(&(*T)->left_child);
        pre_order_create(&(*T)->right_child);
    }
}

void
pre_order_traverse(BT T)
{
    if (T == NULL) {
        return;
    } else {
        int i;
        for (i = 0; i < indent; i++)
            putchar(' ');
        printf("+ %s\n", T->node_value);
        indent += 4;
        pre_order_traverse(T->left_child);
        pre_order_traverse(T->right_child);
        indent -= 4;
    }
} // -- end: binary tree

static PyObject *
_diypy__binary_tree(PyObject *self, PyObject *args)
{
    int order;
    char *bt_str;
    char *str_slice_rec[1023];
    BT T;

    if (!PyArg_ParseTuple(args, "is", &order, &bt_str))
        return NULL;
    split_str(bt_str, str_slice_rec);
    temp_rec = str_slice_rec;
    pre_order_create(&T);
    switch (order) {
        case 0:
            pre_order_traverse(T);
            indent = 0;
            break;
        default:
            PyErr_SetString(PyExc_ValueError,
                            "Unrecognised flag given");
            return NULL;
    }

    Py_RETURN_NONE;
}

PyDoc_STRVAR(_diypy_doc,
    "Data-structure Interface Yourself using Python 3");

static PyMethodDef _diypy_methods[] = {
    {"_binary_tree", (PyCFunction)_diypy__binary_tree, METH_VARARGS,
     "create and initialize a binary tree"},
    {NULL, NULL, 0, NULL} /* Sentinel value represents the end
                             of the method */
};

static struct PyModuleDef _diypymodule = {
    PyModuleDef_HEAD_INIT,
    "_diypy",    /* module name */
    _diypy_doc,  /* module documentation */
    -1,         /* -1 means this module keeps state in global
                   variables. */
    _diypy_methods
};

PyMODINIT_FUNC
PyInit__diypy(void)
{
    return PyModule_Create(&_diypymodule);
}
