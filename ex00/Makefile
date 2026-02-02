CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp BitcoinExchange.cpp
OBJ = $(SRC:.cpp=.o)
NAME = btc

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $@ $^

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re