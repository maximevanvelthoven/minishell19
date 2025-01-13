#---------------------------------------------------------#
CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

GFLAGS	=	-g

# DFLAGS	=	-fsanitize=address -fsanitize=undefined

#---------------------------------------------------------#
SRC_DIR	=	src

SRC		=	$(shell find $(SRC_DIR) -type f -name "*.c")

OBJ_DIR	=	obj

OBJ		=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

INC_DIR	=	Include

LIB_DIR	=	libft42

LIB		=	$(LIB_DIR)/libft.a

#---------------------------------------------------------#
NAME	=	minishell

all:		$(NAME)

lib:		$(LIB)

$(NAME):	$(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(GFLAGS) $(OBJ) -o $@ -L$(LIB_DIR) -lft -lreadline

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(GFLAGS) -I$(INC_DIR) -I$(LIB_DIR)/$(INC_DIR) -c $< -o $@

#---------------------------------------------------------#
clean:
	rm -rf $(OBJ_DIR)

fclean:		clean
	rm -rf $(NAME) *dSYM

libclean:
	rm -rf $(LIB_DIR)/$(OBJ_DIR)
	rm -rf $(LIB)

re: fclean all

.PHONY: all lib clean fclean libclean re