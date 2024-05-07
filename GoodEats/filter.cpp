#include "filter.hpp"
#include "global.hpp"
#include "error.hpp"
void Tag_filter::set_filter(vector<string>filter_base)
	{
		tag = filter_base[0];
		is_filter_set = true;
	}
vector<Recipe*> Tag_filter::filter_recipes(const vector<Recipe*>& recipes)
	{
		vector<Recipe*> filtered_recipes;
		if (!is_filter_set)
			return  recipes;
		for (int i = 0; i < recipes.size(); i++)
		{
			if (recipes[i]->have_the_tag(tag))
				filtered_recipes.push_back(recipes[i]);
		}
		return filtered_recipes;
	}



void Veget_filter::set_filter(vector<string>filter_base)
	{
		is_filter_set = true;
	}
vector<Recipe*> Veget_filter::filter_recipes(const vector<Recipe*>& recipes)
	{
		vector<Recipe*> filtered_recipes;
		if (!is_filter_set)
			return recipes;
		for (int i = 0; i < recipes.size(); i++)
		{
			if (recipes[i]->is_veget())
				filtered_recipes.push_back(recipes[i]);
		}
		return filtered_recipes;
	}




void Time_filter::set_filter(vector<string>filter_base)
	{
		int temp_min = stol(filter_base[0]);
		int temp_max = stol(filter_base[1]);
		if (temp_min > temp_max || temp_min < 0)
			throw Error("Bad Request");
		min_time = temp_min;
		max_time = temp_max;
		is_filter_set = true;
	}
vector<Recipe*> Time_filter::filter_recipes(const vector<Recipe*>& recipes)
	{
		vector<Recipe*> filtered_recipes;
		if (!is_filter_set)
			return recipes;
		for (int i = 0; i < recipes.size(); i++)
		{
			if (recipes[i]->is_in_time_range(min_time, max_time))
				filtered_recipes.push_back(recipes[i]);
		}
		return filtered_recipes;
	}




void Rate_filter::set_filter(vector<string>filter_base)
	{
		int temp_min = stol(filter_base[0]);
		int temp_max = stol(filter_base[1]);
		if (temp_min > temp_max || temp_min < MIN_SCORE - 1 || temp_max > MAX_SCORE)
			throw Error("Bad Request");
		min_rate = temp_min;
		max_rate = temp_max;
		is_filter_set = true;
	}
vector<Recipe*> Rate_filter::filter_recipes(const vector<Recipe*>& recipes)
	{
		vector<Recipe*> filtered_recipes;
		if (!is_filter_set)
			return recipes;
		for (int i = 0; i < recipes.size(); i++)
		{
			if (recipes[i]->is_in_rate_range(min_rate, max_rate))
				filtered_recipes.push_back(recipes[i]);
		}
		return filtered_recipes;
	}