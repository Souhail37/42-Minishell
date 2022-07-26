/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 21:40:14 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 15:00:20 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*remove_fplus(char *value, char c)
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
			return (value);
		}
	}
	return (value);
}

int	ft_strl(char *val, char c)
{
	size_t	len;

	len = 0;
	while (val[len] != '\0' && val[len] != c)
		len++;
	return (len);
}

t_val	*search_plus(t_val *env, char *val)
{
	int	sizeval;
	int	sizeenv;
	int	number;

	sizeval = ft_strl(val, '+');
	number = 0;
	while (env && env->value != NULL)
	{
		sizeenv = ft_strl(env->value, '=');
		number = ft_strncmp(env->value, val, sizeval);
		if (number == 0 && sizeenv == sizeval)
			break ;
		env = env->next;
	}
	return (env);
}

t_val	*exportenv(t_cmd *cmd, int i, int j, int check)
{
	t_val	*result;

	result = NULL;
	if (cmd->cmdarg[i][j] != '+' && check == 1)
		return (printf("export: `%s': not a valid identifier\n",
				cmd->cmdarg[i]), NULL);
	else
	{
		result = search_val(cmd->export->head, cmd->cmdarg[i]);
		if (result)
			return (NULL);
		else
		{
			result = add_val(cmd->cmdarg[i]);
			return (result);
		}
	}
}

t_val	*equal_export(t_cmd *cmd, int i, t_val *env)
{
	char	*temp;
	t_val	*result;

	temp = NULL;
	result = NULL;
	result = search_val(env, cmd->cmdarg[i]);
	if (result)
	{
		temp = result->value;
		result->value = ft_strdup(cmd->cmdarg[i]);
		free(temp);
		temp = NULL;
		return (NULL);
	}
	result = add_val(cmd->cmdarg[i]);
	return (result);
}
