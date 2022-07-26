/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:45:20 by ababouel          #+#    #+#             */
/*   Updated: 2022/07/24 23:33:02 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strdup(const char *s)
{
	char	*data;
	int		index;

	data = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!data)
		return (0);
	index = 0;
	while (s[index])
	{
		data[index] = s[index];
		index++;
	}
	data[index] = '\0';
	return (data);
}

char	*ft_strndup(const char *s, int len)
{
	char	*data;
	int		index;

	data = malloc((len + 1) * sizeof(char));
	if (!data)
		return (0);
	index = 0;
	while (index < len)
	{
		data[index] = s[index];
		index++;
	}
	data[index] = '\0';
	return (data);
}

int	is_alpha(char c)
{
	if (('A' <= c && c <= 'Z')
		|| ('a' <= c && c <= 'z'))
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	x;
	unsigned char	*str;

	x = 0;
	str = s;
	while (x < n)
	{
		str[x] = (unsigned char ) 0;
		x++;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			write(fd, &*s, 1);
			s++;
		}
	}
}
