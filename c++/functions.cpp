#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include "functions.h"

// Function to decrypt Vigenère cipher
std::string decrypt_vigenere(const std::string& ciphertext, const std::string& key, const std::string& custom_alphabet) {
    std::string decrypted_text;
    int key_index = 0;
    int alphabet_len = custom_alphabet.size();
    std::string uppercase_key = key;

    // Convert key to uppercase
    for (char& c : uppercase_key) {
        c = std::toupper(c);
    }

    for (char char_in_cipher : ciphertext) {
        if (custom_alphabet.find(char_in_cipher) != std::string::npos) {
            char key_char = uppercase_key[key_index % uppercase_key.size()];
            key_index++;
            
            int char_index = custom_alphabet.find(char_in_cipher);
            int key_char_index = custom_alphabet.find(key_char);

            int decrypted_char_index = (char_index - key_char_index + alphabet_len) % alphabet_len;
            char decrypted_char = custom_alphabet[decrypted_char_index];

            decrypted_text += decrypted_char;
        } else {
            decrypted_text += char_in_cipher;
        }
    }

    return decrypted_text;
}

// Function to decrypt text with spacing
std::string decrypt_spacing(const std::string& ciphertext, int spacing) {
    int cipherlength = ciphertext.size();
    std::string decrypted_text(cipherlength, ' ');
    int location = 0;

    for (int digit = 1; digit <= cipherlength; digit++) {
        location += spacing;
        if (location > cipherlength - 1) {
            location -= cipherlength;
            if (location > cipherlength - 1) {
                location -= cipherlength;
            }
        }
        decrypted_text[digit - 1] = ciphertext[location - 1];
    }

    return decrypted_text;
}

// Function to generate frequency dictionary
std::unordered_map<char, int> generate_dict_freq(const std::string& ciphertext, const std::string& abc) {
    std::unordered_map<char, int> abc_dict;

    for (char char_in_abc : abc) {
        abc_dict[char_in_abc] = 0;
    }

    for (char char_in_cipher : ciphertext) {
        if (char_in_cipher == '?' || char_in_cipher == '!') {
            continue;
        }
        abc_dict[char_in_cipher]++;
    }

    return abc_dict;
}

// Function to load English dictionary from a CSV file
std::vector<std::string> load_English_dictionary(const std::string& filename) {
    std::vector<std::string> key_list;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        key_list.push_back(line);
    }

    return key_list;
}

void test() {
    // Example usage
    std::string ciphertext2 = "VFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKK?DQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVH?DWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZ?FKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETG";
    std::string ciphertext3 = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW?";
    std::string key = "ABSCISSA";
    std::string custom_alphabet = "KRYPTOSABCDEFGHIJLMNQUVWXZ";

    std::string decrypted_text_vigenere = decrypt_vigenere(ciphertext2, key, custom_alphabet);
    std::cout << "Decrypted Vigenere: " << decrypted_text_vigenere << std::endl;

    int spacing = 192;
    std::string decrypted_text_spacing = decrypt_spacing(ciphertext3, spacing);
    std::cout << "Decrypted Spacing: " << decrypted_text_spacing << std::endl;

    std::unordered_map<char, int> abc_dict = generate_dict_freq(ciphertext3, custom_alphabet);
    for (const auto& pair : abc_dict) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::string filename = "English_word_list.csv";
    std::vector<std::string> english_dictionary = load_English_dictionary(filename);
    for (const auto& word : english_dictionary) {
        std::cout << word << std::endl;
    }
}
