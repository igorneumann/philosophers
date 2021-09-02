# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/29 18:51:16 by ineumann          #+#    #+#              #
#    Updated: 2021/09/02 19:23:47 by ineumann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PARAMS			=	4 20000 2000 2000
NAME			=	philo
SRCS			=	philo.c lists.c utils.c lists_utils.c phil_states.c the-killer.c
OBJS 			=	$(SRCS:.c=.o)
CC				=	@gcc -g -Wall -Wextra -Werror -g3 -fsanitize=address -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) $(LIBS) -o $(NAME)

run: re
	@./philo $(PARAMS)

norm:
	norminette -R ./

clean:
	@rm -f $(OBJS)
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re norm run
