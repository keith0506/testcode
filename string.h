#include <stdlib.h>
#include <cstring>
#include <iostream>
using namespace std;
class String
{
public:
	String(const char *str = NULL);
	String(const String &str);
	~String();
	String operator+(const String &str) const;
	String& operator=(const String &str);
	bool operator==(const String &str) const;

	int length() const{ return len; }
	friend ostream& operator<<(ostream &os, String &str);
private:
	char *data;
	int len;
};
//String shit = String("shit");
//cout<<shit.length();
//String shit = String("shit");
//String fuck = shit;
//String cock = fuck + shit;
