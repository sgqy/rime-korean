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
