/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quick_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cw3l <cw3l@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:07:08 by cw3l              #+#    #+#             */
/*   Updated: 2025/04/12 23:30:18 by cw3l             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char *ft_extract_var(char *env_var)
{
    char *var;
    int equal_idx;

    if(!env_var)
        return(NULL);
    equal_idx = ft_index_of_char(env_var, '=');
    if(equal_idx == -1)
        return(env_var);
    var = ft_substr(env_var, 0, equal_idx);
    return(var);
}

int	str_env_cmp_process(char *s1, char *s2, size_t n)
{
	size_t	i;
	char	*trimed_s1;
	char	*trimed_s2;
	i = 0;

	trimed_s1 = ft_extract_var(s1);
	trimed_s2 = ft_extract_var(s2);
	while ((trimed_s1[i] || trimed_s2[i]) && i < n)
	{
		if ((unsigned char)trimed_s1[i] != (unsigned char)trimed_s2[i])
		{
			if ((unsigned char)trimed_s1[i] > (unsigned char)trimed_s2[i])
				return (1);
			if ((unsigned char)trimed_s1[i] < (unsigned char)trimed_s2[i])
				return (-1);
		}
		i++;
	}
	if(trimed_s1)
		free(trimed_s1);
	if(trimed_s2)
		free(trimed_s2);
	return (0);
}

int	ft_str_env_cmp(char *s1, char *s2, size_t n)
{
	int		process_r;

	if (n == 0)
		return (0);	
	process_r = str_env_cmp_process(s1, s2, ft_strlen_longest(s1,s2));
	//TEST_SUCCES;
	if (process_r != 0)
		return (process_r);
	return (0);
}

int	ft_split_part(char **s, int end, int (*cmp)(char *, char *, size_t len))
{
	int		i;
	int		j;
	char	*pivot;

	i = 0;
	j = end - 1;
	pivot = s[end / 2];
	while (i < j)
	{
		while (cmp(s[i], pivot, ft_strlen(s[i])) < 0)
			i++;
		while (cmp(s[j], pivot, ft_strlen(s[j])) > 0)
			j--;
		if (cmp(s[i], s[j], ft_strlen(s[i])) > 0)
			ft_swap_str(&s[i], &s[j]);
	}
	return (i);
}

void	env_quick_s(char **s, int end, int (*cmp)(char *, char *, size_t len))
{
	int	i;
	if (end <= 1)
		return ;
	i = ft_split_part(s, end, cmp);
	env_quick_s(s, i, cmp);
	env_quick_s(&s[i + 1], end - 1 - i, cmp);
}
