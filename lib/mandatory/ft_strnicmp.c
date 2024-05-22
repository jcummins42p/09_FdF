/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnicmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:14:28 by jcummins          #+#    #+#             */
/*   Updated: 2024/05/03 17:30:27 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnicmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while ((p1[i] || p2[i]) && (i < n))
	{
		if (p1[i] > p2[i] && (p1[i] + 32) != p2[i] && (p1[i] - 32) != p2[i])
			return (1);
		else if (p1[i] < p2[i] && (p1[i] + 32) != p2[i] && \
				(p1[i] - 32) != p2[i])
			return (-1);
		i++;
	}
	return (0);
}
