#include "dic_entry.hpp"
#include "kr_utils.hpp"
#include "fs_utils.hpp"
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>

void dic_dealer::add_word_dic (const char *fn)
{
	auto words = read_lines (fn);
	word_dic.insert (words.begin(), words.end());
}

void dic_dealer::add_hanja_dic (const char *fn)
{
	auto pairs_str = read_lines (fn);
	for (auto &s : pairs_str) {
		std::vector<std::string> lines;
		boost::algorithm::split_regex (lines, s, boost::regex (":"));
		if (lines.size() >= 2) {
			word_dic.insert (lines[0]); // also add to syllable dictionary
			hanja_pair p (lines[0], lines[1]);
			hanja_dic.push_back (p);
		}
	}
}

void dic_dealer::generate()
{
	printf ("Step 1: Generate for syllable dictionary...\n");
	for (auto &s : word_dic) {
		if (s.size() == 0) {
			continue;
		}
		dic_entry e;
		e.word = s;
		e.roma = get_word_roma (s);
		result.push_back (e);
	}

	printf ("Step 2: Generate for hanja dictionary...\n");
	for (auto &s : hanja_dic) {
		dic_entry e;
		e.word = s.second;
		e.roma = get_word_roma (s.first);
		result.push_back (e);
	}
}

std::vector<dic_entry> dic_dealer::get_result()
{
	return result;
}

std::vector<std::string> dic_dealer::get_result_ser()
{
	std::vector<std::string> ret;
	printf ("Generate RIME dict format strings...\n");
	for (auto &e : result) {
		for (auto &r : e.roma) {
			std::string tmp;
			tmp += e.word;
			tmp += "\t";
			tmp += r;
			tmp += "\t";
			tmp += std::to_string (e.weight);
			ret.push_back (tmp);
		}
	}
	return ret;
}
