
#include "nlp.h"
#include "py_util.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  /* Quick Examples */
  Py_Init();
  list<list<string>> l = tokenize("hi there");
  printf("%f\n", compare("hi", "hello"));
  printf("%f\n", compare("Fuck", "Off"));
  list<list<string>> l1 = tokenize("I want to rape a gay bird with used condoms");
  printf("%f\n", compare("shock", "surprise"));
  Py_Finalize();
  return 0;
}