#ifndef __KR_UTILS_HPP__
#define __KR_UTILS_HPP__

#include <cstdint>
#include <vector>
#include <set>
#include <string>

struct syllable {
	uint16_t beg = 0;
	uint16_t mid = 0;
	uint16_t end = 0;
};

syllable expand_syllable (uint16_t syl_code);
std::vector<uint16_t> get_jamo_sequence (uint16_t syl);
std::vector<uint16_t> get_jamo_sequence (syllable syl);
std::set<std::string> get_word_roma (const char *line);
std::set<std::string> get_word_roma (std::string line);
std::set<std::string> get_word_roma (uint16_t syl);
std::set<std::string> get_word_roma (std::u16string line);
std::set<std::string> get_word_roma (std::vector<uint16_t> line);

#endif //__KR_UTILS_HPP__
