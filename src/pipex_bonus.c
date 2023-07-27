/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:38:14 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/27 16:39:46 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char *envp[])
{
	char	**whole_cmd;
	char	*path;
	int		len;
	
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

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	fd_in;
	int	fd_out;

	if (argc < 5)
		handle_error("infile cmd1 cmd2 ... outfile");
	// if here_doc do here_doc
	fd_in = open(argv[1], O_RDONLY, 0777);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(fd_in, 0);
	i = 1;
	while (++i < argc - 2)
		do_pipe(argv[i], envp);
	dup2(fd_out, 1);
	exec(argv[argc - 2], envp);
}
