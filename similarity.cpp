#include <iostream>
#include <string>
#include <list>
#include <Python/Python.h>
#include "similarity.h"

static const char *PFILE = "POS";
static const char *PFUNCTION = "tokenize";

using namespace std;

/**
 * @brief Using python nltk to create tokens list into c++
 * 
 * @return list<list<string>> List of tokens
 */
list<list<string>> tokenize(string sentence)
{
    list<list<string>> tokens;
    PyObject *pModule, *pFunc, *pName, *pArgs, *pValue, *seq, *seq1, *item;
    int i, j, len, len1;
    Py_Initialize();
    /* Changes the current path to source path in order to import python file */
    PyObject *sysPath = PySys_GetObject((char *)"path");
    PyObject *curDir = PyString_FromString(".");
    PyList_Append(sysPath, curDir);
    Py_DECREF(curDir);

    pName = PyString_FromString(PFILE);
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    pFunc = PyObject_GetAttrString(pModule, PFUNCTION);
    Py_DECREF(pModule);
    pArgs = Py_BuildValue("(s)", sentence.c_str());
    /* Calls for tokenize function returns to pValue*/
    pValue = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);

    /* Translates python tokens list to c++ list */
    if (pValue != NULL)
    {
        seq = PySequence_Fast(pValue, "expected list");
        len = PySequence_Size(pValue);
        for (i = 0; i < len; i++)
        {
            list<string> token;
            seq1 = PySequence_Fast(PySequence_Fast_GET_ITEM(seq, i), "expected list");
            len1 = PySequence_Size(PySequence_Fast_GET_ITEM(seq, i));
            for (j = 0; j < len1; j++)
            {
                item = PySequence_Fast_GET_ITEM(seq1, j);
                token.push_back(PyString_AsString(item));
            }
            tokens.push_back(token);
        }
        Py_DECREF(seq);
        Py_DECREF(seq1);
        Py_DECREF(pValue);
    }
    Py_Finalize();
    return tokens;
}
