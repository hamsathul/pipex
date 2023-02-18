/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utls_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkunnam- <hkunnam-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:50:27 by hkunnam-          #+#    #+#             */
/*   Updated: 2023/02/18 16:59:49 by hkunnam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/* compares the null terminated strings and returns an integer value*/
int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;

	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

/* return a file descriptor of int value based on what options are
given and opens in read mode or write mode */
int	open_file(char	*file, int option)
{
	int	fd;

	if (option == 0)
		fd = open(file, O_RDONLY, 0777);
	if (option == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (option == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		error(4);
	return (fd);
}

/* searches through the environment variable for the required name
it iterates through the string to find the first '=' character then
use substr to find the string after '=' charecter. then uses strcmp to 
match the string with the given variable name and returns a
 pointer to the portion 
of the sting after the '=' character. if no matching env variable is found the 
function returns NULL */
char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		str = ft_substr(env[i], 0, j);
		if (ft_strcmp(str, name) == 0)
		{
			free(str);
			return (env[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}

/* This function finds and returns the full path of the command from the 
env variable first the function finds the env variable where "PATH" 
is specified using ft_getenv function
then it splits the env variable using ':' as a delimiter.
the split_cmd array is populated by spltting the cmd variable 
using space character 
as delimiter a loop is started which will iterate through each directory in the 
full_path variable a partial path variable is created by adding '/' to the
 end of the current directory from the full path variable an exec_path variable 
 is created by adding the first string of the split cmd variable to the
end of partial path
the access function is used to check if the file exits (F_OK) and 
is executable (X_OK).
if the file exists and is executable free everything and return exec path
if a valid path is not found return cmd */
char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**full_path;
	char	**split_cmd;
	char	*partial_path;
	char	*exec_path;

	i = -1;
	full_path = ft_split(ft_getenv("PATH", env), ':');
	split_cmd = ft_split(cmd, ' ');
	while (full_path[++i])
	{
		partial_path = ft_strjoin(full_path[i], "/");
		exec_path = ft_strjoin(partial_path, split_cmd[0]);
		free(partial_path);
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			free(split_cmd);
			return (exec_path);
		}
		free(exec_path);
	}
	free(split_cmd);
	free(full_path);
	return (cmd);
}
