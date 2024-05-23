from functions import load_dictionary, decrypt_vigenere, decrypt_spacing
import pandas as pd

ciphertext1 = "EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJYQTQUXQBQVYUVLLTREVJYQTMKYRDMFD"
ciphertext2 = "VFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKK?DQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVH?DWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZ?FKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETG"

#ciphertext3 length = 337
ciphertext3 = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW?"

#ciphertext4 length = 97
ciphertext4 = "OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR"
# ciphertext4_reverse = ciphertext4[::-1]
cipher_dict = {"1":ciphertext1,"2":ciphertext2,"3":ciphertext3,"4":ciphertext4}
custom_alphabet = "KRYPTOSABCDEFGHIJLMNQUVWXZ"
dictname = '../dicts/English_word_list.csv'

# known keys as reference
key1 = "PALIMPSEST"
key2 = "ABSCISSA"

def export_data(filename,decrypt_list,key_list):
    df = pd.DataFrame(decrypt_list,key_list)
    df.to_csv(filename,header=None)
    
def crack_single_vignere(ciphertext,text_number,custom_alphabet):
    decrypt_list = []
    key_matches = []
    key_list = load_dictionary(dictname)

    for key in key_list:
        text = decrypt_vigenere(cipher_dict[text_number], key,custom_alphabet)
        decrypt_list.append(text)
        key_matches.append(key)
        
    filename = f'temp/decryptions_{text_number}.csv'
    export_data(filename,decrypt_list,key_matches)
    
def crack_spacing(ciphertext,text_number):
    decrypt_list = []
    spacing_list = []
    cipherlength = int(len(ciphertext) * 0.9)
    for spacing in range(1,cipherlength):
        text = decrypt_spacing(cipher_dict[text_number],spacing)
        decrypt_list.append(text)
        spacing_list.append(spacing)
        
    filename = f'temp/decryptions_{text_number}.csv'
    export_data(filename,decrypt_list,spacing_list)


if __name__ == "__main__":
    text_number = "2"
    # crack_spacing(cipher_dict[text_number],text_number)
    crack_single_vignere(cipher_dict[text_number],text_number,custom_alphabet)
    