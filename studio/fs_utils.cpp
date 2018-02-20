#include <cstdio>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>

#include "fs_utils.hpp"

std::string read_file (const char *fn)
{
	FILE *fp = fopen (fn, "rb");
	if (fp == 0) {
		printf ("error: %s\n", fn);
		exit (1);
	}
	fseek (fp, 0, SEEK_END);
	int len = ftell (fp);
	char *buf = new char[len];
	fseek (fp, 0, SEEK_SET);
	fread (buf, len, 1, fp);
	fclose (fp);
	std::string str (buf, len);
	delete[] buf;
	return str;
}

std::vector<std::string> read_lines (const char *fn)
{
	auto txt = read_file (fn);
	std::vector<std::string> lines;
	boost::algorithm::split_regex (lines, txt, boost::regex ("\n"));
	return lines;
}

void write_file (const char *fn, const std::string &str)
{
	FILE *fp = fopen (fn, "wb");
	if (fp == 0) {
		printf ("error: %s\n", fn);
		exit (1);
	}
	fwrite (str.c_str(), str.size(), 1, fp);
	fclose (fp);
}
