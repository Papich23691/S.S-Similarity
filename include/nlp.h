#pragma once

#include <iostream>
#include <string>
#include <list>
#include "py_util.h"

using namespace std;

class NLPUtils{
    public:
        NLPUtils() = delete;
        ~NLPUtils() = delete;
        static list<list<string> > tokenize(string sentence);
        static double compare(string word1, string word2);
        static double semantic_similarity(string sentence1,string sentence2);

};

#include "linear_space_util.h"