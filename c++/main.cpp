#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include "functions.h"

void save_csv(const std::string& filename,std::vector<std::string> decrypt_list,std::vector<std::string> key_matches){
    std::ofstream outFile(filename);
    for (size_t i = 0; i < decrypt_list.size(); ++i) {
        outFile << key_matches[i] << "," << decrypt_list[i] << "\n";
    }
    outFile.close();
}

void single_vignere(std::string ciphertext,std::string text_number,std::string custom_alphabet ){
    std::vector<std::string> decrypt_list;
    std::vector<std::string> key_matches;
    std::string dictname_full = "../dicts/English_word_list.csv";
    std::vector<std::string> key_list = load_English_dictionary(dictname_full);

    for (const auto& key : key_list) {
        std::string text = decrypt_vigenere(ciphertext, key, custom_alphabet);
        decrypt_list.push_back(text);
        key_matches.push_back(key);
        }
    std::string file_name = "temp/decryptions_" + text_number + ".csv";
    save_csv(file_name,decrypt_list,key_matches);
    }
    

void double_vignere(std::string ciphertext, std::string text_number,std::string custom_alphabet){
    std::string dictname_full = "../dicts/English_word_list.csv";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::string> key_list_full = load_English_dictionary(dictname_full);

    for (const auto& character : alphabet){
        std::cout << character << std::endl;
        std::vector<std::string> cryptic_list;
        std::vector<std::string> decrypt_list;
        std::vector<std::string> key_matches;
        std::string file_path = "../dicts/English_word_list_" + std::string(1, character) + ".csv";
        std::vector<std::string> key_list2 = load_English_dictionary(file_path);

        for (const auto& key : key_list2) {
            std::string crypt1_text = decrypt_vigenere(ciphertext, key, custom_alphabet);
            cryptic_list.push_back(crypt1_text);
        }

        for (const auto& cryptic : cryptic_list) {
            for (const auto& key2 : key_list_full) {
                std::string crypt2_text = decrypt_vigenere(cryptic, key2, custom_alphabet);
                if (crypt2_text.find("BERLIN") != std::string::npos) {
                    decrypt_list.push_back(crypt2_text);
                    key_matches.push_back(key2);
                    // std::cout << "Match: " << crypt2_text << std::endl;
                }
            }
        }

        std::string file_name = "temp/decryptions4_" + std::string(1, character) + ".csv";
        save_csv(file_name,decrypt_list,key_matches);
    }
    
}

int main() {
    std::string ciphertext1 = "EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJYQTQUXQBQVYUVLLTREVJYQTMKYRDMFD";
    std::string ciphertext2 = "VFPJUDEEHZWETZYVGWHKKQETGFQJNCEGGWHKK?DQMCPFQZDQMMIAGPFXHQRLGTIMVMZJANQLVKQEDAGDVFRPJUNGEUNAQZGZLECGYUXUEENJTBJLBQCRTBJDFHRRYIZETKZEMVDUFKSJHKFWHKUWQLSZFTIHHDDDUVH?DWKBFUFPWNTDFIYCUQZEREEVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDXFLGGTEZ?FKZBSFDQVGOGIPUFXHHDRKFFHQNTGPUAECNUVPDJMQCLQUMUNEDFQELZZVRRGKFFVOEEXBDMVPNFQXEZLGREDNQFMPNZGLFLPMRJQYALMGNUVPDXVKPDQUMEBEDMHDAFMJGZNUPLGEWJLLAETG";
    std::string ciphertext3 = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW?";
    std::string ciphertext4 = "OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR";
    // std::reverse(ciphertext4.begin(), ciphertext4.end());

    std::map<std::string, std::string> cipher_dict = {{"1", ciphertext1},{"2", ciphertext2},{"3", ciphertext3}, {"4", ciphertext4}};
    std::string text_number = "2";
    std::string custom_alphabet = "KRYPTOSABCDEFGHIJLMNQUVWXZ";

    single_vignere(cipher_dict[text_number],text_number, custom_alphabet);
    // double_vignere(cipher_dict[text_number],text_number, custom_alphabet);
    return 0;
}

// g++ -o decrypt main.cpp functions.cpp
