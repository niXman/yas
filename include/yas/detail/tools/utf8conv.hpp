// Copyright (c) 2009-2011 Avanesov Tigran:
// http://forum.vingrad.ru/index.php?showtopic=249965&view=findpost&p=1803380
// http://forum.vingrad.ru/index.php?showtopic=249965&view=findpost&p=1803439

#ifndef _yas__utf8conv_hpp__included_
#define _yas__utf8conv_hpp__included_

#include <string>
#include <sstream>
#include <typeinfo>

namespace yas {
namespace detail {

/***************************************************************************/

template <class To, class From>
class TypeConverter {
public:
	static To Convert(const From& from) {
		std::stringstream stream;
		stream << from;
		To value;
		//Check if stream is bad
		if ( stream.bad() )
		{
			throw std::bad_exception();
		}
		//Check if stream contains variable type you want to get
		if ((stream >> value).fail() || !stream.eof())
		{
			throw std::bad_cast();
		}
		return value;
	}
};
template <class From>
class TypeConverter<std::string, From>
{
public:
	static std::string Convert(const From& from) {
		std::stringstream stream;
		stream << from;
		return stream.str();
	}
};
template <>
class TypeConverter<std::string, std::string>
{
public:
	static std::string Convert(const std::string& from) {
		return from;
	}
};
template <>
class TypeConverter<std::string, std::wstring>
{
public:
	static std::string Convert(const std::wstring& from) {
		std::string result;
		for (std::wstring::const_iterator it = from.begin(); it != from.end(); ++it)
		{
			std::wstring::value_type nchar = *it;
			if (nchar <= 0x7F) {
				result += (char)*it;
			} else if (nchar <= 0x07FF) {
				result += (0xC0 | (nchar >> 6));
				result += (0x80 | (nchar & 0x3F));
			}
#if WCHAR_MAX > 0xffff
			else if (nchar <= 0xFFFF) {
				result += (0xE0 | (nchar >> 12));
				result += (0x80 | ((nchar >> 6) & 0x3F));
				result += (0x80 | (nchar & 0x3F));
			}
			else if (nchar  <= 0x1FFFFF) {
				result += (0xF0 | (nchar >> 18));
				result += (0x80 | ((nchar >> 12) & 0x3F));
				result += (0x80 | ((nchar >> 6) & 0x3F));
				result += (0x80 | (nchar & 0x3F));
			}
#endif
		}
		return result;
	}
};

template <>
class TypeConverter<std::wstring, std::string>
{
public:
	 static std::wstring Convert(const std::string& from) {
		  std::wstring result;
		  unsigned char nchar;
		  wchar_t tmp = 0;
		  for (std::string::const_iterator it = from.begin(); it != from.end(); ++it)
		  {
				nchar = (unsigned char)*it;
				if (nchar <= 0x7F) {
					 tmp = nchar;
				} else if ((nchar & 0xE0) == 0xC0) {
					 tmp = (nchar & 0x1F) << 6;
					 nchar = (unsigned char)*(++it);
					 tmp |= nchar & 0x3F;
				} else if ((nchar & 0xF0) == 0xE0) {
					 tmp = (nchar & 0x0F) << 12;
					 nchar = (unsigned char)*(++it);
					 tmp |= (nchar & 0x3F) << 6;
					 nchar = (unsigned char)*(++it);
					 tmp |= (nchar & 0x3F);
				} else if ((nchar & 0xF8) == 0xF0) {
					 tmp = (nchar & 0x0F) << 18;
					 nchar = (unsigned char)*(++it);
					 tmp |= (nchar & 0x3F) << 12;
					 nchar = (unsigned char)*(++it);
					 tmp |= (nchar & 0x3F) << 6;
					 nchar = (unsigned char)*(++it);
					 tmp |= (nchar & 0x3F);
				}
				result += tmp;
		  }
		  return result;
	 }
};

//lexical_cast function for all types which supports stream I/O
template <class T, class U>
T lexical_cast(const U& from) {
	return TypeConverter<T, U>::Convert( from );
}

/***************************************************************************/

} // namespace detail
} // namespace yas

#endif // _yas__utf8conv_hpp__included_
