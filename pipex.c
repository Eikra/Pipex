/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:27:16 by iecharak          #+#    #+#             */
/*   Updated: 2023/03/09 19:48:52 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env, char **cmd)
{
	int		i;
	char	*str;
	char	**path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	str = ft_substr(env[i], 5, ft_strlen(env[i]));
	path = ft_split(str, ':');
	i = 0;
	if (ft_strchr(cmd[0], '/') && access(cmd[0], X_OK) == -1)
		return (cmd[0]);
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd[0]);
		if (access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	return (NULL);
}

// void	first_cmds(int fd, char **cmnds, char **env, int end[2])
// {
// 	char	*path;

// 	if (fd < 0)
// 		(write(2, "No such file or directory\n", 27), exit(1));
// 	dup2(fd, 0);
// 	dup2(end[1], 1);
// 	close(end[0]);
// 	if (access(cmnds[0], X_OK) == 0)
// 		execve(cmnds[0], cmnds, env);
// 	path = get_path(env, cmnds);
// 	if (execve(path, cmnds, env) == -1)
// 	{
// 		perror("Error");
// 		close(fd);
// 		exit(1);
// 	}
// 	close(fd);
// }

void	second_cmds(int fd, char **cmnds, char **env, int end[2])
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

void	pipex(int f1, int f2, char ***cmnd, char **env)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;

	if (pipe(end) == -1)
	{
		ft_printf("An error ocurred with opening the pipe\n");
		exit(1);
	}
	child1 = fork();
	if (child1 == 0)
		first_cmds(f1, cmnd[0], env, end);
	child2 = fork();
	if (child2 == 0)
		second_cmds(f2, cmnd[1], env, end);
	close(end[0]);
	close(end[1]);
	while (waitpid(0, NULL, 0) > 0)
		;
}

int	main(int ac, char **av, char **env)
{
	char	***cmnd;
	int		fd[2];

	fd[0] = open(av[1], O_RDONLY);
	fd[1] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	cmnd = malloc(sizeof(char **) * 3);
	cmnd[0] = ft_split(av[2], ' ');
	cmnd[1] = ft_split(av[3], ' ');
	if (ac < 5)
	{
		write(1, "you must type at least 5 arguments\n", 36);
		exit(0);
	}
	else if (ac == 6 && !ft_strncmp(av[1], "here_doc", 8)
		&& ft_strlen(av[1]) == 8)
		pipex_herdoc(fd[1], ac, av, env);
	else if (ac == 5)
		pipex(fd[0], fd[1], cmnd, env);
	else
		pipex_bonus(fd, ac, av, env);
	return (0);
}
// -g3 -fsanitize=address