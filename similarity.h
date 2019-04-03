#ifndef SIM    // To make sure you don't declare the function more than once by including the header multiple times.
#define SIM

#include <iostream>
#include <string>
#include <list>

using namespace std;

list<list<string> > tokenize(string sentence);

#endif