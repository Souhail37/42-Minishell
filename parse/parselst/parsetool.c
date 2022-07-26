/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 09:37:45 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 00:59:39 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_data	*init_dt(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->cmd.ffd[0] = -1;
	data->cmd.ffd[1] = -1;
	data->cmd.numfile = 0;
	data->cmd.name = NULL;
	data->cmd.cmdarg = NULL;
	data->cmd.pathcmd = NULL;
	data->cmd.env = NULL;
	data->cmd.export = NULL;
	data->pipe.pfd[1] = -1;
	data->pipe.pfd[0] = -1;
	data->pipe.statpipe = NUL;
	data->next = NULL;
	data->prev = NULL;
	return (data);
}

void	init_lsdata(t_lsdata *t_lsdata)
{
	t_lsdata->head = NULL;
	t_lsdata->tail = NULL;
	t_lsdata->size = 0;
}

int	ins_next_data(t_lsdata *stack, t_data *data)
{
	t_data	*temp;

	if (stack->head == NULL)
	{
		stack->head = data;
		stack->tail = data;
		stack->head->next = NULL;
		stack->head->prev = NULL;
	}
	else
	{
		temp = stack->head;
		while (temp->next)
			temp = temp->next;
		temp->next = data;
		temp->next->prev = temp;
		stack->tail = data;
	}
	stack->size++;
	return (0);
}
