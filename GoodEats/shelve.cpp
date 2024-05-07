#include "shelve.hpp"
#include <sstream>
#include "error.hpp"
#include "global.hpp"
#include "recipe.hpp"
	bool Shelve::varify_id(int id_)
	{
		if (id == id_)
			return true;
		return false;
	}
	string Shelve::get_name()
	{
		return name;
	}
	void Shelve::add_new_recipe(Recipe* new_recipe)
	{
		for (int i = 0; i < recipes.size(); i++)
		{
			if (recipes[i] == new_recipe)
				throw Error("Bad Request");
		}
		recipes.push_back(new_recipe);
	}
	int Shelve::find_recipe_index(int id_)
	{
		for (int i = 0; i < recipes.size(); i++)
			if (recipes[i]->varify_id(id_))
				return i;
		return NOT_FOUND;
	}
	vector<string> Shelve::gather_recipes_info()
	{
		vector<string>recipes_info;
		for (int i = 0; i < recipes.size(); i++)
		{
			recipes_info.push_back(recipes[i]->get_brief_info());
		}
		return recipes_info;
	}


	void Shelve::delete_recipe(int recipe_index)
	{
		recipes.erase(recipes.begin() + recipe_index);
	}
	string Shelve::get_info()
	{
		stringstream info;
		info << id << " " << name ;
	
		return info.str();
	}
