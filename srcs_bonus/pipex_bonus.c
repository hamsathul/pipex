/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkunnam- <hkunnam-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:50:12 by hkunnam-          #+#    #+#             */
/*   Updated: 2023/02/19 17:00:22 by hkunnam-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/* splits the command into parts based on space charecter
get the path from the environment variables
executes the commands with the execve system function */
void	execute(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd[0])
		error(7);
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

/* 
The function takes two parameters:
av: a pointer to a character array that contains the command to be executed.
pipe_fd: a pointer to an integer array that contains the file descriptors 
for the pipe.
The function reads input from standard input using the get_next_line function 
and writes it to the write end of the pipe using the ft_putstr_fd function.
It continues to read and write input until it encounters a line that matches 
the specified delimiter, which is the third command line argument (av[2]). 
When it finds the delimiter, it frees the line buffer and exits with a status 
code of 0.
*/
void	read_write_to_pipe_end(char **av, int *pipe_fd)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putstr_fd(line, pipe_fd[1]);
		free(line);
	}
}

/* 
The function sets up a pipeline using a Unix pipe and forks a child 
process. If the process is the child process, it calls the 
read_write_to_pipe_end function to read input from standard 
input and write it to the write end of the pipe. If the process
is the parent process, it closes the write end of the pipe, 
duplicates the read end of the pipe to standard input using the dup2 function, 
waits for the child process to exit using the wait function, and then returns.
 */
void	here_doc(char **av)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		error(2);
	pid = fork();
	if (pid == -1)
		error(3);
	if (pid == 0)
		read_write_to_pipe_end(av, pipe_fd);
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		wait(NULL);
	}
}

/*
pipe_operation sets up a pipeline between two processes using a Unix pipe.
The pipeline allows the output of one process to be connected to the input 
of another process.
The function takes two parameters:
cmd: a pointer to a character array that contains the command to be executed.
env: a pointer to a character array that contains the environment variables 
for the command. The function performs the following steps:
It creates a pipe using the pipe system call. If the call fails, 
it calls an error function with error code 2.
It forks a child process using the fork system call. 
If the call fails, it calls an error function with error code 3.
If the process is the child process (i.e., pid == 0), 
it closes the read end of the pipe (since it will be writing to the pipe), 
duplicates the write end of the pipe to standard output (file descriptor 1)
using the dup2 system call, and executes the command using a
execute function with the specified command and environment variables.
If the process is the parent process (i.e., pid != 0), 
it closes the write end of the pipe (since it will be reading from the pipe), 
duplicates the read end of the pipe to standard input (file descriptor 0) 
using the dup2 system call.
 */
void	pipe_operation(char *cmd, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		error(2);
	pid = fork();
	if (pid == -1)
		error(3);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		execute(cmd, env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
	}
}

/* 
1.	checks if the number of arguments are 5 or more
2.	checks if the 2nd argumnet is here_doc
3.	if here_doc is found checks if argumnetas are 6 or more
	a.	assigns the delmimiter value as 3
	b.	opens the file in writemode with append option
	c.	calls the here_doc function to read from terminal as user input.
4.	if here_doc is not found 
	a. assigns the delimter value to 2
	b. in file is opened for reading and fd is assigned to fd_in 
	c. out file is opened for writing and fd is assigned to fd_in
	d. fd_in is duplicated to the value of STDIN
5.	a loop is started and value of i is assigned based on weather
	here doc is found or not.
6.	pipe_operation function is called for working through multiple
	pipes. By calling pipe_operation for each command in the 
	range, the loop sets up a pipeline between each pair of adjacent 
	commands. The output of the first command is connected to the 
	input of the second command, the output of the second command 
	is connected to the input of the third command, and so on, 
	until the last command is reached..
7.	fd_out is duplicated to the value of STDOUT
8.	execute function is called to execute different commands
*/
int	main(int ac, char **av, char **env)
{
	int	i;
	int	fd_in;
	int	fd_out;

	if (ac < 5)
		error(1);
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (ac < 6)
			error(5);
		i = 3;
		fd_out = open_file(av[ac - 1], 2);
		here_doc(av);
	}
	else
	{
		i = 2;
		fd_in = open_file(av[1], 0);
		fd_out = open_file(av[ac - 1], 1);
		dup2(fd_in, 0);
	}
	while (i < ac - 2)
		pipe_operation(av[i++], env);
	dup2(fd_out, 1);
	execute(av[ac - 2], env);
}
