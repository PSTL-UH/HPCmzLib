#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2018 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace some string methods, including
//	conversions to or from strings.
//----------------------------------------------------------------------------------------
#include <string>
#include <sstream>
#include <vector>
#include <exception>
#include <cctype>
#include <algorithm>
#include <tuple>
#include <unordered_set>
/***********************************************************************
// crc32 checksum
// adapted from free code by Mark Adler <madler@alumni.caltech.edu>
// see http://www.cdrom.com/pub/infozip/zlib/
************************************************************************/

/* workaround a cpp bug under hpux 10.20 */
#define PACX_0xffffffffL     4294967295ul

static const long int _crc32_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
    0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
    0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
    0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
    0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
    0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
    0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
    0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
    0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
    0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
    0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
    0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
    0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
    0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
    0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
    0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
    0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
    0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
    0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
    0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
    0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
    0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
    0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
    0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
    0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
    0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
    0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
    0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
    0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
    0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
    0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
    0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
    0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
    0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
    0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
    0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
    0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
    0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
    0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
    0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
    0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
    0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
    0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
    0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
    0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
    0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
    0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
    0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
    0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
    0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
    0x2d02ef8dL
};


#define _DO1(buf,i) \
    crc = _crc32_table[((int)crc ^ buf[i]) & 0xff] ^ (crc >> 8)

#define _DO2(buf,i)  _DO1(buf,i); _DO1(buf,i+1);
#define _DO4(buf,i)  _DO2(buf,i); _DO2(buf,i+2);
#define _DO8(buf,i)  _DO4(buf,i); _DO4(buf,i+4);
#define _DO16(buf,i) _DO8(buf,i); _DO8(buf,i+8);

class StringHelper
{
public:
        static int GetHashCode (std::tuple<std::string, std::string> st){
            std::string s0 = std::get<0>(st);
            std::string s1 = std::get<1>(st);
            return (GetHashCode(s0.c_str(), s0.length()) ^ GetHashCode(s1.c_str(), s1.length()));
        }
        static int GetHashCode ( std::vector<std::string> sv ) {
            int hash=0;
            for ( auto s: sv ) {
                hash = hash ^ GetHashCode(s);
            }
            return hash;
        }
        static int GetHashCode ( std::string s ) {
            return GetHashCode (s.c_str(), s.length());
        }
        static int GetHashCode ( const char *buf, size_t len ) {
            int crc = (0 & PACX_0xffffffffL) ^ PACX_0xffffffffL;

            if (buf == NULL) {
                return 0;
            }
            
            if (len >= 16) {
               do  {
                    _DO16(buf,0);
                    buf += 16;
                    len -= 16;
               } while (len >= 16);
            }
            if (len != 0) {
                do  {
                    _DO1(buf,0);
                    buf += 1;
                    len -= 1;
                } while (len > 0);
            }

            return crc ^ PACX_0xffffffffL;
        }
        static std::string toLower(std::string source)
	{
		std::transform(source.begin(), source.end(), source.begin(), ::tolower);
		return source;
	}

	static std::string toUpper(std::string source)
	{
		std::transform(source.begin(), source.end(), source.begin(), ::toupper);
		return source;
	}

	static std::string trimStart(std::string source, const std::string &trimChars = " \t\n\r\v\f")
	{
		return source.erase(0, source.find_first_not_of(trimChars));
	}

	static std::string trimEnd(std::string source, const std::string &trimChars = " \t\n\r\v\f")
	{
		return source.erase(source.find_last_not_of(trimChars) + 1);
	}

	static std::string trim(std::string source, const std::string &trimChars = " \t\n\r\v\f")
	{
		return trimStart(trimEnd(source, trimChars), trimChars);
	}

        static std::string stripUnicode( std::string source )
        {
            std::string result(source.length(), ' ');
            int j=0;
            for ( char c : source ) {                
                if ( c >= 0 && c <128 ) {
                    result[j] = c;
                    j++;
                }
            }
            return result;
        }
        
	static std::string replace(std::string source, const std::string &find, const std::string &replace)
	{
		size_t pos = 0;
		while ((pos = source.find(find, pos)) != std::string::npos)
		{
			source.replace(pos, find.length(), replace);
			pos += replace.length();
		}
		return source;
	}

	static bool startsWith(const std::string &source, const std::string &value)
	{
		if (source.length() < value.length())
			return false;
		else
			return source.compare(0, value.length(), value) == 0;
	}

	static bool endsWith(const std::string &source, const std::string &value)
	{
		if (source.length() < value.length())
			return false;
		else
			return source.compare(source.length() - value.length(), value.length(), value) == 0;
	}

	static std::vector<std::string> split(const std::string &source, char delimiter)
	{
		std::vector<std::string> output;
		std::istringstream ss(source);
		std::string nextItem;

		while (std::getline(ss, nextItem, delimiter))
		{
			output.push_back(nextItem);
		}

		return output;
	}

	static std::vector<std::string> split(const std::string &source, const std::string delimiter)
	{
		std::vector<std::string> output;
                size_t prev = 0, pos = 0;                

                do
                {
                    pos = source.find(delimiter, prev);
                    if (pos == std::string::npos) pos = source.length();
                    std::string token = source.substr(prev, pos-prev);
                    if (!token.empty()) output.push_back(token);
                    prev = pos + delimiter.length();
                }
                while (pos < source.length() && prev < source.length());
                
		return output;
	}

        

