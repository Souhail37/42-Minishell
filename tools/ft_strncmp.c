/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:47:35 by ababouel          #+#    #+#             */
/*   Updated: 2022/06/22 23:56:32 by ababouel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] && s2[index] && s1[index] == s2[index])
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strcat(char *dst, const char *src)
{
	size_t	index;
	size_t	x;
	size_t	y;

	index = ft_strlen(dst);
	x = index;
	y = 0;
	while (src[y] != '\0')
	{
		dst[x] = src[y];
		x++;
		y++;
	}
	dst[x] = '\0';
	return (index + ft_strlen((char *)src));
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				index;

	index = 0;
	if (dst == NULL && src == NULL )
		return (NULL);
	while (index < n)
	{
		((unsigned char *)dst)[index] = ((unsigned char *)src)[index];
		index++;
	}
	return (dst);
}

void	*ft_realloc(void *ptr, size_t size)
{
	char	*dt;

	dt = malloc(size);
	ft_memcpy(dt, ptr, size);
	free(ptr);
	return (dt);
}
