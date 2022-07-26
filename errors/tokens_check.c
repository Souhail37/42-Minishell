/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:24:29 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 16:57:27 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	tokens_check(t_token *temp, int i)
{
	if (i == 0)
	{
		if (!first_check(temp))
			return (0);
	}
	else if (i == 1)
	{
		if (!second_check(temp))
			return (perror(temp->value), 0);
	}
	else if (i == 2)
	{
		if (!second_check(temp))
			return (perror(temp->value), 0);
	}
	else if (i > 2)
	{
		if (!ft_ischar(temp->value) && temp->type == TOKEN_SPACE
			&& temp->type == TOKEN_RINPUT && temp->type == TOKEN_DRINPUT
			&& temp->type == TOKEN_ROUTPUT && temp->type == TOKEN_DROUTPUT)
			return (perror(temp->value), 0);
	}
	return (1);
}

int	check_red(t_token *temp)
{
	if (temp->type == TOKEN_DRINPUT || temp->type == TOKEN_ROUTPUT
		|| temp->type == TOKEN_DROUTPUT || temp->type == TOKEN_RINPUT)
	{
		if (temp->value == NULL)
			return (0);
	}
	return (1);
}

int	check_pipe(t_token *temp)
{
	if (temp->type == TOKEN_PIPE || temp->type == TOKEN_DPIPE
		|| temp->type == TOKEN_DAND)
	{
		if (!temp->next)
			return (printf("syntax error: unexpected end of file\n"), 0);
		while (temp->next)
		{
			if (temp->next->type == TOKEN_PIPE
				|| temp->next->type == TOKEN_DPIPE
				|| temp->next->type == TOKEN_DAND)
				return (printf("syntax error near unexpected token `%s'\n",
						temp->next->value),
					0);
			else if (!temp->next || temp->next->type == TOKEN_SCL)
				return (printf("syntax error: unexpected end of file\n"), 0);
			else
				break ;
		}
	}
	return (1);
}

t_token	*token_while(t_token *temp)
{
	int	i;

	i = 0;
	while (temp->type != TOKEN_PIPE && temp->type != TOKEN_DPIPE
		&& temp->type != TOKEN_DAND)
	{
		if (!tokens_check(temp, i))
		{
			g_l.state = 1;
			return (NULL);
		}
		if (!check_red(temp) || !check_quote(temp->value))
		{
			g_l.state = 258;
			return (NULL);
		}
		if (!temp->next)
			break ;
		temp = temp->next;
		if (temp->type == TOKEN_SPACE)
			i++;
	}
	return (temp);
}

int	printtoken(t_lsnode *lstok)
{
	t_token	*temp;

	temp = lstok->head;
	while (temp)
	{
		if (temp->type == TOKEN_PIPE || temp->type == TOKEN_DPIPE
			|| temp->type == TOKEN_DAND || temp->type == TOKEN_SCL)
		{
			g_l.state = 258;
			return (printf("syntax error near unexpected token `%s'\n",
					temp->value),
				3);
		}
		temp = token_while(temp);
		if (temp == NULL)
			return (printf("syntax error\n"), 0);
		if (!check_pipe(temp))
		{
			g_l.state = 258;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}
