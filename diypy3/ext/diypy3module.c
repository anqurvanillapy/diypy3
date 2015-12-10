/**
 *  This module provides homemade data types for Python 3
 *  interpreter, including:
 *      - stack
 *          + array implementation
 *          + linked list implementation (TODO)
 *      - queue
 *          + linked list implementation
 *      - binary tree
 *          + threaded binary tree (TODO)
 *      - graph (TODO)
 *  Status code:
 *      0: -- OK, or true
 *      1: -- Error, or false
 *      -1: -- Infeasible
 *      -2: -- Overflow
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
 *      show_stack(): -- print the current status of the stack on the stdout.
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
        return -2;
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
            return -2;
        S->base = t;
        S->top = S->base + S->stacksize;
        S->stacksize += stack_increment;
    }
    *S->top++ = e;

    return 1;
}

void
show_stack(ARRSTK S)
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
 *  Link queue methods:
 *      init_queue(): -- 
 *      enqueue(): -- 
 *      show_queue(): --
 *      dequeue(): --
 *      destroy_queue(): --
 */

typedef struct link_queue_node {
    char *node_value;
    struct link_queue_node *next;
} LNKQNODE;
typedef struct link_queue {
    LNKQNODE *front;
    LNKQNODE *rear;
} LNKQ;

int
init_queue(LNKQ *Q)
{
    Q->front = Q->rear = (LNKQNODE *)malloc(sizeof(LNKQNODE));
    if (!Q->front)
        return -2;
    (Q->front)->next = NULL;

    return 1;
}

int
enqueue(LNKQ *Q, char *e)
{
    LNKQNODE *n = (LNKQNODE *)malloc(sizeof(LNKQNODE));
    if (!n)
        return -2;
    n->node_value = e;
    n->next = NULL;
    (Q->rear)->next = n;
    Q->rear = n;

    return 1;
}

void
show_queue(LNKQ Q)
{
    do {
        Q.front = Q.front->next;
        printf("%s\n", Q.front->node_value);
    } while (Q.front != Q.rear);
}

int
dequeue(LNKQ *Q, char **e)
{
    if (Q->front == Q->rear)
        return 0;

    LNKQNODE *p = Q->front->next;
    e = &(p->node_value);
    (Q->front)->next = p->next;
    if (Q->rear == p)
        Q->rear = Q->front;
    free(p);

    return 1;
}

int
destroy_queue(LNKQ *Q)
{
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }

    return 1;
} // -- end: link queue

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
        show_stack(S);
        get_top(S, &topelem);
        printf("get top: %s\n", topelem);
        pop(&S, &popelem);
        printf("pop: %s\n", popelem);
    }
    printf("\nwarning: empty stack\n");

    Py_RETURN_NONE;
}

static PyObject *
_diypy3__link_queue(PyObject *self, PyObject *args)
{
    int i;
    int rec_size;
    char *queue_str;
    char *str_slice_rec[1000];
    LNKQ Q;

    if (!PyArg_ParseTuple(args, "s", &queue_str))
        return NULL;
    rec_size = split_str(queue_str, str_slice_rec);
    temp_rec = str_slice_rec;
    if (!init_queue(&Q))
        return NULL;
    for (i = 0; i < rec_size; i++)
        enqueue(&Q, temp_rec[i]);
    show_queue(Q);

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

static PyMethodDef _diypy3_methods[] = {
    {"_array_stack", (PyCFunction)_diypy3__array_stack, METH_VARARGS,
     "create and initialize an array-implemented stack and make some actions"},
    {"_link_queue", (PyCFunction)_diypy3__link_queue, METH_VARARGS,
     "create and initialize a queue implemented by a linked list and test some methods"},
    {"_binary_tree", (PyCFunction)_diypy3__binary_tree, METH_VARARGS,
     "create and initialize a binary tree"},
    {NULL, NULL, 0, NULL} /* Sentinel value represents the end
                             of the method */
};

PyDoc_STRVAR(_diypy3_doc,
    "Data-structure Interface Yourself using Python 3");

static struct PyModuleDef _diypy3module = {
    PyModuleDef_HEAD_INIT,
    "_diypy3",      /* module name */
    _diypy3_doc,    /* module documentation */
    -1,             /* -1 means this module keeps state in global
                       variables. */
    _diypy3_methods
};

PyMODINIT_FUNC
PyInit__diypy3(void)
{
    return PyModule_Create(&_diypy3module);
}
