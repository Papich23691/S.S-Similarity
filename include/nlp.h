#pragma once

#include <iostream>
#include <string>
#include <list>
#include "py_util.h"

using namespace std;

class nlp{
    public:
        nlp();
        virtual ~nlp() = default;
        list<list<string> > tokenize(string sentence);
        double compare(string word1, string word2);
        double semantic_similarity(string sentence1,string sentence2);

    private:
        std::shared_ptr<PyUtils> _py_util;
       
};

#include "linear_space_util.h"