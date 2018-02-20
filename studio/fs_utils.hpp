#ifndef __FS_UTILS_HPP__
#define __FS_UTILS_HPP__

#include <string>
#include <vector>

std::string read_file (const char *fn);
std::vector<std::string> read_lines (const char *fn);
void write_file (const char *fn, const std::string &str);

#endif /* __FS_UTILS_HPP__ */
