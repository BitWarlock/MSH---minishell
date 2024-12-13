/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 05:08:59 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/02 21:25:34 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sig = SIGINT;

void	ignore_sigs(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		g_sig = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	disable_echo(void)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
		return ;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~(unsigned long)ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
}

void	init_signal(int *status)
{
	disable_echo();
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, signal_handler) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	if (!g_sig)
	{
		*status = 1;
		g_sig = SIGINT;
	}
}
