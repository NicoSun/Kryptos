#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>

std::vector<std::string> load_English_dictionary(const std::string& filename);
std::string decrypt_spacing(const std::string& text, int spacing);
std::string decrypt_vigenere(const std::string& text, const std::string& key, const std::string& alphabet);

#endif // FUNCTIONS_H
