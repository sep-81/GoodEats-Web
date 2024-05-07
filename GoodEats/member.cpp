#include "member.hpp"
#include "filter.hpp"
#include "error.hpp"
#include <iomanip>

bool Member::varify_type(int type_)
	{
		if (type == type_)
			return true;
		return false;
	}

bool Member::varify_password(string password_)
	{
		if (password == password_)
			return true;
		return false;
	}




    User::User(string username_, string password_, int type_) : Member(username_, password_, type_)
	{
		my_filters.push_back(new Tag_filter());
		my_filters.push_back(new Veget_filter());
		my_filters.push_back(new Time_filter());
		my_filters.push_back(new Rate_filter());
	}

	
	void User::pay_money(int total_price)
	{
		if (money - total_price < 0)
			throw Error("Bad request");
		money -= total_price;
	}
	void User::set_filter(vector<string>filter_base, int wich_filter)
	{
		my_filters[wich_filter]->set_filter(filter_base);
	}
	vector<Recipe*> User::filtering(const vector<Recipe*>& recipes)
	{
		vector<Recipe*> filtered_recipes = recipes;
		for (int i = 0; i < my_filters.size(); i++)
		{
			filtered_recipes = my_filters[i]->filter_recipes(filtered_recipes);
		}
		return filtered_recipes;
	}
	void User::remove_filters()
	{
		for (int i = 0; i < my_filters.size(); i++)
		{
			my_filters[i]->clear();
		}
	}
	void User::add_shelve(Shelve* new_shelve)
	{
		my_shelves.push_back(new_shelve);
	}
	void User::remove_recipe_from_shelve(int shelf_id, int recipe_id)
	{
		int shelf_index = find_shelve_index(shelf_id, my_shelves);
		if (shelf_index == NOT_FOUND)
			throw Error("Permission Denied");
		int recipe_index = my_shelves[shelf_index]->find_recipe_index(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Bad Request");
		my_shelves[shelf_index]->delete_recipe(recipe_index);
	}
	

	void User::add_recipe_in_shelve(Shelve* shelf, Recipe* new_recipe)
	{
		for (int i = 0; i < my_shelves.size(); i++)
		{
			if (shelf == my_shelves[i])
			{
				shelf->add_new_recipe(new_recipe);
				return;
			}
		}
		throw Error("Permission Denied");
	}

	vector<string> User::get_shelves_info()
	{
		vector<string>shelves_info;
		for (int i = 0; i < my_shelves.size(); i++)
		{
			shelves_info.push_back(my_shelves[i]->get_info());
		}
		shelves_info = sort_strings(shelves_info, 0, ' ', false);
		return shelves_info;
	}




void Chef::print_total_chef_info()
	{
		cout << username << endl << fixed << setprecision(1) << round_preci_1(get_rate()) << endl
			<< "recipes:" << endl;
		vector<string> recipes_info;
	
		for (int i = 0; i < my_recipes.size(); i++)
		{
			recipes_info.push_back(my_recipes[i]->get_info_for_chef());
		}
		recipes_info = sort_strings(recipes_info, 1, ' ', true);
		cout << gather_strings(recipes_info);
	}
string Chef::get_brief_chef_info()
	{
		ostringstream info;
		double rate = get_rate();
		info << username << " " << fixed << setprecision(1) << round_preci_1(rate);
		return info.str();
	}
double Chef::get_rate()
	{
		double sum_of_rates = 0.0;
		double number_of_recipes = 0.0;
		for (int i = 0; i < my_recipes.size(); i++)
		{
			double rate = my_recipes[i]->get_ave_rate();
			if (rate == 0)
				continue;
			sum_of_rates += rate;
			number_of_recipes++;
		}
		return (number_of_recipes == 0) ? 0 : sum_of_rates / number_of_recipes;

	}
void Chef::add_recipes(Recipe* new_recipe)
	{
		my_recipes.push_back(new_recipe);
	}
void Chef::remove_recipe(int id)
	{
		for (int i = 0; i < my_recipes.size(); i++)
		{
			if (my_recipes[i]->varify_id(id))
			{
				my_recipes.erase(my_recipes.begin() + i);
				return;
			}
		}
		throw Error("Permission Denied");
	}
vector<string> Chef::get_chef_recipes()
	{
		vector<string> recipes_info;
		for (int i = 0; i < my_recipes.size(); i++)
		{
			recipes_info.push_back(my_recipes[i]->get_total_info());
		}
		if (recipes_info.empty())
			throw Error("Empty");

		return sort_strings(recipes_info, 1, ',', true);
	}






