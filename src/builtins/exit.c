/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:31 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/02 19:57:42 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Returns the exit status based on whether the process
 * was terminated by a signal.
 * If the process was signaled the exit code is 128 + signal number.
 * Else the exit code returned as-is.
 */

int	exit_status_code(int exit_code)
{
	if (WIFSIGNALED(exit_code))
	{
		if (WTERMSIG(exit_code) == SIGINT)
			write (1, "\n", 1);
		else if (WTERMSIG(exit_code) == SIGQUIT)
			printf("Quit: 3\n");
		return (128 + WTERMSIG(exit_code));
	}
	return (WEXITSTATUS(exit_code));
}

/*
 * check_arg: check whether the argument is numeric.
 * if not exit print error and exit with 255 exit status.
 *
 * @arg: argument passed to exit.
 * @strs: commands.
 * @env: linked list containing environment variables.
 */

void	check_arg(char *arg, int *status)
{
	int	i;

	i = -1;
	if ((arg[0] == '-' || arg[0] == '+') && ft_strlen(arg) != 1)
		i++;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]) || (ft_atoi(arg) == -1 && ft_strlen(arg) > 15))
		{
			gc_malloc(0, 0);
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", arg);
			exit(255);
		}
	}
	*status = ft_atoi(arg) & 0xFF;
}

void	exit_now(int exit_status)
{
	gc_malloc(0, 0);
	printf("exit\n");
	exit(exit_status);
}

/*
 * exit_: exits the shell with optional exit status.
 *
 * @strs: optional exit status.
 * @env: linked list containing environment variables.
 */

int	exit_(char **strs, int last_exit_stat)
{
	int	exit_status;

	if (!strs)
		exit_now(last_exit_stat);
	if (strs[1])
	{
		check_arg(strs[1], &exit_status);
		if (strs[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return (1);
		}
	}
	exit_status = 0;
	if (strs[1])
		check_arg(strs[1], &exit_status);
	else
		exit_status = last_exit_stat;
	exit_now(exit_status);
	return (0);
}
