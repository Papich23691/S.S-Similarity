# Semantic-similarity
> A tool used to compute the semantic similarity between 2 sentences<br/>
You can view this tool accuracy in this [table](#accuracy)

</br>

## Table of contents
[Baby Steps](#baby-steps)  
[Sentence Semantic Similarity](#ss)                                  
[spaCy Tools](#spacy)       
[Reference and License](#license)  


<a name="baby-steps"/>

## Baby Steps
### Requirements
This tools require `python3-dev` as well as spaCy.</br>
### Installation
```bash
$ pip3 install spacy
$ python3 -m spacy download en
```

</br>
For the more accurate English model

```bash
$ python3 -m spacy download en_core_web_lg
```
For further downloads follow the instructions given in spaCy's [website](https://spacy.io/usage).</br>
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
### The algorithm in a nutshell
##### POS tagging
First of all the 2 sentences are divided to part of speech tags in order to reduce time <br/>
complexity and to make the algorithm more accurate ( only words which have the same tags are being compared ).<br/><br/>

The final result will be calculated using a vector representation of each sentence and in order to do that <br/>
we will need a vector space basis.
##### Linear space basis
All the sentences can be represented by the union of the words in the first sentence and the second sentence. <br/>
But by having similar semantic fields with one another some words in one sentence can be in the span of another word in the another sentence ( In the linear space ). <br/> It means that a sentence can be represented using words which are not a part of it as long <br/>
as certain words in the sentence are linearly dependent by another words in second sentence.<br/><br/>
2 words are considered linearly dependent if they are "similar".<br/>
Comparing only words with the same pos tag, words which are similar to one another are defined by this function.

![equation of similarity](https://latex.codecogs.com/svg.latex?f%20%3A%20S1%20%5Clongrightarrow%20S2%20%5C%5C%20%5C%5Cf%20%3D%20%5C%7B%28x%2Cy%29%20%5C%20%7C%20%5C%20x%20%5Cin%20S1%2C%20y%20%5Cin%20S2%2Csim%28x%2Cy%29%3E0.5%20%5Cland%20%5Cforall%20z%20%5Cin%20S2%2C%20%5Cforall%20w%20%5Cin%20S1%20%2C%20%28sim%28x%2Cy%29%20%5Cgeq%20%28x%2Cz%29%20%5Cland%20sim%28x%2Cy%29%20%5Cgeq%20%28y%2Cw%29%5C%7D%24) 

The basis is a union of the words in the first sentence and the second sentence minus the words from the <br/>
second sentence which are similar to other words in the first sentence. In order to get one word by another<br/>
similar word you can multiply it by their similarity.<br/>
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
I took multiple examples which are shown in this table (Using multiple SpaCy models)<br/>

<a name="accuracy"/>

Sentence 1 | Sentence 2 | Human benchmark | Similarity algorithm - en_core_web_sm | Similarity algorithm - en_core_web_md | Similarity algorithm - en_core_web_lg | 
---        |    ---     |       ---       |         ---          |         ---          |         ---          |
Midday is 12 oclock in the middle of the day.    | Noon is 12 oclock in the middle of the day.       |95.50| 96.9431|85.7143|85.7143|
A boy is a child who will grow up to be a man.    | A lad is a young man or boy.      |58         | 66.6667   |66.6667|66.6667|
The coast is an area of land that is next to the sea.  | The shores or shore of a sea, lake, or wide river is the land along the edge of it.    |58.75 | 73.1581|59.1532|59.1532|
A rooster is an adult male chicken.|A voyage is a long journey on a ship or in a spacecraft.|0.5|55.9171|0|0|
A furnace is a container or enclosed space in which a very hot fire is made, for example, to melt metal, burn rubbish, or produce steam.    | A stove is a piece of equipment which provides heat, either for cooking or for heating a room.     |34.75      | 31.1785 |31.8863|31.8863|
A bird is a creature with feathers and wings, females lay eggs, and most birds can fly. | A cock is an adult male chicken.  |16.25      | 10.2824    |15.7335|20.5201|
In former times, serfs were a class of people who had to work on a particular persons land and could not leave without that persons permission.|A slave is someone who is the property of another person and has to work for that person.|48.25|42.2456 |42.3675|42.3675|
An autograph is the signature of someone famous which is specially written for a fan to keep. | The shores or shore of a sea, lake, or wide river is the land along the edge of it.  |0.50|57.8627 |22.1932|22.1932|
An automobile is a car.|A car is a motor vehicle with room for a small number of passengers.|55.75      |92.9903 |50|50|
A crane is a large machine that moves heavy things by lifting them in the air.|An implement is a tool or other piece of equipment.|18.50|46.7726 |20.0479|20.0479|
A forest is a large area where trees grow close together.|Woodland is land with a lot of trees.|62.75     | 59.4877   | 83.341|33.3333|
An automobile is a car.|In legends and fairy stories, a wizard is a man who has magic powers.|2.00    | 72.951  |0|0
A cock is an adult male chicken.   | A rooster is an adult male chicken.  |86.25        | 75 |75|75|
A magician is a person who entertains people by doing magic tricks.|In legends and fairy stories, a wizard is a man who has magic powers.|35.50|59.9677 |35.0177|34.3168|
When you make a journey, you travel from one place to another.    | A voyage is a long journey on a ship or in a spacecraft.     |36|35.174 |20|11.1111|
A boy is a child who will grow up to be a man.|A rooster is an adult male chicken.|10.75|26.9036 |18.4459|18.4459|
Glass is a hard transparent substance that is used to make things such as windows and bottles.|A tumbler is a drinking glass with straight sides.|13.75|26.3125 |12.7719|12.7719|
Cord is strong, thick string.|A smile is the expression that you have on your face when you are pleased or amused, or when you are being friendly.|1|34.0262|0|0|
An autograph is the signature of someone famous which is specially written for a fan to keep.|Your signature is your name, written in your own characteristic way, often at the end of a document to indicate that you wrote the document or that you agree with what it says.|40.50|69.4671 |47.734|47.734|

*en_core_web_sm* Mean Absolute Error(MAE) - 22.0958 <br/> <br/>
*en_core_web_md* Mean Absolute Error(MAE) - 6.57057 <br/> <br/>
*en_core_web_lg* Mean Absolute Error(MAE) - 7.73736 <br/> <br/>

<a name="spacy"/>

## spaCy Tools.
Becuase of the lack of nlp tools in C++ I used spaCy.<br/>
spaCy is an open source nlp library which is used in this project. <br/>
I chose spaCy over other libraries such as NLTK because of it's accuracy and efficiency as shown [here](https://spacy.io/usage/facts-figures)<br/>
In order to use the pos tagger and the similarity tool of spaCy in C++ simply create an nlp object as shown before.


<a name="license"/>

## Reference and License
  [1] J.O’Shea,Z.Bandar,K.Crockett,andD.McLean,“Pilot short text semantic similarity benchmark data set: Full listing and descrip- tion,” Computing, 2008.
  
This project is licensed under the GNU General Public License v2.0 . See [License](LICENSE) for more info
