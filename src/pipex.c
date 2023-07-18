/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:23:15 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/18 16:06:10 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char *envp[])
{
	char	**whole_cmd;
	char	*path;
	
	whole_cmd = ft_split(cmd, ' ');
	path = find_path(whole_cmd[0], envp);
	if (execve(path, whole_cmd, envp) == -1)
		handle_error("Execve error");
}

void	parent(char *argv[], int pipe_fd[], char *envp[])
{
	int	fd;

	fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (handle_error("Open error"));
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
		return (handle_error("Open error"));
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
		handle_error("Pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("Fork error");
	if (pid == 0)
		child(argv, pipe_fd, envp);
	parent(argv, pipe_fd, envp);
	return (0);
}