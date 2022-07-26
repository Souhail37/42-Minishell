/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 14:24:28 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 02:19:25 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_doll(char *cmd, int i)
{
	if (!cmd[i + 1])
		return (0);
	else if (cmd[i + 1] == '$')
		return (0);
	else
		return (1);
}

static char	*join_new(char *new, char *var, t_val *env, int l)
{
	var[l] = '\0';
	var = search_in_env(env, var);
	if (var)
	{
		new = ft_strjoinbis(new, var);
		free (var);
	}
	else
		free (var);
	return (new);
}

static char	*fill_newbis(char *cmd, char *var, int *i, int *l)
{
	while (cmd[*i] && cmd[*i] != '$'
		&& (ft_isalpha(cmd[*i]) || ft_isdigit(cmd[*i])))
	{
		if (ft_isdigit(cmd[*i]) && cmd[*i - 1] == '$')
		{
			var[(*l)++] = cmd[(*i)++];
			break ;
		}
		var[(*l)++] = cmd[(*i)++];
	}
	return (var);
}

char	*fill_new(char *new, char *cmd, t_val *env, int *i)
{
	char	*var;
	int		l;

	var = malloc(sizeof(char) * ft_strlen(cmd) + 1);
	if (!var)
		return (NULL);
	l = 0;
	(*i)++;
	if (cmd[*i] && cmd[*i] == '?')
		var[l++] = cmd[(*i)++];
	else
		var = fill_newbis(cmd, var, i, &l);
	var[l] = '\0';
	new = join_new(new, var, env, l);
	return (new);
}

char	*search_var(char *cmd, t_val *env)
{
	int		i;
	char	*new;
	char	*temp;

	i = 0;
	new = NULL;
	temp = NULL;
	while (cmd[i])
	{
		if (cmd[i] == '$' && check_doll(cmd, i))
			new = fill_new(new, cmd, env, &i);
		else
		{
			temp = malloc(2);
			temp[0] = cmd[i++];
			temp[1] = '\0';
			new = ft_strjoinbis(new, temp);
			free (temp);
			temp = NULL;
		}
	}
	return (new);
}
