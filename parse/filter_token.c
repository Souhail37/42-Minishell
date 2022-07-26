/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:57:21 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/24 17:43:54 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_squote(char *value)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			check += 1;
		i++;
	}
	if (check % 2 == 0)
		return (1);
	return (0);
}

int	check_dquote(char *value)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (value[i])
	{
		if (value[i] == '"')
			check += 1;
		i++;
	}
	if (check % 2 == 0)
		return (1);
	return (0);
}

int	check_check(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			return (0);
		else if (value[i] == '"')
			return (4);
		i++;
	}
	return (0);
}

char	*remove_quote(char *value, char c)
{
	int	i;

	i = -1;
	while (value[++i])
	{
		if (value[i] == c)
		{
			while (value[i])
			{
				value[i] = value[i + 1];
				i++;
			}
			i = -1;
		}
	}
	return (value);
}

int	ft_filter_token2(char *value)
{
	int	check;

	if (!check_squote(value))
		return (printf("syntax error\n"), -1);
	if (!check_dquote(value))
		return (printf("syntax error\n"), -1);
	check = check_check(value);
	if (check == 4)
		value = remove_quote(value, '\"');
	return (check);
}
