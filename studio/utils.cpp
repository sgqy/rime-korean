
#include "cb_table.hpp"
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

jamo get_jamo(uint16_t syl)
{
	jamo jm;

	if(syl < 0xAC00 || syl > 0xD7A3) {
		return jm;
	}

	syl -= syl_base;
	if(syl % end_cnt) {
		jm.end = end_base + syl % end_cnt;
	}

	syl /= end_cnt;
	jm.mid = mid_base + syl % mid_cnt;

	syl /= mid_cnt;
	jm.beg = beg_base + syl;

	return jm;
}

std::vector<uint16_t> get_alpha_seq(uint16_t syl)
{
	return get_alpha_seq(get_jamo(syl));
}

std::vector<uint16_t> get_alpha_seq(jamo jm)
{
	std::vector<uint16_t> ret;

	uint16_t seq[12] = {0};
	seq[0] = jm.beg;
	seq[4] = jm.mid;
	seq[8] = jm.end;

	for(int i = 0; i < 12; i += 4) {
		for(cb_t *p = (cb_t *)cb_tbl; p->r; ++p) {
			if(seq[i] == p->r) {
				seq[i+0] = p->a;
				seq[i+2] = p->b;
				break;
			}
		}
	}

	for(int i = 0; i < 12; i += 2) {
		for(cb_t *p = (cb_t *)cb_tbl; p->r; ++p) {
			if(seq[i] == p->r) {
				seq[i+0] = p->a;
				seq[i+1] = p->b;
				break;
			}
		}
	}

	for(int i = 0; i < 12; ++i) {
		if(seq[i]) {
			ret.push_back(seq[i]);
		}
	}

	return ret;
}
