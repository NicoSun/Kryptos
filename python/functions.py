def decrypt_vigenere(ciphertext, key, custom_alphabet):
    decrypted_text = ''
    key_index = 0
    key = str(key).upper()

    for char in ciphertext:
        if char in custom_alphabet:
            key_char = key[key_index % len(key)]
            key_index += 1

            char_index = custom_alphabet.index(char)
            key_char_index = custom_alphabet.index(key_char)


            decrypted_char_index = (char_index - key_char_index) % len(custom_alphabet)
            decrypted_char = custom_alphabet[decrypted_char_index]

            decrypted_text += decrypted_char
        else:
            decrypted_text += char

    return decrypted_text

def decrypt_spacing(ciphertext, spacing):
    cipherlength = len(ciphertext)
    decrypted_text = ""
    location = 0
    for digit in range(1,cipherlength+1):
        location +=  spacing
        if location > cipherlength -1:
            location -= cipherlength
            if location > cipherlength -1:
                location -= cipherlength
        decrypted_char = ciphertext[location-1]
        decrypted_text += decrypted_char
        
    return decrypted_text

def generate_dict_freq(ciphertext, abc):
    abc_dict = {}
    for char in abc:
        abc_dict[char] = 0
        
    for char in ciphertext:
        if char == '?' or char == '!':
            continue
        abc_dict[char] += 1
        
    return abc_dict

def decrypt_spacing(ciphertext, spacing):
    cipherlength = len(ciphertext)
    decrypted_text = ""
    location = 0
    for digit in range(1,cipherlength+1):
        location +=  spacing
        if location > cipherlength -1:
            location -= cipherlength
            if location > cipherlength -1:
                location -= cipherlength
        decrypted_char = ciphertext[location-1]
        decrypted_text += decrypted_char
        
    return decrypted_text

def load_dictionary(filename):
    import pandas as pd
    column = ['A']
    key_list_df = pd.read_csv(filename, names=column)
    key_list = key_list_df.A.tolist()
    return key_list