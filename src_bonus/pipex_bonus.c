/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:44:55 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/07 15:06:22 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec(char *cmd, char **env, int exitcode)
{
	char	*path;
	char	**whole_cmd;

	whole_cmd = ft_split(cmd, ' ');
	path = get_path(whole_cmd[0], env);
	if (execve(path, whole_cmd, env) == -1)
	{
		if (ft_strcmp(path, whole_cmd[0]))
			free(path);
		free_tab(whole_cmd);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		exit(exitcode);
	}
}

void	child(char *cmd, char **env)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		handle_error("pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("pid error");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec(cmd, env, 0);
	}
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	heredoc(char *delimiter)
{
	char	*line;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		handle_error("pipe error");
	pid = fork();
	if (pid == -1)
		handle_error("pid error");
	while (pid == 0)
	{
		close(pipefd[0]);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, pipefd[1]);
		free(line);
	}
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

int	main(int ac, char **av, char **env)
{
	int		infile;
	int		outfile;
	int		i;

	if (ac < 5)
		handle_error("./pipex infile cmd1 cmd2 outfile");
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			handle_error("./pipex here_doc DELIMITER cmd1 cmd2 ... outfile");
		heredoc(av[2]);
		i = 2;
	}
	else
	{
		infile = open(av[1], O_RDONLY, 0777);
		dup2(infile, STDIN_FILENO);
		close(infile);
		i = 1;
	}
	while (++i < ac - 2)
		child(av[i], env);
	if (ft_strcmp(av[1], "here_doc") == 0)
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (outfile == -1)
		handle_error(av[ac -1]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	exec(av[ac - 2], env, 127);
}
