#include "linear_space_util.h"
#include <iostream>
#include <list>
#include <string>

#define MIN_VALUE 0.5

/* Calculating the dot product between 2 vectors */
double dot_product(list<double> v1, list<double> v2) {
  double sum = 0;
  unsigned long i = 0;
  for (i = 0; i < v1.size(); i++) {
    list<double>::iterator v1s = v1.begin();
    list<double>::iterator v2s = v2.begin();
    std::advance(v1s, i);
    std::advance(v2s, i);
    sum += ((*v1s) * (*v2s));
  }
  return sum;
}

/* Creates a basis for the sentence linear space */
list<list<string>> create_basis(list<list<string>> s1, list<list<string>> s2) {
  list<list<string>> basis;
  list<list<string>>::iterator i, j;
  list<string>::iterator n, m, maxw, maxw2;
  double max, sim;
  bool isfound = false;
  /* Comparing only word with the same pos tag */
  for (i = s1.begin(); i != s1.end(); ++i) {
    for (j = s2.begin(); j != s2.end(); ++j) {
      if ((*(i->begin())) == (*(j->begin()))) {
        isfound = true;
        /* 2 words are consider the same if the similarity between them is the maximum similarity compared to other words and their similarity is above MIN_VALUE */
        for (n = ++(i->begin()); n != i->end(); ++n) {
          max = MIN_VALUE;
          list<string> v;
          v.push_back(*n);
          maxw = j->end();
          for (m = ++(j->begin()); m != j->end(); ++m) {
            if ((*m) == "\0")
              continue;
            sim = compare(*n, *m);
            if (sim >= max) {
              max = sim;
              maxw = m;
              if (sim == 1)
                break;
            }
          }
          /* Checks the other way around and makes sure the two words are indeed the most similar words to one another */
          if (max < 1)
            max = MIN_VALUE;
          if (maxw != j->end()) {
            maxw2 = n;
            if (max < 1) {
              for (m = ++(i->begin()); m != i->end(); ++m) {
                sim = compare(*maxw, *m);
                if (sim >= max) {
                  max = sim;
                  maxw2 = m;
                  if (sim == 1)
                    break;
                }
              }
            }
            if ((*maxw2) == (*n)) {
              v.push_back(*maxw);
              v.push_back(to_string(max));
              *maxw = "\0";
              *maxw2 = "\0";
            }
          }
          basis.push_back(v);
        }
        break;
      }
    }
    /* If a group of the same pos tag doesn't have another corresponding group with the same pos tag in the other sentence, adds all the words inside of it to the basis */
    if (!isfound) {
      for (n = ++(i->begin()); n != i->end(); ++n) {
        list<string> v;
        v.push_back(*n);
        basis.push_back(v);
      }
    }
  }
  /* Adds all the words that are left from the second sentence */
  for (j = s2.begin(); j != s2.end(); ++j) {
    for (m = ++(j->begin()); m != j->end(); ++m) {
      if ((*m) == "\0")
        continue;
      list<string> v;
      v.push_back(*m);
      basis.push_back(v);
    }
  }
  return basis;
}

/**
 * @brief Using the basis created to create a vector
 * If the first word is in the sentence the scalar is considered 1 
 * otherwise if the second word is is the sentence the similarity between them is the scalar
 * else the word is not in the sentence so it refers to it as a zero
 * 
 */
list<double> create_vector(list<list<string>> s, list<list<string>> basis) {
  list<list<string>>::iterator i;
  list<string>::iterator j;
  list<double> v;
  for (i = basis.begin(); i != basis.end(); i++) {
    if (element_of_sentence(s, (*(i->begin()))))
      v.push_back(1);
    else if (element_of_sentence(s, (*++(i->begin()))))
    {
      j = i->begin();
      advance(j,2);
      v.push_back(stod((*j)));
    }
    else
      v.push_back(0);
  }
  return v;
}

/* Finds if a word is a part of a sentence */
bool element_of_sentence(list<list<string>> s, string word) {
    list<list<string>>::iterator i;
    list<string>::iterator j;
    for (i = s.begin(); i != s.end(); i++) {
      for (j = ++(i->begin()); j != i->end(); j++) {
        if ((*j) == word)
          return true;
      }
    }
  return false;
}