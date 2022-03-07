// helloWrapper.c
#include <Python.h>
#include "aes.h"

//extern int add(int, int);
//extern void out(const char*, const char*);

/*
extern void AES128_ECB_encrypt(uint8_t* input, const uint8_t* key, uint8_t *output);
extern void AES128_ECB_decrypt(uint8_t* input, const uint8_t* key, uint8_t *output);
extern static void BlockCopy(uint8_t* output, uint8_t* input);
extern static void KeyExpansion(void);
extern static void Cipher(void);
extern static void AddRoundKey(uint8_t round);
extern static void SubBytes(void);
extern static void ShiftRows(void);
extern static void MixColumns(void);
*/

//definition of add method
/*
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
*/
static PyObject* AES128_2Rin(PyObject* self, PyObject* args)
{
    int n = 0;
    PyObject* c_list;

    // decide type (list)
    if (!PyArg_ParseTuple(args, "O", &c_list)){
        return NULL;
    }

    // Check list
    if PyList_Check(c_list){
        // get length of the list
        n = PyList_Size(c_list);
    }else{
        return NULL;
    }

    return PyLong_FromLong(n);
}


//pythonから呼ぶためのmethod table 定義
static PyMethodDef hellomethods[] = {
    //{"add", hello_add, METH_VARARGS},
    //{"out", hello_out, METH_VARARGS | METH_KEYWORDS},
    {"AES", AES128_2Rin, METH_VARARGS},
    {NULL},
};

// hello module definition struct
//module 定義
static struct PyModuleDef hello = {
    PyModuleDef_HEAD_INIT,
    "hello", //module name
    "Python3 C API Module(Sample 1)",
    -1,
    hellomethods //method table
};

//module creator
// 関数名は PyInit_{name}
// {name}は PyModuleDef で宣言したmodule name
PyMODINIT_FUNC PyInit_hello(void)
{
    return PyModule_Create(&hello);
}



// https://cpp-learning.com/python_c_api_step2/

// C function "get list and Multiply 2 and item of list"
static PyObject* c_multiply_list(PyObject* c_list, int n)
{
    long a;
    PyObject* result_list, *item;

    // make python list	(length n)
    result_list = PyList_New(n);

    for (int i = 0; i < n; i++){
        item = PyList_GetItem(c_list, i);
        a = PyLong_AsLong(item);    // PyObject -> long
        a = 2 * a;
        item = Py_BuildValue("l", a);  // long -> PyObject
        PyList_SET_ITEM(result_list, i, item);
        Py_DECREF(item);
    }

    Py_DECREF(c_list);

    return result_list;
}

// C function "get list and return list"
static PyObject* py_list(PyObject* self, PyObject* args)
{
    int n;
    PyObject* c_list;

    // decide type (list)
    if (!PyArg_ParseTuple(args, "O", &c_list)){
        return NULL;
    }

    // Check list
    if PyList_Check(c_list){
        // get length of the list
        n = PyList_Size(c_list);
    }else{
        return NULL;
    }

    return c_multiply_list(c_list, n);
}