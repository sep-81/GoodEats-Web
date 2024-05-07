#include "good_eat.hpp"
#include <algorithm>



string Good_eat::process(string line)
{
	vector<string>command;
	command = divide_line(line, ' ');
	try
	{
		manu(command);		
		return "OK";
	}
	catch (Error &e)
	{
		return e.get_error();
	}
}

int Good_eat::get_type()
{
return in_site_member->varify_type(member::CHEF) ? CHEF : USER;
}

string Good_eat::get_username()
{
	return in_site_member->get_username();
}
vector<string> Good_eat::get_all_recipes()
{
	vector<Recipe*> filtered_recipes;
	filtered_recipes = in_site_member->filtering(all_recipes);
	vector<string>recipes_info;
	for (int i = 0; i < filtered_recipes.size(); i++)
	{
		recipes_info.push_back(filtered_recipes[i]->get_brief_info());
	}
	recipes_info = sort_strings(recipes_info, 1, ',', true);
	if (filtered_recipes.empty())
		throw Error("Empty");
	return recipes_info;
}
string Good_eat::get_recipe(string rec_id)
	{
		int recipe_id = stol(rec_id);
		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");

		return all_recipes[recipe_index]->get_total_info();
	}
string Good_eat::get_recipe_img(string recipe_id)
{
	return all_recipes[stoi(recipe_id)-1]->get_image();
}
vector<string> Good_eat::get_shelves()
	{
	
		if (in_site_member->varify_type(CHEF))
			throw Error("Empty");
		vector<string>shelves_info = dynamic_cast<User*>(in_site_member)->get_shelves_info();
		if (shelves_info.size() == 0)
			throw Error("Empty");
	
		return shelves_info;
	}
string Good_eat::post_shelve(string shelf_name)
	{
		Shelve *new_shelve = new Shelve(last_shelve_id + 1, shelf_name);
		last_shelve_id++;
		in_site_member->add_shelve(new_shelve);
		all_shelves.push_back(new_shelve);
		return to_string(last_shelve_id);
	}
string Good_eat::post_recipe(const vector<string>&command)
	{
		Recipe* new_recipe = new Recipe(last_recipe_id + 1, command);
		last_recipe_id++;
		in_site_member->add_recipes(new_recipe);
		all_recipes.push_back(new_recipe);
		return to_string(last_recipe_id);
	}
string Good_eat::get_shelf_name(string shelf_id)
	{
		int shelf_index  = find_shelve_index(stol(shelf_id),all_shelves);
		return all_shelves[shelf_index]->get_name();
	}
vector<string> Good_eat::get_shelve_recipes(string shelf_id)
	{
		
		int shelve_index = find_shelve_index(stol(shelf_id), all_shelves);
		if (shelve_index == NOT_FOUND)
			throw Error("Bad Request");
		
		vector<string>recipes_info = all_shelves[shelve_index]->gather_recipes_info();
		if (recipes_info.empty())
			throw Error("Empty");
		

		
		return  sort_strings(recipes_info, 1, ',', true);
	}
