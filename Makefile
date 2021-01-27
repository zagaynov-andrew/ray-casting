# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nforce <nforce@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:10:51 by ngamora           #+#    #+#              #
#    Updated: 2021/01/27 15:24:22 by nforce           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
GNL_NAME		= gnl.a
PROCESSOR_DIR	= processor/
T_PH_DIR		= t_ph/
LIBFT_DIR		= ./libs/libft/
GNL_DIR			= ./libs/gnl/
SRCS_DIR		= ./srcs/
OBJS_DIR		= objs/
CC				= gcc
CC_FLAGS		= -Wall -Wextra -Werror

LIBFT_SRCS	=	ft_memset.c		\
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
				ft_str_is_empty.c	\
				ft_lli_len.c		\
				ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstclear.c		\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_vec/ft_vec_new.c		\
				ft_vec/ft_vec_push.c	\
				ft_vec/ft_vec_free.c

GNL_SRCS	=	get_next_line.c		\
				get_next_line_utils.c

SRCS	=	$(SRCS_DIR)parser.c					\
			$(SRCS_DIR)parser_utils.c			\
			$(SRCS_DIR)parse_configs.c			\
			$(SRCS_DIR)parse_configs_utils.c	\
			$(SRCS_DIR)s_scene.c				\
			$(SRCS_DIR)map.c					\
			$(SRCS_DIR)test.c

OBJS			= $(notdir $(SRCS:.c=.o))
OBJS_PATH		= $(addprefix $(OBJS_DIR), $(OBJS))
LIBFT_OBJ_PATH	= $(addprefix $(LIBFT_DIR)$(OBJS_DIR), $(notdir $(LIBFT_SRCS:.c=.o)))
GNL_OBJ_PATH	= $(addprefix $(GNL_DIR)$(OBJS_DIR), $(GNL_SRCS:.c=.o))

$(LIBFT_DIR)$(OBJS_DIR)%.o : $(LIBFT_DIR)%.c $(LIBFT_DIR)libft.h
	@$(MAKE) bonus -C $(LIBFT_DIR)
$(LIBFT_DIR)$(OBJS_DIR)%.o : $(LIBFT_DIR)ft_vec/%.c $(LIBFT_DIR)libft.h
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(GNL_DIR)$(OBJS_DIR)%.o : $(GNL_DIR)%.c $(GNL_DIR)get_next_line.h
	@mkdir -p $(GNL_DIR)$(OBJS_DIR)
	@echo "\e[1;31m- Done :\e[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c cub3d.h
	@mkdir -p $(OBJS_DIR)
	@echo "\e[1;31m- Done :\e[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_OBJ_PATH) $(GNL_OBJ_PATH) $(OBJS_PATH)
	@ar r $(NAME) $(LIBFT_OBJ_PATH) $(GNL_OBJ_PATH) $(OBJS_PATH)
	@echo "\e[1;31;42m=====cub3D IS COMPLETED======\e[0m"

all: $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -Rf $(OBJS_DIR)
	rm -Rf $(GNL_DIR)$(OBJS_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(GNL_NAME)										
	rm -f $(NAME)

re: fclean all

#####################################################################
g:
	@gcc -g srcs/*.c libs/gnl/*.c libs/libft/libft.a
#####################################################################

.PHONY : all clean fclean re
