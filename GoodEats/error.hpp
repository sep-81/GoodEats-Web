#ifndef ERROR_H
#define ERROR_H
#include <string>
#include <iostream>
using namespace std;
class Error
{
public:
	Error() {}
	Error(string error)
		:error_text(error) {}
	void change_error(string error) { error_text = error; }
	string get_error() { return error_text; }
	void print_errors() { cout << error_text << endl; }

private:
	string error_text;
};

#endif