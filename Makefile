NAME = ft_gkrellm

OBJ_DIR = obj
SRC_DIR = src

BASE_SRC = main.cpp \
\
		   AMonitorModule.cpp \
		   CPUModule.cpp \
		   DateModule.cpp \
		   OSModule.cpp \
		   UserModule.cpp \
\
		   NCurses.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(BASE_SRC:.cpp=.o))

FLAGS = -Wall -Wextra -Werror -I $(shell pwd)/inc/ -I ~/.brew/include
FLAGS_NC = -lncurses
FLAGS_SFML = -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,~/.brew/lib

$(NAME): build $(OBJ)
	@clang++ $(FLAGS) $(FLAGS_NC) -o $(NAME) $(OBJ)

all: $(NAME)

build:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
