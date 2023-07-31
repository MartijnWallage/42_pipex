/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:44:55 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/31 13:10:25 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_error(char *info)
{
	char	*errno_readable;
	int		len;

	errno_readable = strerror(errno);
	len = ft_strlen(errno_readable);
	write(2, "pipex: ", 7);
	write(2, errno_readable, len);
	len = ft_strlen(info);
	write(2, ": ", 2);
	write(2, info, len);
	write(2, "\n", 1);
	exit(1);
}

void	free_tab(char **tab)
{
	int	i;
	
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	*try_paths(char *cmd, char **paths)
{
	int		i;
	char	*whole_cmd;
	char	*temp;
	
	i = 0;
	while (paths[i])
	{
		whole_cmd = ft_strjoin(paths[i], "/");
		temp = whole_cmd;
		whole_cmd = ft_strjoin(whole_cmd, cmd);
		free(temp);
		if (access(whole_cmd, F_OK | X_OK) == 0)
			return (whole_cmd);
		free(whole_cmd);
		i++;
	}
	return (cmd);
}

char *get_path(char *cmd, char **env)
{
	char	**line;
	char	**paths;
	char	*whole_cmd;
	int		i;

	i = 0;
	while (1)
	{
		line = ft_split(env[i++], '=');
		if (ft_strcmp(line[0], "PATH") == 0)
			break ;
		free_tab(line);
	}
	paths = ft_split(line[1], ':');
	free_tab(line);
	whole_cmd = try_paths(cmd, paths);
	free_tab(paths);
	return (whole_cmd);
}
