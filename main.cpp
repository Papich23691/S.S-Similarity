
#include "linear_space_util.h"
#include "nlp.h"
#include "py_util.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char ** argv) {
  /* Quick Examples */
  Py_Init();
  list<double> v1(4, 5);
  list<double> v2(4, 6);
  printf("%f", dot_product(v1, v2));
  list<list<string>> l = tokenize("Hello there mother long time no see");
  printf("%f\n", compare("hi", "hello"));
  printf("%f\n", compare("Fuck", "Off"));
  list<list<string>> l1 = tokenize("Mom hi it has been long time since we met");
  list<list<string>> l2 = create_basis(l, l1);
  for (auto i:l2){
    printf("\t,{");
    for (auto j:i)
    {
      printf("%s, ",j.c_str());
    }
    printf("}");
  }
  printf("%f\n", compare("shock", "surprise"));
  printf("(");
  list<double> r1=create_vector(l1,l2);
  for (auto i:r1)
    printf(", %f",i);
    printf(")\n");
  Py_Finalize();
  return 0;
}