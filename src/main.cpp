
#include "nlp.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char ** argv) {
  /* Quick Examples */
  nlp n;
 double res1 = n.semantic_similarity("A grin is a broad smile.","A smile is the expression that you have on your face when you are pleased or amused, or when you are being friendly.");

 printf("%f \n",res1);
 
  return 0;
}