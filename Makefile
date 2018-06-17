# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jagarcia <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/05 17:20:08 by jagarcia          #+#    #+#              #
#    Updated: 2018/06/17 08:49:45 by mrodrigu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re exe

NAME = lem-in

CFLAGS =

LECTOR_FUNCS = main.c \
							 ft_reader.c\
							 ft_line_error.c
ALGO_FUNCS =

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

all : $(NAME)

$(NAME) : $(LECTOR_OBJ) $(LIBFT_DIR)$(LIBFT_NAME)
	gcc $(LECTOR_OBJ) -L$(LIBFT_DIR) -l$(LIBFT_ABREV) -I$(INCLUDES_DIR) $(CFLAGS) -o $(NAME)

$(LIBFT_DIR)$(LIBFT_NAME):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)%.o : $(LECTOR_DIR)%.c $(HEADER_PATH)
	gcc $(CFLAGS) -c -I $(INCLUDES_DIR) $<
	mkdir -p $(OBJ_DIR)
	mv -f $(@F) $(OBJ_DIR)

$(OBJ_DIR)%.o : $(ALGO_DIR)%.c $(HEADER_PATH)
	gcc $(CFLAGS) -c -I $(INCLUDES_DIR) $<
	mkdir -p $(OBJ_DIR)
	mv -f $(@F) $(OBJ_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean
	make
