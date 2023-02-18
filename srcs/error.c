/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkunnam- <hkunnam-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:50:37 by hkunnam-          #+#    #+#             */
/*   Updated: 2023/02/18 12:35:01 by hkunnam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error2(int errorcode)
{	
	if (errorcode == 4)
	{
		ft_putstr_fd(C_RED, STDERR_FILENO);
		ft_putstr_fd("Failed to open the file .... \n", STDERR_FILENO);
		ft_putstr_fd(C_RM, STDERR_FILENO);
	}
}

void	error(int errorcode)
{
	if (errorcode == 1)
	{
		ft_putstr_fd(C_RED, STDERR_FILENO);
		ft_putstr_fd("Please check the arguments \n", STDERR_FILENO);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2 \n", STDERR_FILENO);
		ft_putstr_fd(C_RM, STDERR_FILENO);
	}
	else if (errorcode == 2)
	{
		ft_putstr_fd(C_RED, STDERR_FILENO);
		ft_putstr_fd("Pipe operation failed .... \n", STDERR_FILENO);
		ft_putstr_fd(C_RM, STDERR_FILENO);
	}
	else if (errorcode == 3)
	{
		ft_putstr_fd(C_RED, STDERR_FILENO);
		ft_putstr_fd("Fork operation failed .... \n", STDERR_FILENO);
		ft_putstr_fd(C_RM, STDERR_FILENO);
	}
	error2(errorcode);
	exit(errorcode);
}

void	ft_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
