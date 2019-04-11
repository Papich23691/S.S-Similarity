#include <stdio.h>
#include "py_util.h"
#include "Python.h"

#define PFILE "nlp_util"
#define U_PFILE L"nlp_util"

/**
 * @brief Calling a function from python module. 
 *
 * **Make Sure to add Py_Finalize(); after calling the function and using
 * the return value.**
 * 
 * @return result of function
 */
PyObject *py_function(char * fname,const char * argument) {
  PyObject *pValue = NULL, *pModule = NULL, *pFunc, *pArgs;
  wchar_t *argv[1];
  argv[0] = U_PFILE;
  Py_Initialize();
  /* Changes the current path to source path in order to import python file */
  PySys_SetArgv(1, argv);
  pModule = PyImport_Import(PyUnicode_FromString(PFILE));
  pFunc = PyObject_GetAttrString(pModule, fname);
  Py_DECREF(pModule);
  pArgs = Py_BuildValue("(s)", argument);
  /* Calls for function returns to pValue*/
  pValue = PyObject_CallObject(pFunc, pArgs);
  Py_DECREF(pArgs);
  Py_DECREF(pFunc);
  return pValue;
}