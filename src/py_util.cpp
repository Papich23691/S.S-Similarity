#include "py_util.h"
#include "Python.h"
#include <string>
#include <stdio.h>
#define PFILE "nlp_util"
#define U_PFILE L"nlp_util"

static const std::string compare_function_name = "compare";
static const std::string tokenize_function_name = "tokenize";

/**
 * Initializing python with specific file
 * **(Avoid using multiple times)**
 */
void NLPPyUtils::py_init() 
{
  wchar_t *argv[1];
  argv[0] = U_PFILE;
  Py_Initialize();
  PySys_SetArgv(1, argv);
}

NLPPyUtils::NLPPyUtils() : _py_module(nullptr), _py_compare(nullptr)
{
  py_init();
  _py_module = PyImport_Import(PyUnicode_FromString(PFILE));
  if (!_py_module) 
  {
    PyErr_Print();
    exit(1);
  }

  _py_compare = PyObject_GetAttrString(_py_module, compare_function_name.c_str()); 
  if (!_py_compare) 
  {
    PyErr_Print();
    clear_resources();
    exit(1);
  }

  _py_tokenize = PyObject_GetAttrString(_py_module, tokenize_function_name.c_str()); 
  if (!_py_tokenize) 
  {
    PyErr_Print();
    clear_resources();
    exit(1);
  }
}

void NLPPyUtils::clear_resources()
{
  XDECREF_RESOURCE(_py_module);
  XDECREF_RESOURCE(_py_tokenize);
  XDECREF_RESOURCE(_py_compare);
}

PyObject* NLPPyUtils::py_compare(const char* first_word, const char* second_word)
{
  PyObject *pValue = nullptr;
  PyObject *pArgs = nullptr;

  pArgs = Py_BuildValue("(ss)", first_word, second_word); 
  pValue = PyObject_CallObject(_py_compare, pArgs);
  Py_XDECREF(pArgs);
  if (!pValue) 
  {
    PyErr_Print();
    exit(1);
  }

  return pValue;
}

PyObject* NLPPyUtils::py_tokenize(const char* sentence)
{
  PyObject *pValue = nullptr;
  PyObject *pArgs = nullptr;

  pArgs = Py_BuildValue("(s)", sentence); 
  pValue = PyObject_CallObject(_py_tokenize, pArgs);
  Py_XDECREF(pArgs);
  if (!pValue) 
  {
    PyErr_Print();
    exit(1);
  }

  return pValue; 
}

NLPPyUtils::~NLPPyUtils()
{
  clear_resources();
  Py_Finalize();
}

std::shared_ptr<NLPPyUtils> NLPPyUtils::get_py_util()
{
  if (nullptr == _py_util)
  {
    NLPPyUtils* raw_singelton_ptr = new NLPPyUtils();
    _py_util = std::shared_ptr<NLPPyUtils>(raw_singelton_ptr);
  }

  return _py_util;
}