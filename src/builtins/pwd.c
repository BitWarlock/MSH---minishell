/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:38 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:41 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * remove_last_dir: removes the last directory in the pwd path.
 *
 * @pwd: path to remove the last directory from.
 *
 * return: new path.
 *	NULL on failure.
 */

char	*remove_last_dir(char *pwd)
{
	char	*new_value;
	int		i;
	int		last_pos;

	if (!ft_strncmp(pwd, "/", 2) || (count_char(pwd, '/') == 1
			&& pwd[0] == '/'))
		return (free(pwd), ft_strdup("/"));
	last_pos = 0;
	i = 0;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			last_pos = i;
		i++;
	}
	new_value = ft_substr(pwd, 0, last_pos);
	if (!new_value)
		return (NULL);
	return (free(pwd), new_value);
}

/*
 * new_pwd: Updates the PWD envirement variable.
 *
 * @pwd: Current working directory.
 * @tmp: Copy of the Current working directory.
 * @new_value; new PWD envirement variable.
 * @dirs: the new directory splitted by '/'
 *
 * return: new PWD.
 *	NULL in case of failure.
 */

char	*new_pwd(char *pwd, char *tmp, char *new_value, char **dirs)
{
	int		i;

	if (!ft_strncmp(pwd, "/", 1))
		new_value = ft_strdup("/");
	else
		new_value = ft_strdup(tmp);
	i = -1;
	while (dirs[++i])
	{
		if (dirs[i] && !ft_strcmp(dirs[i], ".."))
		{
			if (ft_strncmp(new_value, "/", 2) != 0)
				new_value = remove_last_dir(new_value);
		}
		else if (dirs[i] && ft_strncmp(dirs[i], ".", 2))
			new_value = add_dir(new_value, dirs[i]);
	}
	return (free_split(dirs), new_value);
}

/*
 * handle_pwd: Updates the PWD envirement variable.
 *
 * @head: A pointer to the node that has PWD envirement variablel.
 * @pwd: Current working directory.
 * @home: A character representing the home directory (cd, or cd ~), h for home.
 */

void	handle_pwd(char home, char *pwd, t_envp *head)
{
	char	*tmp;
	char	*new_value;
	int		i;

	i = 0;
	tmp = head->value;
	new_value = NULL;
	if (home == 'h' || (pwd[0] == '/' && !pwd[1]))
	{
		new_value = ft_strdup(pwd);
		if (!new_value)
			return ;
	}
	else
		new_value = new_pwd(pwd, tmp, new_value, ft_split(pwd, "/"));
	if (!new_value)
		return ;
	head->value = new_value;
	free(tmp);
}

/*
 * change_pwds: Updates the PWD and OLDPWD variables.
 *
 * @env: A pointer to the head of linked list envirement variable.
 * @pwd: Current working directory.
 * @home: A character representing the home directory (cd, or cd ~).
 */

void	change_pwds(t_envp **env, char *pwd, char home)
{
	t_envp	*head;
	char	*tmp;
	char	*new_value;

	head = *env;
	while (head)
	{
		if (ft_strcmp(head->name, "OLDPWD") == 0)
		{
			tmp = head->value;
			new_value = ft_strdup(search_env(*env, "PWD"));
			if (new_value)
				head->value = new_value;
		}
		if (ft_strcmp(head->name, "PWD") == 0)
			handle_pwd(home, pwd, head);
		head = head->next;
	}
}

/*
 * pwd_: Prints the current working directory.
 *
 * @env: A pointer to the head of linked list envirement variable.
 *
 * @return:
 *	0 on success.
 *	1 in case of failure.
 */

int	pwd_(t_envp *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 3))
		{
			printf("%s\n", env->value);
			return (0);
		}
		env = env->next;
	}
	ft_printf(2, "Error: PWD is not set\n");
	return (1);
}
