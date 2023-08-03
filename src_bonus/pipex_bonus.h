/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:45:35 by mwallage          #+#    #+#             */
/*   Updated: 2023/08/03 16:32:05 by mwallage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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

#endif
