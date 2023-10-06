#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include "hash.h"

static PyObject *burgerhash(PyObject *self, PyObject *args) {
    char *plaintext;
    Py_ssize_t length;

    if (!PyArg_ParseTuple(args, "s#", &plaintext, &length)) return NULL;

    hash(plaintext, length);

    PyObject *result_obj =
        PyByteArray_FromStringAndSize(ciphertext_buffer, MESSAGE_DIGEST_SIZE);

    return result_obj;
}

static PyObject *version(PyObject *self) { return Py_BuildValue("s", "BETA"); }

static PyMethodDef Methods[] = {
    {"hash", burgerhash, METH_VARARGS, "str function"},
    {"version", (PyCFunction)version, METH_NOARGS, "Returns the version."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef burgerhash_module = {
    PyModuleDef_HEAD_INIT, "_burgerhash", "burgerhash module", -1, Methods};

PyMODINIT_FUNC PyInit__burgerhash(void) {
    return PyModule_Create(&burgerhash_module);
}