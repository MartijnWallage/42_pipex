/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 11:45:35 by mwallage          #+#    #+#             */
/*   Updated: 2023/07/31 13:12:01 by mwallage         ###   ########.fr       */
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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

/*	utils	*/
void	handle_error(char *info);
void	free_tab(char **tab);
char	*get_path(char *cmd, char **env);
/*	libft	*/
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
/*	get_next_line */
char	*get_next_line(int fd);
int		ft_lastchar(char *line);
int		ft_linelen(char *s);
void	*free_strs(char **buffer, char *line);
void	update_buffer(char *buffer);

#endif
