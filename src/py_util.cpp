#include "py_util.h"
#include "Python.h"
#include <stdio.h>
#define PFILE "nlp_util"
#define U_PFILE L"nlp_util"

static PyObject *tagger = nullptr;
static PyObject *sim = nullptr;

/**
 * Initializing python with specific file
 * **(Avoid using multiple times)**
 */
void PyUtils::py_init() 
{
  wchar_t *argv[1];
  argv[0] = U_PFILE;
  Py_Initialize();
  PySys_SetArgv(1, argv);
}

PyUtils::PyUtils()
{
  py_init();
  _py_module = PyImport_Import(PyUnicode_FromString(PFILE));

  if (!_py_module) 
  {
    PyErr_Print();
    exit(1);
  }
}

/**
 * *Calling a function from python module*
 * **(In order to avoid segmentation fault make sure to use
 * `Py_Init();` once at the start of the program
 * and ending the program with `Py_Finalize();`)**
 */
PyObject* PyUtils::nlp_py_function(char *fname, const char *argument, const char *argument2,
                      int argc) {
  PyObject *pValue = nullptr;
  PyObject *pFunc = nullptr;
  PyObject *pArgs = nullptr;

  if (!sim || !tagger)
  {
    pFunc = PyObject_GetAttrString(_py_module, fname);
    if (!pFunc) 
    {
      PyErr_Print();
      exit(1);
    }

    if (!strcmp(fname,"compare"))
    {
		  sim = pFunc;
    }
    else
    {
      tagger = pFunc;     
    }
  }
  
  if (1 == argc)
  {
    pArgs = Py_BuildValue("(s)", argument);
  }
  else if (2 == argc)
  {
    pArgs = Py_BuildValue("(ss)", argument, argument2);
  }

  pFunc = (!strcmp(fname,"compare")) ? sim : tagger;
  
  /* Calls for function returns to pValue*/
  pValue = PyObject_CallObject(pFunc, pArgs);
  if (!pValue) 
  {
    PyErr_Print();
    exit(1);
  }
  Py_XDECREF(pArgs);

  return pValue;
}

PyUtils::~PyUtils()
{
  Py_XDECREF(_py_module);
  Py_Finalize();
}

std::shared_ptr<PyUtils> PyUtils::get_py_util()
{
  if (nullptr == _py_util)
  {
    PyUtils* raw_singelton_ptr = new PyUtils();
    _py_util = std::shared_ptr<PyUtils>(raw_singelton_ptr);
  }

  return _py_util;
}