/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_toolbis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:42:47 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/26 01:36:12 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execpathcmd(t_data *dt)
{
	if (dt->cmd.name != NULL && dt->cmd.cmdarg == NULL)
		creat_heredoc(&dt->cmd);
	if ((dt->cmd.pathcmd && !ft_strncmp(dt->cmd.pathcmd,
				"/usr/bin/cd", ft_strlen(dt->cmd.pathcmd)))
		|| (dt->cmd.cmdarg && !ft_strncmp(dt->cmd.cmdarg[0],
				"cd", ft_strlen(dt->cmd.cmdarg[0]))))
	{
		g_l.state = ft_cd(&dt->cmd);
		return (1);
	}
	return (0);
}

static void	built_exit(t_data *dt)
{
	if (ft_strlen(dt->cmd.cmdarg[0]) > 0 && !ft_strncmp(dt->cmd.cmdarg[0],
			"exit", ft_strlen(dt->cmd.cmdarg[0]))
		&& ft_strlen(dt->cmd.cmdarg[0]) == 4)
	{
		write(1, "exit\n", 6);
		if (dt->cmd.cmdarg[1])
		{
			ft_isfulldigit(dt->cmd.cmdarg[1]);
			g_l.state = ft_atoi(dt->cmd.cmdarg[1]);
		}
		exit(g_l.state);
	}
}

static int	execbuilt(t_data *dt)
{
	if (dt->cmd.cmdarg)
	{
		if (dt->pipe.statpipe == NUL && ft_strlen(dt->cmd.cmdarg[0]) > 0
			&& !ft_strncmp(dt->cmd.cmdarg[0],
				"export", ft_strlen("export"))
			&& ft_strlen(dt->cmd.cmdarg[0]) == 6)
		{
			g_l.state = ft_export(&dt->cmd);
			return (1);
		}
		else if (dt->pipe.statpipe == NUL && ft_strlen(dt->cmd.cmdarg[0]) > 0
			&& !ft_strncmp(dt->cmd.cmdarg[0],
				"unset", ft_strlen(dt->cmd.cmdarg[0]))
			&& ft_strlen(dt->cmd.cmdarg[0]) == 5)
		{
			g_l.state = ft_unset(&dt->cmd);
			return (1);
		}
		built_exit(dt);
	}
	return (0);
}

static void	waitprocess(t_data *dt, int len, int *pid)
{
	int	x;

	x = 0;
	ft_stat_pipe_close(dt);
	while (x < len)
	{
		waitpid(pid[x++], &g_l.state, 0);
		if (WIFEXITED(g_l.state))
			g_l.state = WEXITSTATUS(g_l.state);
	}
	if (g_l.state == SIGINT)
		printf("\n");
	if (g_l.state == SIGQUIT)
		printf("Quit: 3\n");
}

void	execution(t_lsdata *data)
{
	t_data	*dt;
	int		pid[1000];
	int		len;

	len = 0;
	dt = data->head;
	signal(SIGQUIT, handler);
	if (execbuilt(dt) == 1)
		return ;
	if (execpathcmd(dt) == 1)
		return ;
	while (dt != NULL)
	{
		pid[len] = forcked();
		if (pid[len] == 0)
			built(dt, data);
		if (pid[len] > 0)
			redic_close(&dt->cmd);
		if (dt != NULL)
			dt = dt->next;
		len++;
	}
	dt = data->head;
	waitprocess(dt, len, pid);
	signal(SIGQUIT, SIG_IGN);
}
