/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseio.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 02:40:08 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/22 16:47:50 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	parse_redic(t_data *data, t_token *token)
{
	t_cmd	*cmd;

	cmd = &data->cmd;
	if (cmd->name != NULL && token->value != NULL)
	{
		cmd->numfile += 1;
		cmd->name = ft_realloc((void *)cmd->name,
				sizeof(t_file) * (cmd->numfile + 1));
		if (token->value != NULL)
			cmd->name[cmd->numfile - 1].file = token->value;
		cmd->name[cmd->numfile - 1].type = token->type;
		cmd->name[cmd->numfile].file = NULL;
	}
	else
	{
		cmd->name = malloc(sizeof(t_file) * 2);
		if (token->value != NULL)
			cmd->name[0].file = token->value;
		cmd->name[0].type = token->type;
		cmd->name[1].file = NULL;
		cmd->numfile += 1;
	}
	return (0);
}
