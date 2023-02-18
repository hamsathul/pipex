/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkunnam- <hkunnam-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:50:12 by hkunnam-          #+#    #+#             */
/*   Updated: 2023/02/18 13:59:31 by hkunnam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* splits the command into parts based on space charecter
get the path from the environment variables
executes the commands with the execve system function */
void	execute(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd(C_RED, STDERR_FILENO);
		ft_putstr_fd("Command not found : ", STDERR_FILENO);
		ft_putendl_fd(split_cmd[0], STDERR_FILENO);
		ft_putstr_fd(C_RM, STDERR_FILENO);
		ft_free(split_cmd);
		exit(0);
	}
}

/* opens the file for writing
duplicates the fd into STDOUT so any output is written to the file opened.
duplicates the read end of the pipe to STDIN fd so any input read from the 
STDIN will come from the read end of the pipe 
closes the write end of the pipe
executes the command in av[3] */
void	parent_process(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open_file(av[4], 1);
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	execute(av[3], env);
}

/* opens the file for reading
 duplicates fd into STDIN so input operations will read from the
 file insted of the detault STDIN
 duplicates the write end of the pipe to STDOUT so any output operations
 will write to the write end of the pipe insted of the STDOUT
 closes the read end of the pipe
executes the command in av[2] */
void	child_process(char **av, int *pipe_fd, char **env)
{
	int	fd;

	fd = open_file(av[1], 0);
	dup2(fd, 0);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[0]);
	execute(av[2], env);
}

/* checks if the inputs are in the proper format
opens a pipe and forks the processes. send the appropriate
commands to the parent and the child process */
int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (ac != 5)
		error(1);
	if (pipe(pipe_fd) < 0)
		error(2);
	pid = fork();
	if (pid < 0)
		error(3);
	if (pid == 0)
		child_process(av, pipe_fd, env);
	parent_process(av, pipe_fd, env);
}
