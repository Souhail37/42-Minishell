/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:11:22 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 01:17:26 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*return_new(char *new, char *env, int j)
{
	int	len;

	len = 0;
	new = malloc(sizeof(char) * ft_strlen(&env[j]));
	if (!new)
		return (NULL);
	while (env[j])
	{
		new[len] = env[++j];
		len++;
	}
	return (new);
}

char	*search_in_env(t_val *env, char *var)
{
	int		j;
	char	*new;
	t_val	*result;

	new = NULL;
	if (var[0] == '?')
	{
		free (var);
		return (ft_itoa(g_l.state));
	}
	result = search_val(env, var);
	if (result && result->value != NULL)
	{
		j = 0;
		while (result->value[j] != '=')
			j++;
		new = return_new(new, result->value, j);
		free (var);
		return (new);
	}
	free (var);
	return (NULL);
}
