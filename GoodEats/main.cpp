#include "main.hpp"
#include <sstream>



 Response* Signup_handler::callback(Request* req)
 {
	 Response* res = new Response();
        res->setHeader("Content-Type", "text/html");
		string input = "signup "+req->getBodyParam("username") + " " + req->getBodyParam("password") + " " + req->getBodyParam("type");
		string result = good_eat->process(input);
		if (result == "OK")
			if(good_eat->get_type()== member::CHEF)
				res = Response::redirect("/chef");
			else
				res = Response::redirect("/user");
		else
		{
			res = Response::redirect("/error");
			res->setSessionId(result);
		}
     return res;
 }





 Response* Login_handler::callback(Request* req)
 {
	 Response* res = new Response();
        res->setHeader("Content-Type", "text/html");
		string input = "login "+req->getBodyParam("username") + " " + req->getBodyParam("password");
		string result = good_eat->process(input);
		if (result == "OK")
			if(good_eat->get_type()== member::CHEF)
				res = Response::redirect("/chef");
			else
				res = Response::redirect("/user");
		else
		{
			res = Response::redirect("/error");
			res->setSessionId(result);
		}
     return res;
 }



	 Response* Error_handler::callback(Request* req)
	 {
		 ostringstream body;
		
		 body<<"<!DOCTYPE html>\n<html>\n<head>\n<title>error</title>\n</head>\n<body>";
		 body << req->getSessionId();
		 body << "\n</body>\n</html>";
		 Response* res = new Response();
		 res->setHeader("Content-Type", "text/html");
		 res->setSessionId("");
		 res->setBody(body.str());
		 return res;
	 }



 Response* User_handler::callback(Request* req)
  {
	 
	Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
	ostringstream body;
	string status = req->getQueryParam("status");
	
 	body<< "<!DOCTYPE html> \n <html lang='en'> \n <head> \n <meta charset='UTF-8'> \n <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
 	body << "\n <meta name='viewport' content='width=device-width, initial-scale=1.0'> \n  <title>user</title> \n <style>";
 	body << "table, th, td {\nborder: 1px solid black;\nborder-collapse: collapse;\n}\nth, td {\npadding: 5px;\n}\nth {\ntext-align: left;\n} \n div a { \n  color: blue; \n text-decoration: underline;\n  }";
 	body << "body {\n  text-align: center;  background-color: burlywood;\n}\n</style>\n</head>\n<body >\n";
	if (status.size() > 0)
	{
		vector<string> status_items = divide_line(status,' ');
	 	if(status_items[0] == "filter")
		{
			if(status_items[1] == "OK")
			  body << "\n <script> \n alert(\"successful\"); \n </script>";
			else
			{
			  body << "\n <script> \n alert(\"Error : "+status_items[1]+"\"); \n </script>";
			}
		}
	}
	body << "<h1>GOOD_EAT</h1>\n<p><b>wellcome\n"+good_eat->get_username() +"</b></p>";
	body << "<div style=\"border: 1px solid black\">";
	 vector<string>recipes;
	 try {
		recipes = good_eat->get_all_recipes();
	 }
	 catch (Error& e)
	 {
		 body <<"<p>"+e.get_error()+"<p>";
		 recipes = {};
	 }
	 
 	if (recipes.size() > 0)
	{
		body << " <table style=\"width:100%\">";
		body << "<tr>\n<th style=\"width:50%\"><b>Recipe title</b></th>\n<th><b>Recipe id</b></th>\n<th><b>Is Veget</b></th>\n<th><b>Time to Ready</b></th>\n</tr>";
	}
	 for(int i =  0 ; i < recipes.size();i++)
	 {
		vector<string>recipe_items = divide_line(recipes[i],',');
		body << "<tr>";
		body << "<td> <a href=\"/recipe_page?id="+recipe_items[0]+"\">"+recipe_items[1]+"</a> </td>";
		for (int j = 0; j < recipe_items.size(); j++)
		{
			if ( j==1 )
				continue;
			body << "<td>" + recipe_items[j] + "</td>";
		}
		
			body << "</tr>";
	 }
	body << "</table></div>";
	 
	body << "\n<br><br>\n<div style=\"margin: auto;\">\n <form action='/filter'>\n<input type=\"hidden\" name=\"id\" value=\"filter1\" >\n<label for='type_filter'>food_type_filter:</label>\n <input type='text' name='type_filter' id='type_filter' required>";
 	body << "\n<br>\n<input type='submit'>\n</form>\n<form action='/filter'>\n <input type=\"hidden\" name=\"id\" value=\"filter2\" >\n<br>\nduration:\n<br>\n<label for=\"min_time\">from: </label>";
 	body << "\n<input type=\"number\" name=\"min_time\" id=\"min_time\" required>\n<br>\n<label for=\"max_time\">to : </label>";
 	body << "<input type=\"number\" name=\"max_time\" id=\"max_time\" required >\n<br>\n<input type=\"submit\">\n</form>";

 	body << "<form action=\"/filter\">\n<input type=\"hidden\" name=\"id\" value=\"filter3\" > \n<br> \n rate:\n<br> \n<label for=\"min_rate\">from: </label>\n<input type=\"number\" name=\"min_rate\" id=\"min_rate\" required>\n<br>";
    body << " <label for=\"max_rate\">to : </label>\n<input type=\"number\" name=\"max_rate\" id=\"max_rate\" required >\n<br>\n<input type=\"submit\">";
    body << "</form>\n<br><form action=\"/filter\"><p>press delete button to reset filters</p><input type=\"hidden\" name=\"id\" value=\"delete\"><input type=\"submit\" value=\"delete\">"
         << "</form><br>\n<a href=\"/shelvs\">my shlevs</a>\n<br>\n<a href=\"/logout\">logout</a>\n</div>\n</body>\n</html>";
 	
	res->setBody(body.str());
     return res;
 }



 Response* Shelvs_handler::callback(Request* req)
 {
	Response* res = new Response();
    res->setHeader("Content-Type", "text/html");
	ostringstream body;
	vector<string> shelv_list ;
	body<<"<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
        <<"\n<title>my_Shelvs</title>\n<style>\nbody {\nbackground-color: rgb(230, 36, 126);\n } \n div {\nwidth: 60%;\ncolor: blue;\nmargin: auto;\n}\n</style>\n</head>";
	body<<"<body>\n<h2>my_shelvs</h2>\n";
	string new_shelf_name = req->getQueryParam("new_shelf_name");
if (new_shelf_name.size() > 0)
	{
		string new_shelf_id = good_eat->post_shelve(new_shelf_name);
		body << "\n <script> \n alert(\"new_shelf_id : " + new_shelf_id + "\"); \n </script>";
	}

	body<<"<br><br>\n<div>\n <ul>";
	 try {
		shelv_list = good_eat->get_shelves();
	 }
	 catch (Error& e)
	 {
		 body <<"<li>"+e.get_error()+"</li>";
		 shelv_list = {};
	 }
    for (int i = 0; i < shelv_list.size() ; i++)
	{
		vector<string> shelf_info = divide_line(shelv_list[i],' ');
		body << "<li> <a href=\"/shelf_page?id="+shelf_info[0]+"\">"+shelf_info[1]+"</a> <ul>";
		body << "<li>" + shelf_info[0] + "</li></ul>\n</li>";
		
	}
	body<<"</ul>\n</div>\n<br>\n<br>\n<form action=\"/shelvs\">\n <label for=\"add_shelf\">add_shelf:</label>\n<br>\n<input type=\"text\" name=\"new_shelf_name\" id=\"add_shelf\" required>"
	    <<"\n<input type=\"submit\">\n </form>\n<a href=\"/user\">return</a></body>\n</html>";

	res->setBody(body.str());
     return res;
 }


 Response* Logout_handler::callback(Request* req)
 {
	 Response* res = new Response();
	 good_eat->process("logout");
	 res = Response::redirect("/");
	 res->setSessionId("");
  return res;      
 }



 Response* Filter_handler::callback(Request* req)
 {
	 Response* res = new Response();
	 ostringstream body;
	 string filter_type = req->getQueryParam("id");
	 string result;
	 if(filter_type == "filter1")
	 {
		result = good_eat->process("type_filter "+req->getQueryParam("type_filter"));
	 }
	 else if(filter_type == "filter2")
	 {
		result = good_eat->process("time_filter "+req->getQueryParam("min_time")+" "+req->getQueryParam("max_time"));
	 }
	 else if(filter_type == "filter3")
	 {
		result = good_eat->process("rate_filter "+req->getQueryParam("min_rate")+" "+req->getQueryParam("max_rate"));
	 }
	 else if (filter_type == "delete")
	 {
		 result = good_eat->process( "DELETE filters" );
	 }
	 string status = "/user?status=filter "+result;
	 res = Response::redirect(status);	
	
	return res;      
 }


 Response* Recipe_page_handler::callback(Request* req)
 {
	Response* res = new Response();
	ostringstream body;
	string recipe_id = req->getQueryParam("id");
    res->setHeader("Content-Type", "text/html");
	string status = req->getQueryParam("status");
	string recipe_info = good_eat->get_recipe(recipe_id);
	vector<string> recipe_items = divide_line(recipe_info,',');
	body << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">";
    body << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>"+recipe_items[1]+"</title>";
	body << "<style>\ndiv {\nfloat: left;\nwidth: 50%;\n }\n div a {\n color: blue;\ntext-decoration: underline;\n }\n body {\n   background-color: burlywood;\n }";
    body << "img {\ndisplay: block;\n margin-left: auto;\n margin-right: auto;\n width: 50%;\n}\n</style>\n</head>\n<body>\n<h3>"+recipe_items[1]+"</h3>";
     if (status.size() > 0)
	{
		vector<string> status_items = divide_line(status,' ');
	 if(status_items[0] == "rate")
		{
			if(status_items[1] == "OK")
			body << "\n <script> \n alert(\"successful\"); \n </script>";
			else
			{
				body << "\n <script> \n alert(\"Error : "+status_items[1]+"\"); \n </script>";
			}
		}
	}
    body << "<img src=\""+good_eat->get_recipe_img(recipe_id)+"\" alt=\"recipe_image\" >\n<div>\n<ul>\n";
	for(int i = 0 ; i < recipe_items.size();i++)
	{
		
		if(recipe_items[i] == "ingredients:" || recipe_items[i] == "tags:")
		{
			body << "<li>"+recipe_items[i];
			body << "<ul>\n";
			i++;
			while( recipe_items[i].compare(0,18,"minutes to ready: ") && recipe_items[i].compare(0,8,"rating: "))
			{
				body << "<li>"+recipe_items[i]+"</li>";
				i++;
			}
			body << "</ul></li>\n";
		}
	
		body << "<li>"+recipe_items[i]+"</li>";

	}		
    body << "</ul>\n</div>\n<div>\n<p><b>choose rate if you have not rated before<br> and choose edit_rate if have rated before</b></p>"
         << "<form action=\"/\" method=\"POST\" >\n <label for=\"rating\">rating:</label>\n <br>\n<input type=\"number\" step=\"0.01\" id=\"rating\" name=\"rate\" min=\"1.0\" max=\"5.0\" required>";
    body << "<input type=\"hidden\" name=\"recipe_id\" value=\""+recipe_id+"\">\n<input type=\"submit\" value=\"rate\" formaction=\"/rate_handler?type=rate\">"
         << "<input type=\"submit\" value=\"edit_rate\" formaction=\"/rate_handler?type=edit_rate\">\n</div>\n<a href=\"/user\">return</a></body>\n</html>";
	
	res->setBody(body.str());
     return res;
 }


 Response* Rate_handler::callback(Request* req)
 {
	 Response* res = new Response();
	 ostringstream body;
	 string rate_type = req->getQueryParam("type");
	 string id = req->getBodyParam("recipe_id");
	 string result;
	 if(rate_type == "rate")
	 {
		result = good_eat->process("rate "+id+" "+req->getBodyParam("rate"));
	 }
	 else if(rate_type == "edit_rate")
	 {
		result = good_eat->process("edit_rate "+id+" "+req->getBodyParam("rate"));
	 }
	
	 string status = "/recipe_page?id="+id+"&status=rate "+result;
	 res = Response::redirect(status);	
	return res;      
 }


 	Response* Shelf_handler::callback(Request* req)
    {
	Response* res = new Response();
	ostringstream body;
	string shelf_id = req->getQueryParam("id");
	string shelf_name = good_eat->get_shelf_name(shelf_id);
    res->setHeader("Content-Type", "text/html");
	string result = req->getQueryParam("result");
	if(result.size() > 0)
	{
		if( result == "OK")
			  body << "\n <script> \n alert(\"successful\"); \n </script>";
			else
			{
			  body << "\n <script> \n alert(\"Error : "+result+"\"); \n </script>";
			}
	}
	body<< "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
        << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>"+shelf_name+"</title>\n<style>\nbody {\nbackground-color: burlywood;\n}" 
        << "div {\nwidth: 60%;\ncolor: blue;\nmargin: auto;\n}\n</style>\n</head>\n<body>";
	body<< "\n<h3 style=\"text-align:center;\">shelf: "+shelf_name+"<br>id: "+shelf_id+"</h3>";
    body<< "<div>\n<ul>";
	vector<string> recipes;
		 try {
		recipes = good_eat->get_shelve_recipes(shelf_id);
	 }
	 catch (Error& e)
	 {
		 body <<"<li>"+e.get_error()+"</li>";
		 recipes = {};
	 }
	 
 	
	for(int i =  0 ; i < recipes.size();i++)
	{
		vector<string>recipe_items = divide_line(recipes[i],',');
		body << "<li> <a href=\"/recipe_page?id="+recipe_items[0]+"\">"+recipe_items[1]+"</a> <ul>";
		for (int j = 0; j < recipe_items.size(); j++)
		{
			if ( j==1 )
				continue;
			body << "<li>" + recipe_items[j] + "</li>";
		}
		
			body << "</ul></li>";
	}
	body << "</ul></div>";
    body << "<form action=\"/edit_shelf\" method=\"POST\">\n<label for=\"recipe_id\">recipe_id : </label>\n<br>\n<input type=\"number\" name=\"recipe_id\" id=\"recipe_id\">"
         << "<input type=\"submit\" value=\"delete\" formaction=\"/edit_shelf?type=delete\">\n <input type=\"hidden\" name=\"shelf_id\" value=\""+shelf_id+"\">\n<input type=\"submit\" value=\"add\" formaction=\"/edit_shelf?type=add\">"
         << "</form>\n<a href=\"/user\">return</a></body>\n</html>";

	res->setBody(body.str());
     return res;
 	}


 	Response* Edit_shelf::callback(Request* req)
 	{
	 Response* res = new Response();
	 ostringstream body;
	 string shelf_id = req->getBodyParam("shelf_id");
	 string recipe_id = req->getBodyParam("recipe_id");
	 string type = req->getQueryParam("type");
	 string result;
	 if(type == "add")
	 result = good_eat->process("add_shelf_recipe "+shelf_id+" "+recipe_id);
	 else if(type == "delete")
	 result = good_eat->process("delete_shelf_recipe "+shelf_id+" "+recipe_id);
	 

	 string status = "/shelf_page?id="+shelf_id+"&result="+result;
	 res = Response::redirect(status);	
	
	 return res; 
	 }


 	Response* Chef_handler::callback(Request* req)
 	{
	Response* res = new Response();
	ostringstream body;
	string result;
	vector<string> recipes;
	string type = req->getQueryParam("type");
	
	
	
	if (type.size() > 0)
	{
		if(type == "add")
		{
			vector<string> recipe_info;
			recipe_info.push_back(req->getBodyParam("title"));
			recipe_info.push_back(req->getBodyParam("ingredients"));
			recipe_info.push_back(req->getBodyParam("vegetarian"));
			recipe_info.push_back(req->getBodyParam("min_to_ready"));
			recipe_info.push_back(req->getBodyParam("tags"));
			recipe_info.push_back(req->getBodyParam("img"));

			result = good_eat->post_recipe(recipe_info);
		}
		else if( type == "delete")
		{
			string recipe_id = req->getBodyParam("recipe_id");
			result = good_eat->process("delete_recipe "+recipe_id);
		}
	}
    res->setHeader("Content-Type", "text/html");

	body << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"UTF-8\">\n<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
         << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n<title>Chef</title>\n<style>#d1 {background-color: aquamarine; }\nbody {\nbackground-color: burlywood;\n}" 
         << "div {\nwidth: 60%;\ncolor: blue;\nmargin: auto;\n}\n h2 {text-align: center;}\n</style>\n</head>\n<body><h2>wellcom to good_eat <br> chef: "+good_eat->get_username()+"</h2>";
	if (type == "add")
	{
		body << "\n <script> \n alert(\"new recipe_id : "+result+"\"); \n </script>";
	}
	if(type == "delete")
	{
		if(result == "OK")
			body << "\n <script> \n alert(\"successful\"); \n </script>";
		else
		{
			body << "\n <script> \n alert(\"Error : "+result+"\"); \n </script>";
		}
	}
	body <<"<div>";
	try
	{
		recipes = good_eat->get_my_recipes();
	}
	catch (Error& e)
	{
		body <<"<ul><li>"+e.get_error()+"</li></ul>";
		recipes = {};
	}
	for (int i = 0; i < recipes.size();i++)
	{
		body << "<ul>";
		vector<string> recipe_items = divide_line(recipes[i],',');
		for(int i = 0 ; i < recipe_items.size();i++)
		{
			if(recipe_items[i] == "ingredients:" || recipe_items[i] == "tags:")
			{
			body << "<li>"+recipe_items[i];
			body << "<ul>\n";
			i++;
			while( recipe_items[i].compare(0,18,"minutes to ready: ") && recipe_items[i].compare(0,8,"rating: "))
			{
				body << "<li>"+recipe_items[i]+"</li>";
				i++;
			}
			body << "</ul></li>\n";
			}

			body << "<li>"+recipe_items[i]+"</li>";
		}	
		body << "</ul>";
	}
	body << "</div>\n<div>\n<form action=\"/chef?type=add\" method=\"POST\">\n<p>add recipe :</p>\n<label for=\"title\">recipe title :</label>\n<input type=\"text\" name=\"title\" id=\"title\" required>"
         << "<br>\n<p>note <b>delimiter is ','</b></p>\n<label for=\"‫‪ingredients\">‫‪ingredients‬‬ : </label>\n<textarea name=\"ingredients\" id=\"ingredients\" cols=\"30\" rows=\"10\" required></textarea>"
         << "<br>\n<label for=\"‫‪vegetarian\">‫‪vegetarian‬‬ : </label>\n<select name=\"vegetarian\" id=\"vegetarian\" required>\n<option value=\"Yes\">Yes</option>\n<option value=\"No\">No</option>\n</select>"
         << "<br>\n<label for=\"min_to_ready\">‫‪minutes_to_ready : ‬‬</label>\n<input type=\"number\" id=\"min_to_ready\" min=\"0\" name=\"min_to_ready\" required>\n<br>\n<p>note <b>delimiter is ','</b></p>"
         << "<label for=\"tags\">tags : </label>\n<input type=\"text\" size=\"50\" id=\"tags\" name=\"tags\"required>\n<br>\n<label for=\"image\">image address : </label>\n<input type=\"url\" name=\"img\" id=\"image\" required>"
         << "<br>\n<input type=\"submit\">\n</form>\n</div>\n<div id=\"d1\">\n<form action=\"/chef?type=delete\" method=\"POST\">\n<p style=\"color: crimson;\">please enter recipe id for deleting</p>\n<label for=\"delete_recipe\">delete_recipe : </label>";
    body << "<input type=\"number\" name=\"recipe_id\" id=\"delete_recipe\" required>\n<br>\n<input type=\"submit\" >\n</form>\n\n<br>\n<a href=\"/logout\">logout</a>\n</div>\n</body>\n</html>";

	res->setBody(body.str());
     return res;
 	}

void run()
{
	Good_eat* my_good_eat = new Good_eat();
	Good_eat* ptr1 = my_good_eat;
    Server server(8080);
    server.get("/",new ShowPage("base.html"));
    server.get("/login",new ShowPage("login.html"));
	server.post("/login",new Login_handler(my_good_eat));
    server.get("/signup",new ShowPage("signup.html"));
	server.post("/signup",new Signup_handler(my_good_eat));
	server.get("/error",new Error_handler());
	server.get("/user",new User_handler(my_good_eat));
	server.get("/filter",new Filter_handler(my_good_eat));
	server.get("/shelvs",new Shelvs_handler(my_good_eat));
	server.get("/shelf_page",new Shelf_handler(my_good_eat));
	server.post("/edit_shelf",new Edit_shelf(my_good_eat));
	server.get("/recipe_page",new Recipe_page_handler(my_good_eat));
	server.post("/rate_handler",new Rate_handler(my_good_eat));
	server.get("/logout", new Logout_handler(my_good_eat));
	Chef_handler* chef_handler = new Chef_handler(my_good_eat);
	server.get("/chef", chef_handler);
	server.post("/chef", chef_handler);
	server.run();
}
int main()
{
  run();
}
