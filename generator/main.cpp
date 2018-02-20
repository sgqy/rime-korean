#include <cstdio>
#include <cstring>

#include "dic_entry.hpp"
#include "fs_utils.hpp"

static const char *dic_hdr =
    "# Dictionary of Korean romaji IME\n"
    "\n"
    "---\n"
    "name: roma_kr\n"
    "version: \"1.0\"\n"
    "sort: by_weight\n"
    "use_preset_vocabulary: false\n"
    "...\n"
    "\n";

int main (int argc, char **argv)
{
	if (argc != 4) {
		printf ("%s <word-dic> <hanja-dic> <rime-dic.yaml>\n", argv[0]);
		return 1;
	}
	dic_dealer d;
	printf ("Import word dic...\n");
	d.add_word_dic (argv[1]);
	printf ("Import hanja dic...\n");
	d.add_hanja_dic (argv[2]);
	d.generate();
	printf ("Get serialized table...\n");
	auto ser = d.get_result_ser();
	ser.insert (ser.begin(), std::string (dic_hdr));
	printf ("Write RIME dic...\n");
	write_lines (argv[3], ser);
	return 0;
}
