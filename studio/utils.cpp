
#include <vector>
#include <string>

#include "cb_table.hpp"
#include "pc_table.hpp"
#include "utils.hpp"

enum jamo_pref : uint16_t {
	syl_base = 0xAC00,
	beg_base = 0x1100,
	mid_base = 0x1161,
	end_base = 0x11A7,
	mid_cnt  = 21,
	end_cnt  = 28,
};

// https://github.com/choehwanjin/libhangul/blob/master/hangul/hangulctype.c
// hangul_syllable_to_jamo

jamo get_jamo (uint16_t syl)
{
	jamo jm;

	if (syl < 0xAC00 || syl > 0xD7A3) {
		return jm;
	}

	syl -= syl_base;

	if (syl % end_cnt) {
		jm.end = end_base + syl % end_cnt;
	}

	syl /= end_cnt;
	jm.mid = mid_base + syl % mid_cnt;

	syl /= mid_cnt;
	jm.beg = beg_base + syl;

	return jm;
}

void decom_jamo (const uint16_t R, uint16_t *a, uint16_t *b)
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

std::vector<uint16_t> get_alpha_seq (uint16_t syl)
{
	return get_alpha_seq (get_jamo (syl));
}

std::vector<uint16_t> get_alpha_seq (jamo jm)
{
	std::vector<uint16_t> ret;

	uint16_t seq[12] = {0};
	seq[0] = jm.beg;
	seq[4] = jm.mid;
	seq[8] = jm.end;

	for (int i = 0; i < 12; i += 4) {
		decom_jamo (seq[i], seq + i, seq + i + 2);
	}

	for (int i = 0; i < 12; i += 2) {
		decom_jamo (seq[i], seq + i, seq + i + 1);
	}

	for (int i = 0; i < 12; ++i) {
		if (seq[i]) {
			ret.push_back (seq[i]);
		}
	}

	return ret;
}

std::string get_roma_single (const uint16_t jm)
{
	std::string ret;

	for (ph_t *p = (ph_t *) ph_tbl; p->syl(); ++p) {
		if (jm == p->syl()) {
			ret += p->pho();
			break;
		}
	}

	return ret;
}

std::string get_alpha_roma (const uint16_t al)
{
	std::string ret;

	if (al == 0) {
		return ret;
	}

	uint16_t seq[3] = {0};
	seq[0] = al;

	for (ph_t *p = (ph_t *) ph_tbl; p->syl(); ++p) {
		if (seq[0] == p->syl()) {
			ret += p->pho();
			break;
		}
	}

	if (ret.size() != 0) {
		return ret;
	}

	decom_jamo (seq[0], seq + 1, seq + 2);
	ret += get_alpha_roma (seq[1]);
	ret += get_alpha_roma (seq[2]);
	return ret;
}

std::string get_roma_single_cb_vo (const uint16_t syl)
{
	std::string ret;

	auto jm = get_jamo (syl);

	ret += get_alpha_roma (jm.beg);
	ret += get_alpha_roma (jm.mid);
	ret += get_alpha_roma (jm.end);

	return ret;
}

std::set<std::string> get_roma (uint16_t syl)
{
	std::vector<uint16_t> arg;
	arg.push_back (syl);
	return get_roma (arg);
}

std::set<std::string> get_roma (std::u16string line)
{
	std::vector<uint16_t> lv (line.begin(), line.end());
	return get_roma (lv);
}

std::set<std::string> get_roma (std::vector<uint16_t> line)
{
	std::set<std::string> ret;

	// Type 1: Convert directly, with seperated alphabets
	std::string tmp;

	for (auto i = line.begin(); i != line.end(); ++i) {
		auto seq = get_alpha_seq (*i);

		for (auto j = seq.begin(); j != seq.end(); ++j) {
			tmp += get_roma_single (*j);
		}
	}

	ret.insert (tmp);
	tmp.clear();

	// Type 2: Convert directly, with combined vowels
	for (auto i = line.begin(); i != line.end(); ++i) {
		tmp += get_roma_single_cb_vo (*i);
	}

	ret.insert (tmp);
	tmp.clear();

	return ret;
}
