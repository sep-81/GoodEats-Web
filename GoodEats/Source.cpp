#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;
class Member;
class Recipe;
class Chef;
class User;
class Shelve;

enum filters
{
	tag_filter = 0,
	veget_filter,
	time_filter,
	rate_fliter
};
enum member
{
	CHEF = 1,
	USER = 2,
	SUPPLIER = 3
};
const double DISCOUNT = 0.9;
const int ON_DISCOUNT = 1;
const int OUT_OF_DISCOUNT = 2;
const int DISCOUNT_LIMIT = 20;
const int PRINT_OK = 1;
const int NOT_PRINT_OK = 2;
const int MAX_SCORE = 5;
const int MIN_SCORE = 1;
const string SOMETHING = "";
const string YES_OR_NO = " ";
const string A_NUMBER = "1.1";
const string AN_INTEGER = "2";
const int NOT_FOUND = -2;
const int FOUND = -1;
const vector<vector<string>> COMMANDS = {
	{ "POST", "signup", "?", "username", SOMETHING, "password", SOMETHING, "type", SOMETHING },
	{ "POST", "login", "?", "username", SOMETHING, "password", SOMETHING },
	{ "POST", "logout" },
	{ "POST", "recipes", "?", "title", SOMETHING, "ingredients", SOMETHING, "vegetarian", YES_OR_NO, "minutes_to_ready", A_NUMBER, "tags", SOMETHING, "image_address", SOMETHING },
	{ "POST", "rates", "?", "recipe_id", AN_INTEGER, "score", A_NUMBER },
	{ "POST", "shelves", "?", "name", SOMETHING },
	{ "POST", "filters", "?", "tag", SOMETHING },
	{ "POST", "filters", "?", "vegetarian" },
	{ "POST", "filters", "?", "min-minutes", A_NUMBER, "max-minutes", A_NUMBER },
	{ "POST", "filters", "?", "min_rating", A_NUMBER, "max_rating", A_NUMBER },
	{ "GET", "recipes" },
	{ "GET", "recipes", "?", "id", AN_INTEGER },
	{ "GET", "shelves", "?", "username", SOMETHING, "limit", AN_INTEGER },
	{ "GET", "shelves_recipes", "?", "shelf_id", AN_INTEGER },
	{ "GET", "chefs" },
	{ "GET", "chefs", "?", "chef_username", SOMETHING },
	{ "GET", "users" },
	{ "GET", "my_recipes" },
	{ "PUT", "rates", "?", "recipe_id", AN_INTEGER, "score", A_NUMBER },
	{ "PUT", "shelves_recipes", "?", "shelf_id", AN_INTEGER, "recipe_id", AN_INTEGER },
	{ "DELETE", "recipes", "?", "id", AN_INTEGER },
	{ "DELETE", "filters" },
	{ "DELETE", "shelves_recipes", "?", "shelf_id", AN_INTEGER, "recipe_id", AN_INTEGER },
	{"POST", "signup_supplier", "?", "name", SOMETHING, "email", SOMETHING, "password", SOMETHING},
	{ "POST", "offers", "?", "ingredient", SOMETHING, "price", A_NUMBER, "count", AN_INTEGER, "packaging", A_NUMBER },
	{ "PUT", "offers", "?", "ingredient", SOMETHING, "price", A_NUMBER, "count", AN_INTEGER },
	{ "DELETE", "offers", "?", "ingredient", SOMETHING },
	{ "GET", "credits" },
	{ "PUT", "credits", "?", "money", A_NUMBER },
	{ "POST", "orders", "?", "recipe_id", AN_INTEGER },
	{ "GET", "orders" },
	{ "POST", "login", "?", "email", SOMETHING, "password", SOMETHING }
};

enum Post_Commands
{
	SIGNUP = 1,
	LOGIN = 2,
	LOGOUT = 3,
	POST_RECIPES = 4,
	POST_RATES = 5,
	POST_SHELVE = 6,
	POST_TAG_FILTER = 7,
	POST_VEGET_FILTER = 8,
	POST_TIME_FILTER = 9,
	POST_RATE_FILTER = 10,
	GET_RECIPES_VER_1 = 11,
	GET_RECIPES_VER_2 = 12,
	GET_SHELVES = 13,
	GET_SHELVES_RECIPES = 14,
	GET_CHEFS_VER_1 = 15,
	GET_CHEFS_VER_2 = 16,
	GET_USERS = 17,
	GET_MY_RECIPES = 18,
	PUT_RATES = 19,
	PUT_SHELVES_RECIPES = 20,
	DELETE_RECIPES = 21,
	DELETE_FILTERS = 22,
	DELETE_SHELVES_RECIPES = 23,
	SUPPLIER_SIGNUP = 24,
	POST_OFFERS = 25,
	PUT_OFFERS = 26,
	DELETE_OFFERS = 27,
	GET_CREDITS = 28,
	PUT_CREDITS = 29,
	POST_ORDERS = 30,
	GET_ORDERS = 31,
	SUPPLIER_LOGIN = 32
};

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

string gather_strings(const vector<string>& entry, string divider = "") {
	string all;
	for (int i = 0; i < entry.size(); i++) {
		all += entry[i];
		if (i != entry.size() - 1)
			all += divider;
	}
	return all;
}

class Order;
class Offer;
class Supplier;

