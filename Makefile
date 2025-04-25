NAME        := so_long

# Compiler and Flags
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -Ofast

# Directories
SRC_DIR     := src
LIBFTDIR    := ./libft
MLX_DIR     := ./lib/MLX42

# Libraries
LIBFT       := $(LIBFTDIR)/libft.a
HEADERS     := -I$(LIBFTDIR) -I$(MLX_DIR)/include

# Adjust this if using 42Homebrew (uncomment the one you use)
GLFW_LIB    := -L/opt/homebrew/opt/glfw/lib       # Homebrew
# GLFW_LIB := -L/Users/$(USER)/.brew/opt/glfw/lib # 42Homebrew

FRAMEWORKS  := -framework Cocoa -framework OpenGL -framework IOKit
LIBS        := $(MLX_DIR)/build/libmlx42.a $(GLFW_LIB) -lglfw -ldl -pthread -lm $(FRAMEWORKS)

# Sources and Objects
SRCS        := $(wildcard $(SRC_DIR)/*.c)
OBJS        := $(SRCS:.c=.o)

# Targets
all: libmlx $(LIBFT) $(NAME)

libmlx:
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build > /dev/null
	@cmake --build $(MLX_DIR)/build -j4 > /dev/null

$(LIBFT):
	@make -C $(LIBFTDIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< && printf "Compiling: $(notdir $<)\n"

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFTDIR) clean
	@rm -rf $(MLX_DIR)/build

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx