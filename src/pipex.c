/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:45:11 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/31 15:24:45 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(int pipefd[2], char **av, char **env)
{
	int		infile;
	char	*path;
	char	**whole_cmd;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
		handle_error(av[1]);
	dup2(infile, 0);
	dup2(pipefd[1], 1);
	close(pipefd[0]);
	whole_cmd = ft_split(av[2], ' ');
	path = get_path(whole_cmd[0], env);
	if (execve(path, whole_cmd, env) == -1)
	{
		close(infile);
		close(pipefd[1]);
		free(path);
		free_tab(whole_cmd);
		handle_error("command not found");
	}
}

void	parent(int pipefd[2], char **av, char **env)
{
	int		outfile;
	char	*path;
	char	**whole_cmd;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		handle_error(av[4]);	
	dup2(outfile, 1);
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	whole_cmd = ft_split(av[3], ' ');
	path = get_path(whole_cmd[0], env);
	if (execve(path, whole_cmd, env) == -1)
	{
		close(outfile);
		close(pipefd[0]);
		free(path);
		free_tab(whole_cmd);
		handle_error("command not found");
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc < 5)
		handle_error("Not enough arguments");
	if (pipe(pipefd) == -1)
		handle_error("pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("fork error");
	if (pid == 0)
		child(pipefd, argv, envp);
	parent(pipefd, argv, envp);
	return (0);
}
