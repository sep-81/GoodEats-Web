#ifndef FILTER_H
#define FILTER_H
#include <string>
#include <vector>
#include "recipe.hpp"
using namespace std;

class Filter
{
public:
	virtual void set_filter(vector<string>filter_base) = 0;
	virtual vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes) = 0;
	virtual void clear() { is_filter_set = false; }
protected:
	bool is_filter_set = false;
};

class Tag_filter : public Filter
{
public:
	void set_filter(vector<string>filter_base);
	
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes);
	

private:
	string tag;

};

class Veget_filter : public Filter
{
public:
	void set_filter(vector<string>filter_base);
	
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes);


private:


};

class Time_filter : public Filter
{
public:
	void set_filter(vector<string>filter_base);
	
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes);

private:

	int min_time;
	int max_time;

};

class Rate_filter : public Filter
{
public:
	void set_filter(vector<string>filter_base);
	
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes);
	
private:
	int min_rate;
	int max_rate;

};



#endif