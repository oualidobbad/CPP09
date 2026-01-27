CXX = c++
CXXFLAGS = -Wall -Wextra -Werror 
SRC = main.cpp RPN.cpp
OBJ = $(SRC:.cpp=.o)
NAME = RPN

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