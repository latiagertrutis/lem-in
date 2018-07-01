# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jagarcia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 17:20:08 by jagarcia          #+#    #+#              #
#    Updated: 2018/07/01 21:46:57 by jagarcia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re exe

NAME = lem-in

CFLAGS = -fsanitize=address

LECTOR_FUNCS =	main.c \
				ft_reader.c\
				ft_line_error.c \
				ft_check_number_of_ants.c \
				check_comment_line.c \
				ft_ini_node.c \
				ft_set_links.c \
				ft_search_paths.c \
				ft_algorithm.c \
				ft_prepare_conjunts.c \
				ft_abs_double.c \
				ft_solve_system.c \
				ft_cuantity_of_ants.c \
				ft_solution.c \
				ft_distribute_ants.c \
				ft_depure_graf.c \
				algorithm_funcs1.c \
				algorithm_funcs2.c \
				searcher_funcs.c \
				resize_links.c \
				check_link_format.c

OBJ_DIR = objects/
LIBFT_DIR = libft/
LECTOR_DIR = srcs/
ALGO_DIR =
INCLUDES_DIR = includes/
GRAPHIC_DIR = srcs/graphics/

LIBFT_NAME = libft.a
LIBFT_ABREV = ft
HEADERS = lem-in.h

HEADER_PATH = $(patsubst %.h, $(INCLUDES_DIR)%.h,$(HEADERS))
LECTOR_OBJ = $(patsubst %.c, $(OBJ_DIR)%.o,$(LECTOR_FUNCS))
ALGO_OBJ = $(patsubst %.c, $(OBJ_DIR)%.o,$(ALGO_FUNCS))

OBJ = $(MAIN_OBJ) $(ALGO_OBJ)

all : | $(LIBFT_DIR)$(LIBFT_NAME) $(NAME)

$(NAME) :
	@printf "\033[92mCreating $(NAME)\033[0m\n"
	@$(MAKE) $(LECTOR_OBJ) 
	@gcc $(LECTOR_OBJ) -L$(LIBFT_DIR) -l$(LIBFT_ABREV) -I$(INCLUDES_DIR) $(CFLAGS) -o $(NAME)
	@printf "\033[92mDone $(NAME)[\xE2\x9C\x94]\n\033[0m"


$(LIBFT_DIR)$(LIBFT_NAME):
	@$(MAKE) -sC $(LIBFT_DIR)

$(OBJ_DIR)%.o : $(LECTOR_DIR)%.c $(HEADER_PATH)
	@printf "\033[92m--->Compiling $(@F)\n\033[0m"
	@gcc $(CFLAGS) -c -I $(INCLUDES_DIR) $<
	@mkdir -p $(OBJ_DIR)
	@mv -f $(@F) $(OBJ_DIR)

clean:
	@printf "\033[92m***Cleaning Objects***\033[0m\n"
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@printf "\033[92m***Cleaning Executables & Libraries***\033[0m\n"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	@make