class Error
{
public:
	Error() {}
	Error(string error)
		:error_text(error) {}
	void change_error(string error) { error_text = error; }
	string get_error() { return error_text; }
	void print_errors() { cout << error_text << endl; }

private:
	string error_text;
};
struct Rating
{
	Rating(double score_, Member *rater_)
		: score(score_), rater(rater_) {}
	double score = 0.0;
	Member *rater;
	//Member *chef;
	//Recipe *recipe;

};
class Recipe
{
public:
	//Recipe(int id_, string title_, vector<string> ingredients_, bool isVegeterian_, int minutes_to_ready_, vector<string> tags_, string imageAddress_, Member *chef_)
	//	: id(id_), title(title_), ingredients(ingredients_), is_vegeterian(isVegeterian_),
	//	minutes_to_ready(minutes_to_ready_), tags(tags_), image_address(imageAddress_), chef(chef_) {}
	Recipe(int shelf_id, const vector<string>&command)
	{
		id = shelf_id;
		ingredients = divide_line(command[6], ',');
		tags = divide_line(command[12], ',');
		is_vegeterian = is_veget(command[8]);
		minutes_to_ready = stol(command[10]);
		title = command[4];
		image_address = command[14];
	}
	bool is_veget(string status) const
	{
		return (status == "No") ? false : true;
	}
	bool varify_id(int id_) const
	{
		if (id == id_)
			return true;
		return false;
	}
	vector<string> get_ingredients()
	{
		return ingredients;
	}
	string get_total_info() const
	{
		ostringstream info;
		info << id << endl << title << endl << "vegetarian: " << is_veget(is_vegeterian) << endl
			<< "ingredients: [" << gather_strings(ingredients, ", ") << ']' << endl
			<< "minutes to ready: " << minutes_to_ready << endl << "tags: [" << gather_strings(tags, ", ") << ']' << endl
			<< "rating: " << fixed << setprecision(1) << round_preci_1(ave_rate) << endl;
		return info.str();
	}
	string is_veget(bool status) const
	{
		return status ? "Yes" : "No";
	}
	string get_info_for_chef() const
	{
		ostringstream line;
		line << id << ' ' << title << ' ' << is_veget(is_vegeterian) << ' ' << minutes_to_ready << ' ' << fixed
			<< setprecision(1) << round_preci_1(ave_rate) << "\n";
		return line.str();
	}

	string get_brief_info() const
	{
		ostringstream line;
		line << id << ' ' << title << ' ' << is_veget(is_vegeterian) << ' ' << minutes_to_ready;
		return line.str();
	}

	void cal_total_rate()
	{
		double sum = 0;
		for (int i = 0; i < ratings.size(); i++)
		{
			sum += ratings[i].score;
		}
		ave_rate = (ratings.size() == 0) ? 0 : sum / ratings.size();
	}
	void add_new_rating(double score, Member *new_rater)
	{
		if (find_rater_index(new_rater) != NOT_FOUND)
			throw Error("Bad Request");
		if (!is_score_valid(score))
			throw Error("Bad Request");
		ratings.push_back(Rating(score, new_rater));
		cal_total_rate();
	}
	int find_rater_index(Member *new_rater) const
	{
		for (int i = 0; i < ratings.size(); i++)
			if (ratings[i].rater == new_rater)
				return i;
		return NOT_FOUND;
	}

	void edit_rate(double score, Member *new_rater)
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

	bool is_score_valid(double score) const
	{
		if (score < MIN_SCORE || score > MAX_SCORE)
			return false;
		return true;
	}
	bool have_the_tag(string tag) const
	{
		for (int i = 0; i < tags.size(); i++)
		{
			if (tag == tags[i])
				return true;
		}
		return false;
	}
	bool is_veget() const
	{
		return is_vegeterian;
	}
	bool is_in_time_range(int min_time, int max_time) const
	{
		if (minutes_to_ready >= min_time && minutes_to_ready <= max_time)
			return true;
		return false;
	}
	bool is_in_rate_range(double min_rate, double max_rate) const
	{
		if (ave_rate >= min_rate && ave_rate <= max_rate)
			return true;
		return false;
	}
	double get_ave_rate()
	{
		return ave_rate;
	}

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
	void set_filter(vector<string>filter_base)
	{
		tag = filter_base[0];
		is_filter_set = true;
	}
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes)
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

private:
	string tag;

};

class Veget_filter : public Filter
{
public:
	void set_filter(vector<string>filter_base)
	{
		is_filter_set = true;
	}
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes)
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

private:


};

class Time_filter : public Filter
{
public:
	void set_filter(vector<string>filter_base)
	{
		int temp_min = stol(filter_base[0]);
		int temp_max = stol(filter_base[1]);
		if (temp_min > temp_max || temp_min < 0)
			throw Error("Bad Request");
		min_time = temp_min;
		max_time = temp_max;
		is_filter_set = true;
	}
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes)
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
private:

	int min_time;
	int max_time;

};

class Rate_filter : public Filter
{
public:
	void set_filter(vector<string>filter_base)
	{
		int temp_min = stol(filter_base[0]);
		int temp_max = stol(filter_base[1]);
		if (temp_min > temp_max || temp_min < MIN_SCORE - 1 || temp_max > MAX_SCORE)
			throw Error("Bad Request");
		min_rate = temp_min;
		max_rate = temp_max;
		is_filter_set = true;
	}
	vector<Recipe*> filter_recipes(const vector<Recipe*>& recipes)
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
private:
	int min_rate;
	int max_rate;

};

