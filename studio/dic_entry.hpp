#ifndef __DIC_ENTRY_HPP__
#define __DIC_ENTRY_HPP__

#include <string>
#include <set>
#include <vector>
#include <utility>

struct dic_entry {
	std::string word;
	std::set<std::string> roma;
	int weight = 0;
};

class dic_dealer
{
	typedef std::pair<std::string, std::string> hanja_pair;
	std::vector<hanja_pair> hanja_dic;
	std::set<std::string> word_dic;
	std::vector<dic_entry> result;
public:
	void add_word_dic (const char *fn);
	void add_hanja_dic (const char *fn);
	void generate();
	std::vector<dic_entry> get_result();
	std::vector<std::string> get_result_ser();
};

#endif /* __DIC_ENTRY_HPP__ */
