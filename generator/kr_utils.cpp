#include "cb_table.hpp"
#include "pc_table.hpp"
#include "kr_utils.hpp"
#include "str_utils.hpp"

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
		// Type 1 : Compatibility jamo
		if (syl_code < 0x3131 || syl_code > 0x318e) {
			return syl;
		}
		for (jt_t *p = (jt_t *)jamo_trans_tbl; p->tr; ++p) {
			if (syl_code == p->tr) {
				syl_code = p->rl;
			}
		}
		syl.beg = syl_code;
		return syl;
	}

	// Type 2 : Combined syllable
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
	for (cb_t *p = (cb_t *)cb_tbl; p->r; ++p) {
		if (R == p->r) {
			if (a) {
				*a = p->a;
			}
			if (b) {
				*b = p->b;
			}
			return;
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

	for (ph_t *p = (ph_t *)ph_tbl; p->jamo(); ++p) {
		if (seq[0] == p->jamo()) {
			ret = p->phon();
			return ret;
		}
	}

	decombine_jamo (seq[0], seq + 1, seq + 2);
	ret += get_jamo_roma (seq[1]);
	ret += get_jamo_roma (seq[2]);

	return ret;
}

static std::string get_syllable_roma (const uint16_t syl)
{
	std::string ret;
	ret += get_jamo_roma (syl);
	if (ret.size()) {
		return ret;
	}

	auto jm = expand_syllable (syl);

	ret += get_jamo_roma (jm.beg);
	ret += get_jamo_roma (jm.mid);
	ret += get_jamo_roma (jm.end);

	return ret;
}

static std::vector<std::string> get_phonetic_link (const uint16_t end, const uint16_t beg)
{
	for (ch_t *p = (ch_t *)pc_tbl; p->end(); ++p) {
		if (end == p->end() && beg == p->beg()) {
			return p->pho();
		}
		uintptr_t *j = (uintptr_t *)p;
		j += p->pho().size() + 1;
		p = (ch_t *)j;
	}
	std::string s;
	s += get_jamo_roma (end);
	s += get_jamo_roma (beg);
	std::vector<std::string> ret;
	ret.push_back (s);
	return ret;
}

std::set<std::string> get_word_roma (const char *line)
{
	return get_word_roma (u8_to_u16_vec (line));
}

std::set<std::string> get_word_roma (std::string line)
{
	return get_word_roma (u8_to_u16_vec (line));
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
	std::string tmp;

	//// Type 1: Convert directly, with separated alphabets

	for (auto i = line.begin(); i != line.end(); ++i) {
		auto seq = get_jamo_sequence (*i);
		for (auto j = seq.begin(); j != seq.end(); ++j) {
			tmp += get_jamo_roma (*j);
		}
	}
	ret.insert (tmp);
	tmp.clear();

	//// Type 2: Convert directly, with combined vowels

	for (auto i = line.begin(); i != line.end(); ++i) {
		tmp += get_syllable_roma (*i);
	}
	ret.insert (tmp);
	tmp.clear();

	//// Type 3: Include phonetic changes

	// expand syllables in line
	std::vector<syllable> sv;
	for (auto i = line.begin(); i != line.end(); ++i) {
		sv.push_back (expand_syllable (*i));
	}
	// get all possible roma sequence of syllables
	std::vector<std::vector<std::string>> seq;
	for (size_t i = 0; i < sv.size(); ++i) {
		if (i == 0) {
			std::vector<std::string> jrv;
			jrv.push_back (get_jamo_roma (sv[i].beg));
			seq.push_back (jrv);
		}

		std::vector<std::string> jrv;
		jrv.push_back (get_jamo_roma (sv[i].mid));
		seq.push_back (jrv);

		if (i == sv.size() - 1) {
			std::vector<std::string> jrv;
			jrv.push_back (get_jamo_roma (sv[i].end));
			seq.push_back (jrv);
		} else {
			auto jrv = get_phonetic_link (sv[i].end, sv[i + 1].beg);
			seq.push_back (jrv);
		}
	}
	// do Cartesion-like product
	auto pro = str_product (seq);
	// save result
	for (auto &s : pro) {
		ret.insert (s);
	}

	return ret;
}
