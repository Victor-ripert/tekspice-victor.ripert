##
## EPITECH PROJECT, 2026
## cPoolDay4
## File description:
## Makefile
##

NAME = nanotekspice

CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I.

SRC = components/AComponent.cpp \
      components/AndComponent.cpp \
      components/ClockComponent.cpp \
      components/FalseComponent.cpp \
      components/InputComponent.cpp \
      components/NotComponent.cpp \
      components/OutputComponent.cpp \
      components/TrueComponent.cpp \
      components/XorComponent.cpp \
	components/OrComponent.cpp \
      components/NorComponent.cpp \
      components/NandComponent.cpp \
      components/Component4071.cpp \
      components/Component4001.cpp \
      components/Component4011.cpp \
      components/Component4030.cpp \
      components/Component4081.cpp \
      core/Circuit.cpp \
      core/Factory.cpp \
      core/FileReader.cpp \
      core/NanoTekSpiceExceptions.cpp \
      core/UserInput.cpp\
	main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
