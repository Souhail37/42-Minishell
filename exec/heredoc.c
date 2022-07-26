/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 01:20:41 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/26 01:41:01 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*search_var1(char *cmd, t_val *env)
{
	int		i;
	char	*new;
	char	*temp;

	i = 0;
	new = NULL;
	temp = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '$')
			new = fill_new(new, cmd, env, &i);
		else
		{
			temp = malloc(2);
			temp[0] = cmd[i++];
			temp[1] = '\0';
			new = ft_strjoinbis(new, temp);
			free(temp);
		}
	}
	return (new);
}

static void	heredocbis(t_file *file, t_cmd *cmd, int x)
{
	int		fdh;
	char	*buf;

	fdh = open("/tmp/.hedoc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1337)
	{
		buf = readline("> ");
		if (buf == NULL || (buf && ft_strcmp(buf, file[x].file) == 0))
			break ;
		if (cmd->env != NULL)
			buf = search_var1(buf, cmd->env->head);
		write(fdh, buf, ft_strlen(buf));
		write(fdh, "\n", 1);
		free(buf);
		buf = NULL;
	}
	free(buf);
	buf = NULL;
	close(fdh);
}

void	creat_heredoc(t_cmd *cmd)
{
	int		x;
	t_file	*file;

	x = 0;
	file = cmd->name;
	while (file[x].file != NULL)
	{
		if (file[x].type == TOKEN_DRINPUT)
			heredocbis(file, cmd, x);
		x++;
	}
}
