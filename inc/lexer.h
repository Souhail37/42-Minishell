/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:20:07 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/24 17:36:11 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  LEXER_H
# define LEXER_H

# include "lib.h"
# include "lstree.h"

typedef struct s_lexer
{
	char			*src;
	size_t			size;
	char			c;
	unsigned int	i;
}	t_lexer;

t_lexer	*init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
t_token	*lexer_next_token(t_lexer *lexer);
t_token	*lexer_parse_cmd(t_lexer *lexer);
t_token	*lexer_advance_with(t_lexer *lexer, t_token *token);
void	lexer_whitespace(t_lexer *lexer);
t_token	*lexer_redirection(t_lexer *lexer, char *ch, t_type type);
t_token	*lexer_parse_quote(t_lexer *lexer, char ch, t_type type);
t_token	*lexer_parse_exp(t_lexer *lexer);
t_token	*lexer_parse_dollar(t_lexer *lexer);
t_token	*lexer_cat_token(t_lexer *lexer);

#endif
