# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/29 18:51:16 by ineumann          #+#    #+#              #
#    Updated: 2021/07/29 18:55:49 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
SRCS			=	philo.c
LIBFT			=	./includes/libft
CC				=	@gcc -g -Wall -Wextra -Werror -g3 -fsanitize=address -pthread

all: $(NAME)

$(NAME): $(CC) $(SRCS) $(LIBS) -o $(NAME)

norm:
	norminette -R ./

clean:
	@rm -f $(OBJS)
	@$(MAKE) -s clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re norm
