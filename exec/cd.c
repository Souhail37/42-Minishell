/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 15:57:12 by sismaili          #+#    #+#             */
/*   Updated: 2022/07/25 19:54:09 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/exec.h"

static char	*cd_home(t_val *env)
{
	t_val	*result;

	result = search_val(env, "HOME");
	if (result)
		return (ft_strchr(result->value, '/'));
	return (NULL);
}

static void	ft_env_oldpwd(t_val *env)
{
	char	str[1000];
	t_val	*result;
	char	*temp;

	temp = NULL;
	if (getcwd(str, sizeof(str)) == NULL)
		return ;
	result = search_val(env, "OLDPWD");
	if (result)
	{
		temp = result->value;
		result->value = ft_strjoin("OLDPWD=", str);
		free(temp);
		temp = NULL;
	}
}

static void	ft_env_pwd(t_val *env)
{
	char	str[1000];
	t_val	*result;
	char	*temp;

	temp = NULL;
	if (getcwd(str, sizeof(str)) == NULL)
		return ;
	result = search_val(env, "PWD");
	if (result)
	{
		temp = result->value;
		result->value = ft_strjoin("PWD=", str);
		free(temp);
		temp = NULL;
	}
}

int	ft_cd(t_cmd *cmd)
{
	char	*home;

	ft_env_oldpwd(cmd->env->head);
	if (!cmd->cmdarg[1])
	{
		home = cd_home(cmd->env->head);
		if (!home)
			return (printf("cd: HOME not set\n"), 1);
		chdir(home);
		return (0);
	}
	if (chdir(cmd->cmdarg[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmdarg[1]);
		return (1);
	}
	ft_env_pwd(cmd->env->head);
	return (0);
}
