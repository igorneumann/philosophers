# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/29 18:51:16 by ineumann          #+#    #+#              #
#    Updated: 2021/08/26 19:06:30 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
SRCS			=	philo.c lists.c utils.c lists_utils.c phil_states.c
CC				=	@gcc -g -Wall -Wextra -Werror -g3 -fsanitize=address -pthread

all: $(NAME)

$(NAME): 
	$(CC) $(SRCS) $(LIBS) -o $(NAME)

norm:
	norminette -R ./

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm
