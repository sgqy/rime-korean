
#include <cstdio>
#include <cstring>

#include "str_utils.hpp"
#include "kr_utils.hpp"

int main (int argc, char **argv)
{
	auto set = get_word_roma (u8_to_u16_str (argv[1]));

	for (auto& s : set) {
		printf ("%s\n", s.c_str());
	}

	return 0;
}