class Shelve
{
public:
	Shelve(int id_, string name_)
		: id(id_), name(name_) {}
	bool varify_id(int id_)
	{
		if (id == id_)
			return true;
		return false;
	}
	void add_new_recipe(Recipe* new_recipe)
	{
		for (int i = 0; i < recipes.size(); i++)
		{
			if (recipes[i] == new_recipe)
				throw Error("Bad Request");
		}
		recipes.push_back(new_recipe);
	}
	int find_recipe_index(int id_)
	{
		for (int i = 0; i < recipes.size(); i++)
			if (recipes[i]->varify_id(id_))
				return i;
		return NOT_FOUND;
	}
	vector<string> gather_recipes_info()
	{
		vector<string>recipes_info;
		for (int i = 0; i < recipes.size(); i++)
		{
			recipes_info.push_back(recipes[i]->get_brief_info());
		}
		return recipes_info;
	}

	//const vector<Recipe*>& get_recipes(){	return recipes;}
	void delete_recipe(int recipe_index)
	{
		recipes.erase(recipes.begin() + recipe_index);
	}
	string get_info()
	{
		stringstream info;
		info << id << " " << name << "\n";
		//allShelves[i]->getId()) + " " + allShelves[i]->getName() + "\n"
		return info.str();
	}

private:
	int id;
	string name;
	vector<Recipe *> recipes;
};

int find_shelve_index(int shelve_id, const vector<Shelve*>&shelves)
{
	for (int i = 0; i < shelves.size(); i++)
		if (shelves[i]->varify_id(shelve_id))
			return i;
	return NOT_FOUND;
}

class Member
{
public:
	Member(string username_, string password_, int type_) : username(username_), password(password_), type(type_) {}
	bool varify_type(int type_)
	{
		if (type == type_)
			return true;
		return false;
	}
	virtual void set_filter(vector<string>filter_base, int wich_filter) {}
	virtual void remove_filters() {}
	string get_username() { return username; }
	virtual bool varify_email(string email_) { return false; }

	bool varify_password(string password_)
	{
		if (password == password_)
			return true;
		return false;
	}
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
	virtual void add_order(vector<Offer*> best_offers, int recipe_id, double total_price) {}
	void increase_money(double money_)
	{
		money += money_;
	}
	virtual string get_brief_chef_info() { return SOMETHING; }
	virtual void print_chef_recipes() {}
protected:
	double money = 0.0;
	string username;
	string password;
	int type;
};
class Offer
{
public:
	Offer(string ingre, double price_, int count_, double pack, Member* supplier_) : ingredient(ingre), count(count_), price(price_),
		packaging(pack), supplier(supplier_) {}
	string get_ingre() { return ingredient; }
	void edit_offer(double new_price, int new_count)
	{
		count = new_count;
		price = new_price;
	}
	void sold(bool is_on_discount = false)
	{
		count--;
		double total_price = is_on_discount ? DISCOUNT*(price + packaging) : (price + packaging);
		supplier->increase_money(total_price);
	}
	double get_total_price(bool is_on_discount = false)
	{
		return is_on_discount ? DISCOUNT*(price + packaging) : (price + packaging);
	}
	int get_count() { return count; }
	string get_supplier_name()
	{
		return supplier->get_username();
	}
private:
	string ingredient;
	int count;
	double price;
	double packaging;
	Member* supplier;
};
class Order
{
public:
	Order(vector<Offer*> best_offers, int id, double price) : offers(best_offers), recipe_id(id), total_price(price) {}
	vector<string> gather_offers()
	{
		vector<string> collection;
		vector<Offer*> offers_ = offers;
		while (!offers_.empty())
		{
			vector<string> ingredients;
			string supplier_name = offers_[0]->get_supplier_name();
			for (int i = 0; i < offers_.size(); i++)
				if (supplier_name == offers_[i]->get_supplier_name())
					ingredients.push_back(offers_[i]->get_ingre());
			int i = 0;
			while (i < offers_.size())
				if (supplier_name == offers_[i]->get_supplier_name())
					offers_.erase(offers_.begin() + i);
				else
					i++;
			collection.push_back(supplier_offers(ingredients, supplier_name));
		}
		return collection;
	}
	string supplier_offers(vector<string> ingredients, string supplier_name)
	{
		ostringstream order_info;
		sort(ingredients.begin(), ingredients.end());
		order_info << supplier_name << " ";
		for (int i = 0; i < ingredients.size(); i++)
		{
			if (i < ingredients.size() - 1)
				order_info << ingredients[i] << " ";
			else
				order_info << ingredients[i];
		}
		return order_info.str();
	}
	void print()
	{
		vector<string> offers = gather_offers();
		sort(offers.begin(), offers.end());
		for (int i = 0; i < offers.size(); i++)
			cout << offers[i] + "\n";

		cout << total_price << endl;
	}
	int get_recipe_id() { return recipe_id; }
private:
	double total_price;
	int recipe_id;
	vector<Offer*> offers;

};

