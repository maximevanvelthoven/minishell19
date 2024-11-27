#---------------------------------------------------------#

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

GFLAGS	=	-g

#DFLAGS	=	-fsanitize=address -fsanitize=undefined
#---------------------------------------------------------#

SRC_DIR	=	src

SRC		=	$(shell find $(SRC_DIR) -type f -name "*.c")

OBJ = $(SRC:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)


INC_DIR	=	Include

LIB_DIR	=	libft42

LIB		=	$(LIB_DIR)/libft.a


.PHONY: all lib clean fclean libclean re
#---------------------------------------------------------#

NAME	=	minishell

all:		$(NAME)

lib:		$(LIB)

$(NAME):	$(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(DFLAGS) $(GFLAGS) $(OBJ) -o $@ -L$(LIB_DIR) -lft -lreadline

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(SRC_DIR)/%.o:	$(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIB_DIR)/$(INC_DIR) -c $< -o $@
#---------------------------------------------------------#

clean:
	rm -rf $(OBJ)

fclean:		clean
	rm -rf $(NAME) *dSYM

libclean:
	rm -rf $(LIB_DIR)/$(OBJ_DIR)
	rm -rf $(LIB)

re: fclean all

libre: libclean lib
