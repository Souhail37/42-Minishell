/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exectool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 06:32:14 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/26 01:39:19 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	open_here_doc(t_cmd *cmd, int flag)
{
	if (cmd->ffd[0] > 0)
		close(cmd->ffd[0]);
	if (cmd->cmdarg != NULL)
		creat_heredoc(cmd);
	cmd->ffd[0] = open("/tmp/.hedoc", flag, 0644);
}

static void	openfileredic(char *file, int *fd, int flags)
{
	if (*fd > 0)
		close(*fd);
	*fd = open(file, flags, 0644);
	if (*fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		perror(" ");
		g_l.state = 1;
		exit(g_l.state);
	}
}

int	filein(t_cmd *cmd)
{
	int		x;
	t_file	*file;

	x = 0;
	file = cmd->name;
	while (file[x].file != NULL)
	{
		if (file[x].type == TOKEN_DRINPUT)
			open_here_doc(cmd, O_RDONLY);
		if (file[x].type == TOKEN_RINPUT)
			openfileredic(file[x].file, &cmd->ffd[0], O_RDONLY);
		if (file[x].type == TOKEN_ROUTPUT)
			openfileredic(file[x].file, &cmd->ffd[1],
				O_WRONLY | O_CREAT | O_TRUNC);
		if (file[x].type == TOKEN_DROUTPUT)
			openfileredic(file[x].file, &cmd->ffd[1],
				O_WRONLY | O_CREAT | O_APPEND);
		x++;
	}
	return (0);
}

void	ft_stat_pipe_dup(t_data *dt, t_lsdata *lsdata)
{
	t_pipe	*cupipe;
	t_pipe	*pvpipe;
	t_data	*data;

	data = lsdata->head;
	cupipe = &dt->pipe;
	if (dt->prev != NULL)
		pvpipe = &dt->prev->pipe;
	if (cupipe->statpipe == START)
		dup2(cupipe->pfd[1], STDOUT_FILENO);
	if (cupipe->statpipe == UPDATE)
	{
		dup2(pvpipe->pfd[0], STDIN_FILENO);
		dup2(cupipe->pfd[1], STDOUT_FILENO);
	}
	if (cupipe->statpipe == END)
		dup2(pvpipe->pfd[0], STDIN_FILENO);
	ft_stat_pipe_close(data);
}
