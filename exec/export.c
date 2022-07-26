/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:41:51 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 19:54:20 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

t_val	*plus_export(char *cmd, t_val *env)
{
	char	*temp;
	char	*temp2;
	t_val	*result;

	temp = NULL;
	temp2 = NULL;
	result = search_plus(env, cmd);
	if (result)
	{
		temp = ft_strchr(cmd, '=');
		temp2 = ft_strchr(result->value, '=');
		if (temp2 == NULL)
			result->value = ft_strjoinbis(result->value, &temp[0]);
		else
			result->value = ft_strjoinbis(result->value, &temp[1]);
		return (NULL);
	}
	result = add_val(remove_fplus(cmd, '+'));
	return (result);
}

static int	tools_export(t_cmd *cmd, t_val *result, int i, int j)
{
	if ((cmd->cmdarg[i][j] == '=' || (cmd->cmdarg[i][j] == '+'
		&& cmd->cmdarg[i][j + 1] == '=')))
	{
		if (cmd->cmdarg[i][j] == '+')
		{
			dup_plus_export(cmd, result, i);
			return (0);
		}
		else
		{
			dup_equal_export(cmd, result, i);
			return (0);
		}
	}
	return (1);
}

static void	check_export(t_cmd *cmd, int i)
{
	int		j;
	int		check;
	t_val	*result;

	j = 0;
	check = 0;
	result = NULL;
	while (cmd->cmdarg[i][j])
	{
		if (check == 0)
		{
			if (!tools_export(cmd, result, i, j))
				return ;
		}
		if (!ft_isalpha(cmd->cmdarg[i][j]) && cmd->cmdarg[i][j] != '_'
			&& !ft_isdigit(cmd->cmdarg[i][j]))
			check = 1;
		j++;
	}
	result = exportenv(cmd, i, j, check);
	if (result)
		add_node(cmd->export, result);
}

static int	check_sort(t_cmd *cmd)
{
	t_val	*head;

	head = NULL;
	if (!cmd->cmdarg[1])
	{
		sorting(cmd->export->head);
		head = cmd->export->head;
		while (head)
		{
			printf("declare -x %s\n", head->value);
			head = head->next;
		}
		return (0);
	}
	return (1);
}

int	ft_export(t_cmd *cmd)
{
	int		i;

	i = 1;
	if (!check_sort(cmd))
		return (1);
	while (cmd->cmdarg[i])
	{
		if (ft_isalpha(cmd->cmdarg[i][0]) || cmd->cmdarg[i][0] == '_')
		{
			if (!(cmd->cmdarg[i][0] == '_' && cmd->cmdarg[i][1] == '='))
				check_export(cmd, i);
		}
		else
			return (printf("export: `%s': not a valid identifier\n",
					cmd->cmdarg[i]),
				1);
		i++;
	}	
	return (0);
}
