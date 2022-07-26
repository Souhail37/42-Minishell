/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sismaili <sismaili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:33:48 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/20 13:22:29 by sismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int	nbrword(char const *s, char *delim)
{
	int	status;
	int	nbr;

	status = 0;
	nbr = 0;
	while (*s)
	{
		if (is_delim(*s, delim))
			status = 0;
		else if (status == 0)
		{
			status = 1;
			nbr++;
		}
		s++;
	}
	return (nbr);
}

static char	*repchz(char const *s, char *c, char rech)
{
	size_t	i;
	char	*str;

	i = 0;
	str = ft_strdup(s);
	while (str[i])
	{
		if (is_delim(str[i], c))
			str[i] = rech;
		i++;
	}
	return (str);
}

char	**ft_freememory(char **data, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (data)
			free(data[i]);
		i++;
	}
	free(data);
	return (data);
}

static char	**injectdata(char **data, char const *s, char *str)
{
	size_t	len;
	int		index;
	size_t	len_s;

	len = 0;
	index = 0;
	len_s = ft_strlen(s);
	while (len < len_s)
	{
		while (len <= len_s && str[len] == '\0')
			len++;
		if (len <= len_s)
		{
			data[index] = ft_strdup(str + len);
			if (!data[index])
				return (ft_freememory(data, index));
			index++;
		}
		while (len <= len_s && str[len] != '\0')
			len++;
	}
	return (data);
}

char	**ft_split(char const *s, char *c)
{
	char	**data;
	char	*str;

	if (!s)
		return (NULL);
	data = NULL;
	data = malloc(sizeof(char *) * (nbrword(s, c) + 1));
	if (!data)
	{
		free(data);
		return (NULL);
	}
	if (nbrword(s, c) > 0)
	{
		str = repchz(s, c, '\0');
		data = injectdata(data, s, str);
		free(str);
	}
	data[nbrword(s, c)] = NULL;
	return (data);
}
