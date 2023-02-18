/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkunnam- <hkunnam-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:48:22 by hkunnam-          #+#    #+#             */
/*   Updated: 2023/02/18 14:36:44 by hkunnam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../libft/libft/include/libft.h"

# define C_RED	"\033[0;31m"
# define C_RM	"\033[0m"

int		ft_strcmp(char *s1, char *s2);
int		open_file(char	*file, int option);
char	*ft_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	error(int errorcode);
void	ft_free(char **str);
#endif