class User : public Member
{
public:
	User(string username_, string password_, int type_) : Member(username_, password_, type_)
	{
		my_filters.push_back(new Tag_filter());
		my_filters.push_back(new Veget_filter());
		my_filters.push_back(new Time_filter());
		my_filters.push_back(new Rate_filter());
	}
	void add_order(vector<Offer*> best_offers, int recipe_id, double total_price)
	{

		my_orders.push_back(new Order(best_offers, recipe_id, total_price));
		my_orders.back()->print();
	}

	void print_all_orders()
	{
		
		if (my_orders.size() <= 0)
			throw Error("Empty");
		for (int i = 0; i < my_orders.size(); i++)
		{
			cout << "====order_" << i+1 << "====" << endl
				<< my_orders[i]->get_recipe_id() << endl;
			my_orders[i]->print();
		}
	}
	void pay_money(int total_price)
	{
		if (money - total_price < 0)
			throw Error("Bad request");
		money -= total_price;
	}
	void set_filter(vector<string>filter_base, int wich_filter)
	{
		my_filters[wich_filter]->set_filter(filter_base);
	}
	vector<Recipe*> filtering(const vector<Recipe*>& recipes)
	{
		vector<Recipe*> filtered_recipes = recipes;
		for (int i = 0; i < my_filters.size(); i++)
		{
			filtered_recipes = my_filters[i]->filter_recipes(filtered_recipes);
		}
		return filtered_recipes;
	}
	void remove_filters()
	{
		for (int i = 0; i < my_filters.size(); i++)
		{
			my_filters[i]->clear();
		}
	}
	void add_shelve(Shelve* new_shelve)
	{
		my_shelves.push_back(new_shelve);
	}
	void remove_recipe_from_shelve(int shelf_id, int recipe_id)
	{
		int shelf_index = find_shelve_index(shelf_id, my_shelves);
		if (shelf_index == NOT_FOUND)
			throw Error("Permission Denied");
		int recipe_index = my_shelves[shelf_index]->find_recipe_index(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Bad Request");
		my_shelves[shelf_index]->delete_recipe(recipe_index);
	}
	//void delete_recipe_in_shelves(int index)

	void add_recipe_in_shelve(Shelve* shelf, Recipe* new_recipe)
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

	vector<string> get_shelves_info()
	{
		vector<string>shelves_info;
		for (int i = 0; i < my_shelves.size(); i++)
		{
			shelves_info.push_back(my_shelves[i]->get_info());
		}
		shelves_info = sort_strings(shelves_info, 0, ' ', false);
		return shelves_info;
	}

private:

	vector<Filter*>my_filters;
	vector<Shelve*>my_shelves;
	vector<Order*>my_orders;
};

class Chef : public Member
{
public:
	Chef(string username_, string password_, int type_) : Member(username_, password_, type_) {}
	void print_total_chef_info()
	{
		cout << username << endl << fixed << setprecision(1) << round_preci_1(get_rate()) << endl
			<< "recipes:" << endl;
		vector<string> recipes_info;
		//if (my_recipes.empty())
		//throw Error("Empty");
		for (int i = 0; i < my_recipes.size(); i++)
		{
			recipes_info.push_back(my_recipes[i]->get_info_for_chef());
		}
		recipes_info = sort_strings(recipes_info, 1, ' ', true);
		cout << gather_strings(recipes_info);
	}
	string get_brief_chef_info()
	{
		ostringstream info;
		double rate = get_rate();
		info << username << " " << fixed << setprecision(1) << round_preci_1(rate);
		return info.str();
	}
	double get_rate()
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
	void add_recipes(Recipe* new_recipe)
	{
		my_recipes.push_back(new_recipe);
	}
	void remove_recipe(int id)
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
	void print_chef_recipes()
	{
		vector<string> recipes_info;
		for (int i = 0; i < my_recipes.size(); i++)
		{
			recipes_info.push_back(my_recipes[i]->get_total_info());
		}
		if (recipes_info.empty())
			throw Error("Empty");

		cout << gather_strings(sort_strings(recipes_info, 1, '\n', true), "\n") << endl;
	}
	//const vector<Recipe*>& get_recipes(){	return my_recipes;}
private:
	vector<Recipe*>my_recipes;
};

class Supplier :public Member
{
public:
	Supplier(string username_, string password_, string email_) : Member(username_, password_, member::SUPPLIER), email(email_) {}
	bool varify_email(string email_)
	{
		if (email == email_)
			return true;
		return false;
	}
	vector<Offer*> find_offers(vector<string> ingres)
	{
		vector<Offer*> offers;
		for (int i = 0; i < ingres.size(); i++)
		{
			for (int j = 0; j < my_offers.size(); j++)
				if (my_offers[j]->get_ingre() == ingres[i])
					if (my_offers[j]->get_count() > 0)
					{
						offers.push_back(my_offers[j]);
						break;
					}
		}
		return offers;
	}
	int find_offer(string ingre)
	{
		for (int i = 0; i < my_offers.size(); i++)
		{
			if (my_offers[i]->get_ingre() == ingre)
				return i;
		}
		return NOT_FOUND;
	}
	void delete_offer(string ingre)
	{
		int offer_index = find_offer(ingre);
		if (offer_index == NOT_FOUND)
			throw Error("Bad Request");
		my_offers.erase(my_offers.begin() + offer_index);
	}
	void add_offer(string ingre, double price, int count, double packaging, Member* supplier)
	{
		int offer_index = find_offer(ingre);
		if (offer_index != NOT_FOUND)
			throw Error("Bad Request");
		my_offers.push_back(new Offer(ingre, price, count, packaging, supplier));
	}
	void edit_offer(string ingre, double new_price, int new_count)
	{
		int offer_index = find_offer(ingre);
		if (offer_index == NOT_FOUND)
			throw Error("Bad Request");
		my_offers[offer_index]->edit_offer(new_price, new_count);
	}


private:

