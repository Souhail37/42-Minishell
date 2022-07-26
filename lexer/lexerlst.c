/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerlst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 05:29:58 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/24 19:32:05 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_qte(t_lexer *lexer, int isqte, char str)
{
	if (lexer->c == str)
	{
		if (isqte == 1)
			isqte = 0;
		else if (isqte == 0)
			isqte = 1;
	}
	return (isqte);
}

void	lexer_whitespace(t_lexer *lexer)
{
	while (is_delim(lexer->c, WHITESP))
		lexer_advance(lexer);
}

t_token	*lexer_parse_exp(t_lexer *lexer)
{
	char	*value;
	int		isqted;
	int		isqtes;

	isqted = 0;
	isqtes = 0;
	value = ft_calloc(1, sizeof(char));
	while (lexer->c != '\0')
	{
		if (isqted == 1 || isqtes == 1 || !is_delim(lexer->c, " |<>\0"))
		{
			if ((isqted == 0 && isqtes == 0) || isqted == 1)
				isqted = is_qte(lexer, isqted, '"');
			if ((isqted == 0 && isqtes == 0) || isqtes == 1)
				isqtes = is_qte(lexer, isqtes, '\'');
			value = ft_strjoinbis(value, &lexer->c);
			lexer_advance(lexer);
		}
		else
			break ;
	}
	return (init_token(TOKEN_EXP, value));
}

t_token	*lexer_parse_quote(t_lexer *lexer, char ch, t_type type)
{
	char	*c;
	char	*value;
	int		len;

	len = 0;
	value = NULL;
	c = lexer->src + lexer->i + 1;
	lexer_advance(lexer);
	while (c[len] != '\0')
	{
		if (c[len] == ch)
			break ;
		len++;
	}
	if (c[len] == ch)
	{
		if (len == 0)
			value = ft_strdup("\0");
		else
			value = ft_strndup(lexer->src + (lexer->i - 1), len + 2);
		lexer->i += ++len;
		lexer->c = lexer->src[lexer->i];
	}
	return (init_token(type, value));
}

t_token	*lexer_parse_dollar(t_lexer *lexer)
{
	char	*c;
	char	*value;
	int		len;

	len = 0;
	c = lexer->src + lexer->i;
	while (c[len] != '\0' && !is_delim(c[len], " |'\"&<>"))
		len++;
	if (len != 1 && c[1] == '$')
	{
		value = ft_strndup(lexer->src + lexer->i + 1, len - 1);
		lexer->i += len;
		lexer->c = lexer->src[lexer->i];
		return (init_token(TOKEN_DOLLAR, value));
	}
	else
	{
		value = ft_strndup(lexer->src + lexer->i, len);
		while (len--)
			lexer_advance(lexer);
		return (init_token(TOKEN_EXP, value));
	}
}
