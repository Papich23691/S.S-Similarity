#ifndef V_SPACE   
#define V_SPACE

#include <iostream>
#include <string>
#include <list>
#include "nlp.h"

using namespace std;

double dot_product(list<double> v1,list<double> v2);
list<list<string>> create_basis(list<list<string>> s1, list<list<string>> s2);
list<double> create_vector(list<list<string>> s, list<list<string>> basis);
bool element_of_sentence(list<list<string>> s,string word);

#endif