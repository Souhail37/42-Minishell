/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:18:53 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 01:14:24 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	swap_env(t_val *val1, t_val *val2)
{
	char	*temp;

	temp = NULL;
	temp = val1->value;
	val1->value = val2->value;
	val2->value = temp;
}

static void	exp_sort(t_val *val)
{
	int		j;
	t_val	*env;

	j = 0;
	env = val;
	while (env->next && env->value[j])
	{
		if (env->value[j] > env->next->value[j])
		{
			swap_env(env, env->next);
			break ;
		}
		else if (env->value[j] == env->next->value[j])
			j++;
		else
			break ;
	}
}

void	sorting(t_val *val)
{
	t_val	*temp;
	t_val	*tmp2;

	temp = val;
	while (temp)
	{
		tmp2 = val;
		while (tmp2)
		{
			exp_sort(tmp2);
			tmp2 = tmp2->next;
		}
		temp = temp->next;
	}
}
