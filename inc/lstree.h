/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 18:06:02 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/25 15:05:53 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LSTREE_H
# define LSTREE_H

# include "lexer.h"
# include "lib.h"

typedef struct s_val
{
	char			*value;
	struct s_val	*next;
	struct s_val	*prev;	
}	t_val;
typedef struct s_env
{
	t_val	*head;
	t_val	*tail;
	int		size;
}	t_env;
typedef struct s_gl
{
	int		g_pid;
	int		state;
	t_env	*export;
	char	**env;
}	t_gl;

t_gl	g_l;
typedef enum e_mpipe
{
	NUL	= -1,
	START = 0,
	UPDATE = 1,
	END	= 2
}	t_statpipe;

typedef struct file
{
	char	*file;
	t_type	type;
}	t_file;

typedef struct s_pipe
{
	int			pfd[2];
	t_statpipe	statpipe;
}	t_pipe;

typedef struct s_cmd
{
	int		ffd[2];
	int		numfile;
	char	*pathcmd;
	char	**cmdarg;
	t_env	*env;
	t_env	*export;
	t_file	*name;
}	t_cmd;

typedef struct s_data
{
	t_pipe			pipe;
	t_cmd			cmd;
	struct s_data	*next;
	struct s_data	*prev;
}	t_data;

typedef struct s_lsdata
{
	int		size;
	int		nupipe;
	t_data	*head;
	t_data	*tail;
}	t_lsdata;

void	init_lsdata(t_lsdata *lstree);
void	parsing(t_lsdata *lstree, t_lsnode *lsnode, t_env *env);
int		ins_next_tree(t_lsdata *stack, t_data *data);
void	ft_freetree(t_lsdata *sk);
void	parse_cmd(t_data *data, t_token *token, t_env *env);
t_data	*parse_pipe(t_lsdata *lsdata, t_data *data);
int		ins_next_data(t_lsdata *stack, t_data *data);
int		parse_redic(t_data *lsdata, t_token *token);
t_data	*init_dt(void);
int		ft_filter_token2(char *value);
void	ft_freestackbis(t_lsnode *sk);
void	ft_freestack(t_lsnode *sk);
void	ft_free_env(t_env *env);

#endif
