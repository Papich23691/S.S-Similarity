#include "linear_space_util.h"
#include <iostream>
#include <list>
#include <string>

#define MIN_VALUE 0.5

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

list<list<string>> create_basis(list<list<string>> s1, list<list<string>> s2) {
  list<list<string>> basis;
  list<list<string>>::iterator i, j;
  list<string>::iterator n, m, maxw, maxw2;
  double max, sim;
  int c = 0;
  bool isfound = false;
  for (i = s1.begin(); i != s1.end(); ++i) {
    for (j = s2.begin(); j != s2.end(); ++j) {
      if ((*(i->begin())) == (*(j->begin()))) {
        isfound = true;
        for (n = ++(i->begin()); n != i->end(); ++n) {
          max = MIN_VALUE;
          list<string> v;
          v.push_back(*n);
          maxw = j->end();
          for (m = ++(j->begin()); m != j->end(); ++m) {
            if ((*m) == "\0")
              continue;
            sim = compare(*n, *m);
            ++c;
            if (sim >= max) {
              max = sim;
              maxw = m;
              if (sim == 1)
                break;
            }
          }
          if (max < 1)
            max = MIN_VALUE;
          if (maxw != j->end()) {
            maxw2 = n;
            if (max < 1) {
              for (m = ++(i->begin()); m != i->end(); ++m) {
                sim = compare(*maxw, *m);
                ++c;
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
    if (!isfound) {
      for (n = ++(i->begin()); n != i->end(); ++n) {
        list<string> v;
        v.push_back(*n);
        basis.push_back(v);
      }
    }
  }
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