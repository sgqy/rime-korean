
#include <cstdio>
#include <cstring>
#include <locale>
#include <codecvt>
#include "utils.hpp"

int main(int argc, char **argv)
{
	std::string in = argv[1];
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	std::u16string dest = convert.from_bytes(in);

	std::vector<uint16_t> line;
	line.push_back(0xac15);
	line.push_back(0xd64d);
	line.push_back(0xb9bd);

	auto set = get_roma(dest);
	for(auto &s : set) {
		printf("%s\n", s.c_str());
	}

	return 0;
}
