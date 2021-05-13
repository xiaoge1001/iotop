#include <sys/syscall.h>
#include <Python.h>

#if PY_MAJOR_VERSION < 2 || (PY_MAJOR_VERSION == 2 && PY_MINOR_VERSION <= 3)
#define NO_METHODS NoMethods
static PyMethodDef NoMethods[] = {
    {NULL, NULL, 0, NULL}
};
#else
#define NO_METHODS NULL
#endif

#if PY_MAJOR_VERSION >= 3
PyDoc_STRVAR(doc, "SYS_ioprio_get and SYS_ioprio_set for syscalls");
static struct PyModuleDef mod = {
    PyModuleDef_HEAD_INIT,
    "_ioprio",
    doc,
    -1,
    NO_METHODS,
    NULL,
    NULL,
    NULL,
    NULL
};

#define INIT_FUNC PyInit__ioprio
#define INIT_MOD  PyModule_Create(&mod)
#define INIT_ERR  NULL
#define INIT_RET  return m
#else
#define INIT_FUNC init_ioprio
#define INIT_MOD  Py_InitModule("_ioprio", NO_METHODS)
#define INIT_ERR
#define INIT_RET
#endif  // PY_MAJOR_VERSION >= 3

PyMODINIT_FUNC INIT_FUNC(void)
{
    PyObject *m = INIT_MOD;

    if (m == NULL) {
        return INIT_ERR;
    }

#ifdef SYS_ioprio_get
    PyModule_AddIntConstant(m, "SYS_ioprio_get", SYS_ioprio_get);
#endif

#ifdef SYS_ioprio_set
    PyModule_AddIntConstant(m, "SYS_ioprio_set", SYS_ioprio_set);
#endif

    INIT_RET;
}
