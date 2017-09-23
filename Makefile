# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nocardoz <nocardoz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/21 14:12:44 by nocardoz          #+#    #+#              #
#    Updated: 2017/09/22 20:06:37 by nocardoz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
LIBFT = libs/libft

# HEADERS = headers $(LIBFT)

FILESC = srcs/*.c
# FILESO = 

.PHONY: all clean fclean re

all: $(NAME)

# $(FILESO):
#	@gcc -Wall -Wextra -Werror -c $(FILESC)
# $(FILESO)
$(NAME):
	@gcc $(FILESC) -o $(NAME) -I headers -I $(LIBFT) -L$(LIBFT) -lft

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
