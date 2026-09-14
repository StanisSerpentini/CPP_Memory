NAME := CPP_Memory

SRC :=	main.cpp	\
		init_game.cpp	\
		main_loop.cpp	\
		help.cpp

CXX := g++

CXXFLAGS += -Wall -Wextra -Werror -std=c++20

LDFLAGS := -lfmt -lftxui-component -lftxui-dom -lftxui-screen

CPPFLAGS := -I./include -I/usr/local/include

SRC := $(addprefix src/, $(SRC))

OBJ := $(SRC:.cpp=.o)

RM := rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CXXFLAGS += -g3
debug: re

.PHONY: all clean fclean re debug
