
#include "nlp.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc,char ** argv) 
{
  /* Quick Examples */
  nlp n;
  double res1 = n.semantic_similarity("Midday is 12 oclock in the middle of the day.","Noon is 12 oclock in the middle of the day.");

  printf("%f \n",res1);
 
  return 0;
}