#pragma once

#include <iostream>
#include <string>
#include <list>
#include "nlp.h"

using namespace std;

class LSUtils final
{
    public:
        LSUtils() = delete;
        ~LSUtils() = delete;
        static double dot_product(list<double> v1,list<double> v2);
        static list<list<string>> create_basis(list<list<string>> s1, list<list<string>> s2,nlp *nl);
        static list<double> create_vector(list<list<string>> s, list<list<string>> basis);
        static bool element_of_sentence(list<list<string>> s,string word);
};