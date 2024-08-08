/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:35 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 20:15:47 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	fork_failed(int fork_err)
{
	if (!fork_err)
		perror("fork");
	fork_err = 1;
	return ;
}

void	second_child(t_ast *ast, t_shell *sh, int *fd, int *status)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (fork_failed(sh->fork_err));
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		ast->right->token->right_pipe = 1;
		traverse_tree(ast->right, sh);
		exit(sh->exit_status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, status, 0);
	sh->exit_status = exit_status_code(*status);
}

void	dup_stin(int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}

void	pipe_operator(t_ast *ast, t_shell *sh)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (!ast || ast->token->name != PIPE)
		return ;
	if (pipe(fd) < 0)
		return (perror("pipe"));
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (fork_failed(sh->fork_err));
	if (pid == 0)
	{
		dup_stin(fd);
		ast->left->token->left_pipe = 1;
		traverse_tree(ast->left, sh);
		exit(sh->exit_status);
	}
	if (!sh->fork_err)
		second_child(ast, sh, fd, &status);
	while (wait(NULL) < 0 && !sh->fork_err)
		;
}
