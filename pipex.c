/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozlu <yozlu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:25:16 by yozlu             #+#    #+#             */
/*   Updated: 2025/03/23 17:25:16 by yozlu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child(char **av, char **env, int *fds)
{
	int	fd_infile;

	fd_infile = open(av[1], O_RDONLY);
	if (fd_infile == -1)
		error("RFILE");
	dup2(fds[1], 1);
	dup2(fd_infile, 0);
	close(fds[0]);
	close(fds[1]);
	close(fd_infile);
	do_execve(env, av[2]);
}

static void	grandchild(char **av, char **env, int *fds)
{
	int	fd_outfile;

	fd_outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd_outfile == -1)
		error("WFILE");
	dup2(fds[0], 0);
	dup2(fd_outfile, 1);
	close(fds[0]);
	close(fds[1]);
	close(fd_outfile);
	do_execve(env, av[3]);
}

static int	creat_process(void (*func)(char **, char **, int *)
		, char **av, char **env, int *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
		func(av, env, fds);
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid_child;
	pid_t	pid_grand_child;
	int		fds[2];

	if (env == NULL) 
		error();
	if (ac == 5)
	{
		if (pipe(fds) == -1)
			error();
		pid_child = creat_process(child, av, env, fds);
		pid_grand_child = creat_process(grandchild, av, env, fds);
		close(fds[0]);
		close(fds[1]);
		waitpid(pid_child, NULL, 0);
		waitpid(pid_grand_child, NULL, 0);
	}
	else
		error();
}
