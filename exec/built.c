/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:13:20 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 21:13:19 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	builtin_cmdargbis(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp(data->cmd.cmdarg[0],
			"pwd", ft_strlen(data->cmd.cmdarg[0]))
		&& ft_strlen(data->cmd.cmdarg[0]) == 3)
	{
		g_l.state = ft_pwd();
		exit(g_l.state);
	}
	else if (!ft_strncmp(data->cmd.cmdarg[0],
			"echo", ft_strlen(data->cmd.cmdarg[0]))
		&& ft_strlen(data->cmd.cmdarg[0]) == 4)
	{
		g_l.state = ft_echo(cmd);
		exit(g_l.state);
	}
}

static void	builtin_cmdarg(t_data *data, t_cmd *cmd)
{
	if (data->pipe.statpipe != NUL
		&& !ft_strncmp(data->cmd.cmdarg[0],
			"export", ft_strlen(data->cmd.cmdarg[0]))
		&& ft_strlen(data->cmd.cmdarg[0]) == 6)
	{
		g_l.state = ft_export(cmd);
		exit(g_l.state);
	}
	else if (data->pipe.statpipe != NUL
		&& !ft_strncmp(data->cmd.cmdarg[0],
			"unset", ft_strlen(data->cmd.cmdarg[0]))
		&& ft_strlen(data->cmd.cmdarg[0]) == 5)
	{
		g_l.state = ft_unset(cmd);
		exit(g_l.state);
	}
}

void	handler(int hand)
{
	if (hand == SIGQUIT && g_l.g_pid == 1)
		return ;
	if (hand == SIGINT && g_l.g_pid == 0)
		exit(2);
	if (hand == SIGQUIT && g_l.g_pid == 0)
		exit(3);
	if (hand == SIGINT && g_l.g_pid == 1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	path_cmd(t_data *dt)
{
	t_cmd	*cmd;

	cmd = &dt->cmd;
	if (!ft_strncmp(cmd->pathcmd, "/usr/bin/env", ft_strlen(cmd->pathcmd)))
		g_l.state = ft_env(&dt->cmd);
	else if (!ft_strncmp(cmd->pathcmd, "/bin/pwd", ft_strlen(cmd->pathcmd)))
		g_l.state = ft_pwd();
	else if (!ft_strncmp(cmd->pathcmd, "/bin/echo", ft_strlen(cmd->pathcmd)))
		g_l.state = ft_echo(cmd);
	else
		exec_pipe(dt);
	exit(g_l.state);
}

void	built(t_data *data, t_lsdata *lsdata)
{
	t_cmd	*cmd;

	cmd = &data->cmd;
	ft_stat_pipe_dup(data, lsdata);
	redic_open(cmd);
	builtin_cmdarg(data, cmd);
	builtin_cmdargbis(data, cmd);
	if (cmd->pathcmd)
		path_cmd(data);
	else
	{
		printf("%s: command not found\n", cmd->cmdarg[0]);
		g_l.state = 127;
		exit(g_l.state);
	}
}
