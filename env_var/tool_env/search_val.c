/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:17:17 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 01:15:14 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	ft_strlequal(char *val)
{
	size_t	len;

	len = 0;
	while (val[len] != '\0')
	{
		if (val[len] == '=')
			return (len);
		len++;
	}
	return (len);
}

t_val	*search_val(t_val *env, char *val)
{
	int	sizeval;
	int	sizeenv;
	int	number;

	sizeval = ft_strlequal(val);
	number = 0;
	while (env && env->value != NULL)
	{
		sizeenv = ft_strlequal(env->value);
		number = ft_strncmp(env->value, val, sizeval);
		if (number == 0 && sizeenv == sizeval)
			break ;
		env = env->next;
	}
	return (env);
}
