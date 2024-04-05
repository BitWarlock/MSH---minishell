# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 20:21:35 by yel-yaqi          #+#    #+#              #
#    Updated: 2024/04/05 21:02:18 by yel-yaqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

TARGET_TEST = test

TARGET_TEST_SOURCES = checks/bct_tests.c \

MAIN_SOURCES = src/bct.c

ALL_SOURCES = $(MAIN_SOURCES) $(TARGET_TEST_SOURCES)

HEADER = include/minishell.h

MAIN_OBJ = $(MAIN_SOURCES:.c=.o)

TEST_OBJ = $(TARGET_TEST_SOURCES:.c=.o)

all: $(NAME)

check: $(TARGET_TEST)

src/%.o: src/%.c $(HEADER) Makefile
	cc $(CFLAGS) -c $< -o $@

checks/%.o: checks/%.c $(HEADER) Makefile
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(MAIN_OBJ) $(HEADER) Makefile
	cc $(CFLAGS) $(MAIN_OBJ) -o $@

$(TARGET_TEST): $(TEST_OBJ) $(HEADER) Makefile
	cc $(CFLAGS) $(TEST_OBJ) -o $@

clean:
	rm -f src/*.o
	rm -f checks/*.o

fclean: clean
	rm -f minishell

re: fclean all

.PHONY: check