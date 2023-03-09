/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:58:13 by iecharak          #+#    #+#             */
/*   Updated: 2023/03/09 19:41:00 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// char	*get_path(char **env, char **cmd)
// {
// 	int		i;
// 	char	*str;
// 	char	**path;

// 	i = 0;
// 	while (env[i])
// 	{
// 		if (!ft_strncmp(env[i], "PATH=", 5))
// 			break ;
// 		i++;
// 	}
// 	str = ft_substr(env[i], 5, ft_strlen(env[i]));
// 	path = ft_split(str, ':');
// 	i = 0;
// 	if (ft_strchr(cmd[0], '/') && access(cmd[0], X_OK) == -1)
// 		return (cmd[0]);
// 	while (path[i])
// 	{
// 		path[i] = ft_strjoin(path[i], "/");
// 		path[i] = ft_strjoin(path[i], cmd[0]);
// 		if (access(path[i], X_OK) == 0)
// 			return (path[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

void	first_cmds(int fd, char **cmnds, char **env, int end[2])
{
	char	*path;

	if (fd < 0)
		(write(2, "No such file or directory\n", 27), exit(1));
	dup2(fd, 0);
	dup2(end[1], 1);
	close(end[0]);
	if (access(cmnds[0], X_OK) == 0)
		execve(cmnds[0], cmnds, env);
	path = get_path(env, cmnds);
	if (execve(path, cmnds, env) == -1)
	{
		perror("Error");
		close(fd);
		exit(1);
	}
	close(fd);
}

void	last_cmds(int fd, char **cmnds, char **env, int end[2])
{
	char	*path;

	dup2(fd, 1);
	dup2(end[0], 0);
	close(end[1]);
	if (access(cmnds[0], X_OK) == 0)
		execve(cmnds[0], cmnds, env);
	path = get_path(env, cmnds);
	if (execve(path, cmnds, env) == -1)
	{
		perror("Error");
		close(fd);
		exit(1);
	}
}

void	midl_cmds(char **cmnds, char **env, int end1[2], int end2[2])
{
	char	*path;

	dup2(end1[0], 0);
	close(end1[1]);
	dup2(end2[1], 1);
	close(end2[0]);
	if (access(cmnds[0], X_OK) == 0)
		execve(cmnds[0], cmnds, env);
	path = get_path(env, cmnds);
	if (execve(path, cmnds, env) == -1)
	{
		exit(1);
	}
}

t_int	midle_process(int ac, int **end, char **av, char **env)
{
	char	***cmnd;
	t_int	t;

	t.i = 0;
	t.j = 2;
	cmnd = malloc(sizeof(char **) * (ac));
	while (++t.j < (ac - 2) && ++t.i)
	{
		end[t.i] = malloc(sizeof(int) * 2);
		pipe(end[t.i]);
		if (fork() == 0)
		{
			cmnd[t.i] = ft_split(av[t.j], ' ');
			midl_cmds(cmnd[t.i], env, end[(t.i) - 1], end[t.i]);
		}
		else
		{
			close(end[(t.i) - 1][0]);
			close(end[(t.i) - 1][1]);
		}
	}
	return (t);
}

void	pipex_bonus(int *fd, int ac, char **av, char **env)
{
	char	***cmnd;
	int		**end;
	t_int	t;

	end = malloc(sizeof(int *) * ac);
	end[0] = malloc(sizeof(int) * 2);
	pipe(end[0]);
	cmnd = malloc(sizeof(char **) * (ac));
	cmnd[0] = ft_split(av[2], ' ');
	if (fork() == 0)
		first_cmds(fd[0], cmnd[0], env, end[0]);
	t = midle_process(ac, end, av, env);
	if (fork() == 0 && t.j == (ac - 2))
	{
		cmnd[t.i] = ft_split(av[ac - 2], ' ');
		last_cmds(fd[1], cmnd[t.i], env, end[t.i]);
	}
	close(end[t.i][0]);
	close(end[t.i][1]);
	while (waitpid(0, NULL, 0) > 0)
		;
}

// int	main(int ac, char **av, char **env)
// {
// 	int	fd[2];

// 	if (ac < 5)
// 	{
// 		write(1, "you must type at least 5 arguments\n", 36);
// 		exit(0);
// 	}
// 	fd[0] = open(av[1], O_RDONLY);
// 	fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	pipex_bonus(fd, ac, av, env);
// 	return (0);
// }
