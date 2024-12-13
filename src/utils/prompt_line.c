/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:38:13 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/02 11:38:14 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*simple_pwd(char *pwd, char *home)
{
	char			*rest_path;
	char			*simplified;
	unsigned int		len;

	if (!home)
		return (pwd);
	len = (unsigned int)ft_strlen(home);
	if (ft_strncmp(pwd, home, ft_strlen(home)))
		return (pwd);
	rest_path = ft_substr(pwd, len, ft_strlen(pwd) - len);
	simplified = ft_strjoin("~", rest_path);
	return (simplified);
}

char	*ps1_prompt(char *pwd, char *home, int exit_status)
{
	char	*prompt;
	char	*tmp;

	tmp = "\001"ORANGE"\002┏━\001"RED"\002🅼.🆂.🅷 \001"
		ORANGE"\002════«\001\e[30m"RED"\002";
	if (!pwd)
		pwd = ft_strdup("");
	prompt = ft_strjoin(tmp, simple_pwd(pwd, home));
	if (!exit_status)
		prompt = ft_strjoin(prompt, "\001\e[0m"ORANGE"\002»\n┗━☿️\001"
				GREEN"\002➠\001\e[0m \002");
	else
		prompt = ft_strjoin(prompt, "\001\e[0m"ORANGE"\002»\n┗━☿️\001"
				REDD"\002➠\001\e[0m \002");
	if (!prompt)
		return (NULL);
	return (prompt);
}

int	check_line(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (1);
		str++;
	}
	return (0);
}

char	**ls_colored(char **cmds)
{
	char	**new_cmds;
	size_t	len;
	size_t	i;

	len = 0;
	while (cmds[len])
		len++;
	new_cmds = gc_malloc(sizeof(char *) * (len + 2), COLLECT);
	if (!new_cmds)
		return (perror("malloc"), NULL);
	new_cmds[0] = cmds[0];
	new_cmds[1] = ft_strdup("-G");
	i = 1;
	while (i <= len)
	{
		new_cmds[i + 1] = cmds[i];
		i++;
	}
	new_cmds[i] = NULL;
	return (new_cmds);
}

char	*check_cwd_valid(t_envp **env)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
		return (tmp);
	print_error("cd: error retrieving current directory: ",
			"getcwd: cannot access parent directories: No such file or directory");
	change_env_value(env, "PWD", remove_last_dir(search_env(*env, "PWD")));
	chdir(search_env(*env, "PWD"));
	return (NULL);
}
