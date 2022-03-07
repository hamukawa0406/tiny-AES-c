// helloWrapper.c
#include "Python.h"

extern int add(int, int);
extern void out(const char*, const char*);

extern void AES128_ECB_encrypt(uint8_t* input, const uint8_t* key, uint8_t *output);
extern void AES128_ECB_decrypt(uint8_t* input, const uint8_t* key, uint8_t *output);
extern static void BlockCopy(uint8_t* output, uint8_t* input);
extern static void KeyExpansion(void);
extern static void Cipher(void);
extern static void AddRoundKey(uint8_t round);
extern static void SubBytes(void);
extern static void ShiftRows(void);
extern static void MixColumns(void);

//definition of add method
static PyObject* hello_add(PyObject* self, PyObject* args)
{
    int x, y, g;

    if (!PyArg_ParseTuple(args, "ii", &x, &y))
        return NULL;
    g = add(x, y);
    return Py_BuildValue("i", g);
}

//definition of out method
static PyObject* hello_out(PyObject* self, PyObject* args, PyObject* kw)
{
    const char* adrs = NULL;
    const char* name = NULL;
    static char* argnames[] = {"adrs", "name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kw, "|ss",
            argnames, &adrs, &name))
        return NULL;
    out(adrs, name);
    return Py_BuildValue("");
}
static PyObject* hello_AES128_2Rin(PyObject* self, PyObject* args, PyObject* kw)
{
    const char* adrs = NULL;
    const char* name = NULL;
    uint8_t* intput = NULL;
    uint8_t* key = NULL;
    uint8_t* output = NULL;
    static char* argnames[] = {"adrs", "name", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kw, "|ss",
            argnames, &adrs, &name))
        return NULL;
    out(adrs, name);
    return Py_BuildValue("");
}


//definition of all methods of my module
static PyMethodDef hellomethods[] = {
    {"add", hello_add, METH_VARARGS},
    {"out", hello_out, METH_VARARGS | METH_KEYWORDS},
    {NULL},
};

// hello module definition struct
static struct PyModuleDef hello = {
    PyModuleDef_HEAD_INIT,
    "hello",
    "Python3 C API Module(Sample 1)",
    -1,
    hellomethods
};

//module creator
PyMODINIT_FUNC PyInit_hello(void)
{
    return PyModule_Create(&hello);
}
