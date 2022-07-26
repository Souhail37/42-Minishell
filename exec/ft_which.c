/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 03:01:49 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/23 18:24:32 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*point_slash(char *cmd)
{
	char	*str;
	char	*temp;
	char	cwd[1000];
	int		i;
	int		j;

	i = 0;
	j = 2;
	temp = malloc(sizeof(char) * ft_strlen(cmd) - 1);
	while (cmd[j])
		temp[i++] = cmd[j++];
	temp[i] = '\0';
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		str = ft_strjoin(cwd, "/");
		str = ft_strjoinbis(str, temp);
	}
	free(temp);
	if (!access(str, X_OK))
		return (str);
	free(str);
	str = NULL;
	return (NULL);
}

char	*ft_access(char **spl, char *cmd, int j)
{
	char	*str;

	str = ft_strjoin(spl[j], "/");
	str = ft_strjoinbis(str, cmd);
	if (!access(str, X_OK))
	{
		spl = ft_freedt(spl);
		return (str);
	}
	else
	{
		free(str);
		str = NULL;
		return (NULL);
	}
}

char	*ft_which1(char *cmd, char **spl, int j)
{
	char	*access;

	access = ft_access(spl, cmd, j);
	if (access)
		return (access);
	else
		return (NULL);
}

char	*ft_which2(char *cmd, t_val *env, char *which)
{
	char	**spl;
	int		i;

	i = 0;
	spl = NULL;
	spl = ft_split(env->value, ":");
	while (spl[i])
	{
		which = ft_which1(cmd, spl, i);
		if (which)
			return (which);
		i++;
	}
	if (spl)
		spl = ft_freedt(spl);
	return (NULL);
}

char	*ft_which(char *cmd, t_env *env)
{
	char	*which;
	t_val	*result;

	which = NULL;
	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	if (cmd[0] == '.' && cmd[1] == '/')
		return (point_slash(cmd));
	result = search_val(env->head, "PATH");
	if (result)
	{
		which = ft_which2(cmd, result, which);
		if (which)
			return (which);
	}
	return (NULL);
}