        static std::string join(const std::vector<std::string> &source, char delimiter)
        {
            std::string output;
            
            for ( auto s = source.begin(); s != source.end(); s++ ) {
                auto r = s + 1;
                if ( r == source.end() ) {
                    output += (*s);
                }
                else {
                    output += (*s) + std::to_string(delimiter);
                }
            }
            return output;
	}

        static std::string join(const std::unordered_set<std::string> &source, std::string delimiter)
        {
            std::string output;
            
            for ( auto s = source.begin(); s != source.end(); s++ ) {
                auto r = s;
                if ( ++r == source.end() ) {
                    output += (*s);
                }
                else {
                    output += (*s) + delimiter;
                }
            }
            return output;
	}

        
        static std::string join(const std::vector<std::string> &source, std::string &delimiter)
        {
            std::string output;
            
            for ( auto s = source.begin(); s != source.end(); s++ ) {
                auto r = s + 1;
                if ( r == source.end() ) {
                    output += (*s);
                }
                else {
                    output += (*s) + delimiter;
                }
            }
            return output;
	}

        
	template<typename T>
	static std::string toString(const T &subject)
	{
		std::ostringstream ss;
		ss << subject;
		return ss.str();
	}

	template<typename T>
	static T fromString(const std::string &subject)
	{
		std::istringstream ss(subject);
		T target;
		ss >> target;
		return target;
	}

	static bool isEmptyOrWhiteSpace(const std::string &source)
	{
		if (source.length() == 0)
			return true;
		else
		{
			for (long unsigned int index = 0; index < source.length(); index++)
			{
				if (!std::isspace(source[index]))
					return false;
			}

			return true;
		}
	}

	template<typename T>
	static std::string formatSimple(const std::string &input, T arg0)
	{
		std::ostringstream ss;
		int lastCloseBrace = -1;
		int openBrace = -1;
		while ((openBrace = input.find('{', openBrace + 1)) > -1)
		{
                    if ( (openBrace + 1) < (int) input.length())
			{
				if (input[openBrace + 1] == '{')
				{
					openBrace++;
					continue;
				}

				int closeBrace = input.find('}', openBrace + 1);
				if (closeBrace > -1)
				{
					ss << input.substr(lastCloseBrace + 1, openBrace - lastCloseBrace - 1);
					lastCloseBrace = closeBrace;

					std::string index = trim(input.substr(openBrace + 1, closeBrace - openBrace - 1));
					if (index == "0")
						ss << arg0;
					else
						throw std::runtime_error("Only simple positional format specifiers are handled by the 'formatSimple' helper method.");
				}
			}
		}

		if ( (lastCloseBrace + 1) < (int) input.length())
			ss << input.substr(lastCloseBrace + 1);

		return ss.str();
	}

	template<typename T1, typename T2>
	static std::string formatSimple(const std::string &input, T1 arg0, T2 arg1)
	{
		std::ostringstream ss;
		long int lastCloseBrace = -1;
		int openBrace = -1;
		while ((openBrace = input.find('{', openBrace + 1)) > -1)
		{
                    if ((long unsigned int)openBrace + 1 < input.length())
			{
				if (input[openBrace + 1] == '{')
				{
					openBrace++;
					continue;
				}

				int closeBrace = input.find('}', openBrace + 1);
				if (closeBrace > -1)
				{
					ss << input.substr(lastCloseBrace + 1, openBrace - lastCloseBrace - 1);
					lastCloseBrace = closeBrace;

					std::string index = trim(input.substr(openBrace + 1, closeBrace - openBrace - 1));
					if (index == "0")
						ss << arg0;
					else if (index == "1")
						ss << arg1;
					else
						throw std::runtime_error("Only simple positional format specifiers are handled by the 'formatSimple' helper method.");
				}
			}
		}

		if ((long unsigned int)(lastCloseBrace + 1) < input.length())
			ss << input.substr(lastCloseBrace + 1);

		return ss.str();
	}

	template<typename T1, typename T2, typename T3>
	static std::string formatSimple(const std::string &input, T1 arg0, T2 arg1, T3 arg2)
	{
		std::ostringstream ss;
		int lastCloseBrace = -1;
		int openBrace = -1;
		while ((openBrace = input.find('{', openBrace + 1)) > -1)
		{
                    if ((long unsigned int)(openBrace + 1) < input.length())
			{
				if (input[openBrace + 1] == '{')
				{
					openBrace++;
					continue;
				}

				int closeBrace = input.find('}', openBrace + 1);
				if (closeBrace > -1)
				{
					ss << input.substr(lastCloseBrace + 1, openBrace - lastCloseBrace - 1);
					lastCloseBrace = closeBrace;

					std::string index = trim(input.substr(openBrace + 1, closeBrace - openBrace - 1));
					if (index == "0")
						ss << arg0;
					else if (index == "1")
						ss << arg1;
					else if (index == "2")
						ss << arg2;
					else
						throw std::runtime_error("Only simple positional format specifiers are handled by the 'formatSimple' helper method.");
				}
			}
		}

		if ((long unsigned int)(lastCloseBrace + 1) < input.length())
			ss << input.substr(lastCloseBrace + 1);

		return ss.str();
	}
};
