#include <Python.h>

static PyObject *DiypyInitError;

PyDoc_STRVAR(diypy_doc,
    "Data-structure Interface Yourself using Python");

static PyObject *
diypy_bintree(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    if (sts < 0) {
        PyErr_SetString(DiypyInitError, "binary tree initialization failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}

static PyMethodDef DiypyMethods[] = {
    {"bintree", diypy_bintree, METH_VARARGS,
     "create and initialize a binary tree"},
    {NULL, NULL, 0, NULL} /* Sentinel value represents the end
                             of the method */
};

static struct PyModuleDef diypymodule = {
    PyModuleDef_HEAD_INIT,
    "diypy",    /* module name */
    diypy_doc,  /* module documentation */
    -1,         /* -1 means this module keeps state in global
                   variables. */
    DiypyMethods
};

PyMODINIT_FUNC
PyInit_diypy(void)
{
    PyObject *m;

    m = PyModule_Create(&diypymodule);
    if (m == NULL)
        return NULL;

    DiypyInitError = PyErr_NewException("diypy.InitError", NULL, NULL);
    Py_INCREF(DiypyInitError);
    PyModule_AddObject(m, "InitError", DiypyInitError);
    return m;
}