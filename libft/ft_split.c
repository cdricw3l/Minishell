/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbouhadr <cbouhadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:53:35 by cbouhadr          #+#    #+#             */
/*   Updated: 2024/10/12 17:15:22 by cbouhadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *str, char c)
{
	size_t	i;
	size_t	word_count;
	size_t	is_word;

	i = 0;
	word_count = 0;
	is_word = 0;
	while (str[i] && i < ft_strlen(str) - 1)
	{
		if (str[i] == c)
		{
			is_word = 0;
			i++;
		}
		if (str[i] != c)
		{
			if (is_word == 0)
				word_count++;
			is_word = 1;
			i++;
		}
	}
	return (word_count);
}

static void	ft_free(char **p, size_t index)
{
	size_t	k;

	k = 0;
	while (k <= index)
	{
		p[k] = NULL;
		free(p[k]);
		k++;
	}
	p = NULL;
	free(p);
}

static void	check_alloc(char **ptr, size_t j)
{
	if (!*ptr[j])
		ft_free(ptr, j);
}

static char	**process_data(char **ptr, char const *s, char c, size_t nb_word)
{
	size_t	i;
	size_t	j;
	size_t	len;

	j = 0;
	i = 0;
	while (j < nb_word)
	{
		if (s[i] != c)
		{
			len = (ft_strchr(&s[i], c)) - &s[i];
			if (len <= ft_strlen(s))
			{
				ptr[j] = ft_substr(&s[i], 0, len);
				i = (len - 1) + i;
			}
			else if (len > ft_strlen(s))
				ptr[j] = ft_strdup(&s[i]);
			check_alloc(ptr, j);
			j++;
		}
		i++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	size_t	word;
	char	**ptr;

	word = 0;
	if (!s)
		return (NULL);
	word = count_word(s, c);
	ptr = malloc((sizeof(char *) * (word + 1)));
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	process_data(ptr, s, c, word);
	return (ptr);
}
