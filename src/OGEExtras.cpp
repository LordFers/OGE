#include <stdarg.h>
#include <memory>
#include <cstring>
#include <windows.h>

#include "OGEExtras.hpp"

namespace vb6 {

//App_t App_t::Instance;
Err_t Err_t::Instance;

std::string string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* reserve 2 times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

std::vector <std::string> split(std::string src, char delim)
{
	src += '\0'; //ésto es un parche re trucho, arreglar el código de abajo.

	std::vector <std::string> ret;
	std::string tempval;
	for (std::string::iterator i = src.begin(); i < src.end(); i++)
	{
		if (*i == delim)
		{
			ret.push_back(tempval);
			tempval.clear();
		}
		else
			tempval.push_back(*i);
	}
	return ret;
}

void Name(std::string oldName, std::string newName) {
	// Rename a file
	// throw std::runtime_error("Name not implemented");
	// boost::system::error_code ec;
    rename(oldName.c_str(), newName.c_str());
}

void Kill(std::string FileName) {
    DeleteFile(LPCWSTR(FileName.c_str()));
}

void FileCopy(std::string oldfile, std::string newfile) {
    CopyFile(LPCWSTR (oldfile.c_str()), LPCWSTR (newfile.c_str()), FALSE);
}


}

