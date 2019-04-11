
import spacy

nlp = spacy.load("en_core_web_sm")

def tokenize(sentence):
    doc = nlp(sentence)
    tags = []
    if doc != [] :
        tags.append([doc[0].pos_])
        for w in doc :
            istag=False 
            for t in tags :
                if t[0] == w.pos_ :
                    t.append(w.text)
                    istag=True
            if istag==False :
                tag=[w.pos_,w.text]
                tags.append(tag)
    return tags

