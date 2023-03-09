/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:49:06 by iecharak          #+#    #+#             */
/*   Updated: 2023/03/09 19:58:17 by iecharak         ###   ########.fr       */
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

// void	second_cmds(int fd, char **cmnds, char **env, int end[2])
// {
// 	char	*path;

// 	dup2(fd, 1);
// 	dup2(end[0], 0);
// 	close(end[1]);
// 	if (access(cmnds[0], X_OK) == 0)
// 		execve(cmnds[0], cmnds, env);
// 	path = get_path(env, cmnds);
// 	if (execve(path, cmnds, env) == -1)
// 	{
// 		perror("Error");
// 		close(fd);
// 		exit(1);
// 	}
// }

void	midl_cmds_herdoc(char **cmnds, char **env, int end1[2], int end2[2])
{
	char	*path;

	dup2(end1[0], 0);
	dup2(end2[1], 1);
	if (access(cmnds[0], X_OK) == 0)
		execve(cmnds[0], cmnds, env);
	path = get_path(env, cmnds);
	if (execve(path, cmnds, env) == -1)
	{
		perror("Error");
		exit(1);
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	get_next_line_herdoc(int end[2], char **av)
{
	char	*str;

	while (1)
	{
		str = get_next_line(0);
		if (!ft_strncmp(av[2], str, ft_strlen(av[2]))
			&& ft_strlen(av[2]) == (ft_strlen(str) - 1))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, end[1]);
		free(str);
	}
}

void	pipex_herdoc(int fd, int ac, char **av, char **env)
{
	int		**end;
	char	***cmnd;

	end = malloc(sizeof(int *) * (ac - 3));
	cmnd = malloc(sizeof(char **) * (3));
	end[0] = malloc(sizeof(int) * 2);
	pipe(end[0]);
	get_next_line_herdoc(end[0], av);
	close(end[0][1]);
	end[1] = malloc(sizeof(int) * 2);
	pipe(end[1]);
	if (fork() == 0)
	{
		cmnd[0] = ft_split(av[3], ' ');
		midl_cmds_herdoc(cmnd[0], env, end[0], end[1]);
	}
	if (fork() == 0)
	{
		cmnd[1] = ft_split(av[4], ' ');
		second_cmds(fd, cmnd[1], env, end[1]);
	}
	close(end[1][0]);
	close(end[1][1]);
	while (waitpid(0, NULL, 0) > 0)
		;
}

// int	main(int ac, char **av, char **env)
// {
// 	int fd;

// 	fd = open(av[5], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	pipex_herdoc(fd, ac, av, env);
// 	return (0);
// }