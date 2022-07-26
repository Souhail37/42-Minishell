/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:44:53 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 21:12:18 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static void	check_echo(t_cmd *cmd, int i)
{
	while (cmd->cmdarg[i])
	{
		printf("%s", cmd->cmdarg[i]);
		i++;
		if (cmd->cmdarg[i])
			printf(" ");
	}
}

static int	check_echo1(t_cmd *cmd, int *i, int check)
{
	int	j;

	while (cmd->cmdarg[*i]
		&& cmd->cmdarg[*i][0] == '-' && cmd->cmdarg[*i][1] == 'n')
	{
		j = 1;
		check = 0;
		while (cmd->cmdarg[*i][j] == 'n')
		{
			j++;
			if (cmd->cmdarg[*i][j] == '\0')
				check = 1;
		}
		if (check == 1)
			(*i)++;
		else
			break ;
	}
	return (check);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	check;

	i = 1;
	check = -1;
	if (!cmd->cmdarg[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	check = check_echo1(cmd, &i, check);
	check_echo(cmd, i);
	if (check == -1)
		printf("\n");
	return (0);
}
