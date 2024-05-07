#ifndef GLOBAL_H
#define GLOBAL_H
#include <string>
#include <vector>
using namespace std;
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
	{"signup",SOMETHING,SOMETHING,SOMETHING},
	{ "login", SOMETHING, SOMETHING },
	{"logout" },
	{ "add_recipe", SOMETHING, SOMETHING, YES_OR_NO, A_NUMBER,  SOMETHING,  SOMETHING },
	{ "rate", AN_INTEGER, A_NUMBER },
	{ "POST", "shelves", "?", "name", SOMETHING },
	{ "type_filter", SOMETHING },
	{ "POST", "filters", "?", "vegetarian" },
	{ "time_filter", A_NUMBER, A_NUMBER },
	{ "rate_filter",A_NUMBER, A_NUMBER },
	{ "GET", "recipes" },
	{ "GET", "recipes", "?", "id", AN_INTEGER },
	{ "GET", "shelves"},
	{ "GET", "shelves_recipes", "?", "shelf_id", AN_INTEGER },
	{ "GET", "chefs" },
	{ "GET", "chefs", "?", "chef_username", SOMETHING },
	{ "GET", "users" },
	{ "GET", "my_recipes" },
	{ "edit_rate",AN_INTEGER, A_NUMBER },
	{ "add_shelf_recipe",AN_INTEGER,AN_INTEGER },
	{ "delete_recipe",  AN_INTEGER },
	{ "DELETE", "filters" },
	{ "delete_shelf_recipe",  AN_INTEGER,  AN_INTEGER },
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

const vector<string> divide_line(const string& line, char divider);

bool is_number(string number);

double round_preci_1(double number);

int find_index(string target, const vector<string> &range) ;

int find_index(int target, const vector<int> &range) ;
vector<string> sort_strings(const vector<string> &entry, int which_index, char divider, bool by_string);


string gather_strings(const vector<string>& entry, string divider = "");



int find_shelve_index(int shelve_id, const vector<Shelve*>&shelves);


bool is_it_int(double number);


#endif