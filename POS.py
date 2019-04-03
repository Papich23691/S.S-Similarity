import nltk


def tokenize(sentence):
    ''' 
    Pos tagging a sentence using NLTK and returning a list of all 
    parts of speech and their corresponding words for each one 
    '''
    tewt = nltk.word_tokenize(sentence)
    pos=nltk.pos_tag(tewt)
    if pos != None :
        tags = [[pos[0][1]]]
        for w in pos:
            istag=False 
            for t in tags:
                if t[0] == w[1] :
                    t.append(w[0])
                    istag=True
            if istag==False :
                tag=[w[1],w[0]]
                tags.append(tag)
        return tags
        