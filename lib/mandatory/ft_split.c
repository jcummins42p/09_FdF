/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcummins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:46:20 by jcummins          #+#    #+#             */
/*   Updated: 2024/04/29 16:55:57 by jcummins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	wcount(char const *s, char c)
{
	int	i;
	int	words;

	if (!s)
		return (0);
	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			words++;
		while (s[i] != c && s[i])
			i++;
	}
	return (words);
}

static unsigned int	lcount(char const *s, char c, int i)
{
	int	letters;

	letters = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		letters++;
		i++;
	}
	return (letters);
}

char	**ft_split(char const *s, char c)
{
	char			**split;
	unsigned int	i;
	unsigned int	word;
	unsigned int	words_total;
	unsigned int	letters_total;

	i = 0;
	word = 0;
	words_total = wcount(s, c);
	split = (char **)malloc((words_total + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	while (word < words_total)
	{
		letters_total = lcount(s, c, i);
		while (s[i] == c)
			i++;
		split[word] = ft_substr(s, i, letters_total);
		i += letters_total;
		word++;
	}
	split[word] = NULL;
	return (split);
}

/*int	main(void)*/
/*{*/
	/*char const	*str;*/
	/*char		c;*/
	/*int			i;*/

	/*str = "   tripouille 0 0 0 0 0 0 1";*/
	/*c = ' ';*/
	/*i = 0;*/
	/*while (i < 10)*/
		/*printf("Count of %s\n", ft_split(str, c)[i++]);*/
	/*return (0);*/
/*}*/
