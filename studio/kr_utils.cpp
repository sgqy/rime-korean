
#include <vector>
#include <string>

#include "cb_table.hpp"
#include "kr_utils.hpp"
#include "pc_table.hpp"

enum korean_property : uint16_t {
	syl_base = 0xAC00,
	beg_base = 0x1100,
	mid_base = 0x1161,
	end_base = 0x11A7,
	mid_cnt  = 21,
	end_cnt  = 28,
};

// https://github.com/choehwanjin/libhangul/blob/master/hangul/hangulctype.c
// hangul_syllable_to_jamo

syllable expand_syllable (uint16_t syl_code)
{
	syllable syl;

	if (syl_code < 0xAC00 || syl_code > 0xD7A3) {
		return syl;
	}

	syl_code -= syl_base;

	if (syl_code % end_cnt) {
		syl.end = end_base + syl_code % end_cnt;
	}

	syl_code /= end_cnt;
	syl.mid = mid_base + syl_code % mid_cnt;

	syl_code /= mid_cnt;
	syl.beg = beg_base + syl_code;

	return syl;
}

static void decombine_jamo (const uint16_t R, uint16_t *a, uint16_t *b)
{
	for (cb_t *p = (cb_t *) cb_tbl; p->r; ++p) {
		if (R == p->r) {
			if (a) {
				*a = p->a;
			}

			if (b) {
				*b = p->b;
			}

			break;
		}
	}
}

std::vector<uint16_t> get_jamo_sequence (uint16_t syl)
{
	return get_jamo_sequence (expand_syllable (syl));
}

std::vector<uint16_t> get_jamo_sequence (syllable syl)
{
	std::vector<uint16_t> ret;

	uint16_t seq[12] = {0};
	seq[0] = syl.beg;
	seq[4] = syl.mid;
	seq[8] = syl.end;

	for (int i = 0; i < 12; i += 4) {
		decombine_jamo (seq[i], seq + i, seq + i + 2);
	}

	for (int i = 0; i < 12; i += 2) {
		decombine_jamo (seq[i], seq + i, seq + i + 1);
	}

	for (int i = 0; i < 12; ++i) {
		if (seq[i]) {
			ret.push_back (seq[i]);
		}
	}

	return ret;
}

static std::string get_jamo_roma (const uint16_t jamo)
{
	std::string ret;

	if (jamo == 0) {
		return ret;
	}

	uint16_t seq[3] = {0};
	seq[0] = jamo;

	for (ph_t *p = (ph_t *) ph_tbl; p->jamo(); ++p) {
		if (seq[0] == p->jamo()) {
			ret += p->phon();
			break;
		}
	}

	if (ret.size() != 0) {
		return ret;
	}

	decombine_jamo (seq[0], seq + 1, seq + 2);
	ret += get_jamo_roma (seq[1]);
	ret += get_jamo_roma (seq[2]);

	return ret;
}

static std::string get_syllable_roma (const uint16_t syl)
{
	std::string ret;

	auto jm = expand_syllable (syl);

	ret += get_jamo_roma (jm.beg);
	ret += get_jamo_roma (jm.mid);
	ret += get_jamo_roma (jm.end);

	return ret;
}

std::set<std::string> get_word_roma (uint16_t syl)
{
	std::vector<uint16_t> arg;
	arg.push_back (syl);
	return get_word_roma (arg);
}

std::set<std::string> get_word_roma (std::u16string line)
{
	std::vector<uint16_t> lv (line.begin(), line.end());
	return get_word_roma (lv);
}

std::set<std::string> get_word_roma (std::vector<uint16_t> line)
{
	std::set<std::string> ret;

	// Type 1: Convert directly, with separated alphabets
	std::string tmp;

	for (auto i = line.begin(); i != line.end(); ++i) {
		auto seq = get_jamo_sequence (*i);

		for (auto j = seq.begin(); j != seq.end(); ++j) {
			tmp += get_jamo_roma (*j);
		}
	}

	ret.insert (tmp);
	tmp.clear();

	// Type 2: Convert directly, with combined vowels
	for (auto i = line.begin(); i != line.end(); ++i) {
		tmp += get_syllable_roma (*i);
	}

	ret.insert (tmp);
	tmp.clear();

	return ret;
}
