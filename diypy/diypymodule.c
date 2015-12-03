#include <Python.h>

PyDoc_STRVAR(diypy_doc,
    "Data-structure Interface Yourself using Python");

static PyObject *
diypy_bintree(PyObject *self, PyObject *args)
{
    const char *greetings;

    if (!PyArg_ParseTuple(args, "s", &greetings))
        return NULL;
    if (strlen(greetings) == 0) {
        PyErr_SetString(PyExc_ValueError, "Cannot input an empty char");
        return NULL;
    }
    printf("Hello, %s!\n", greetings);
    
    Py_RETURN_NONE;
}

static PyMethodDef diypy_methods[] = {
    {"bintree", (PyCFunction)diypy_bintree, METH_VARARGS,
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
    diypy_methods
};

PyMODINIT_FUNC
PyInit_diypy(void)
{
    return PyModule_Create(&diypymodule);
}