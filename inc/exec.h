/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:09:46 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/26 01:14:23 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "lib.h"
# include "lstree.h"
# include "minishell.h"
# include <sys/wait.h>
# include <termios.h>

char	*ft_which(char *cmd, t_env *env);
void	exec_cmd(t_cmd *cmd);
int		forcked(void);
int		filein(t_cmd *redic);
int		piped(int *fd);
void	exec_redic(t_cmd *redic, t_cmd *cmd);
void	built(t_data *data, t_lsdata *lsdata);
int		ft_cd(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_pwd(void);
int		ft_env(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
t_val	*exportenv(t_cmd *cmd, int i, int j, int check);
int		ft_unset(t_cmd *cmd);
void	handler(int hand);
int		printtoken(t_lsnode *lstok);
int		first_check(t_token *temp);
int		second_check(t_token *temp);
char	*search_var(char *cmd, t_val *env);
char	*search_in_env(t_val *env, char *var);
char	*return_new(char *new, char *env, int j);
char	*remove_quote(char *value, char c);
void	ft_stat_pipe_dup(t_data *dt, t_lsdata *lsdata);
void	ft_stat_pipe_close(t_data *dt);
void	exec_pipe(t_data *dt);
void	redic_close(t_cmd *cmd);
void	redic_open(t_cmd *cmd);
char	**ft_freedt(char **data);
char	*fill_new(char *new, char *cmd, t_val *env, int *i);
void	sorting(t_val *val);
t_val	*search_val(t_val *env, char *val);
void	rm_var(t_env *val, char *var);
void	add_node(t_env *env, t_val *val);
void	init_env(t_env *env);
void	dup_envis(t_env *lenv, char **env);
t_val	*add_val(char *env);
char	*remove_fplus(char *value, char c);
int		ft_strl(char *val, char c);
t_val	*search_plus(t_val *env, char *val);
t_val	*equal_export(t_cmd *cmd, int i, t_val *env);
void	dup_plus_export(t_cmd *cmd, t_val *result, int i);
void	dup_equal_export(t_cmd *cmd, t_val *result, int i);
t_val	*plus_export(char *cmd, t_val *env);
int		check_quote(char *value);
void	creat_heredoc(t_cmd *cmd);

#endif