	string email;
	vector<Offer*>my_offers;
};

bool is_it_int(double number)
{
	return (number - floor(number) == 0) ? true : false;
}

class Ingredient
{
public:
	Ingredient(string name) : ingredient(name) {}
	bool increase()
	{
		number_of_offers++;
		return number_of_offers == DISCOUNT_LIMIT;
	}
	bool decrease()
	{
		number_of_offers--;
		return number_of_offers == 19;
	}
	string get_name() { return ingredient; }

private:
	string ingredient;
	int number_of_offers = 1;
};
class Discount
{
public:
	int find_ingredient(string name)
	{
		for (int i = 0; i < offered_ingredients.size(); i++)
		{
			if (offered_ingredients[i].get_name() == name)
				return i;
		}
		return NOT_FOUND;
	}
	void add_offer(string ingre)
	{
		int ingre_index = find_ingredient(ingre);
		if (ingre_index == NOT_FOUND)
		{
			offered_ingredients.push_back(Ingredient(ingre));
		}
		else
		{
			if (offered_ingredients[ingre_index].increase())
				discount_list.push_back(ingre_index);
		}
	}
	void delete_offer(int ingre_index)
	{
		if (offered_ingredients[ingre_index].decrease())
			for (int i = 0; i < discount_list.size(); i++)
				if (ingre_index == discount_list[i])
				{
					discount_list.erase(discount_list.begin() + i);
					return;
				}
	}
	vector<string> get_on_off_ingres()
	{
		vector<string> ingres_on_off;
		for (int i = 0; i < discount_list.size(); i++)
		{
			ingres_on_off.push_back(offered_ingredients[discount_list[i]].get_name());
		}
		return ingres_on_off;
	}
	void update(vector<Offer*> best_offers)
	{
		for (int i = 0; i < best_offers.size(); i++)
		{
			if (best_offers[i]->get_count() <= 0)
				for (int j = 0; j < offered_ingredients.size(); j++)
					if (offered_ingredients[j].get_name() == best_offers[i]->get_ingre())
					{
						delete_offer(j);
						break;
					}
		}
	}
private:
	vector<Ingredient>offered_ingredients;
	vector<int>discount_list;
};
class Good_eat
{
public:
	void process()
	{
		vector<string>command;
		string line;

		while (getline(cin, line))
		{
			command = divide_line(line, ' ');
			try
			{
				manu(command);
				
			}
			catch (Error &e)
			{
				e.print_errors();
			}
		}
	}
private:
	Member *in_site_member = NULL;
	vector<Member*>all_members;
	vector<Recipe*>all_recipes;
	vector<Shelve*>all_shelves;
	Discount discount;
	int last_recipe_id = 0;
	int last_shelve_id = 0;

	void manu(const vector<string>&command)
	{
		int print_status;
		int command_number = find_command(command);
		if (in_site_member == NULL)
		{
			which_registering_commands(command, command_number);
			print_status = PRINT_OK;
		}
		else if (in_site_member->varify_type(member::CHEF))
		{
			print_status = which_chef_commands(command, command_number);
		}
		else if (in_site_member->varify_type(member::USER))
		{
			print_status = which_user_commands(command, command_number);
		}
		else if (in_site_member->varify_type(member::SUPPLIER))
		{
			print_status = which_supplier_command(command, command_number);
		}
		if (print_status == PRINT_OK)
			cout << "OK\n";
	}


	void which_registering_commands(const vector<string>&command, int which_command)
	{
		if (which_command == SIGNUP) signup(command);
		else if (which_command == LOGIN) login(command);
		else if (which_command == SUPPLIER_SIGNUP) supplier_signup(command);
		else if (which_command == SUPPLIER_LOGIN) supplier_login(command);
		else throw Error("Permission Denied");
	}

	int which_user_commands(const vector<string>&command, int which_command)
	{
		int print_status = PRINT_OK;
		if (which_command == LOGOUT) logout();
		else if (which_command == POST_RATES) post_rate(command);
		else if (which_command == POST_SHELVE)
		{
			post_shelve(command);
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == POST_TAG_FILTER) post_tag_filter(command);
		else if (which_command == POST_VEGET_FILTER) post_veget_filter(command);
		else if (which_command == POST_TIME_FILTER) post_time_filter(command);
		else if (which_command == POST_RATE_FILTER) post_rate_filter(command);
		else if (which_command == GET_RECIPES_VER_1)
		{
			get_all_recipes();
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == GET_RECIPES_VER_2)
		{
			get_recipe(command);
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == GET_SHELVES)
		{
			get_shelves(command);
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == GET_SHELVES_RECIPES)
		{
			get_shelve_recipes(command);
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == GET_CHEFS_VER_1)
		{
			get_all_chefs();
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == GET_CHEFS_VER_2)
		{
			get_chef(command);
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == GET_USERS)
		{
			get_users();
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == PUT_RATES) put_rate(command);
		else if (which_command == PUT_SHELVES_RECIPES) put_shelve_recipe(command);
		else if (which_command == DELETE_FILTERS) delete_filters();
		else if (which_command == DELETE_SHELVES_RECIPES) delete_shelve_recipe(command);
		else if (which_command == GET_CREDITS)
		{
			get_credit();
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == PUT_CREDITS) put_credit(command);
		else if (which_command == POST_ORDERS)
		{
			post_order(command);
			print_status = NOT_PRINT_OK;
		}
		else if (which_command == GET_ORDERS)
		{
			get_orders();
			print_status = NOT_PRINT_OK;
		}

		else throw Error("Permission Denied");

		return print_status;
	}

