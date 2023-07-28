/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:38:14 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/28 16:40:26 by mwallage         ###   ########.fr       */
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
	{
		free_tab(whole_cmd);
		handle_error(cmd);
	}
}

void	do_pipe(char *cmd, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		handle_error("pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("fork error");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		exec(cmd, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
}

void	heredoc_input(char *delimiter, int pipefd[2])
{
	char	*input;

	close(pipefd[0]);
	while (1)
	{
		input = get_next_line(STDIN_FILENO);
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(input);
			exit(0);
		}
		ft_putstr_fd(input, pipefd[1]);
		free(input);
	}	
}

void	heredoc(char *delimiter)
{	
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		handle_error("pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("fork error");
	if (pid == 0)
		heredoc_input(delimiter, pipefd);
	if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		wait(NULL);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	fd_in;
	int	fd_out;

	if (argc < 5)
		handle_error("infile cmd1 cmd2 ... outfile");
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			handle_error("not enough arguments");
		i = 2;
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
		heredoc(argv[2]);
	}
	else
	{
		fd_in = open(argv[1], O_RDONLY, 0777);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd_in, 0);
		i = 1;
	}
	while (++i < argc - 2)
		do_pipe(argv[i], envp);
	dup2(fd_out, 1);
	exec(argv[argc - 2], envp);
}
