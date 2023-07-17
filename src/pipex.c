/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:23:15 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/17 18:27:29 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

 void	handle_error()
{
	ft_printf("Error\n");
	exit(1);
}

void	exec(char *cmd, char *envp[])
{
	ft_printf("%s, %s", cmd, envp[0]);
/* 	char	**whole_cmd;
	char	*path;
	
	whole_cmd = ft_split(cmd, ' ');
	path = find_path(whole_cmd[0], envp);
	if (execve(path, whole_cmd, envp) == -1)
		handle_error(); */
}

void	parent(char *argv[], int pipe_fd[], char *envp[])
{
	int	fd;

	fd = open(argv[4], O_RDONLY | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		return (handle_error());
	dup2(fd, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	exec(argv[3], envp);
}

void	child(char *argv[], int pipe_fd[], char *envp[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		return (handle_error());
	dup2(fd, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	exec(argv[2], envp);
}

int	main(int argc, char *argv[], char **envp)
{
 	int		pipe_fd[2];
	pid_t	pid;
	
	if (argc != 5)
		return (1);
	if (pipe(pipe_fd) == -1)
		handle_error();
	pid = fork();
	if (pid == -1)
		handle_error();
	if (pid == 0)
		child(argv, pipe_fd, envp);
	parent(argv, pipe_fd, envp);
	return (0);
}