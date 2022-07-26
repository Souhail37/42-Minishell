/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:14:09 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 22:00:46 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*readline_t(void)
{
	char			*buf;
	struct termios	attr;
	struct termios	old_attr;

	tcgetattr(STDIN_FILENO, &old_attr);
	attr = old_attr;
	attr.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &attr);
	buf = readline("minishell$ ");
	tcsetattr(STDIN_FILENO, TCSANOW | TCSAFLUSH, &old_attr);
	return (buf);
}

t_lsnode	*add_init_lstok(t_lsnode *lstok, char *line)
{
	t_lexer	*lexer;
	t_token	*token;

	lexer = NULL;
	token = NULL;
	init_stack(lstok);
	lexer = init_lexer(line);
	while (lexer->i < ft_strlen(line))
	{
		if (lexer->src[lexer->i] != '\0')
			token = lexer_next_token(lexer);
		if (token != NULL)
			ins_next_node(lstok, (void *) token);
	}
	free(lexer);
	lexer = NULL;
	return (lstok);
}

static int	exitcheck(t_env *env, char *line)
{
	if (!line)
	{
		printf("\033[11C\033[1Aexit\n");
		ft_free_env(env);
		ft_free_env(g_l.export);
		return (1);
	}
	return (0);
}

static void	loop_line(t_env *env, char *line)
{
	t_lsnode	lstok;
	t_lsdata	lsdata;

	if (line != NULL)
	{
		add_init_lstok(&lstok, line);
		init_lsdata(&lsdata);
		if (printtoken(&lstok))
		{
			if (delete_var(&lstok, env))
			{	
				parsing(&lsdata, &lstok, env);
				if (lsdata.head->cmd.name || lsdata.head->cmd.cmdarg != NULL)
					execution(&lsdata);
			}
			ft_freestack(&lstok);
			ft_freetree(&lsdata);
		}
		else
			ft_freestackbis(&lstok);
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*tenv;
	char	*line;

	(void) av;
	(void) ac;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	tenv = malloc(sizeof(t_env));
	g_l.export = malloc(sizeof(t_env));
	dup_envis(tenv, env);
	dup_envis(g_l.export, env);
	while (1337)
	{
		g_l.g_pid = 1;
		line = readline_t();
		g_l.g_pid = 0;
		if (exitcheck(tenv, line))
			exit(0);
		if (ft_strlen(line) > 0)
			add_history(line);
		loop_line(tenv, line);
	}
	return (0);
}
