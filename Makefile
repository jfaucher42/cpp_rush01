NAME = ft_gkrellm

OBJ_DIR = obj
SRC_DIR = src

BASE_SRC = main.cpp \
\
		   AMonitorModule.cpp \
		   CPUModule.cpp \
		   DateModule.cpp \
		   NetworkModule.cpp \
		   OSModule.cpp \
		   RAMModule.cpp \
		   UserModule.cpp \
		   VMModule.cpp \
\
		   NCurses.cpp \
			 Sfml.cpp

OBJ = $(addprefix $(OBJ_DIR)/, $(BASE_SRC:.cpp=.o))

FLAGS = -Wall -Wextra -Werror -I $(shell pwd)/inc/ -I ~/.brew/include
FLAGS_NC = -lncurses
FLAGS_SFML = -L ~/.brew/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-network -lsfml-audio -Wl,-rpath,~/.brew/opt/sfml/lib/

$(NAME): $(OBJ_DIR) $(OBJ)
	@export DYLD_LIBRARY_PATH=~/.brew/opt/sfml/lib/
	clang++ $(FLAGS) $(FLAGS_SFML) $(FLAGS_NC) -o $(NAME) $(OBJ)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	c++ $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
