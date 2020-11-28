#include "nlp.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

/**
 * Using python spaCy to create tokens list into c++ list
 * Returning list<list<string>> List of tokens
 */
list<list<string> > NLPUtils::tokenize(string sentence) {
  list<list<string> > tokens;
  PyObject *pValue = nullptr;
  PyObject *item = nullptr;
  int i = 0;
  int j = 0;
  int len = 0;
  int len1 = 0;
  std::shared_ptr<PyUtils> py_util = PyUtils::get_py_util();
  
  pValue = py_util->nlp_py_function("tokenize", sentence.c_str(), "", 1);
  /* Translates python tokens list to c++ list */
  if (pValue != nullptr) {
    len = PyList_GET_SIZE(pValue);
    for (i = 0; i < len; i++) {
      list<string> token;
      len1 = PyList_GET_SIZE(PyList_GetItem(pValue, i));
      for (j = 0; j < len1; j++) {
        /* Python 3 api uses only unicode type strings */
        item = PyList_GetItem(PyList_GetItem(pValue, i), j);
        item = PyUnicode_AsEncodedString(item, "UTF-8", "strict");
        token.push_back(PyBytes_AS_STRING(item));
      }
      tokens.push_back(token);
    }
    if (item)
      Py_XDECREF(item);
    Py_XDECREF(pValue);
  }
  return tokens;
}

/**
 * Using python spaCy to compare 2 words.
 * Returning similarity between words
 */
double NLPUtils::compare(string word1, string word2) {
  PyObject *pValue = nullptr;
  double score = 0;
  std::shared_ptr<PyUtils> py_util = PyUtils::get_py_util();

  pValue = py_util->nlp_py_function("compare", word1.c_str(), word2.c_str(), 2);
  score = PyFloat_AsDouble(pValue);
  Py_XDECREF(pValue);
  return score;
}

 double NLPUtils::semantic_similarity(string sentence1,string sentence2)
 {
   list<list<string>> t1 = tokenize(sentence1);
   list<list<string>> t2 = tokenize(sentence2);
   list<list<string>> B = LSUtils::create_basis(t1, t2);
   list<double> v1 = LSUtils::create_vector(t1,B);
   list<double> v2= LSUtils::create_vector(t2,B);
   return LSUtils::dot_product(v1,v2)/ LSUtils::dot_product(v1,v1);
 }
