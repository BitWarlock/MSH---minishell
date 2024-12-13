/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:48:14 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/09 00:27:50 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <dirent.h>

# include "../libft/libft.h"
# include "structs.h"
# include "builtins.h"
# include "exec.h"

# define BACKWARDS 0
# define FORWARDS 1

/* Error codes */

# define ERR_NOFILE 127
# define ERR_NOCMD  127
# define ERR_NOPERM 126

/* Error messages */

# define MSG_NOFILE "No such file or directory"
# define MSG_NOCMD  "Command not found"
# define MSG_NOPERM "Permission denied"

/* garbage collector defines */
# define NO_SIZE 0
# define CLEAR 0
# define COLLECT 1

/* types */
# define NOTHING_TYPED -1
# define OPERATOR 0
# define COMMAND 1
# define ARGUMENT 2
# define PARA_OPEN 3
# define PARA_CLOSE 4
# define AND_OR 5
# define PARA 6
# define FILE 7
# define LIMITER 8

/* names */
# define NONE -1
# define AND 0
# define OR 1
# define PIPE 2
# define REDIR_OUT 3
# define REDIR_IN 4
# define HERE_DOC 5
# define REDIR_APP 6
# define NOT_OP 7
# define LIMITER 8

# define YELLOW "\e[38;5;214m"
# define RED	"\e[38;5;226m"
# define REDD	"\e[31m"
# define GREEN "\e[32m"
# define ORANGE "\e[38;5;51m"

/* parser */
void	tokenize(char **word_list, t_token **token_list);
void	build_simple(t_token *token, t_token *cmd);
void	build_compound(t_token *token, int marker);
void	make_irregular_arguments(t_token *tokens);
void	put_args_into_cmd_tokens(t_token *tokens);
void	type_files_and_limiters(t_token *tokens);
void	set_tokens_expansion_indices(t_token *tokens);
void	append(t_token *node, t_token **list);
void	connect_redirections(t_token *tokens);
void	build_redirections(t_token *tokens);
void	connect_pipelines(t_token *token);
void	rl_replace_line(char *str, int a);
void	name_operators(t_token *tokens);
void	remove_quotes(t_token *tokens);
void	connect_para(t_token *tokens);
void	multi(char *word, t_token **token_list);
void	classify(t_token *token_list);
void	build_list(t_token *start);
void	set_env_var_ends(char *expr, size_t *var_ends_arr);

t_token	*search(t_token *from, int name, int direction);
t_token	*simplify_para(t_token *tokens);
t_token	*init_node(char *word);

t_ast	*build_ast(char *expr, t_shell *sh);
t_ast	*fetch_ast(t_token *tokens);

int		check_builtins(char *str, t_envp **env, t_shell *sh);
int		check_tokenizer_output(t_token *tokens);
int		is_heredoc_operator(t_token *token);
int		is_redir_operator(t_token *token);
int		build_pipelines(t_token *token);
int		quotes_balanced(char *line);
int		check_tokens(char *line);
int		is_operator(char *word);
int		is_quoted(char c);

size_t	count_substrs(char *str, char *charset);
size_t	count_vars(char *expr);

bool	strequal(char *str0, char *str1);

/* garbage collector */
void	*gc_malloc(size_t size, int lever);

char	**ft_split(char *str, char *charset);

int		in_charset(char c, char *charset);

/* Signals */

void	init_signal(int *sigint);
void	signal_handler(int sig);
void	disable_echo(void);

/* Execution */

void	builtins_exe(char *cmd, t_ast *node, t_shell *sh);
void	increment_vars(int *i, int *j, size_t *arr_index);
void	traverse_tree(t_ast *ast, t_shell *sh);
void	ignore_sigs(void);
void	increment_shlvl(t_envp **env);
int		execute_cmd(char **cmd, char *env[], t_shell *sh, t_ast *ast);

char	*ps1_prompt(char *pwd, char *home, int exit_status);
char	*check_cwd_valid(t_envp **env);
char	*remove_last_dir(char *pwd);
char	**ls_colored(char **cmds);

int		check_line(const char *str);
int		exit_status_code(int exit_code);

#endif
