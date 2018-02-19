#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <cstdint>
#include <vector>
#include <string>

struct jamo {
	uint16_t beg;
	uint16_t mid;
	uint16_t end;
};

jamo get_jamo(uint16_t syl);
std::vector<uint16_t> get_alpha_seq(uint16_t syl);
std::vector<uint16_t> get_alpha_seq(jamo jm);

#endif //__UTILS_HPP__
