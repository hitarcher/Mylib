#pragma once

#define __MY_SWITCHS_H__

#ifndef __MY_SWITCHS_H__
#define __MY_SWITCHS_H__

//////////////////////////////////////////////////////////////////////////
// �ο���https://stackoverflow.com/questions/4014827/how-can-i-compare-strings-in-c-using-a-switch-statement
//////////////////////////////////////////////////////////////////////////

#pragma comment(lib,"regex.lib") 

#include <string>
#include <regex.h>
#include <stdbool.h>

/** Begin a switch for the string x */
#define switchs(x) \
    { std::string __sw = (x); bool __done = false; bool __cont = false; \
        regex_t __regex; regcomp(&__regex, ".*", 0); do {

/** Check if the string matches the cases argument (case sensitive) */
#define cases(x)    } if ( __cont || !strcmp ( __sw.c_str(), x ) ) \
                        { __done = true; __cont = true;

/** Check if the string matches the icases argument (case insensitive) */
#define icases(x)    } if ( __cont || !strcasecmp ( __sw.c_str(), x ) ) { \
                        __done = true; __cont = true;

/** Check if the string matches the specified regular expression using regcomp(3) */
#define cases_re(x,flags) } regfree ( &__regex ); if ( __cont || ( \
                              0 == regcomp ( &__regex, x, flags ) && \
                              0 == regexec ( &__regex, __sw.c_str(), 0, NULL, 0 ) ) ) { \
                                __done = true; __cont = true;

/** Default behaviour */
#define defaults    } if ( !__done || __cont ) {

/** Close the switchs */
#define switchs_end } while ( 0 ); regfree(&__regex); }

#endif



#ifndef __MY_STRING__H__
#define __MY_STRING__H__

/************************************************************************/
/*                               base64                                 */
/************************************************************************/
/*
base64.cpp and base64.h

Copyright (C) 2004-2008 Ren�� Nyffenegger

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

Ren�� Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/

#include <string>
#include <assert.h>
using namespace::std;

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

inline
std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;
}

inline
std::string base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = (unsigned char)(base64_chars.find(char_array_4[i]));

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = (unsigned char)(base64_chars.find(char_array_4[j]));

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

/************************************************************************/
/*                                 ����                                 */
/************************************************************************/
// �ο���https://blog.csdn.net/netyeaxi/article/details/81036482
#include <string>
#include <locale>
#include <codecvt>

// string�ı��뷽ʽΪutf8������ã�
inline
std::string wstring2utf8string(const std::wstring& str)
{
	static std::wstring_convert<std::codecvt_utf8<wchar_t> > strCnv;
	return strCnv.to_bytes(str);
}

inline
std::wstring utf8string2wstring(const std::string& str)
{
	static std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
	return strCnv.from_bytes(str);
}

// string�ı��뷽ʽΪ��utf8����������뷽ʽ���ɲ��ã�
inline
std::string wstring2string(const std::wstring& str, const std::string& locale)
{
	typedef std::codecvt_byname<wchar_t, char, std::mbstate_t> F;
	static std::wstring_convert<F> strCnv(new F(locale));

	return strCnv.to_bytes(str);
}

inline
std::wstring string2wstring(const std::string& str, const std::string& locale)
{
	typedef std::codecvt_byname<wchar_t, char, std::mbstate_t> F;
	static std::wstring_convert<F> strCnv(new F(locale));

	return strCnv.from_bytes(str);
}

inline
unsigned char ToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

inline
unsigned char FromHex(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else assert(0);
	return y;
}

inline
std::string UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);
		}
	}
	return strTemp;
}

inline
std::string UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
}

inline
std::string easytoUTF(IN std::string bgk)
{
	std::wstring wgbk = string2wstring(bgk, "zh-CN");
	return wstring2utf8string(wgbk);
}

inline
std::string easytoGBK(IN std::string utf)
{
	std::wstring wutf = utf8string2wstring(utf);
	return wstring2string(wutf, "zh-CN");
}

// �ο���https://stackoverflow.com/questions/7369344/how-to-unescape-strings-in-c-c
// ȡ��ת��
/*
** Does not generate hex character constants.
** Always generates triple-digit octal constants.
** Always generates escapes in preference to octal.
** Escape question mark to ensure no trigraphs are generated by repetitive use.
** Handling of 0x80..0xFF is locale-dependent (might be octal, might be literal).
*/
inline
void chr_cstrlit(unsigned char u, char *buffer, size_t buflen)
{
	if (buflen < 2)
		*buffer = '\0';
	else if (isprint(u) && u != '\'' && u != '\"' && u != '\\' && u != '\?')
		sprintf(buffer, "%c", u);
	else if (buflen < 3)
		*buffer = '\0';
	else
	{
		switch (u)
		{
		case '\a':  strcpy(buffer, "\\a"); break;
		case '\b':  strcpy(buffer, "\\b"); break;
		case '\f':  strcpy(buffer, "\\f"); break;
		case '\n':  strcpy(buffer, "\\n"); break;
		case '\r':  strcpy(buffer, "\\r"); break;
		case '\t':  strcpy(buffer, "\\t"); break;
		case '\v':  strcpy(buffer, "\\v"); break;
		case '\\':  strcpy(buffer, "\\\\"); break;
		case '\'':  strcpy(buffer, "\\'"); break;
		case '\"':  strcpy(buffer, "\\\""); break;
		case '\?':  strcpy(buffer, "\\\?"); break;
		default:
			if (buflen < 5)
				*buffer = '\0';
			else
				// edit by mingl : ��Ϊ�����ģ����Դ˴�ֱ����
				buffer[0] = u;
			break;
		}
	}
}

inline
void str_cstrlit(const char *str, char *buffer, size_t buflen)
{
	unsigned char u;
	size_t len;

	while ((u = (unsigned char)*str++) != '\0')
	{
		chr_cstrlit(u, buffer, buflen);
		if ((len = strlen(buffer)) == 0)
			return;
		buffer += len;
		buflen -= len;
	}
	*buffer = '\0';
}

inline
std::string easyEscape(IN std::string cstring)
{
	const int bufflen = cstring.size() * 2 + 1;
	char* buff = new char[bufflen];
	memset(buff, 0x00, bufflen);
	str_cstrlit(cstring.c_str(), buff, bufflen);
	std::string tmp = buff;
	delete[] buff;
	return tmp;
}

/************************************************************************/
/*                                ����                                  */
/************************************************************************/
#include "json.hpp"
using json = nlohmann::json;

inline
json merge(const json &a, const json &b)
{
	json result = a.flatten();
	json tmp = b.flatten();

	for (json::iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		result[it.key()] = it.value();
	}

	return result.unflatten();
}

inline
std::string vstring(const char * format, ...)
{
	std::string result;
	va_list args, args_copy;

	va_start(args, format);
	va_copy(args_copy, args);

	int len = vsnprintf(nullptr, 0, format, args);
	if (len < 0) {
		va_end(args_copy);
		va_end(args);
		throw std::runtime_error("vsnprintf error");
	}

	if (len > 0) {
		result.resize(len);
		// note: &result[0] is *guaranteed* only in C++11 and later
		// to point to a buffer of contiguous memory with room for a
		// null-terminator, but this "works" in earlier versions
		// in *most* common implementations as well...
		vsnprintf(&result[0], len + 1, format, args_copy); // or result.data() in C++17 and later...
	}

	va_end(args_copy);
	va_end(args);

	return result;
}
#endif



