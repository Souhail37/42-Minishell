/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:51:32 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 17:51:41 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lstree.h"
#include "exec.h"

void	ft_free_env(t_env *env)
{
	t_val	*node;
	t_val	*temp;

	node = env->head;
	while (node != NULL)
	{
		temp = node;
		node = node->next;
		free(temp->value);
		temp->value = NULL;
		free(temp);
		temp = NULL;
	}
	init_env(env);
	free(env);
}
