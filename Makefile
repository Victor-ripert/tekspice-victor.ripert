##
## EPITECH PROJECT, 2026
## cPoolDay4
## File description:
## Makefile
##

NAME = Test

CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror

SRC = AComponent.cpp\
AndComponent.cpp\
ClockComponent.cpp\
FalseComponent.cpp\
InputComponent.cpp\
main.cpp\
NotComponent.cpp\
OrComponent.cpp\
OutputComponent.cpp\
TrueComponent.cpp\
XorComponent.cpp\
Circuit.cpp\
Factory.cpp\
FileReader.cpp\
UserInput.cpp\
 NanoTekSpiceExceptions.cpp


OBJ = $(SRC:.cpp=.o)

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
