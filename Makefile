# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/05 20:21:35 by yel-yaqi          #+#    #+#              #
#    Updated: 2024/08/08 10:33:04 by yel-yaqi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

USER			:= $(shell whoami)
ERASE			= \033[2K\r
ORANGE			= \033[38;5;214m
TEAL			= \033[38;5;228m
RED				= \033[38;5;196m
GREEN			= \033[92m
NEON			= \033[38;5;51m
PURPLE			= \033[38;5;92;1m
RESET			= \033[0m
CFLAGS_R		= -O3 -Wall -Wextra -Werror -g -lreadline \
				   -fsanitize=address \
				   -fsanitize=pointer-subtract -fsanitize=pointer-compare \
				   -fno-omit-frame-pointer -O1
CFLAGS			= -O3 -Wall -Wextra -Werror -g -Werror -Wshadow -Wconversion -Wformat \
				   -Wnull-dereference -Wunused
NAME			= minishell
LIB_DIR			= ./libft
LIBFT			= $(LIB_DIR)/libft.a
MAIN_SOURCES 	= src/parser_engine/syntax_analyser/check_tokenizer_output.c \
			src/parser_engine/tokenizer/make_irregular_arguments.c \
			src/parser_engine/tokenizer/type_files_and_limiters.c \
			src/parser_engine/parser/put_args_into_cmd_tokens.c \
			src/parser_engine/syntax_analyser/quotes_balanced.c \
			src/parser_engine/parser/set_expansion_indices.c \
			src/parser_engine/syntax_analyser/check_tokens.c \
			src/parser_engine/parser/connect_redirections.c \
			src/parser_engine/parser/build_redirections.c \
			src/parser_engine/parser/build_redir_branch.c \
			src/parser_engine/tokenizer/name_operators.c \
			src/parser_engine/parser/connect_pipelines.c \
			src/parser_engine/parser/set_env_var_ends.c \
			src/parser_engine/parser/build_pipelines.c \
			src/parser_engine/tokenizer/is_operator.c \
			src/parser_engine/parser/remove_quotes.c \
			src/parser_engine/tokenizer/classify.c \
			src/parser_engine/tokenizer/tokenize.c \
			src/parser_engine/parser/build_list.c \
			src/parser_engine/parser/fetch_ast.c \
			src/parser_engine/tokenizer/multi.c \
			src/parser_engine/parser/parse.c \
			src/parser_engine/parser/para.c \
			src/expand/expand_heredoc.c \
			src/expand/wildcard_utils.c \
			src/builtins/unset_append.c \
			src/expand/expand_remove.c \
			src/utils/heredoc_utils.c \
			src/utils/split/strlcpy.c \
			src/builtins/env_shlvl.c \
			src/utils/split/strlen.c \
			src/utils/split/quoted.c \
			src/utils/split/substr.c \
			src/utils/split/strdup.c \
			src/utils/split/split.c \
			src/utils/redir_utils.c \
			src/builtins/export_u.c \
			src/builtins/builtins.c\
			src/exec/redirections.c \
			src/utils/prompt_line.c \
			src/utils/envp_list.c \
			src/builtins/export.c \
			src/utils/char_utils.c \
			src/expand/wildcard.c \
			src/utils/strequal.c \
			src/builtins/unset.c \
			src/builtins/exit.c \
			src/expand/expand.c \
			src/builtins/echo.c \
			src/exec/traverse.c \
			src/exec/here_doc.c\
			src/exec/command.c \
			src/builtins/env.c \
			src/builtins/pwd.c \
			src/builtins/cd.c \
			src/exec/and_or.c \
			src/minishell_.c \
			src/exec/path.c \
			src/exec/pipe.c \
			src/utils/gc.c \
			src/signal.c \
			src/list.c \

MAIN_OBJ 	= $(MAIN_SOURCES:.c=.o)

HEADER 		= include/minishell.h include/structs.h include/exec.h include/builtins.h libft/libft.h

define PRINT_LOADING
	@for i in $(shell seq 0 15); do \
		printf "\033[2K\r$(NEON)Compiling src/$*.c... $(NEON)[ "; \
		for j in $$(seq 0 $$i); do printf "▓"; done; \
		for j in $$(seq $$i 15); do printf " "; done; \
		printf "]$(RESET)"; \
	done; \
	printf ""
endef

define MINISHELL_ART
\n\033[38;5;214;7m\033[0m\
\t\t\033[33;92;1m╔╦╗╦╔╗╔╦╔═╗╦ ╦╔═╗╦  ╦  \033[0m\n\
\t\t\033[33;92;1m║║║║║║║║╚═╗╠═╣║╣ ║  ║  \033[0m\n\
\t\t\033[33;92;1m╩ ╩╩╝╚╝╩╚═╝╩ ╩╚═╝╩═╝╩═╝\033[0m\n\
\033[0m
endef

CFLAGS_R += -L/Users/$(USER)/.brew/opt/readline/lib

all: $(NAME)
	@printf "%b\n" "$(value MINISHELL_ART)"
	@echo "\t\t\t$(GREEN)IS READY$(RESET)"

check: $(TARGET_TEST)

libft: $(LIBFT)

src/%.o: src/%.c $(HEADER) Makefile
	$(PRINT_LOADING)
	@cc -c $< -o $@ $(CFLAGS)

$(NAME): $(MAIN_OBJ) $(LIBFT)
	@cc $^ -o $@ $(CFLAGS_R)

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR)
clean:
	@echo "$(RED)Cleaning up...$(RESET)"
	@$(RM) $(MAIN_OBJ)
	@$(MAKE) -C libft/ clean
	@echo "$(RED)clean finished$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft/ fclean
	@echo "$(RED)fclean finished$(RESET)"

re: fclean all


.PHONY: check
