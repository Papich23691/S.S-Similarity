#ifndef NLP   
#define NLP

#include <iostream>
#include <string>
#include <list>
#include "py_util.h"

using namespace std;

class nlp{
    public:
        nlp();
        ~nlp();
        list<list<string> > tokenize(string sentence);
        double compare(string word1, string word2);
        double semantic_similarity(string sentence1,string sentence2);
    private:
        static bool init;
};

#include "linear_space_util.h"

#endif