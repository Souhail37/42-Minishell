/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:12:41 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 21:19:56 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init_env(t_env *env)
{
	env->head = NULL;
	env->tail = NULL;
	env->size = 0;
}

t_val	*add_val(char *env)
{
	t_val	*val;

	val = malloc(sizeof(t_val));
	val->value = ft_strdup(env);
	val->next = NULL;
	return (val);
}

void	add_node(t_env *env, t_val *val)
{
	t_val	*temp;

	temp = env->head;
	if (env->head == NULL)
	{
		env->head = val;
		env->tail = val;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = val;
		val->prev = temp;
		env->tail = val;
	}
	env->size += 1;
}

void	dup_envis(t_env *lenv, char **env)
{
	int	x;

	x = 0;
	init_env(lenv);
	while (env[x])
		add_node(lenv, add_val(env[x++]));
}

char	**dup_env(t_env *lenv)
{
	t_val	*env;
	char	**data;
	int		x;

	x = 0;
	env = lenv->head;
	if (lenv->size > 0)
		data = malloc(sizeof(char *) * (lenv->size + 1));
	while (env)
	{
		data[x] = ft_strdup(env->value);
		env = env->next;
		x++;
	}
	if (lenv->size > 0)
		data[x] = NULL;
	return (data);
}
