/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:47:35 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 16:23:51 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static int	error_unset(t_cmd *cmd, int i)
{
	if (ft_isalpha(cmd->cmdarg[i][0]) || cmd->cmdarg[i][0] == '_')
		return (0);
	else
	{
		printf("unset: `%s': not a valid identifier\n", cmd->cmdarg[i]);
		return (1);
	}
}

int	ft_unset(t_cmd *cmd)
{
	int		i;

	i = 1;
	while (cmd->cmdarg[i])
	{
		if (error_unset(cmd, i))
			return (1);
		rm_var(cmd->env, cmd->cmdarg[i]);
		rm_var(cmd->export, cmd->cmdarg[i]);
		i++;
	}
	return (0);
}
