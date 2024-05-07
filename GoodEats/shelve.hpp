#ifndef SHELVE_H
#define SHELVE_H
#include <string>
#include <vector>
using namespace std;
class Recipe;
class Shelve
{
public:
	Shelve(int id_, string name_)
		: id(id_), name(name_) {}
	bool varify_id(int id_);
	
	string get_name();
	
	void add_new_recipe(Recipe* new_recipe);
	
	int find_recipe_index(int id_);
	
	vector<string> gather_recipes_info();



	void delete_recipe(int recipe_index);
	
	string get_info();
	

private:
	int id;
	string name;
	vector<Recipe *> recipes;
};





#endif