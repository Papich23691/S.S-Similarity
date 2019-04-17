
#include "linear_space_util.h"
#include "nlp.h"
#include "py_util.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  /* Quick Examples */
  Py_Init();
  list<double> v1(4, 5);
  list<double> v2(4, 6);
  printf("%f", dot_product(v1, v2));
  list<list<string>> l = tokenize("My dog has a puppy");
  printf("%f\n", compare("hi", "hello"));
  printf("%f\n", compare("Fuck", "Off"));
  list<list<string>> l1 = tokenize("My pet has a baby");
  list<list<string>> l2 = create_basis(l, l1);
  for (auto i:l2){
    printf("\n{");
    for (auto j:i)
    {
      printf("%s, ",j.c_str());
    }
    printf("}");
  }
  printf("%f\n", compare("shock", "surprise"));
  Py_Finalize();
  return 0;
}