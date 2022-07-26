/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:52:07 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/22 18:34:00 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*init_lexer(char *line)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->src = line;
	lexer->i = 0;
	lexer->size = ft_strlen(line);
	lexer->c = lexer->src[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->size && lexer->src[lexer->i] != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
	}
}

static unsigned int	loop(char *c)
{
	unsigned int	len;

	len = 0;
	while (c[len] != '\0')
	{
		if (c[len] == ' ' || c[len] == '>'
			|| c[len] == '<' || c[len] == '|')
			break ;
		len++;
	}
	return (len);
}

static void	lexer_red_adv(t_lexer *lexer, unsigned int size)
{
	unsigned int	len;

	len = 0;
	while (len++ < size)
		lexer_advance(lexer);
	lexer_whitespace(lexer);
}

t_token	*lexer_redirection(t_lexer *lexer, char *ch, t_type type)
{
	char			*c;
	char			*value;
	unsigned int	len;
	unsigned int	size;

	len = 0;
	value = NULL;
	size = ft_strlen(ch);
	lexer_red_adv(lexer, size);
	c = &lexer->src[lexer->i];
	len = loop(c);
	if (c[len] == '\0' || c[len] == ' ' || c[len] == '<'
		|| c[len] == '|' || c[len] == '>')
	{
		if (len == 0)
			value = NULL;
		else
			value = ft_strndup(lexer->src + lexer->i, len);
		size = 0;
		while (size++ < len)
			lexer_advance(lexer);
	}
	return (init_token(type, value));
}