vector<string> Good_eat::get_my_recipes()
	{
		return dynamic_cast<Chef*>(in_site_member)->get_chef_recipes();
	}

	void Good_eat::manu(const vector<string>&command)
	{
		int command_number = find_command(command);
		if (in_site_member == NULL)
		{
			which_registering_commands(command, command_number);
		}
		else if (in_site_member->varify_type(member::CHEF))
		{
			which_chef_commands(command, command_number);
		}
		else if (in_site_member->varify_type(member::USER))
		{
			which_user_commands(command, command_number);
		}
		
	}


	void Good_eat::which_registering_commands(const vector<string>&command, int which_command)
	{
		if (which_command == SIGNUP) signup(command);
		else if (which_command == LOGIN) login(command);
		else if (which_command == SUPPLIER_LOGIN) supplier_login(command);
		else throw Error("Permission Denied");
	}

	void Good_eat::which_user_commands(const vector<string>&command, int which_command)
	{
		if (which_command == LOGOUT) logout();
		else if (which_command == POST_RATES) post_rate(command);
		
		else if (which_command == POST_TAG_FILTER) post_tag_filter(command);
		else if (which_command == POST_VEGET_FILTER) post_veget_filter(command);
		else if (which_command == POST_TIME_FILTER) post_time_filter(command);
		else if (which_command == POST_RATE_FILTER) post_rate_filter(command);
		else if (which_command == GET_RECIPES_VER_1)
		{
			get_all_recipes();

		}
		else if (which_command == GET_RECIPES_VER_2)
		{
			
		}
		else if (which_command == GET_SHELVES)
		{
			get_shelves();
		}
		else if (which_command == GET_SHELVES_RECIPES)
		{
			
		}
		else if (which_command == GET_CHEFS_VER_1)
		{
			get_all_chefs();
		}
		else if (which_command == GET_CHEFS_VER_2)
		{
			get_chef(command);
		}
		else if (which_command == GET_USERS)
		{
			get_users();
		}
		else if (which_command == PUT_RATES) put_rate(command);
		else if (which_command == PUT_SHELVES_RECIPES) put_shelve_recipe(command);
		else if (which_command == DELETE_FILTERS) delete_filters();
		else if (which_command == DELETE_SHELVES_RECIPES) delete_shelve_recipe(command);
		else if (which_command == GET_CREDITS)
		{
			get_credit();

		}
		else if (which_command == PUT_CREDITS) put_credit(command);
		else if (which_command == POST_ORDERS)
		{
			
		
		}
		else if (which_command == GET_ORDERS)
		{
			get_orders();
			
		}

		else throw Error("Permission Denied");

	}

	void Good_eat::which_chef_commands(const vector<string>&command, int which_command)
	{
		
		if (which_command == LOGOUT)
		{
			logout();
		}
		else if (which_command == POST_RECIPES) post_recipe(command);
		else if (which_command == GET_MY_RECIPES) get_my_recipes();
		else if (which_command == DELETE_RECIPES)
		{
			delete_recipes(command);
			
		}
		else throw Error("Permission Denied");

	
	}
	
	
	int Good_eat::find_command(const vector<string>&command)
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
				{
					continue;
				}

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
		throw Error("Baddd Request");

	}
	
	void Good_eat::put_credit(const vector<string>&command)
	{
		in_site_member->increase_money(stod(command[4]));
	}
	void Good_eat::get_orders()
	{
		in_site_member->print_all_orders();
	}


	
	
	int Good_eat::find_member(string username)
	{
		for (int i = 0; i < all_members.size(); i++)
			if (all_members[i]->get_username() == username)
				return i;
		return NOT_FOUND;
	}
    
	void Good_eat::signup(const vector<string>&command)
	{
		string username = command[1], password = command[2], type = command[3];
		if (find_member(username) != NOT_FOUND)
			throw Error("Badd Request");
		int type_ = find_index(type, vector<string>{"chef", "user"});
		if (type_ == NOT_FOUND)
			throw Error("Bad Request");
		else if (type_ == CHEF) all_members.push_back(new Chef(username, password, type_));
		else if (type_ == USER) all_members.push_back(new User(username, password, type_));
		in_site_member = all_members.back();
	}
	void Good_eat::logout()
	{
		in_site_member->remove_filters();
		in_site_member = NULL;
	}
	void Good_eat::login(const vector<string>&command)
	{
		int member_index = find_member(command[1]);
		if (member_index == NOT_FOUND)
			throw Error("Bad Request");
		if (!all_members[member_index]->varify_password(command[2]))
			throw Error("Bad Request");
		in_site_member = all_members[member_index];
	}
	
	int Good_eat::find_email(string email)
	{
		for (int i = 0; i < all_members.size(); i++)
			if (all_members[i]->varify_email(email))
				return i;
		return NOT_FOUND;
	}
	
	
	void Good_eat::supplier_login(const vector<string>&command)
	{
		int member_index = find_email(command[4]);
		if (member_index == NOT_FOUND)
			throw Error("Bad Request");
		if (!all_members[member_index]->varify_password(command[6]))
			throw Error("Bad Request");
		in_site_member = all_members[member_index];
	}
	
	void Good_eat::get_credit()
	{
		cout << in_site_member->get_money() << endl;
	}
	

	



	int Good_eat::find_recipe(int recipe_id)
	{
		for (int i = 0; i < all_recipes.size(); i++)
			if (all_recipes[i]->varify_id(recipe_id))
				return i;
		return NOT_FOUND;
	}
	void Good_eat::post_rate(const vector<string>&command)
	{
		int recipe_id = stol(command[1]);
		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		all_recipes[recipe_index]->add_new_rating(stod(command[2]), in_site_member);
	}

	void Good_eat::print_id(int id)
	{
		cout << id << '\n';
	}

	void Good_eat::post_tag_filter(const vector<string>&command)
	{
		vector<string>tag = { command[1] };
		in_site_member->set_filter(tag, 0);
	}

	void Good_eat::post_veget_filter(const vector<string>&command)
	{
		in_site_member->set_filter(command, 1);
	}
	void Good_eat::post_time_filter(const vector<string>&command)
	{
		vector<string>time_range = { command[1],command[2] };
		in_site_member->set_filter(time_range, 2);
	}

	void Good_eat::post_rate_filter(const vector<string>&command)
	{
		vector<string>rate_range = { command[1],command[2] };
		in_site_member->set_filter(rate_range, 3);
	}
	
	
	

	void Good_eat::get_all_chefs()
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
	void Good_eat::get_chef(const vector<string>&command)
	{
		int chef_index = find_member(command[4]);
		if (chef_index == NOT_FOUND || all_members[chef_index]->varify_type(USER))
			throw Error("Not Found");

		all_members[chef_index]->print_total_chef_info();
	}
	void Good_eat::get_users()
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
	void Good_eat::put_rate(const vector<string>&command)
	{
		int recipe_id = stol(command[1]);
		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not_Found");
		all_recipes[recipe_index]->edit_rate(stod(command[2]), in_site_member);
	}
	void Good_eat::put_shelve_recipe(const vector<string>&command)
	{
		int shelf_id, recipe_id;
		shelf_id = stol(command[1]);  recipe_id = stol(command[2]);

		int recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		int shelf_index = find_shelve_index(shelf_id, all_shelves);
		if (shelf_index == NOT_FOUND)
			throw Error("Not Found");
		in_site_member->add_recipe_in_shelve(all_shelves[shelf_index], all_recipes[recipe_index]);
	}

	void Good_eat::delete_filters()
	{
		in_site_member->remove_filters();
	}
	void Good_eat::delete_shelve_recipe(const vector<string>&command)
	{
		int shelf_id = stol(command[1]);
		int recipe_id = stol(command[2]);
		in_site_member->remove_recipe_from_shelve(shelf_id, recipe_id);

	}
	
	

	void Good_eat::delete_recipes(const vector<string>&command)
	{
		int recipe_id = stol(command[1]);
		int recipe_index;
		recipe_index = find_recipe(recipe_id);
		if (recipe_index == NOT_FOUND)
			throw Error("Not Found");
		in_site_member->remove_recipe(recipe_id);
		

		all_recipes.erase(all_recipes.begin() + recipe_index);
	}



