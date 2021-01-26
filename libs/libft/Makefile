# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nforce <nforce@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/15 17:57:46 by ngamora           #+#    #+#              #
#    Updated: 2021/01/27 00:26:15 by nforce           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror

SRCS	=	ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memccpy.c	\
			ft_memmove.c 	\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strlen.c		\
			ft_isalpha.c 	\
			ft_isdigit.c	\
			ft_isalnum.c	\
			ft_isascii.c	\
			ft_isprint.c	\
			ft_toupper.c	\
			ft_tolower.c	\
			ft_strchr.c		\
			ft_strrchr.c	\
			ft_strncmp.c	\
			ft_strlcpy.c	\
			ft_strlcat.c	\
			ft_strnstr.c	\
			ft_atoi.c		\
			ft_calloc.c		\
			ft_strdup.c		\
			ft_substr.c		\
			ft_strjoin.c 	\
			ft_strtrim.c	\
			ft_split.c		\
			ft_itoa.c		\
			ft_strmapi.c	\
			ft_putchar_fd.c	\
			ft_putstr_fd.c	\
			ft_putendl_fd.c	\
			ft_putnbr_fd.c	\
			ft_putnstr_fd.c	\
			ft_abs.c		\
			ft_llitoa.c		\
			ft_itoa_base.c	\
			ft_strupcase.c	\
			ft_str_is_empty.c		\
			ft_lli_len.c			\
			ft_vec/ft_vec_new.c		\
			ft_vec/ft_vec_push.c	\
			ft_vec/ft_vec_free.c

SRCS_BONUS	=	ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstclear.c		\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				$(SRCS)

OBJS_DIR = objs/
OBJS = $(notdir $(SRCS:.c=.o))
OBJS_PATH = $(addprefix $(OBJS_DIR), $(OBJS))
OBJS_BONUS = $(notdir $(SRCS_BONUS:.c=.o))
OBJS_BONUS_PATH = $(addprefix $(OBJS_DIR), $(OBJS_BONUS))


$(OBJS_DIR)%.o : %.c libft.h
	@mkdir -p $(OBJS_DIR)
	@echo "\e[1;31m- Done :\e[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : ft_vec/%.c libft.h
	@mkdir -p $(OBJS_DIR)
	@echo "\e[1;31m- Done :\e[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS_PATH)
	@ar r $(NAME) $(OBJS_PATH)
	@echo "\e[1;31;42m=====LIBFT IS COMPLETED======\e[0m"

all: $(NAME)

clean:
	rm -Rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJS_BONUS_PATH)
	@ar r $(NAME) $(OBJS_BONUS_PATH)
	@echo "\e[1;31;42m=====FULL LIBFT IS COMPLETED======\e[0m"

.PHONY : $(NAME) all clean fclean re
