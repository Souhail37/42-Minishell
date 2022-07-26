/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:35:05 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 00:59:03 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "lib.h"
#include "lstree.h"

char	**ft_freedt(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		data[i] = NULL;
		i++;
	}
	free(data);
	data = NULL;
	return (data);
}

static void	freedata(t_data *item)
{
	int	x;

	x = 0;
	if (item->cmd.pathcmd != NULL)
		free(item->cmd.pathcmd);
	if (item->cmd.cmdarg != NULL)
		item->cmd.cmdarg = ft_freedt(item->cmd.cmdarg);
	if (item->cmd.name != NULL)
	{
		while (item->cmd.name[x].file != NULL)
		{
			free(item->cmd.name[x].file);
			item->cmd.name[x].file = NULL;
			x++;
		}
		free(item->cmd.name);
	}
	item->cmd.pathcmd = NULL;
	item->cmd.name = NULL;
	free(item);
	item = NULL;
}

void	ft_freetree(t_lsdata *sk)
{
	t_data	*node;
	t_data	*temp;

	if (!sk)
		return ;
	temp = sk->head;
	while (temp != NULL)
	{
		node = temp;
		temp = temp->next;
		if (node != NULL)
			freedata(node);
	}
	init_lsdata(sk);
}

void	ft_freestackbis(t_lsnode *sk)
{
	t_token	*node;
	t_token	*temp;

	node = sk->head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		if (temp->value && (temp->type == TOKEN_DOLLAR
				|| temp->type == TOKEN_EXP
				|| temp->type == TOKEN_DQUOTE
				|| temp->type == TOKEN_SINQTE))
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
	init_stack(sk);
}

void	ft_freestack(t_lsnode *sk)
{
	t_token	*node;
	t_token	*temp;

	node = sk->head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp);
		temp = NULL;
	}
	init_stack(sk);
}
