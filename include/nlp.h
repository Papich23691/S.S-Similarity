#ifndef NLP   
#define NLP

#include <iostream>
#include <string>
#include <list>
#include <Python.h>

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


#endif