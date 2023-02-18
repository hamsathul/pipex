# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkunnam- <hkunnam-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/18 11:48:04 by hkunnam-          #+#    #+#              #
#    Updated: 2023/02/18 17:32:01 by hkunnam-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address -static-libasan

RM = rm -rf

# Colors
GR	= \033[32;1m
RE	= \033[31;1m
YE	= \033[33;1m
CY	= \033[36;1m
RC	= \033[0m

SRCS = 	srcs/pipex.c\
		srcs/utls.c\
		srcs/error.c\
		libft/libft/libft.a\

SRCS_BONUS = 	srcs_bonus/pipex_bonus.c\
				srcs_bonus/utls_bonus.c\
				srcs_bonus/error_bonus.c\
				libft/libft/libft.a\

$(NAME) :
	@echo "\n$(GR)Generating Libft...$(RC)\n"
	@make all -C libft/libft/
	@echo "$(GR)Libft created!$(RC)\n"
	@echo "\n$(CY)Generating pipex executable...$(RC)\n"
	@gcc $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "$(GR)Done!$(RC)\n\n"

bonus :
	@echo "\n$(GR)Generating Libft...$(RC)\n"
	@make all -C libft/libft/
	@echo "$(GR)Libft created!$(RC)\n"
	@echo "\n$(CY)Generating pipex bonus executable...$(RC)\n"
	@gcc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)
	@echo "$(GR)Pipex bonus Done!$(RC)\n\n"

all : $(NAME)

fclean : clean
	@echo "\n$(YE)Cleaning all additional objects and libraries...$(RC)\n"
	@$(RM) $(NAME)
	@make fclean -C libft/libft/
	@echo "$(RE)All libraries removed!$(RC)\n"

clean :
	@echo "\n$(YE)Cleaning all object files...$(RC)\n"
	@$(RM) $(NAME)
	@make clean -C libft/libft/
	@echo "$(RE)objects removed!$(RC)\n"

re : fclean all

.PHONY: clean fclean re all