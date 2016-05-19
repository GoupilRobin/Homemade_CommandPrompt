#ifndef ustring_h_
#define ustring_h_

#include <string>

namespace std
{
	typedef std::basic_string<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> ustring;
}

#endif