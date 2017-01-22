NAME = ft_gkrellm

BASE_SRC = main.cpp \
\
		   AMonitorModule.cpp \
		   CPUModule.cpp \
		   UserModule.cpp \
\
		   NCurses.cpp

OBJ = $(addprefix obj/, $(BASE_SRC:.cpp=.o))

FLAGS = -Wall -Wextra -Werror -I $(shell pwd)/inc/

FLAGS_NC = -lncurses

$(NAME): build $(OBJ)
	@clang++ $(FLAGS) $(FLAGS_NC) -o $(NAME) $(OBJ)

all: $(NAME)

build:
	mkdir -p obj

obj/%.o: src/%.cpp
	clang++ $(FLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
