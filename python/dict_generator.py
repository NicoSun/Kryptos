from functions import load_dictionary
import pandas as pd

dictname = '../dicts/English_word_list.csv'
alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
dict_list = load_dictionary(dictname)

for char in alphabet:
    char_dict = []
    for word in dict_list:
        word = str(word)
        if word[0].upper() == char:
            char_dict.append(word)
            dict_list.remove(word)
    
    df = pd.DataFrame(char_dict)
    df.to_csv(f'../dicts/English_word_list_{char}.csv',header=None,index=None)
