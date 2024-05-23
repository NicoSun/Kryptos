#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <thread>
#include <mutex>
#include "functions.h"

std::mutex mtx;  // Mutex for critical section
std::vector<std::string> decrypt_list;
std::vector<std::string> key_matches;

void process_cryptic(const std::char& character, const std::vector<std::string>& key_list_full, const std::string& custom_alphabet, std::string& ciphertext) {
    std::cout << character << std::endl;
    std::vector<std::string> cryptic_list;
    std::vector<std::string> decrypt_list;
    std::vector<std::string> key_matches;
    std::string file_path = "dicts/English_word_list_" + std::string(1, character) + ".csv";
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

void save_csv(const std::string& filename,std::vector<std::string> decrypt_list,std::vector<std::string> key_matches){
    std::ofstream outFile(filename);
    for (size_t i = 0; i < decrypt_list.size(); ++i) {
        outFile << key_matches[i] << "," << decrypt_list[i] << "\n";
    }
    outFile.close();
}

void double_vignere(std::string& ciphertext, std::string text_number,std::string& custom_alphabet){
    std::string dictname_full = "English_word_list.csv";
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::vector<std::string> key_list_full = load_English_dictionary(dictname_full);
    std::vector<std::thread> threads;

    for (const auto& character : alphabet){
        threads.emplace_back(process_cryptic, character, key_list_full, custom_alphabet, ciphertext);
    }
    
}

int main() {
    std::string ciphertext3 = "ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIACHTNREYULDSLLSLLNOHSNOSMRWXMNETPRNGATIHNRARPESLNNELEBLPIIACAEWMTWNDITEENRAHCTENEUDRETNHAEOETFOLSEDTIWENHAEIOYTEYQHEENCTAYCREIFTBRSPAMHHEWENATAMATEGYEERLBTEEFOASFIOTUETUAEOTOARMAEERTNRTIBSEDDNIAAHTTMSTEWPIEROAGRIEWFEBAECTDDHILCEIHSITEGOEAOSDDRYDLORITRKLMLEHAGTDHARDPNEOHMGFMFEUHEECDMRIPFEIMEHNLSSTTRTVDOHW?";
    std::string ciphertext4 = "OBKRUOXOGHULBSOLIFBBWFLRVQQPRNGKSSOTWTQSJQSSEKZZWATJKLUDIAWINFBNYPVTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR";
    // std::reverse(ciphertext4.begin(), ciphertext4.end());

    std::map<std::string, std::string> cipher_dict = {{"3", ciphertext3}, {"4", ciphertext4}};
    std::string text_number = "4";
    std::string custom_alphabet = "KRYPTOSABCDEFGHIJLMNQUVWXZ";

    double_vignere(cipher_dict[text_number],text_number, custom_alphabet);
    return 0;
}
