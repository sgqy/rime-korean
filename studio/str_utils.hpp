
#ifndef STR_UTILS_HPP_
#define __STR_UTILS_HPP__

#include <locale>
#include <codecvt>
#include <cstdint>
#include <vector>
#include <string>

std::vector<uint16_t> u8_to_u16_vec (const char *s);
std::vector<uint16_t> u8_to_u16_vec (std::string s);
std::u16string u8_to_u16_str (const char *s);
std::u16string u8_to_u16_str (std::string s);
std::vector<std::string> str_product (std::vector<std::vector<std::string>> c);

#endif /* STR_UTILS_HPP_ */
