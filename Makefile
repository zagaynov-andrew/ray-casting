# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:10:51 by ngamora           #+#    #+#              #
#    Updated: 2021/03/31 18:23:06 by ngamora          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
GNL_NAME		= gnl.a
PROCESSOR_DIR	= processor/
T_PH_DIR		= t_ph/
LIBFT_DIR		= ./libs/libft/
GNL_DIR			= ./libs/gnl/
MLX_DIR			= ./libs/minilibx-linux/
PARSER_DIR		= parser/
ENGINE_DIR		= engine/
MANDATORY_DIR	= mandatory/
BONUS_DIR		= bonus/
SRCS_DIR		= ./srcs/
OBJS_DIR		= objs/
CC				= gcc
CC_FLAGS		= -Wall -Wextra -Werror
MLX_FLAGS = -L./libs/minilibx-linux -lmlx -L%%%%/lib -lXext -lX11 -lm -lbsd

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
				ft_strcmp.c		\
				ft_str_is_empty.c	\
				ft_lli_len.c		\
				ft_is_whitespace.c	\
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

SRCS	=	$(SRCS_DIR)$(PARSER_DIR)parser.c				\
			$(SRCS_DIR)$(PARSER_DIR)parser_utils.c			\
			$(SRCS_DIR)$(PARSER_DIR)parse_configs.c			\
			$(SRCS_DIR)$(PARSER_DIR)parse_configs_utils.c	\
			$(SRCS_DIR)$(PARSER_DIR)int_overflow.c	\
			$(SRCS_DIR)$(PARSER_DIR)parse_texture_path.c	\
			$(SRCS_DIR)$(PARSER_DIR)map.c					\
			$(SRCS_DIR)$(PARSER_DIR)map_utils.c				\
			$(SRCS_DIR)$(PARSER_DIR)s_scene.c				\
			$(SRCS_DIR)$(ENGINE_DIR)drawer.c				\
			$(SRCS_DIR)$(ENGINE_DIR)dda.c					\
			$(SRCS_DIR)$(ENGINE_DIR)vec2.c					\
			$(SRCS_DIR)$(ENGINE_DIR)vec2f.c					\
			$(SRCS_DIR)$(ENGINE_DIR)vec2f_utils.c			\
			$(SRCS_DIR)$(ENGINE_DIR)player.c				\
			$(SRCS_DIR)$(ENGINE_DIR)side.c					\
			$(SRCS_DIR)$(ENGINE_DIR)is_wall.c				\
			$(SRCS_DIR)$(ENGINE_DIR)textures.c				\
			$(SRCS_DIR)$(ENGINE_DIR)textures_utils.c		\
			$(SRCS_DIR)$(ENGINE_DIR)game.c					\
			$(SRCS_DIR)$(ENGINE_DIR)sprite_utils.c			\
			$(SRCS_DIR)$(ENGINE_DIR)bmp.c					\
			$(SRCS_DIR)$(ENGINE_DIR)is_corner.c				\
			$(SRCS_DIR)$(ENGINE_DIR)engine.c				\
			$(SRCS_DIR)errors.c								\
			$(SRCS_DIR)main.c

SRCS_MANDATORY	=	$(SRCS_DIR)$(MANDATORY_DIR)hook.c		\
					$(SRCS_DIR)$(MANDATORY_DIR)movement.c	\
					$(SRCS_DIR)$(BONUS_DIR)sprite.c

SRCS_BONUS		=	$(SRCS_DIR)$(BONUS_DIR)hook_bonus.c		\
					$(SRCS_DIR)$(BONUS_DIR)movement_bonus.c	\
					$(SRCS_DIR)$(BONUS_DIR)sprite_bonus.c

OBJS			= $(notdir $(SRCS:.c=.o))
OBJS_PATH		= $(addprefix $(OBJS_DIR), $(OBJS))
LIBFT_OBJ_PATH	= $(addprefix $(LIBFT_DIR)$(OBJS_DIR), $(notdir $(LIBFT_SRCS:.c=.o)))
GNL_OBJ_PATH	= $(addprefix $(GNL_DIR)$(OBJS_DIR), $(GNL_SRCS:.c=.o))
OBJS_MANDATORY			= $(notdir $(SRCS_MANDATORY:.c=.o))
OBJS_MANDATORY_PATH		= $(addprefix $(OBJS_DIR), $(OBJS_MANDATORY))
OBJS_BONUS			= $(notdir $(SRCS_BONUS:.c=.o))
OBJS_BONUS_PATH		= $(addprefix $(OBJS_DIR), $(OBJS_BONUS))

