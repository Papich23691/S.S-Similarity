#include "nlp.h"
#include "Python.h"
#include "py_util.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

/**
 * @brief Using python spacy to create tokens list into c++
 *
 * @return list<list<string>> List of tokens
 */
list<list<string> > tokenize(string sentence) {
  list<list<string> > tokens;
  PyObject *pValue, *item = NULL;
  int i, j, len = 0, len1 = 0;
  pValue = py_function("tokenize", sentence.c_str());
  /* Translates python tokens list to c++ list */
  if (pValue != NULL) {
    len = PyList_GET_SIZE(pValue);
    for (i = 0; i < len; i++) {
      list<string> token;
      len1 = PyList_GET_SIZE(PyList_GetItem(pValue, i));
      for (j = 0; j < len1; j++) {
        /* Python 3 api uses only unicode type strings */
        item = PyList_GetItem(PyList_GetItem(pValue,i), j);
        item = PyUnicode_AsEncodedString(item,"UTF-8","strict");
        token.push_back(PyBytes_AS_STRING(item));
      }
      tokens.push_back(token);
    }
    if (item) Py_DECREF(item);
    Py_DECREF(pValue);
  }
  Py_Finalize();
  return tokens;
}
