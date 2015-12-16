/**
 *  This module provides homemade data types for Python 3
 *  interpreter, including:
 *      - stack
 *          + array implementation
 *      - queue
 *          + linked list implementation
 *      - matrix
 *          + triplet sparse matrix
 *      - binary tree
 *          + threaded binary tree (TODO)
 *      - graph (TODO)
 *  Status code:
 *       0: -- OK, or true
 *       1: -- Error, or false
 *      -1: -- Infeasible
 *      -2: -- Overflow
 *  Public functions:
 *      split_str(): -- replaces the spaces in the pre-order
 *                      binary tree string with null characters
 *                      and use a pointer array to allocate every
 *                      string.
 */

 #include "Python.h"

#define ARRSTK_MAXSIZE 1000
#define LNKQ_MAXSIZE 1000
#define TRISMX_MAXSIZE 12500
#define BT_MAXSIZE 1023

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
 *      init_queue(): -- create and init a linked list queue
 *      enqueue(): -- enqueue and assign the value to the node
 *      show_queue(): -- print the current status of the queue to stdout
 *      dequeue(): -- dequeue and return the dequeued node value
 *      destroy_queue(): -- destroy this queue
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
        printf("%s, ", Q.front->node_value);
    } while (Q.front != Q.rear);

    printf("\b\b  \n");
}

int
dequeue(LNKQ *Q, char **e)
{
    if (Q->front == Q->rear)
        return 0;

    LNKQNODE *p = Q->front->next;
    *e = p->node_value;
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
 *  Triplet sparse matrix methods:
 *
 */

typedef struct triplet_sparse_matrix_unit {
    int i;  // row
    int j;  // column
    char *unit_value;
} UNIT;

typedef struct triplet_sparse_matrix {
    UNIT data[TRISMX_MAXSIZE + 1];
    int mu, nu, tu; // rows, columns, and non-zeros
} TRISMX;

int
create_sparse_trismx(TRISMX *M, int mu, int nu, int tu)
{
    int k;
    int rec_index = 0;

    M->mu = mu;
    M->nu = nu;
    M->tu = tu;
    for (k = 1; k <= M->tu; k++) {
        sscanf(temp_rec[rec_index], "%d", &(M->data[k].i));
        sscanf(temp_rec[rec_index + 1], "%d", &(M->data[k].j));
        M->data[k].unit_value = temp_rec[rec_index + 2];
        rec_index += 3;
        if (M->data[k].i > mu || M->data[k].j > nu || M->data[k].unit_value == 0)
            return 0;
        if (M->data[k].i <= 0 || M->data[k].j <= 0)
            return 0;
    }

    return 1;
}

int
fast_transpose_trismx(TRISMX *M, TRISMX *N)
{
    int col;
    int t;
    int p, q;
    int *num;
    int *cpot;

    num = (int *)malloc((M->nu + 1) * sizeof(int));
    if (!num)
        return -2;
    cpot = (int *)malloc((M->nu + 1)* sizeof(int));
    if (!cpot)
        return -2;
    N->mu = M->nu;
    N->nu = M->mu;
    N->tu = M->tu;
    if (N->tu) {
        for (col = 1; col <= M->nu; col++)
            num[col] = 0;
        for (t = 1; t <= M->tu; t++)
            num[M->data[t].j]++;
        cpot[1] = 1;
        for (col = 2; col <= M->nu; col++)
            cpot[col] = cpot[col - 1] + num[col - 1];
        for (p = 1; p <= M->tu; p++) {
            col = M->data[p].j;
            q = cpot[col];
            N->data[q].i = M->data[p].j;
            N->data[q].j = M->data[p].i;
            N->data[q].unit_value = M->data[p].unit_value;
            cpot[col]++;
        }
    }

    return 1;
}

void
visualize_trismx(TRISMX *M)
{
    int p;

    for (p = 1; p <= M->tu; p++)
        printf("%d\t%d\t%s\n", M->data[p].i,
                               M->data[p].j,
                               M->data[p].unit_value);
}

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

/**
 *  Graph methods:
 */

static PyObject *
_diypy3__array_stack(PyObject *self, PyObject *args)
{
    int i;
    int rec_size;
    char *stack_str;
    char *str_slice_rec[ARRSTK_MAXSIZE];
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
    printf("array stack initialized\n");
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
    char *str_slice_rec[LNKQ_MAXSIZE];
    char *deq;
    LNKQ Q;

    if (!PyArg_ParseTuple(args, "s", &queue_str))
        return NULL;
    rec_size = split_str(queue_str, str_slice_rec);
    temp_rec = str_slice_rec;
    if (!init_queue(&Q))
        return NULL;
    printf("linked list queue initialized\n");
    printf("\n");
    for (i = 0; i < rec_size; i++) {
        printf("enqueue: %s\n", temp_rec[i]);
        enqueue(&Q, temp_rec[i]);
    }
    while (Q.front != Q.rear) {
        printf("\nstatus: ");
        show_queue(Q);
        dequeue(&Q, &deq);
        printf("dequeue: %s\n", deq);
    }
    printf("\nwarning: empty queue\n");

    Py_RETURN_NONE;
}

static PyObject *
_diypy3__triplet_sparse_matrix(PyObject *self, PyObject *args)
{
    int mu;
    int nu;
    int tu;
    char *trismx_str;
    char *str_slice_rec[TRISMX_MAXSIZE];
    TRISMX M;
    TRISMX N;

    if (!PyArg_ParseTuple(args, "iiis", &mu,
                                        &nu,
                                        &tu,
                                        &trismx_str))
        return NULL;
    split_str(trismx_str, str_slice_rec);
    temp_rec = str_slice_rec;
    create_sparse_trismx(&M, mu, nu, tu);
    printf("triplet sparse matrix initialized\n");
    visualize_trismx(&M);
    printf("fast transpose this matrix:\n");
    fast_transpose_trismx(&M, &N);
    visualize_trismx(&N);

    Py_RETURN_NONE;
}

static PyObject *
_diypy3__binary_tree(PyObject *self, PyObject *args)
{
    int order;
    char *bt_str;
    char *str_slice_rec[BT_MAXSIZE];
    BTNODE *T;

    if (!PyArg_ParseTuple(args, "is", &order, &bt_str))
        return NULL;
    split_str(bt_str, str_slice_rec);
    temp_rec = str_slice_rec;
    pre_order_create(&T);
    printf("binary tree initialized\n");
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
    {"_triplet_sparse_matrix", (PyCFunction)_diypy3__triplet_sparse_matrix, METH_VARARGS,
     "create and initialize a triplet matrix and test tranposing method"},
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
