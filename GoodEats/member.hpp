#ifndef MEMBER_H
#define MEMBER_H
#include <string>
#include <vector>
#include "recipe.hpp"
#include "shelve.hpp"
#include "global.hpp"
#include "filter.hpp"
using namespace std;



class Member
{
public:
	Member(string username_, string password_, int type_) : username(username_), password(password_), type(type_) {}
	
    bool varify_type(int type_);

	virtual void set_filter(vector<string>filter_base, int wich_filter) {}
	virtual void remove_filters() {}
	string get_username() { return username; }
	virtual bool varify_email(string email_) { return false; }

	bool varify_password(string password_);
	
	virtual void print_all_orders() {}
	virtual void pay_money(double total_price) {};
	virtual vector<Recipe*> filtering(const vector<Recipe*>& recipes) { return recipes; }
	virtual void add_recipes(Recipe *recipe) {}
	virtual void add_recipe_in_shelve(Shelve* shelf, Recipe* new_recipe) {}
	virtual void print_total_chef_info() {}
	virtual void remove_recipe(int id) {}
	virtual void remove_recipe_from_shelve(int shelf_id, int recipe_id) {}
	virtual void add_shelve(Shelve *newShelve) {}
	double get_money() { return money; }
	
	void increase_money(double money_){ money += money_; }
	virtual string get_brief_chef_info() { return SOMETHING; }

protected:
	double money = 0.0;
	string username;
	string password;
	int type;
};



class User : public Member
{
public:
	User(string username_, string password_, int type_) ;
	
	
	void pay_money(int total_price);
	
	void set_filter(vector<string>filter_base, int wich_filter);
	
	vector<Recipe*> filtering(const vector<Recipe*>& recipes);
	
	void remove_filters();
	
	void add_shelve(Shelve* new_shelve);
	
	void remove_recipe_from_shelve(int shelf_id, int recipe_id);
	
	void add_recipe_in_shelve(Shelve* shelf, Recipe* new_recipe);
	

	vector<string> get_shelves_info();

private:

	vector<Filter*>my_filters;
	vector<Shelve*>my_shelves;

};


class Chef : public Member
{
public:
	Chef(string username_, string password_, int type_) : Member(username_, password_, type_) {}
	void print_total_chef_info();
	
	string get_brief_chef_info();
	
	double get_rate();
	
	void add_recipes(Recipe* new_recipe);
	
	void remove_recipe(int id);
	
	vector<string> get_chef_recipes();

	
private:
	vector<Recipe*>my_recipes;
};



#endif