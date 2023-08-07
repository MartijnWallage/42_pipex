/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:45:11 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/07 15:43:09 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(int pipefd[2], char **av, char **env)
{
	int		infile;
	char	*path;
	char	**whole_cmd;

	infile = open(av[1], O_RDONLY, 0777);
	if (infile == -1)
		handle_error(av[1]);
	dup2(infile, 0);
	dup2(pipefd[1], 1);
	close(infile);
	close_pipes(pipefd);
	whole_cmd = ft_split(av[2], ' ');
	path = get_path(whole_cmd[0], env);
	if (execve(path, whole_cmd, env) == -1)
	{
		if (ft_strcmp(path, whole_cmd[0]))
			free(path);
		free_tab(whole_cmd);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(av[2], 2);
		exit(0);
	}
}

static void	parent(int pipefd[2], char **av, char **env)
{
	int		outfile;
	char	*path;
	char	**whole_cmd;

	outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		handle_error(av[4]);
	dup2(outfile, 1);
	dup2(pipefd[0], 0);
	close(outfile);
	close_pipes(pipefd);
	whole_cmd = ft_split(av[3], ' ');
	path = get_path(whole_cmd[0], env);
	if (execve(path, whole_cmd, env) == -1)
	{
		if (ft_strcmp(path, whole_cmd[0]))
			free(path);
		free_tab(whole_cmd);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(av[3], 2);
		exit(127);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc < 5)
		handle_error("./pipex infile cmd1 cmd2 outfile");
	if (pipe(pipefd) == -1)
		handle_error("pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("fork error");
	if (pid == 0)
		child(pipefd, argv, envp);
	waitpid(pid, NULL, 0);
	parent(pipefd, argv, envp);
}
