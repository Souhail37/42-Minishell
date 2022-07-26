/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_val.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:15:02 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 21:19:33 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_val	*rm_val(t_val *val)
{
	free(val->value);
	val->value = NULL;
	free(val);
	val = NULL;
	return (val);
}

static int	index_node(t_val *head, t_val *val)
{
	t_val	*temp;
	int		x;

	x = 0;
	temp = head;
	while (temp)
	{
		if (ft_strcmp(temp->value, val->value) == 0)
			return (x);
		x++;
		temp = temp->next;
	}
	return (x);
}

static void	rm_varbis(t_val *result, t_val *tprv, t_val *tnxt)
{
	tprv = result->prev;
	tnxt = result->next;
	if (tprv)
		tprv->next = tnxt;
	if (tnxt)
		tnxt->prev = tprv;
}

void	rm_var(t_env *val, char *var)
{
	t_val	*result;
	t_val	*tprv;
	t_val	*tnxt;
	int		rel;

	tprv = NULL;
	tnxt = NULL;
	rel = 0;
	result = search_val(val->head, var);
	if (result && result->value != NULL)
	{
		rel = index_node(val->head, result);
		if (rel == 0)
			val->head = val->head->next;
		else
			rm_varbis(result, tprv, tnxt);
		result = rm_val(result);
		val->size--;
	}
}
