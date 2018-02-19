// phonetic & changes table

#ifndef __PHCH_TABLE_HPP__
#define __PHCH_TABLE_HPP__

#include <vector>

class ph_t {
	uintptr_t _syl;
	uintptr_t _pho;
public:
	uint16_t syl() {
		return (uint16_t)_syl;
	}
	char *pho() {
		return (char *)_pho;
	}
};

class ch_t {
	uintptr_t _end;
	uintptr_t _beg;
public:
	uint16_t end() {
		return (uint16_t)_end;
	}
	uint16_t beg() {
		return (uint16_t)_beg;
	}
	std::vector<char *> pho() {
		std::vector<char *> ret;
		for(char *p = (char *)(&_beg+1); p; ++p) {
			ret.push_back(p);
		}
		return ret;
	}
};

static const uintptr_t ph_tbl[] = {
	// vowel
	0x1161, (uintptr_t)"a",   // ᅡ
	0x1162, (uintptr_t)"ae",  // ᅢ
	0x1163, (uintptr_t)"ya",  // ᅣ
	0x1164, (uintptr_t)"yae", // ᅤ
	0x1165, (uintptr_t)"eo",  // ᅥ
	0x1166, (uintptr_t)"e",   // ᅦ
	0x1167, (uintptr_t)"yeo", // ᅧ
	0x1168, (uintptr_t)"ye",  // ᅨ
	0x1169, (uintptr_t)"o",   // ᅩ
	0x116a, (uintptr_t)"wa",  // ᅪ
	0x116b, (uintptr_t)"wae", // ᅫ
	0x116c, (uintptr_t)"oe",  // ᅬ
	0x116d, (uintptr_t)"yo",  // ᅭ
	0x116e, (uintptr_t)"u",   // ᅮ
	0x116f, (uintptr_t)"wo",  // ᅯ
	0x1170, (uintptr_t)"we",  // ᅰ
	0x1171, (uintptr_t)"wi",  // ᅱ
	0x1172, (uintptr_t)"yu",  // ᅲ
	0x1173, (uintptr_t)"eu",  // ᅳ
	0x1174, (uintptr_t)"ui",  // ᅴ
	0x1175, (uintptr_t)"i",   // ᅵ
	// initial
	0x1100, (uintptr_t)"g",   // ᄀ
	0x1101, (uintptr_t)"kk",  // ᄁ
	0x1102, (uintptr_t)"n",   // ᄂ
	0x1103, (uintptr_t)"d",   // ᄃ
	0x1104, (uintptr_t)"tt",  // ᄄ
	0x1105, (uintptr_t)"r",   // ᄅ
	0x1106, (uintptr_t)"m",   // ᄆ
	0x1107, (uintptr_t)"b",   // ᄇ
	0x1108, (uintptr_t)"pp",  // ᄈ
	0x1109, (uintptr_t)"s",   // ᄉ
	0x110a, (uintptr_t)"ss",  // ᄊ
	0x110b, (uintptr_t)"",    // ᄋ
	0x110c, (uintptr_t)"j",   // ᄌ
	0x110d, (uintptr_t)"jj",  // ᄍ
	0x110e, (uintptr_t)"ch",  // ᄎ
	0x110f, (uintptr_t)"k",   // ᄏ
	0x1110, (uintptr_t)"t",   // ᄐ
	0x1111, (uintptr_t)"p",   // ᄑ
	0x1112, (uintptr_t)"h",   // ᄒ
	// final
	0x11a8, (uintptr_t)"k",   // ᆨ
	0x11a9, (uintptr_t)"k",   // ᆩ
	0x11ab, (uintptr_t)"n",   // ᆫ
	0x11ae, (uintptr_t)"t",   // ᆮ
	0x11af, (uintptr_t)"l",   // ᆯ
	0x11b7, (uintptr_t)"m",   // ᆷ
	0x11b8, (uintptr_t)"p",   // ᆸ
	0x11ba, (uintptr_t)"t",   // ᆺ
	0x11bb, (uintptr_t)"t",   // ᆻ
	0x11bc, (uintptr_t)"ng",  // ᆼ
	0x11bd, (uintptr_t)"t",   // ᆽ
	0x11be, (uintptr_t)"t",   // ᆾ
	0x11bf, (uintptr_t)"k",   // ᆿ
	0x11c0, (uintptr_t)"t",   // ᇀ
	0x11c1, (uintptr_t)"p",   // ᇁ
	0x11c2, (uintptr_t)"h",   // ᇂ

	0, 0,
};

