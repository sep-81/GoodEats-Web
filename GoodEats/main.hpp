#ifndef MAIN_H
#define MAIN_H
#include "./server/server.hpp"
#include "good_eat.hpp"

class Signup_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Signup_handler(Good_eat* good) : good_eat(good) {}
 Response* callback(Request* req);
 

};
class Login_handler : public RequestHandler 
{
private:
	Good_eat* good_eat;
public:
	Login_handler(Good_eat* good) : good_eat(good) {}
 Response* callback(Request* req);
 

};
class Error_handler : public RequestHandler
{
private:

public:
	 Response* callback(Request* req);
	

};

class User_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	User_handler(Good_eat* good) : good_eat(good) {}
    Response* callback(Request* req);
 

};

class Shelvs_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Shelvs_handler(Good_eat* good) : good_eat(good) {}
    Response* callback(Request* req);
 


};
class Logout_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Logout_handler(Good_eat* good) : good_eat(good) {}
    Response* callback(Request* req);
 

};
class Filter_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Filter_handler(Good_eat* good) : good_eat(good) {}
    Response* callback(Request* req);

};
class Recipe_page_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
 Recipe_page_handler(Good_eat* good) : good_eat(good) {}
 Response* callback(Request* req);
 
};


class Rate_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Rate_handler(Good_eat* good) : good_eat(good) {}
    Response* callback(Request* req);
 
};


class Shelf_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Shelf_handler(Good_eat* good) : good_eat(good) {}
 	Response* callback(Request* req);
 
};


class Edit_shelf : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Edit_shelf(Good_eat* good) : good_eat(good) {}
 	Response* callback(Request* req);
 	
};
class Chef_handler : public RequestHandler
{
private:
	Good_eat* good_eat;
public:
	Chef_handler(Good_eat* good) : good_eat(good) {}
 	Response* callback(Request* req);
 
};

void run();





#endif