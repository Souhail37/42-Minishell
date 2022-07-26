/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 01:44:43 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 02:00:45 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	dup_plus_export(t_cmd *cmd, t_val *result, int i)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(cmd->cmdarg[i]);
	result = plus_export(cmd->cmdarg[i], cmd->env->head);
	if (result)
		add_node(cmd->env, result);
	result = NULL;
	result = plus_export(temp, cmd->export->head);
	if (result)
		add_node(cmd->export, result);
	free(temp);
	temp = NULL;
}

void	dup_equal_export(t_cmd *cmd, t_val *result, int i)
{
	result = equal_export(cmd, i, cmd->env->head);
	if (result)
		add_node(cmd->env, result);
	result = equal_export(cmd, i, cmd->export->head);
	if (result)
		add_node(cmd->export, result);
}

void	ft_stat_pipe_close(t_data *dt)
{
	while (dt)
	{
		if (dt->pipe.pfd[0] > 0)
			close(dt->pipe.pfd[0]);
		if (dt->pipe.pfd[1] > 0)
			close(dt->pipe.pfd[1]);
		if (dt != NULL)
			dt = dt->next;
	}
}
