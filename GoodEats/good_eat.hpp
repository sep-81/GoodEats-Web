#ifndef GOOD_EAT_H
#define GOOD_EAT_H
#include <string>
#include <vector>
#include "error.hpp"
#include "global.hpp"
#include "member.hpp"
#include "recipe.hpp"
#include "shelve.hpp"

using namespace std;

class Good_eat
{
public:
string process(string line);

int get_type();

string get_username();

vector<string> get_all_recipes();

string get_recipe(string rec_id);

string get_recipe_img(string recipe_id);

vector<string> get_shelves();
	
string post_shelve(string shelf_name);
	
string post_recipe(const vector<string>&command);
	
string get_shelf_name(string shelf_id);
	
vector<string> get_shelve_recipes(string shelf_id);
	
vector<string> get_my_recipes();
	
private:
	Member *in_site_member = NULL;
	vector<Member*>all_members;
	vector<Recipe*>all_recipes;
	vector<Shelve*>all_shelves;
	
	int last_recipe_id = 0;
	int last_shelve_id = 0;

	void manu(const vector<string>&command);
	


	void which_registering_commands(const vector<string>&command, int which_command);
	

	void which_user_commands(const vector<string>&command, int which_command);


	void which_chef_commands(const vector<string>&command, int which_command);
	
	
	
	int find_command(const vector<string>&command);
	
	
	
	void put_credit(const vector<string>&command);
	
	void get_orders();
	

	
	int find_member(string username);
	
	void signup(const vector<string>&command);
	
	void logout();

	void login(const vector<string>&command);

	
	int find_email(string email);

	
	
	void supplier_login(const vector<string>&command);
	
	
	void get_credit();

	int find_recipe(int recipe_id);
	
	void post_rate(const vector<string>&command);


	void print_id(int id);
	
	void post_tag_filter(const vector<string>&command);
	
	void post_veget_filter(const vector<string>&command);

	void post_time_filter(const vector<string>&command);
	

	void post_rate_filter(const vector<string>&command);
	

	void get_all_chefs();

	void get_chef(const vector<string>&command);

	void get_users();

	void put_rate(const vector<string>&command);

	void put_shelve_recipe(const vector<string>&command);


	void delete_filters();

	void delete_shelve_recipe(const vector<string>&command);
		
	void delete_recipes(const vector<string>&command);
	
};





#endif