	int which_chef_commands(const vector<string>&command, int which_command)
	{
		int print_status = NOT_PRINT_OK;
		if (which_command == LOGOUT)
		{
			logout();
			print_status = PRINT_OK;
		}
		else if (which_command == POST_RECIPES) post_recipes(command);
		else if (which_command == GET_MY_RECIPES) get_my_recipes(command);
		else if (which_command == DELETE_RECIPES)
		{
			delete_recipes(command);
			print_status = PRINT_OK;
		}
		else throw Error("Permission Denied");

		return print_status;
	}
	
	int which_supplier_command(const vector<string>&command, int which_command)
	{
		int print_status = PRINT_OK;
		if (which_command == LOGOUT) logout();
		else if (which_command == POST_OFFERS) post_offer(command);
		else if (which_command == PUT_OFFERS)  put_offer(command);
		else if (which_command == DELETE_OFFERS) delete_offer(command);
		else if (which_command == GET_CREDITS)
		{
			get_credit();
			print_status = NOT_PRINT_OK;
		}
		else throw Error("Permission Denied");
		return print_status;
	}
	int find_command(const vector<string>&command)
	{
		int command_status;
		for (int i = 0; i < COMMANDS.size(); i++)
		{
			command_status = FOUND;
			if (command.size() != COMMANDS[i].size())
				continue;
			for (int j = 0; j < COMMANDS[i].size(); j++)
			{
				if (COMMANDS[i][j] == SOMETHING)
					continue;

				if (COMMANDS[i][j] == YES_OR_NO)
				{
					if (command[j] == "Yes" || command[j] == "No")
						continue;
					else
					{
						command_status = NOT_FOUND;
						break;
					}
				}

				if (COMMANDS[i][j] == A_NUMBER)
				{
					if (is_number(command[j]))
						continue;
					else
					{
						command_status = NOT_FOUND;
						break;
					}
				}
				if (COMMANDS[i][j] == AN_INTEGER)
				{
					if (is_number(command[j]) && is_it_int(stod(command[j])))
						continue;
					else
					{
						command_status = NOT_FOUND;
						break;
					}

				}
				if (COMMANDS[i][j] != command[j])
				{
					if (j == 2 && (i == COMMANDS.size() - 1))
						throw Error("Not Found");
					command_status = NOT_FOUND;
					break;
				}
			}
			if (command_status == FOUND)
				return i + 1;
		}
		throw Error("Bad Request");

	}
	void put_credit(const vector<string>&command)
	{
		in_site_member->increase_money(stod(command[4]));
	}
	void get_orders()
	{
		in_site_member->print_all_orders();
	}
	void post_order(const vector<string>&command)
	{
		int recipe_index = find_recipe(stol(command[4]));
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		vector<Offer*> best_offers = offers_list(recipe_index);
		double total_price = cal_total_price(best_offers);
		in_site_member->pay_money(total_price);
		pay_suppliers(best_offers);
		in_site_member->add_order(best_offers, stol(command[4]), total_price);
		//print_order(best_offers);
		discount.update(best_offers);
	}

	void pay_suppliers(vector<Offer*> best_offers)
	{
		vector<string> on_off_ingres = discount.get_on_off_ingres();
		for (int i = 0; i < best_offers.size(); i++)
		{
			bool is_found = false;
			for (int j = 0; j < on_off_ingres.size(); j++)
				if (best_offers[i]->get_ingre() == on_off_ingres[j])
				{
					is_found = true;
					break;
				}
			best_offers[i]->sold(is_found);
		}

	}
	double cal_total_price(vector<Offer*> best_offers)
	{
		double total_price = 0.0;

		vector<string> on_off_ingres = discount.get_on_off_ingres();
		for (int i = 0; i < best_offers.size(); i++)
		{
			bool is_found = false;
			for (int j = 0; j < on_off_ingres.size(); j++)
				if (best_offers[i]->get_ingre() == on_off_ingres[j])
				{
					is_found = true;
					break;
				}
			total_price += best_offers[i]->get_total_price(is_found);
		}
		return total_price;
	}

