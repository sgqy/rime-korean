#include <algorithm>
#include "str_utils.hpp"

std::vector<uint16_t> u8_to_u16_vec (const char *s)
{
	return u8_to_u16_vec (std::string (s));
}

std::vector<uint16_t> u8_to_u16_vec (std::string s)
{
	auto ws = u8_to_u16_str (s);
	std::vector<uint16_t> lv (ws.begin(), ws.end());
	return lv;
}

std::u16string u8_to_u16_str (const char *s)
{
	return u8_to_u16_str (std::string (s));
}
std::u16string u8_to_u16_str (std::string s)
{
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.from_bytes (s);
}

// indexer for indefinite loop
struct product_property {
	std::vector<int> _len;
	std::vector<int> idx;
	bool valid = false;
	void add()
	{
		bool inc = true;

		for (int j = idx.size() - 1; j >= 0; --j) {
			if (inc) {
				++idx[j];
			}

			if (idx[j] == _len[j]) {
				idx[j] = 0;
				inc = true;
			} else {
				inc = false;
			}
		}

		int sum = 0;

		for (auto& j : idx) {
			sum += j;
		}

		if (sum == 0) {
			valid = false;
		}
	}
	void init (std::vector<std::vector<std::string>> c)
	{
		for (auto j = c.begin(); j != c.end(); ++j) {
			_len.push_back (j->size());
			idx.push_back (0);
		}

		valid = true;
	}
};

std::vector<std::string> str_product (std::vector<std::vector<std::string>> c)
{
	std::vector<std::string> ret;
	product_property p;

	for (p.init (c); p.valid; p.add()) {
		std::string tmp;

		for (int i = 0; i < c.size(); ++i) {
			tmp += c[i][p.idx[i]];
		}

		ret.push_back (tmp);
	}

	return ret;
}
