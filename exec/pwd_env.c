/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 19:31:12 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 21:08:37 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

int	ft_pwd(void)
{
	char	str[1000];

	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
	return (0);
}

int	ft_env(t_cmd *cmd)
{
	t_val	*head;
	char	*str;

	head = cmd->env->head;
	if (cmd->cmdarg[1])
	{
		printf("env: %s: No such file or directory\n", cmd->cmdarg[1]);
		return (1);
	}
	while (head)
	{
		str = ft_strchr(head->value, '=');
		if (str && str[0] == '=')
			printf("%s\n", head->value);
		head = head->next;
	}
	return (0);
}
