#ifndef RECIPE_H
#define RECIPE_H
#include <string>
#include <vector>
using namespace std;
class Member;

struct Rating
{
	Rating(double score_, Member *rater_)
		: score(score_), rater(rater_) {}
	double score = 0.0;
	Member *rater;
	

};

class Recipe
{
public:

	Recipe(int recipe_id, const vector<string>&command);
	
	string get_image();
	
	bool is_veget(string status) const;
	
	bool varify_id(int id_) const;
	
	vector<string> get_ingredients();

	string get_total_info() const;
	
	string is_veget(bool status) const;

	string get_info_for_chef() const;
	

	string get_brief_info() const;
	

	void cal_total_rate();
	
	void add_new_rating(double score, Member *new_rater);
	
	int find_rater_index(Member *new_rater) const;
	

	void edit_rate(double score, Member *new_rater);


	bool is_score_valid(double score) const;
	
	bool have_the_tag(string tag) const;
	
	bool is_veget() const;

	bool is_in_time_range(int min_time, int max_time) const;
	
	bool is_in_rate_range(double min_rate, double max_rate) const;
	
	double get_ave_rate();
	
private:
	int id;
	string title;
	vector<string> ingredients;
	bool is_vegeterian;
	int minutes_to_ready;
	vector<string> tags;
	string image_address;
	double ave_rate = 0.0;
	vector<Rating > ratings;
	Member *chef;


};

#endif