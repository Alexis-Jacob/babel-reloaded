##
## Makefile for make in /home/jeremy/Epitech/Tek3/babel
## 
## Made by jeremy
## Login   <jeremy@epitech.net>
## 
## Started on  Wed Nov  7 10:59:00 2012 jeremy
## Last update Tue Nov 20 10:28:40 2012 jeremy
##

NAME	=	serveur

GXX	=	g++

RM	=	rm -rf

SRC	=	$(wildcard src/*.cpp)

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS +=	-std=c++0x -Wall -W -g3 $(INCLUDE)

LIB	=	-lboost_regex -lboost_thread -lboost_serialization -lboost_system -lboost_date_time -pthread

INCLUDE =	-Iheaders/

$(NAME)	:	$(OBJ)
		$(GXX) -o $(NAME) $(OBJ) $(LIB) $(INCLUDE)

all	:	$(NAME)

clean	:
		$(RM) *.o *~ \#*\# src/*.o
		rm `find . -name "*~"`

fclean	:	clean
		$(RM) $(NAME)
re	:	fclean all

.PHONY	:	all clean fclean re
