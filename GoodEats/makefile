CC=g++
STD=-std=c++11 -Wall -g
CF=$(STD)



all: goodeats.out


template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o template_parser.o

response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o response.o

request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o request.o

utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o utilities.o

server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o server.o

route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o route.o

main.o: main.cpp main.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c main.cpp -o main.o

goodeats.out: main.o response.o request.o utilities.o server.o route.o template_parser.o good_eat.o global.o member.o shelve.o recipe.o filter.o
	$(CC) $(CF) main.o response.o request.o utilities.o server.o route.o template_parser.o global.o member.o shelve.o recipe.o filter.o good_eat.o -o goodeats.out


 	
global.o: global.cpp global.hpp
	$(CC) -c global.cpp -o global.o	
		
		
member.o: member.cpp member.hpp 
	$(CC) -c member.cpp -o member.o
 	
shelve.o: shelve.cpp shelve.hpp error.hpp
	$(CC) -c shelve.cpp -o shelve.o
 	
recipe.o: recipe.cpp recipe.hpp error.hpp global.hpp
	$(CC) -c recipe.cpp -o recipe.o
 	
filter.o: filter.cpp filter.hpp error.hpp
	$(CC) -c filter.cpp -o filter.o	
 	
good_eat.o: good_eat.hpp good_eat.cpp
	$(CC) -c good_eat.cpp -o good_eat.o

.PHONY: clean
clean:
	rm -rf  *.o *.out
