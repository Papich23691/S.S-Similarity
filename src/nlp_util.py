
import spacy
import warnings

nlp = spacy.load("en_core_web_lg")

def tokenize(sentence):
    doc = nlp(sentence)
    tags = []
    if doc != [] :
        tags.append([doc[0].pos_])
        for w in doc :
            if w.pos_ == "PUNCT" :
                continue
            istag=False 
            for t in tags :
                if t[0] == w.pos_ :
                    t.append(w.text)
                    istag=True
            if istag==False :
                tag=[w.pos_,w.text]
                tags.append(tag)
    return tags

def compare(word1,word2):
    with warnings.catch_warnings():
        warnings.simplefilter("ignore")
        return nlp(word1).similarity(nlp(word2))


