/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:29:31 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/12 16:29:31 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*join_path(char *path, char *cmd)
{
	char	*tmp;
	char	*new_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		perror("Malloc");
	new_path = ft_strjoin(tmp, cmd);
	if (!new_path)
		perror("Malloc");
	free(tmp);
	return (new_path);
}

char	*find_path(char *cmd, char *env[], t_shell *sh)
{
	char	*path_env;
	char	**paths;
	char	*path;
	int		i;

	path_env = search_env(sh->env, "PATH");
	paths = ft_split(path_env, ":");
	i = 0;
	while (paths[i])
	{
		path = join_path(paths[i], cmd);
		if (!access(path, F_OK))
			return (free_split(paths), path);
		free(path);
		i++;
	}
	free_split(paths);
	return (NULL);
}

int	execute_cmd(char **cmd, char *env[], t_shell *sh)
{
	char	*path;
	char	*path_env;
	int		pid;

	path_env = search_env(sh->env, "PATH");
	if (!path_env)
		return (print_error(cmd[0], "No such file or directory"), 127);
	path = find_path(cmd[0], env, sh);
	if (!path)
		return (print_error(cmd[0], "Command not found"), 127);
	if (access(path, X_OK) != 0)
		return (print_error(cmd[0], "Permission denied"), 126);
	pid = fork();
	if (!pid)
		execve(path, cmd, env);
	else
		waitpid(pid, &sh->exit_status, 0);
	return (free(path), WEXITSTATUS(sh->exit_status));
}
