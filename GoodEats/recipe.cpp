#include "recipe.hpp"
#include "global.hpp"
#include "error.hpp"
#include <sstream>
#include <iomanip>
	Recipe::Recipe(int recipe_id, const vector<string>&command)
	{
		id = recipe_id;
		ingredients = divide_line(command[1], ',');
		tags = divide_line(command[4], ',');
		is_vegeterian = is_veget(command[2]);
		minutes_to_ready = stol(command[3]);
		title = command[0];
		image_address = command[5];
	}
	string Recipe::get_image()
	{
		return image_address;
	}
	bool Recipe::is_veget(string status) const
	{
		return (status == "No") ? false : true;
	}
	bool Recipe::varify_id(int id_) const
	{
		if (id == id_)
			return true;
		return false;
	}
	vector<string> Recipe::get_ingredients()
	{
		return ingredients;
	}
	string Recipe::get_total_info() const
	{
		ostringstream info;
		
		info << id << "," << title << "," << "vegetarian: " << is_veget(is_vegeterian) << ","
			<< "ingredients:," << gather_strings(ingredients, ",") << ","
			<< "minutes to ready: " << minutes_to_ready << "," << "tags:," << gather_strings(tags, ",") <<","
			<< "rating: " << fixed << setprecision(1) << round_preci_1(ave_rate) ;
		return info.str();
	}
	string Recipe::is_veget(bool status) const
	{
		return status ? "Yes" : "No";
	}
	string Recipe::get_info_for_chef() const
	{
		ostringstream line;
		line << id << ' ' << title << ' ' << is_veget(is_vegeterian) << ' ' << minutes_to_ready << ' ' << fixed
			<< setprecision(1) << round_preci_1(ave_rate) << "\n";
		return line.str();
	}

	string Recipe::get_brief_info() const
	{
		ostringstream line;
		line << id << ',' << title << ',' << is_veget(is_vegeterian) << ',' << minutes_to_ready;
		return line.str();
	}

	void Recipe::cal_total_rate()
	{
		double sum = 0;
		for (int i = 0; i < ratings.size(); i++)
		{
			sum += ratings[i].score;
		}
		ave_rate = (ratings.size() == 0) ? 0 : sum / ratings.size();
	}
	void Recipe::add_new_rating(double score, Member *new_rater)
	{
		if (find_rater_index(new_rater) != NOT_FOUND)
			throw Error("Bad Request");
		if (!is_score_valid(score))
			throw Error("Bad Request");
		ratings.push_back(Rating(score, new_rater));
		cal_total_rate();
	}
	int Recipe::find_rater_index(Member *new_rater) const
	{
		for (int i = 0; i < ratings.size(); i++)
			if (ratings[i].rater == new_rater)
				return i;
		return NOT_FOUND;
	}

	void Recipe::edit_rate(double score, Member *new_rater)
	{
		int rater_index = find_rater_index(new_rater);
		if (rater_index == NOT_FOUND)
			throw Error("Bad Request");
		if (!is_score_valid(score))
			throw Error("Bad Request");
		if (ratings[rater_index].score != score)
		{
			ratings[rater_index].score = score;
			cal_total_rate();
		}
	}

	bool Recipe::is_score_valid(double score) const
	{
		if (score < MIN_SCORE || score > MAX_SCORE)
			return false;
		return true;
	}
	bool Recipe::have_the_tag(string tag) const
	{
		for (int i = 0; i < tags.size(); i++)
		{
			if (tag == tags[i])
				return true;
		}
		return false;
	}
	bool Recipe::is_veget() const
	{
		return is_vegeterian;
	}
	bool Recipe::is_in_time_range(int min_time, int max_time) const
	{
		if (minutes_to_ready >= min_time && minutes_to_ready <= max_time)
			return true;
		return false;
	}
	bool Recipe::is_in_rate_range(double min_rate, double max_rate) const
	{
		if (ave_rate >= min_rate && ave_rate <= max_rate)
			return true;
		return false;
	}
	double Recipe::get_ave_rate()
	{
		return ave_rate;
	}