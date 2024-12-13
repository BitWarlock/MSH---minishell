/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:44 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/29 22:30:59 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"
# include <stdio.h>

void	expand_arg_entries(char **args, size_t *entry_i, char *pattern);
void	second_child(t_ast *ast, t_shell *sh, int *fd, int *status);
void	and_or_operators(t_ast *ast, t_shell *sh);
void	doc_close(t_ast *ast, t_shell *sh, int i);
void	heredoc_apply(t_ast *ast, t_shell *sh);
void	pipe_operator(t_ast *ast, t_shell *sh);
void	redirect_out(t_ast *ast, t_shell *sh);
void	redirect_app(t_ast *ast, t_shell *sh);
void	size_heredocs(t_ast *ast, int *size);
void	redirect_in(t_ast *ast, t_shell *sh);
void	here_doc(t_ast *ast, t_shell *sh);
void	command(t_ast *ast, t_shell *sh);
void	copy_to_stdin(char *tmp_file);
void	fork_failed(int fork_err);
void	dup_stin(int *fd);

char	*expand_in_heredoc(char *var, t_shell *sh, int expand_flag);
char	**check_expand(char **args, t_shell *sh, t_token *token);
char	*expand_(char *result, char *var, int *i, t_shell *sh);
char	*init_vars(int *i, int *j, char **tmp, char **result);
char	**wildcard_expansion(char **args, t_token *tokens);
char	**remove_null_values(char **args, int *is_null);
char	*copy_char(int *i, char *var, char *result);
char	*find_path(char *cmd, char *path_env);
char	*get_tmp_file_name(int i);
char	*hereoc_lim(t_ast *ast);

size_t		args_len(char **args);

ssize_t	entries_count(char **args);
ssize_t	entry_count(char *pattern);

int		character_valid(char c, int is_last, int join_string, char *input);
int		file_out_fd(char *token, t_ast *ast, t_shell *sh, char flag);
int		entry_pattern_match(const char *entry, const char *pattern);
int		match_suffix(const char *entry, const char *pattern);
int		set_exit_error(t_shell *sh, char *file, char *msg);
int		file_in_fd(t_ast *ast, t_shell *sh, char *file);
int		include_hidden(char first, char *entry);
int		*new_arr(char **args);

#endif // !EXEC_H
