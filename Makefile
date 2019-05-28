#-------------------------- Key Values ---------------------------------------
NAME		:=	wolf3d
CFLAGS		:=	-Wall -Werror -Wextra
CC			:=	gcc

DIR_INC		:=	includes/
DIR_SRC		:=	srcs/
DIR_OBJ		:=	objs/
CH_SRC		:=	c
CH_OBJ		:=	o

DIR_LIB		:=	libft/
DIR_LIB_INC	:=	$(DIR_LIB)

LIBFT		:=	$(DIR_LIB)libft.a
MLX			:=	-L minilibx -lmlx -framework OpenGL -framework AppKit

#-------------------------- Paths --------------------------------------------

DIR_DRAW	:=	$(DIR_SRC)draw/

#-------------------------- Header files -------------------------------------
COR_H		:=	$(DIR_INC)fractol.h

#-------------------------- Source files -------------------------------------
COR_C		:=	#$(DIR_DRAW)burning_ship.c\#
				$(DIR_SRC)main.c

#-------------------------- Init OBJ, INC ------------------------------------
OBJ			:=	$(patsubst $(DIR_SRC)%,$(DIR_OBJ)%,\
				$(COR_C:.$(CH_SRC)=.$(CH_OBJ)))

INC			:=	$(addprefix -I, $(DIR_LIB_INC) $(DIR_INC))

#-------------------------- Make ---------------------------------------------
all: lib $(DIR_OBJ) $(NAME)

lib:
	@make -C $(DIR_LIB)

$(DIR_OBJ):
	@mkdir -p $(DIR_OBJ)

#-------------------------- Link Block ---------------------------------------
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT) $(MLX)
	@echo "Linking" [ $(NAME) ]

#-------------------------- Compil Block -------------------------------------
#COR
$(DIR_OBJ)%.$(CH_OBJ): $(DIR_SRC)%.$(CH_SRC)\
$(COR_H)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@echo "Compiling" [ $< ]

#-------------------------- Clean --------------------------------------------
clean:
	@make -C $(DIR_LIB) clean
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files $(NAME) ]"

fclean:
	@make -C $(DIR_LIB) fclean
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files $(NAME) ]"
	@rm -f $(NAME)
	@echo "Clean" [ $(NAME) ]

re: fclean all

.PHONY: all clean fclean re
