# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cfeijoo <cfeijoo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/03 17:38:57 by cfeijoo           #+#    #+#              #
#    Updated: 2013/12/11 13:57:16 by cfeijoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

LIBNAME = ft
LIBFOLDER = libft
INCFOLDER = libft/includes

SRC	= ft_ls.c \
	  main.c
	
OSRC = $(SRC:.c=.o)

CFLAGS = -g -Wall -Wextra -Werror
CC = gcc

$(NAME):
	@echo "\n**** COMPILING $(NAME)\n"
	$(CC) $(CFLAGS) -I $(INCFOLDER) -c $(SRC)
	$(CC) $(CFLAGS) -L $(LIBFOLDER) -l $(LIBNAME) $(OSRC) -o $(NAME)

updatelib:
	@echo "\n**** UPDATING LIB\n"
	cd $(LIBFOLDER)	\
	&& git pull
	make -C $(LIBFOLDER) re

clean:
	if [ -f $(OSRC) ]; \
		then /bin/rm -f $(OSRC); \
	fi

fclean: clean
	if [ -f $(NAME) ]; \
		then /bin/rm -f $(NAME); \
	fi

re: fclean $(NAME)