	vector<Offer*> offers_list(int recipe_index)
	{
		vector<string>ingredients = all_recipes[recipe_index]->get_ingredients();
		vector<Offer*>best_offers, offers;
		for (int i = 0; i < all_members.size(); i++)
		{
			if (!all_members[i]->varify_type(member::SUPPLIER))
				continue;
			offers = dynamic_cast<Supplier*>(all_members[i])->find_offers(ingredients);
			best_offers = find_best_offers(best_offers, offers);
		}
		if (ingredients.size() != best_offers.size())
			throw Error("Not Found");
		return best_offers;
	}
	vector<Offer*>  find_best_offers(vector<Offer*>best_offers, vector<Offer*>offers)
	{
		if (best_offers.size() == 0)
			return offers;
		for (int i = 0; i < offers.size(); i++)
		{
			bool is_offer_found = false;
			for (int j = 0; j < best_offers.size(); j++)
			{
				if (best_offers[j]->get_ingre() == offers[i]->get_ingre())
				{
					is_offer_found = true;
					if (best_offers[j]->get_total_price() > offers[i]->get_total_price())
					{
						best_offers.erase(best_offers.begin() + j);
						best_offers.push_back(offers[i]);
					}
					break;
				}
			}
			if (is_offer_found == false)
				best_offers.push_back(offers[i]);
		}
		return best_offers;
	}
	
	int find_member(string username)
	{
		for (int i = 0; i < all_members.size(); i++)
			if (all_members[i]->get_username() == username)
				return i;
		return NOT_FOUND;
	}
	void signup(const vector<string>&command)
	{
		string username = command[4], password = command[6], type = command[8];
		if (find_member(username) != NOT_FOUND)
			throw Error("Bad Request");
		int type_ = find_index(type, vector<string>{"chef", "user"});
		if (type_ == NOT_FOUND)
			throw Error("Bad Request");
		else if (type_ == CHEF) all_members.push_back(new Chef(username, password, type_));
		else if (type_ == USER) all_members.push_back(new User(username, password, type_));
		in_site_member = all_members.back();
	}
void logout()
	{
		in_site_member->remove_filters();
		in_site_member = NULL;
	}
void login(const vector<string>&command)
	{
		int member_index = find_member(command[4]);
		if (member_index == NOT_FOUND)
			throw Error("Bad Request");
		if (!all_members[member_index]->varify_password(command[6]))
			throw Error("Bad Request");
		in_site_member = all_members[member_index];
	}
	
	int find_email(string email)
	{
		for (int i = 0; i < all_members.size(); i++)
			if (all_members[i]->varify_email(email))
				return i;
		return NOT_FOUND;
	}
	void supplier_signup(const vector<string>&command)
	{
		string username = command[4], email = command[6], password = command[8];
		if (find_member(username) != NOT_FOUND)
			throw Error("Bad Request");
		if (find_email(email) != NOT_FOUND)
			throw Error("Bad Request");
		all_members.push_back(new Supplier(username, password, email));
		in_site_member = all_members.back();

	}
	
	void supplier_login(const vector<string>&command)
	{
		int member_index = find_email(command[4]);
		if (member_index == NOT_FOUND)
			throw Error("Bad Request");
		if (!all_members[member_index]->varify_password(command[6]))
			throw Error("Bad Request");
		in_site_member = all_members[member_index];
	}
	
	void get_credit()
	{
		cout << in_site_member->get_money() << endl;
	}
	void post_offer(const vector<string>&command)
	{
		int count = stol(command[8]);
		if (count != 0)
			discount.add_offer(command[4]);

		double price = stod(command[6]), packaging = stod(command[10]);
		dynamic_cast<Supplier*>(in_site_member)->add_offer(command[4], price, count, packaging, in_site_member);
	}
	void put_offer(const vector<string>&command)
	{
		int ingre_index = discount.find_ingredient(command[4]);
		if (ingre_index == NOT_FOUND)
			throw Error("Bad Request");
		int count = stol(command[8]);
		double price = stod(command[6]);
		dynamic_cast<Supplier*>(in_site_member)->edit_offer(command[4], price, count);
	}
	void delete_offer(const vector<string>&command)
	{
		int ingre_index = discount.find_ingredient(command[4]);
		if (ingre_index == NOT_FOUND)
			throw Error("Not Found");
		dynamic_cast<Supplier*>(in_site_member)->delete_offer(command[4]);
		discount.delete_offer(ingre_index);
	}



	int find_recipe(int recipe_id)
	{
		for (int i = 0; i < all_recipes.size(); i++)
			if (all_recipes[i]->varify_id(recipe_id))
				return i;
		return NOT_FOUND;
	}
	void post_rate(const vector<string>&command)
	{
		int recipe_id = stol(command[4]);
		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		all_recipes[recipe_index]->add_new_rating(stod(command[6]), in_site_member);
	}
	void post_shelve(const vector<string>&command)
	{
		Shelve *new_shelve = new Shelve(last_shelve_id + 1, command[4]);
		last_shelve_id++;
		in_site_member->add_shelve(new_shelve);
		all_shelves.push_back(new_shelve);
		print_id(last_shelve_id);
	}
	void print_id(int id)
	{
		cout << id << '\n';
	}

	void post_tag_filter(const vector<string>&command)
	{
		vector<string>tag = { command[4] };
		in_site_member->set_filter(tag, 0);
	}

	void post_veget_filter(const vector<string>&command)
	{
		in_site_member->set_filter(command, 1);
	}
	void post_time_filter(const vector<string>&command)
	{
		vector<string>time_range = { command[4],command[6] };
		in_site_member->set_filter(time_range, 2);
	}

