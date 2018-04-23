#include "string.h"
String::String(const char *str)
{
	if(str == NULL)
	{
		len = 0;
		data = new char[1];
		*data = 0;
	}
	else
	{
		len = strlen(str);
		data = new char[len + 1];
		strcpy(data, str);
	}
}
String::String(const String &str)
{
	len = str.length();
	data = new char[len + 1];
	strcpy(data, str.data);
}
String::~String()
{
	delete []data;
	len = 0;
}
String& String::operator=(const String &str)
{
	if(this == &str) return *this;
	delete []data;
	len = str.length();
	data = new char[len + 1];
	strcpy(data, str.data);
	return *this;
}
String String::operator+(const String &str) const
{
	String newString;
	newString.len = str.length() + len;
	newString.data = new char[newString.len + 1];
	strcpy(newString.data, this->data);
	strcat(newString.data, str.data);
	return newString;
}
inline bool String::operator==(const String &str) const
{
	if(len != str.len) return false;
	return strcmp(data, str.data) ? false : true;
}
ostream& operator<<(ostream &os, String &str)
{
	os << str.data;
	return os;
}
