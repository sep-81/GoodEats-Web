#include "global.hpp"
#include <sstream>
#include <cmath>
#include <algorithm>
#include "shelve.hpp"
const vector<string> divide_line(const string& line, char divider)
{
	vector<string> divided_line;
	string argument;
	istringstream arguments(line);
	while (getline(arguments, argument, divider)) {
		if (argument == "")
			continue;
		divided_line.push_back(argument);
	}
	return divided_line;
}

bool is_number(string number)
{
	size_t lenght;
	stod(number, &lenght);
	return (lenght == number.size()) ? true : false;
}

double round_preci_1(double number)
{
	number *= 10;
	number = ceil(number);
	number /= 10;
	return number;
}
int find_index(string target, const vector<string> &range) {
	for (int i = 0; i < range.size(); i++)
		if (target == range[i]) return i + 1;
	return NOT_FOUND;
}

int find_index(int target, const vector<int> &range) {
	for (int i = 0; i < range.size(); i++)
		if (target == range[i]) return i + 1;
	return NOT_FOUND;
}

vector<string> sort_strings(const vector<string> &entry, int which_index, char divider, bool by_string)
{
	vector<string> result, result_;
	vector<int> result_int;
	int argument_;
	for (int i = 0; i < entry.size(); i++) {
		string argument = divide_line(entry[i], divider)[which_index];
		result_.push_back(argument);
		int index_of_element;
		if (!by_string)
		{
			argument_ = stol(argument);
			result_int.push_back(argument_);
			sort(result_int.begin(), result_int.end());
			index_of_element = find_index(argument_, result_int);
		}
		else
		{
			sort(result_.begin(), result_.end());
			index_of_element = find_index(argument, result_);
		}
		result.insert(result.begin() + (index_of_element - 1), entry[i]);
	}
	return result;
}

string gather_strings(const vector<string>& entry, string divider) {
	string all;
	for (int i = 0; i < entry.size(); i++) {
		all += entry[i];
		if (i != entry.size() - 1)
			all += divider;
	}
	return all;
}


int find_shelve_index(int shelve_id, const vector<Shelve*>&shelves)
{
	for (int i = 0; i < shelves.size(); i++)
		if (shelves[i]->varify_id(shelve_id))
			return i;
	return NOT_FOUND;
}


bool is_it_int(double number)
{
	return (number - floor(number) == 0) ? true : false;
}