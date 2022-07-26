/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:45:33 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 02:10:49 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	first_check(t_token *temp)
{
	if (!ft_ischar(temp->value) && temp->type != 13 && temp->type != 12
		&& temp->type != 11 && temp->type != 10 && temp->type != 9)
		return (0);
	return (1);
}

int	second_check(t_token *temp)
{
	if (!ft_ischar(temp->value) && temp->type != 10
		&& temp->type != 13 && temp->type != 12
		&& temp->type != 11 && temp->type != 9)
		return (0);
	return (1);
}

static int	search_quote(char *value, char c, int *i)
{
	if (value[*i] == c)
	{
		(*i)++;
		while (value[*i] != c)
		{
			(*i)++;
			if (value[*i] == '\0')
				return (0);
		}
	}
	return (1);
}

int	check_quote(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!search_quote(value, '"', &i))
			return (0);
		else if (!search_quote(value, '\'', &i))
			return (0);
		i++;
	}
	return (1);
}
