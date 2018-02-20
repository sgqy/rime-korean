#include <cstdio>
#include <cstring>

#include "dic_entry.hpp"

int main (int argc, char **argv)
{
	dic_dealer d;
	d.add_word_dic (argv[1]);
	d.add_hanja_dic (argv[2]);
	d.generate();
	auto set = d.get_result_ser();
	for (auto &s : set) {
		printf ("%s\n", s.c_str());
	}

	return 0;
}
