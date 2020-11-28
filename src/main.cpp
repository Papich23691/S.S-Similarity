
#include "nlp.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc,char ** argv) 
{
  /* Quick Examples */
  std::vector<std::pair<std::string, std::string>> sentences = 
  {
    {"Midday is 12 oclock in the middle of the day.", "Noon is 12 oclock in the middle of the day."},
    {"A boy is a child who will grow up to be a man.", "A lad is a young man or boy."},
    {"The coast is an area of land that is next to the sea.", "The shores or shore of a sea, lake, or wide river is the land along the edge of it."}
  };

  for (auto& sentences_pair : sentences)
  {
    std::string first_sentence = sentences_pair.first;
    std::string second_sentence = sentences_pair.second;
    std::cout << "First sentence: " << first_sentence << std::endl;
    std::cout << "Second sentence: " << second_sentence << std::endl;
    double res1 = NLPUtils::semantic_similarity(first_sentence, second_sentence);
    std::cout << "Score: " << to_string(res1) << std::endl;
    std:cout << std::endl;
  }
  
  return 0;
}