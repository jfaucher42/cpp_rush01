NAME = ft_gkrellm

BASE_SRC = main.cpp \
		   AMonitorModule.cpp \
		   CPUModule.cpp \
		   NCurses.cpp \
		   UserModule.cpp \
			 Sfml.cpp

OBJ = $(addprefix obj/, $(BASE_SRC:.cpp=.o))

FLAGS = -Wall -Wextra -Werror -I $(shell pwd)/inc/ -I ~/.brew/include
FLAGS_NC = -lncurses
FLAGS_SFML = -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,~/.brew/lib

$(NAME): build $(OBJ)
	@clang++ $(FLAGS) $(FLAGS_SFML) $(FLAGS_NC) -o $(NAME) $(OBJ)

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