$(LIBFT_DIR)$(OBJS_DIR)%.o : $(LIBFT_DIR)%.c $(LIBFT_DIR)libft.h
	@$(MAKE) bonus -C $(LIBFT_DIR)
$(LIBFT_DIR)$(OBJS_DIR)%.o : $(LIBFT_DIR)ft_vec/%.c $(LIBFT_DIR)libft.h
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(GNL_DIR)$(OBJS_DIR)%.o : $(GNL_DIR)%.c $(GNL_DIR)get_next_line.h
	@mkdir -p $(GNL_DIR)$(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(SRCS_DIR)cub3d.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(PARSER_DIR)%.c $(SRCS_DIR)cub3d.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(ENGINE_DIR)%.c $(SRCS_DIR)cub3d.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(MANDATORY_DIR)%.c $(SRCS_DIR)cub3d.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)$(BONUS_DIR)%.c $(SRCS_DIR)cub3d.h
	@mkdir -p $(OBJS_DIR)
	@echo "\033[1;31m- Done :\033[0m $<"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(NAME): $(LIBFT_OBJ_PATH) $(GNL_OBJ_PATH) $(OBJS_PATH) $(OBJS_MANDATORY_PATH)
	@$(MAKE) -C $(MLX_DIR)
	@echo "\033[1;31;42m=====MLX IS COMPLETED======\033[0m\n"
	@gcc -o $(NAME) $(LIBFT_OBJ_PATH) $(GNL_OBJ_PATH) $(OBJS_PATH) $(OBJS_MANDATORY_PATH) $(MLX_FLAGS)
	@echo "\033[1;31;42m=====cub3D IS COMPLETED======\033[0m\n"
	@echo "\033[1;33m __   __    ______    ______    __    __    ______    ______    ______    "
	@echo "/\ \`-.\ \  /\  ___\  /\  __ \  /\ \`-./  \  /\  __ \  /\  == \  /\  __ \   "
	@echo "\ \ \-.  \ \ \ \__ \ \ \  __ \ \ \ \-./\ \ \ \ \/\ \ \ \  __<  \ \  __ \  "
	@echo " \ \_\\\\\\\`\_\ \ \_____\ \ \_\ \_\ \ \_\ \ \_\ \ \_____\ \ \_\ \_\ \ \_\ \_\ "
	@echo "  \/_/ \/_/  \/_____/  \/_/\/_/  \/_/  \/_/  \/_____/  \/_/ /_/  \/_/\/_/ \033[0m"

all: $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	rm -Rf $(OBJS_DIR)
	rm -Rf $(GNL_DIR)$(OBJS_DIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(GNL_NAME)										
	rm -f $(NAME)

re: fclean all

bonus: $(LIBFT_OBJ_PATH) $(GNL_OBJ_PATH) $(OBJS_PATH) $(OBJS_BONUS_PATH)
	@$(MAKE) -C $(MLX_DIR)
	@echo "\033[1;31;42m=====MLX IS COMPLETED======\033[0m\n"
	@gcc -o $(NAME) $(LIBFT_OBJ_PATH) $(GNL_OBJ_PATH) $(OBJS_PATH) $(OBJS_BONUS_PATH) $(MLX_FLAGS)
	@echo "\033[1;31;42m=====cub3D bonus IS COMPLETED======\033[0m\n"
	@echo "\033[1;33m __   __    ______    ______    __    __    ______    ______    ______    "
	@echo "/\ \`-.\ \  /\  ___\  /\  __ \  /\ \`-./  \  /\  __ \  /\  == \  /\  __ \   "
	@echo "\ \ \-.  \ \ \ \__ \ \ \  __ \ \ \ \-./\ \ \ \ \/\ \ \ \  __<  \ \  __ \  "
	@echo " \ \_\\\\\\\`\_\ \ \_____\ \ \_\ \_\ \ \_\ \ \_\ \ \_____\ \ \_\ \_\ \ \_\ \_\ "
	@echo "  \/_/ \/_/  \/_____/  \/_/\/_/  \/_/  \/_/  \/_____/  \/_/ /_/  \/_/\/_/ \033[0m"

.PHONY : all clean fclean re bonus
