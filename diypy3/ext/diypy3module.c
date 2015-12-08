/**
 *  This module provides homemade data types for Python 3
 *  interpreter, including:
 *      - stack
 *          + array implementation
 *      - binary tree
 *          + threaded binary tree
 *      - graph
 *  Public functions:
 *      split_str(): -- replaces the spaces in the pre-order
 *                      binary tree string with null characters
 *                      and use a pointer array to allocate every
 *                      string.
 */

 #include "Python.h"

char **temp_rec;

int
split_str(char *str, char **rec)
{
    char *ptr = str;
    int i = 0;
    int count = 0;

    while (*ptr != '\0') {
        rec[i] = ptr;
        while (*ptr != ' ') {
            ptr++;
        }
        *ptr = '\0';
        ptr++;
        i++;
        count++;
    }

    return count;
}

/**
 *  Array stack methods:
 *      init_stack(): -- initialize an array stack with max size and increment
 *                       size.
 *      push(): -- push values from the string array into the stack.
 *      show(): -- print the current status of the stack on the stdout.
 *      get_top(): -- return the top value of the stack to a variable.
 *      pop(): -- return the top value of the stack to a variable and
 *                then pop it out of the stack.
 */

typedef struct array_stack {
    char **base;
    char **top;
    int stacksize;
} ARRSTK;
int stack_init_size;
int stack_increment;

int
init_stack(ARRSTK *S)
{
    S->base = (char **)malloc(stack_init_size * sizeof(ARRSTK));
    if (!S->base)
        return -1;
    S->top = S->base;
    S->stacksize = stack_init_size;
    
    return 1;
}

int
push(ARRSTK *S, char *e)
{
    char **t;

    if (S->top - S->base >= S->stacksize) {
        t = (char **)realloc(S->base, (stack_increment + S->stacksize) * sizeof(char));
        if (!t)
            return -1;
        S->base = t;
        S->top = S->base + S->stacksize;
        S->stacksize += stack_increment;
    }
    *S->top++ = e;

    return 1;
}

void
show(ARRSTK S)
{
    do {
        S.top--;
        printf("%s, ", *S.top);
    } while (S.top != S.base);
    printf("\b\b  \n");
}

int
get_top(ARRSTK S, char **e)
{
    if (S.top == S.base)
        return 0;
    *e = *(S.top - 1);

    return 1;
}

int
pop(ARRSTK *S, char **e)
{
    if (S->top == S->base)
        return 0;
    *e = *--S->top;

    return 1;    
} // -- end: array stack

/**
 *  Binary tree methods:
 *      pre_order_create(): -- creates a binary tree by pre-order
 *                             recursion.
 *      pre_order_visualize(): -- visualize the initialized binary
 *                                tree like book content.
 */

typedef struct binary_tree_node {
    char *node_value;
    struct binary_tree_node *left_child;
    struct binary_tree_node *right_child;
} BTNODE;
int indent = 0;

int
pre_order_create(BTNODE **T)
{
    if (strcmp(*temp_rec, "0") == 0) {
        *T = NULL;
        temp_rec++;
    } else {
        *T = (BTNODE *)malloc(sizeof(BTNODE));
        (*T)->node_value = *temp_rec;
        temp_rec++;
        pre_order_create(&(*T)->left_child);
        pre_order_create(&(*T)->right_child);
    }

    return 1;
}

void
pre_order_visualize(BTNODE *T)
{
    if (T == NULL) {
        return;
    } else {
        int i;
        for (i = 0; i < indent; i++)
            putchar(' ');
        printf("+ %s\n", T->node_value);
        indent += 4;
        pre_order_visualize(T->left_child);
        pre_order_visualize(T->right_child);
        indent -= 4;
    }
} // -- end: binary tree

static PyObject *
_diypy3__array_stack(PyObject *self, PyObject *args)
{
    int i;
    int rec_size;
    char *stack_str;
    char *str_slice_rec[1000];
    char *topelem, *popelem;
    ARRSTK S;

    if (!PyArg_ParseTuple(args, "iis",
                          &stack_init_size,
                          &stack_increment,
                          &stack_str))
        return NULL;
    rec_size = split_str(stack_str, str_slice_rec);
    temp_rec = str_slice_rec;
    if (!init_stack(&S))
        return NULL;
    printf("\n");
    for (i = 0; i < rec_size; i++) {
        printf("push: %s\n", temp_rec[i]);
        push(&S, temp_rec[i]);
    }
    while (S.top != S.base) {
        printf("\nstatus: ");
        show(S);
        get_top(S, &topelem);
        printf("get top: %s\n", topelem);
        pop(&S, &popelem);
        printf("pop: %s\n", popelem);
    }
    printf("\nwarning: empty stack\n");

    Py_RETURN_NONE;
}

static PyObject *
_diypy3__binary_tree(PyObject *self, PyObject *args)
{
    int order;
    char *bt_str;
    char *str_slice_rec[1023];
    BTNODE *T;

    if (!PyArg_ParseTuple(args, "is", &order, &bt_str))
        return NULL;
    split_str(bt_str, str_slice_rec);
    temp_rec = str_slice_rec;
    pre_order_create(&T);
    switch (order) {
        case 0:
            pre_order_visualize(T);
            indent = 0;
            break;
        default:
            PyErr_SetString(PyExc_ValueError,
                            "Unrecognised flag given");
            return NULL;
    }

    Py_RETURN_NONE;
}

PyDoc_STRVAR(_diypy3_doc,
    "Data-structure Interface Yourself using Python 3");

static PyMethodDef _diypy3_methods[] = {
    {"_array_stack", (PyCFunction)_diypy3__array_stack, METH_VARARGS,
     "create and initialize an array-implemented stack and make some actions"},
    {"_binary_tree", (PyCFunction)_diypy3__binary_tree, METH_VARARGS,
     "create and initialize a binary tree"},
    {NULL, NULL, 0, NULL} /* Sentinel value represents the end
                             of the method */
};

static struct PyModuleDef _diypy3module = {
    PyModuleDef_HEAD_INIT,
    "_diypy3",    /* module name */
    _diypy3_doc,  /* module documentation */
    -1,         /* -1 means this module keeps state in global
                   variables. */
    _diypy3_methods
};

PyMODINIT_FUNC
PyInit__diypy3(void)
{
    return PyModule_Create(&_diypy3module);
}
