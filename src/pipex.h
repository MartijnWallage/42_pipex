/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:45:35 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/07 15:41:08 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft/inc/libft.h"

/*	utils	*/
void	handle_error(char *info);
void	free_tab(char **tab);
char	*get_path(char *cmd, char **env);
void	close_pipes(int pipefd[2]);

#endif
