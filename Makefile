# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dteemo <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 11:58:34 by dteemo            #+#    #+#              #
#    Updated: 2020/02/05 11:58:37 by dteemo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

### PATH ###
SRCS_PATH = srcs/
OBJ_PATH  = obj/
LIBFT_PATH = libft/
INC_FILES = includes/ft_printf.h includes/libft.h

FLAGS = -Wall -Wextra -Werror
INC = -I ./includes/ -I ./$(LIBFT_PATH)
HEADERS = libft.h ft_ls.h

SRCS_NAME = ft_printf.c \
			args.c \
			bonus.c \
			nbrs.c \
			strs.c \
			helpers.c \
			helpers2.c \
			convert_f.c \
			convert_f_helpers.c \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(INC_FILES)
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "\033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
