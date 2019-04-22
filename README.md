# Semantic-similarity
> A tool used to compute the semantic similarity between 2 sentences

</br>

## Table of contents
[Baby Steps](#baby-steps)  
[Sentence Semantic Similarity](#ss)                                  
[Python-C-api](#py_info)  
[spaCy Tools](#spacy)       
[Reference and License](#license)  


<a name="baby-steps"/>

## Baby Steps
### Requirements
This tools require python3 as well as spaCy.</br>
### Installation
In order to download spaCy follow the instructions given in spaCy's [website](https://spacy.io/usage).</br>
##### MacOS
Using MacOS it is important to use python3 in order to install spaCy given the fact that </br>
python2 isn't built on wide build in MacOS.
##### Languages 
For different languages install the specific language model given in spaCy's [website](https://spacy.io/usage).</br>
Afterwards replace the models'n name in [nlp_util.py](src/nlp_util.py) ( line 9 ).</br> For further [info](https://spacy.io/models) .
### Compiling
The makefile is located in src directory so type </br>
```bash
$ cd src && make
```
The program is supposed to compile with no errors .



<a name="ss"/>

## Sentence Semantic Similarity
### Usage
In order to use the sentence semantic similarity function you'll need to create an nlp object.<br/>
```C++
#include "nlp.h"

.
.
. 

nlp [object name];
[object name].semantic_similarity(Sentence_1,Sentence_2);
```
The function will return a number between 0 and 1 ( Closer to 1 is more similar )
### Algorithm in a nutshell
##### POS tagging
First of all the 2 sentences are divided to part of speech tags in order to reduce time <br/>
complexity and to make the algorithm more accurate ( only words which have the same tags are being compared ).<br/><br/>

The final result will be calculated using a vector representation of each sentence and in order to do that <br/>
we will need a vector space basis.
##### Linear space basis
All the sentences can be represented by the union of the words in the first sentence and the second sentence. <br/>
But by having similar semantic field with one another some words in one sentence can be represented as a projection on another word in the another sentence ( In the linear space ). <br/> It means that a sentence can be represented using words which are not a part of it as long <br/>
as certain words in the sentence can be represented as a projection on them.<br/><br/>
A word is not considered orthogonal to another word (it has a pr by James O’Sheaojection over it) if they are "similar".<br/>
Comparing only words with the same pos tag, words which are similar to one another are defined by this function.

![equation of similarity](https://latex.codecogs.com/svg.latex?f%20%3A%20S1%20%5Clongrightarrow%20S2%20%5C%5C%20%5C%5Cf%20%3D%20%5C%7B%28x%2Cy%29%20%5C%20%7C%20%5C%20x%20%5Cin%20S1%2C%20y%20%5Cin%20S2%2Csim%28x%2Cy%29%3E0.5%20%5Cland%20%5Cforall%20z%20%5Cin%20S2%2C%20%5Cforall%20w%20%5Cin%20S1%20%2C%20%28sim%28x%2Cy%29%20%5Cgeq%20%28x%2Cz%29%20%5Cland%20sim%28x%2Cy%29%20%5Cgeq%20%28y%2Cw%29%5C%7D%24) 

The basis is a union of the words in the first sentence and the second sentence minus the words from the <br/>
second sentence which are similar to other words in the first sentence and the orthogonal projection<br/>
of one word on another is the similarity multiplied by the word.<br/>
In the program the similar words will be saved together in the list representing the basis in order to avoid <br/>
calculating the similarity twice and checking which words are similar.
##### Vectors
Let basis <br/>![basis](https://latex.codecogs.com/svg.latex?B%3D%5C%7Bv_0%2C...%2Cv_n%5C%7D)<br/>
![vecor](https://latex.codecogs.com/svg.latex?%5C%20V%20%3D%20%28W_0%2C..%2CW_n%29) 
 for the second sentence will be determined as <br/><br/>
 ![vecotr sentence2](https://latex.codecogs.com/svg.latex?W_i%20%3D%20%5Cbegin%7Bcases%7D%201%20%5C%20%5C%20if%20%5C%20v_i%20%5Cin%20Sentence%20%5C%5C%20sim%28v_i%2Cu_i%29%20%5C%20%5C%20if%20%5C%20%5C%20u_i%20%5Cin%20Sentence%20%5Cland%20f%28v_i%29%20%3D%20u_i%20%5C%5C%200%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20otherwise%20%5Cend%7Bcases%7D)<br/>
 And for the first sentence as <br/>
 ![first](https://latex.codecogs.com/svg.latex?W_i%20%3D%20%5Cbegin%7Bcases%7D%201%20%5C%20%5C%20if%20%5C%20v_i%20%5Cin%20Sentence%20%5C%5C%200%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20%5C%20otherwise%20%5Cend%7Bcases%7D)
##### Result
The result will be calculated by using cosine similarity and by calculating the division between the vector norms<br/><br/>
![calculation](https://latex.codecogs.com/svg.latex?Sentence%20%5C%20sim%20%3D%20%5Cdfrac%7B%20V1%20%5Ccdot%20V2%20%7D%7B%7C%7CV1%7C%7C%20%5Ctimes%20%7C%7CV2%7C%7C%7D%20%5Ctimes%20%5Cdfrac%7B%20%7C%7CV2%7C%7C%20%7D%7B%7C%7CV1%7C%7C%20%7D%20%3D%20%5Cdfrac%7B%20V1%20%5Ccdot%20V2%20%7D%7BV1%20%5Ccdot%20V1%7D)
### Stats
Using the benchmark data base by James O’Shea [[1]](#license) <br/>
I took multiple examples which are shown in this table (Using the more accurate spaCy model)<br/>

Sentence 1 | Sentence 2 | Human benchmark | Similarity algorithm | 
---        |    ---     |       ---       |         ---          |
Midday is 12 oclock in the middle of the day.    | Noon is 12 oclock in the middle of the day.       |0.9550| 0.968959|
A boy is a child who will grow up to be a man.    | A lad is a young man or boy.      |0.5800         | 0.600000  |
The coast is an area of land that is next to the sea.  | The shores or shore of a sea, lake, or wide river is the land along the edge of it.    |0.5875        | 0.692073             |
A furnace is a container or enclosed space in which a very hot fire is made, for example, to melt metal, burn rubbish, or produce steam.    | A stove is a piece of equipment which provides heat, either for cooking or for heating a room.     |0.3475      | 0.489148 |
A bird is a creature with feathers and wings, females lay eggs, and most birds can fly. | A cock is an adult male chicken.  |0.1625      | 0.314249    |
In former times, serfs were a class of people who had to work on a particular persons land and could not leave without that persons permission.|A slave is someone who is the property of another person and has to work for that person.|0.4825|0.483493 |
An autograph is the signature of someone famous which is specially written for a fan to keep. | The shores or shore of a sea, lake, or wide river is the land along the edge of it.  |0.0050| 0.411809|
An automobile is a car.|A car is a motor vehicle with room for a small number of passengers.|0.5575      |0.666667|
A forest is a large area where trees grow close together.|Woodland is land with a lot of trees.|0.6275     | 0.428571  | 
An automobile is a car.|In legends and fairy stories, a wizard is a man who has magic powers.|0.0200    | 0.500000  | 
A cock is an adult male chicken.   | A rooster is an adult male chicken.  |0.8625        | 0.857143 |
When you make a journey, you travel from one place to another.    | A voyage is a long journey on a ship or in a spacecraft.     |0.3600      | 0.315914|




<a name="license"/>

## Reference and License
  [1] J.O’Shea,Z.Bandar,K.Crockett,andD.McLean,“Pilotshorttext semantic similarity benchmark data set: Full listing and descrip- tion,” Computing, 2008.
  
This project is licensed under the GNU General Public License v2.0 . See [License](LICENSE) for more info
