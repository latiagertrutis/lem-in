# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jagarcia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 17:20:08 by jagarcia          #+#    #+#              #
#    Updated: 2018/09/04 17:50:14 by mrodrigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re exe

NAME = lem-in

CFLAGS =  #-Wall -Wextra -Werror -g3 #-fsanitize=address

FUNCS =			main.c \
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
				check_link_format.c \
				ft_print_map.c \
				free_info.c \
				check_double_links.c

OBJ_DIR = objects/
LIBFT_DIR = libft/
FUNCS_DIR = srcs/
INCLUDES_DIR = includes/
GRAPHIC_DIR = srcs/graphics/

LIBFT_NAME = libft.a
LIBFT_ABREV = ft
HEADERS = lemin.h

HEADER_PATH = $(patsubst %.h, $(INCLUDES_DIR)%.h,$(HEADERS))
OBJ = $(patsubst %.c, $(OBJ_DIR)%.o,$(FUNCS))

MODE = 0

.PHONY: check_lib

ifeq ($(MODE), 1)

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(OBJ) -L$(LIBFT_DIR) -l$(LIBFT_ABREV) -I$(INCLUDES_DIR) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)%.o : $(FUNCS_DIR)%.c $(HEADER_PATH) $(LIBFT_DIR)$(LIBFT_NAME)
	@printf "\033[92m--->Compiling $(@F)\n\033[0m"
	@gcc $(CFLAGS) -c -I $(INCLUDES_DIR) $<
	@mkdir -p $(OBJ_DIR)
	@mv -f $(@F) $(OBJ_DIR)

else
$(NAME) : | check_lib $(OBJ)  

$(OBJ_DIR)%.o : $(FUNCS_DIR)%.c $(HEADER_PATH) $(LIBFT_DIR)$(LIBFT_NAME)
	@printf "\033[92mCreating $(NAME)\033[0m\n"
	@$(MAKE) MODE=1
	@printf "\033[92mDone $(NAME)[\xE2\x9C\x94]\n\033[0m"
endif

check_lib:
	@$(MAKE) -sC $(LIBFT_DIR)

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
