/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:09:27 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:51:41 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "structs.h"
# include <stdio.h>

/* Built-ins */

void	change_env_value(t_envp **env, char *name, char *new_value);
void	append_to_env(t_envp **env, char *name, char *value);
void	change_pwds(t_envp **env, char *pwd, char home);
void	shlvl_check(char *str, t_envp **env, t_shell *sh);
void	init_envp(char *envp[], t_envp **en);
void	add_empty(t_envp **env, char *var);
void	print_export_vars(t_envp *head);

int		exit_(char **strs, int last_exit_stat);
int		export_(t_envp *env, char **args);
int		unset_(t_envp **env, char **args);
int		cd_(char **args, t_envp **env);
int		is_spaces(char *str);
int		echo_(char **args);
int		env_(t_envp *head);
int		pwd_(t_envp *env);

size_t		first_occur(char *str, char h);

char	*search_env_name(t_envp *env, char *val);
char	*search_env(t_envp *env, char *val);
char	*add_dir(char *pwd, char *dir);
char	*oldpwd_(t_envp *env);

/* Utils */

void	addnode(t_envp **head, char *name, char *value);
char	**copy_env_to_arr(t_envp *env);
void	free_split(char **strs);
void	free_envp(t_envp *head);

int		print_error(char *str, char *arg);
int		count_char(char *str, char h);
int		is_tilde(char *s1, char *s2);
int		args_empty(char **args);
int		count_dots(char **dirs);
int		is_builtin(char *str);

t_envp	*create_node(char *name, char *value);
t_envp	*setup_basic_env(void);

#endif // !BUILTINS_H
