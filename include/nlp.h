#pragma once

#include <iostream>
#include <string>
#include <list>
#include "py_util.h"

class NLPUtils{
    public:
        NLPUtils() = delete;
        ~NLPUtils() = delete;
        static std::list<std::list<std::string> > tokenize(const std::string sentence);
        static double compare(const std::string word1, const std::string word2);
        static double semantic_similarity(const std::string sentence1,const std::string sentence2);
};

#include "linear_space_util.h"