	void post_rate_filter(const vector<string>&command)
	{
		vector<string>rate_range = { command[4],command[6] };
		in_site_member->set_filter(rate_range, 3);
	}
	void get_all_recipes()
	{
		vector<Recipe*> filtered_recipes;
		filtered_recipes = in_site_member->filtering(all_recipes);
		vector<string>recipes_info;
		for (int i = 0; i < filtered_recipes.size(); i++)
		{
			recipes_info.push_back(filtered_recipes[i]->get_brief_info());
		}
		recipes_info = sort_strings(recipes_info, 1, ' ', true);
		if (filtered_recipes.empty())
			throw Error("Empty");
		cout << gather_strings(recipes_info, "\n") << endl;
	}
	void get_recipe(const vector<string>&command)
	{
		int recipe_id = stol(command[4]);
		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		cout << all_recipes[recipe_index]->get_total_info();
	}
	void get_shelves(const vector<string>&command)
	{
		int user_index = find_member(command[4]);
		if (user_index == NOT_FOUND)
			throw Error("Bad Request");
		if (all_members[user_index]->varify_type(CHEF))
			throw Error("Empty");
		vector<string>shelves_info = dynamic_cast<User*>(all_members[user_index])->get_shelves_info();
		if (shelves_info.size() == 0)
			throw Error("Empty");
		int limit = stol(command[6]);
		if (limit < 0)
			throw Error("Bad Request");
		limit = limit <= shelves_info.size() ? limit : shelves_info.size();
		for (int i = 0; i < limit; i++)
		{
			cout << shelves_info[i];
		}
	}
	void get_shelve_recipes(const vector<string>&command)
	{
		//vector<Recipe*> filtered_recipes;
		int shelve_index = find_shelve_index(stol(command[4]), all_shelves);
		if (shelve_index == NOT_FOUND)
			throw Error("Bad Request");
		//filtered_recipes = in_site_member->filtering(all_shelves[shelve_index]->get_recipes());
		vector<string>recipes_info = all_shelves[shelve_index]->gather_recipes_info();
		if (recipes_info.empty())
			throw Error("Empty");
		recipes_info = sort_strings(recipes_info, 1, ' ', true);

		cout << gather_strings(recipes_info, "\n") << endl;
	}
	void get_all_chefs()
	{
		vector<string> chefs_info;
		for (int i = 0; i < all_members.size(); i++)
			if (all_members[i]->varify_type(CHEF))
			{
				chefs_info.push_back(all_members[i]->get_brief_chef_info());
			}
		if (chefs_info.empty())
			throw Error("Empty");
		sort(chefs_info.begin(), chefs_info.end());
		cout << gather_strings(chefs_info, "\n") << endl;
	}
	void get_chef(const vector<string>&command)
	{
		int chef_index = find_member(command[4]);
		if (chef_index == NOT_FOUND || all_members[chef_index]->varify_type(USER))
			throw Error("Not Found");
		//vector<Recipe*> filtered_recipes;
		//filtered_recipes = in_site_member->filtering(dynamic_cast<Chef*>(all_members[chef_index])->get_recipes());
		all_members[chef_index]->print_total_chef_info();
	}
	void get_users()
	{
		vector<string> usernames;
		for (int i = 0; i < all_members.size(); i++)
			if (all_members[i]->varify_type(USER) && all_members[i] != in_site_member)
				usernames.push_back(all_members[i]->get_username());
		if (usernames.empty())
			throw Error("Empty");
		sort(usernames.begin(), usernames.end());
		cout << gather_strings(usernames, "\n") << endl;
	}
	void put_rate(const vector<string>&command)
	{
		int recipe_id = stol(command[4]);
		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not_Found");
		all_recipes[recipe_index]->edit_rate(stod(command[6]), in_site_member);
	}
	void put_shelve_recipe(const vector<string>&command)
	{
		int shelf_id, recipe_id;
		shelf_id = stol(command[4]);  recipe_id = stol(command[6]);

		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		int shelf_index = find_shelve_index(shelf_id, all_shelves);
		if (shelf_index == NOT_FOUND)
			throw Error("Not Found");
		in_site_member->add_recipe_in_shelve(all_shelves[shelf_index], all_recipes[recipe_index]);
	}

	void delete_filters()
	{
		in_site_member->remove_filters();
	}
	void delete_shelve_recipe(const vector<string>&command)
	{
		int shelf_id = stol(command[4]);
		int recipe_id = stol(command[6]);
		in_site_member->remove_recipe_from_shelve(shelf_id, recipe_id);

	}
	void post_recipes(const vector<string>&command)
	{
		Recipe* new_recipe = new Recipe(last_recipe_id + 1, command);
		last_recipe_id++;
		in_site_member->add_recipes(new_recipe);
		all_recipes.push_back(new_recipe);
		print_id(last_recipe_id);
	}
	void  get_my_recipes(const vector<string>&command)
	{
		in_site_member->print_chef_recipes();
	}

	void delete_recipes(const vector<string>&command)
	{
		int recipe_id = stol(command[4]);
		int recipe_index;
		recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		in_site_member->remove_recipe(recipe_id);
		/*	for (int i = 0; i < all_shelves.size(); i++)
		{
		recipe_index = all_shelves[i]->find_recipe_index(recipe_id);
		if (recipe_index != NOT_FOUND)
		all_shelves[i]->delete_recipe(recipe_index);
		}

		delete all_recipes[recipe_index];*/

		all_recipes.erase(all_recipes.begin() + recipe_index);
	}
};

