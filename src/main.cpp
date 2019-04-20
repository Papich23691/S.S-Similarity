
#include "linear_space_util.h"
#include "nlp.h"
#include "py_util.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char ** argv) {
  /* Quick Examples */
  nlp n;
  printf("%f\n",n.semantic_similarity("My dog has a puppy","My pet has a baby"));
  return 0;
}