static const uintptr_t pc_tbl[] = {
	// ᆨ
	0x11a8, 0x110b, (uintptr_t)"g", 0,
//	0x11a8, 0x1100, (uintptr_t)"kg", 0,
	0x11a8, 0x1102, (uintptr_t)"ngn", 0,
//	0x11a8, 0x1103, (uintptr_t)"kd", 0,
	0x11a8, 0x1105, (uintptr_t)"ngn", 0,
	0x11a8, 0x1106, (uintptr_t)"ngm", 0,
//	0x11a8, 0x1107, (uintptr_t)"kb", 0,
//	0x11a8, 0x1109, (uintptr_t)"ks", 0,
//	0x11a8, 0x110c, (uintptr_t)"kj", 0,
//	0x11a8, 0x110e, (uintptr_t)"kch", 0,
//	0x11a8, 0x110f, (uintptr_t)"kk", 0,
//	0x11a8, 0x1110, (uintptr_t)"kt", 0,
//	0x11a8, 0x1111, (uintptr_t)"kp", 0,
	0x11a8, 0x1112, (uintptr_t)"kh", (uintptr_t)"k", 0,
	// ᆫ
//	0x11ab, 0x110b, (uintptr_t)"n", 0,
//	0x11ab, 0x1100, (uintptr_t)"ng", 0,
//	0x11ab, 0x1102, (uintptr_t)"nn", 0,
//	0x11ab, 0x1103, (uintptr_t)"nd", 0,
	0x11ab, 0x1105, (uintptr_t)"ll", (uintptr_t)"nn", 0,
//	0x11ab, 0x1106, (uintptr_t)"nm", 0,
//	0x11ab, 0x1107, (uintptr_t)"nb", 0,
//	0x11ab, 0x1109, (uintptr_t)"ns", 0,
//	0x11ab, 0x110c, (uintptr_t)"nj", 0,
//	0x11ab, 0x110e, (uintptr_t)"nch", 0,
//	0x11ab, 0x110f, (uintptr_t)"nk", 0,
//	0x11ab, 0x1110, (uintptr_t)"nt", 0,
//	0x11ab, 0x1111, (uintptr_t)"np", 0,
//	0x11ab, 0x1112, (uintptr_t)"nh", 0,
	// ᆮ
	0x11ae, 0x110b, (uintptr_t)"d", (uintptr_t)"j", 0,
//	0x11ae, 0x1100, (uintptr_t)"tg", 0,
	0x11ae, 0x1102, (uintptr_t)"nn", 0,
//	0x11ae, 0x1103, (uintptr_t)"td", 0,
	0x11ae, 0x1105, (uintptr_t)"nn", 0,
	0x11ae, 0x1106, (uintptr_t)"nm", 0,
//	0x11ae, 0x1107, (uintptr_t)"tb", 0,
//	0x11ae, 0x1109, (uintptr_t)"ts", 0,
//	0x11ae, 0x110c, (uintptr_t)"tj", 0,
//	0x11ae, 0x110e, (uintptr_t)"tch", 0,
//	0x11ae, 0x110f, (uintptr_t)"tk", 0,
//	0x11ae, 0x1110, (uintptr_t)"tt", 0,
//	0x11ae, 0x1111, (uintptr_t)"tp", 0,
	0x11ae, 0x1112, (uintptr_t)"th", (uintptr_t)"t", (uintptr_t)"ch", 0,
	// ᆯ
	0x11af, 0x110b, (uintptr_t)"r", 0,
//	0x11af, 0x1100, (uintptr_t)"lg", 0,
	0x11af, 0x1102, (uintptr_t)"ll", (uintptr_t)"nn", 0,
//	0x11af, 0x1103, (uintptr_t)"ld", 0,
	0x11af, 0x1105, (uintptr_t)"ll", 0,
//	0x11af, 0x1106, (uintptr_t)"lm", 0,
//	0x11af, 0x1107, (uintptr_t)"lb", 0,
//	0x11af, 0x1109, (uintptr_t)"ls", 0,
//	0x11af, 0x110c, (uintptr_t)"lj", 0,
//	0x11af, 0x110e, (uintptr_t)"lch", 0,
//	0x11af, 0x110f, (uintptr_t)"lk", 0,
//	0x11af, 0x1110, (uintptr_t)"lt", 0,
//	0x11af, 0x1111, (uintptr_t)"lp", 0,
//	0x11af, 0x1112, (uintptr_t)"lh", 0,
	// ᆷ
//	0x11b7, 0x110b, (uintptr_t)"m", 0,
//	0x11b7, 0x1100, (uintptr_t)"mg", 0,
//	0x11b7, 0x1102, (uintptr_t)"mn", 0,
//	0x11b7, 0x1103, (uintptr_t)"md", 0,
	0x11b7, 0x1105, (uintptr_t)"mn", 0,
//	0x11b7, 0x1106, (uintptr_t)"mm", 0,
//	0x11b7, 0x1107, (uintptr_t)"mb", 0,
//	0x11b7, 0x1109, (uintptr_t)"ms", 0,
//	0x11b7, 0x110c, (uintptr_t)"mj", 0,
//	0x11b7, 0x110e, (uintptr_t)"mch", 0,
//	0x11b7, 0x110f, (uintptr_t)"mk", 0,
//	0x11b7, 0x1110, (uintptr_t)"mt", 0,
//	0x11b7, 0x1111, (uintptr_t)"mp", 0,
//	0x11b7, 0x1112, (uintptr_t)"mh", 0,
	// ᆸ
	0x11b8, 0x110b, (uintptr_t)"b", 0,
//	0x11b8, 0x1100, (uintptr_t)"pg", 0,
	0x11b8, 0x1102, (uintptr_t)"mn", 0,
//	0x11b8, 0x1103, (uintptr_t)"pd", 0,
	0x11b8, 0x1105, (uintptr_t)"mn", 0,
	0x11b8, 0x1106, (uintptr_t)"mm", 0,
//	0x11b8, 0x1107, (uintptr_t)"pb", 0,
//	0x11b8, 0x1109, (uintptr_t)"ps", 0,
//	0x11b8, 0x110c, (uintptr_t)"pj", 0,
//	0x11b8, 0x110e, (uintptr_t)"pch", 0,
//	0x11b8, 0x110f, (uintptr_t)"pk", 0,
//	0x11b8, 0x1110, (uintptr_t)"pt", 0,
//	0x11b8, 0x1111, (uintptr_t)"pp", 0,
	0x11b8, 0x1112, (uintptr_t)"ph", (uintptr_t)"p", 0,
	// ᆺ
	0x11ba, 0x110b, (uintptr_t)"s", 0,
//	0x11ba, 0x1100, (uintptr_t)"tg", 0,
	0x11ba, 0x1102, (uintptr_t)"nn", 0,
//	0x11ba, 0x1103, (uintptr_t)"td", 0,
	0x11ba, 0x1105, (uintptr_t)"nn", 0,
	0x11ba, 0x1106, (uintptr_t)"nm", 0,
//	0x11ba, 0x1107, (uintptr_t)"tb", 0,
//	0x11ba, 0x1109, (uintptr_t)"ts", 0,
//	0x11ba, 0x110c, (uintptr_t)"tj", 0,
//	0x11ba, 0x110e, (uintptr_t)"tch", 0,
//	0x11ba, 0x110f, (uintptr_t)"tk", 0,
//	0x11ba, 0x1110, (uintptr_t)"tt", 0,
//	0x11ba, 0x1111, (uintptr_t)"tp", 0,
	0x11ba, 0x1112, (uintptr_t)"th", (uintptr_t)"t", (uintptr_t)"ch", 0,
	// ᆼ
//	0x11bc, 0x110b, (uintptr_t)"ng", 0,
//	0x11bc, 0x1100, (uintptr_t)"ngg", 0,
//	0x11bc, 0x1102, (uintptr_t)"ngn", 0,
//	0x11bc, 0x1103, (uintptr_t)"ngd", 0,
	0x11bc, 0x1105, (uintptr_t)"ngn", 0,
//	0x11bc, 0x1106, (uintptr_t)"ngm", 0,
//	0x11bc, 0x1107, (uintptr_t)"ngb", 0,
//	0x11bc, 0x1109, (uintptr_t)"ngs", 0,
//	0x11bc, 0x110c, (uintptr_t)"ngj", 0,
//	0x11bc, 0x110e, (uintptr_t)"ngch", 0,
//	0x11bc, 0x110f, (uintptr_t)"ngk", 0,
//	0x11bc, 0x1110, (uintptr_t)"ngt", 0,
//	0x11bc, 0x1111, (uintptr_t)"ngp", 0,
//	0x11bc, 0x1112, (uintptr_t)"ngh", 0,
	// ᆽ
	0x11bd, 0x110b, (uintptr_t)"j", 0,
//	0x11bd, 0x1100, (uintptr_t)"tg", 0,
	0x11bd, 0x1102, (uintptr_t)"nn", 0,
//	0x11bd, 0x1103, (uintptr_t)"td", 0,
	0x11bd, 0x1105, (uintptr_t)"nn", 0,
	0x11bd, 0x1106, (uintptr_t)"nm", 0,
//	0x11bd, 0x1107, (uintptr_t)"tb", 0,
//	0x11bd, 0x1109, (uintptr_t)"ts", 0,
//	0x11bd, 0x110c, (uintptr_t)"tj", 0,
//	0x11bd, 0x110e, (uintptr_t)"tch", 0,
//	0x11bd, 0x110f, (uintptr_t)"tk", 0,
//	0x11bd, 0x1110, (uintptr_t)"tt", 0,
//	0x11bd, 0x1111, (uintptr_t)"tp", 0,
	0x11bd, 0x1112, (uintptr_t)"th", (uintptr_t)"t", (uintptr_t)"ch", 0,
	// ᆾ
	0x11be, 0x110b, (uintptr_t)"ch", 0,
//	0x11be, 0x1100, (uintptr_t)"tg", 0,
	0x11be, 0x1102, (uintptr_t)"nn", 0,
//	0x11be, 0x1103, (uintptr_t)"td", 0,
	0x11be, 0x1105, (uintptr_t)"nn", 0,
	0x11be, 0x1106, (uintptr_t)"nm", 0,
//	0x11be, 0x1107, (uintptr_t)"tb", 0,
//	0x11be, 0x1109, (uintptr_t)"ts", 0,
//	0x11be, 0x110c, (uintptr_t)"tj", 0,
//	0x11be, 0x110e, (uintptr_t)"tch", 0,
//	0x11be, 0x110f, (uintptr_t)"tk", 0,
//	0x11be, 0x1110, (uintptr_t)"tt", 0,
//	0x11be, 0x1111, (uintptr_t)"tp", 0,
	0x11be, 0x1112, (uintptr_t)"th", (uintptr_t)"t", (uintptr_t)"ch", 0,
	// ᇀ
	0x11c0, 0x110b, (uintptr_t)"t", (uintptr_t)"ch", 0,
//	0x11c0, 0x1100, (uintptr_t)"tg", 0,
	0x11c0, 0x1102, (uintptr_t)"nn", 0,
//	0x11c0, 0x1103, (uintptr_t)"td", 0,
	0x11c0, 0x1105, (uintptr_t)"nn", 0,
	0x11c0, 0x1106, (uintptr_t)"nm", 0,
//	0x11c0, 0x1107, (uintptr_t)"tb", 0,
//	0x11c0, 0x1109, (uintptr_t)"ts", 0,
//	0x11c0, 0x110c, (uintptr_t)"tj", 0,
//	0x11c0, 0x110e, (uintptr_t)"tch", 0,
//	0x11c0, 0x110f, (uintptr_t)"tk", 0,
//	0x11c0, 0x1110, (uintptr_t)"tt", 0,
//	0x11c0, 0x1111, (uintptr_t)"tp", 0,
	0x11c0, 0x1112, (uintptr_t)"th", (uintptr_t)"t", (uintptr_t)"ch", 0,
	// ᇂ
	0x11c2, 0x110b, (uintptr_t)"h", 0,
	0x11c2, 0x1100, (uintptr_t)"k", 0,
	0x11c2, 0x1102, (uintptr_t)"nn", 0,
	0x11c2, 0x1103, (uintptr_t)"t", 0,
	0x11c2, 0x1105, (uintptr_t)"nn", 0,
	0x11c2, 0x1106, (uintptr_t)"nm", 0,
	0x11c2, 0x1107, (uintptr_t)"p", 0,
	0x11c2, 0x1109, (uintptr_t)"hs", 0,
	0x11c2, 0x110c, (uintptr_t)"ch", 0,
//	0x11c2, 0x110e, (uintptr_t)"tch", 0,
//	0x11c2, 0x110f, (uintptr_t)"tk", 0,
//	0x11c2, 0x1110, (uintptr_t)"tt", 0,
//	0x11c2, 0x1111, (uintptr_t)"tp", 0,
	0x11c2, 0x1112, (uintptr_t)"t", 0,

	0, 0, 0,
};

#endif //__PHCH_TABLE_HPP__
