/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mababou <mababou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:56:31 by mababou           #+#    #+#             */
/*   Updated: 2022/04/14 14:35:03 by mababou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static int	is_sep(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	nb_words(char const *s, char const *set)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if ((i == 0 || is_sep(s[i - 1], set)) && s[i] && !is_sep(s[i], set))
			nb++;
		i++;
	}
	return (nb);
}

static int	strlen_sep(char const *s, char const *set)
{
	int	len;

	len = 0;
	while (s[len] && !is_sep(s[len], set))
		len++;
	return (len);
}

static char	*strdup_sep(t_data *data, char const *s, char const *set)
{
	char	*output;
	int		i;

	i = 0;
	output = malloc_log(data, strlen_sep(s, set) + 1);
	while (s[i] && !is_sep(s[i], set))
	{
		output[i] = s[i];
		i++;
	}
	output[i] = 0;
	return (output);
}

char	**ft_split(t_data *data, char *s, const char *set)
{
	char	**tab;
	int		w;
	int		i;

	tab = malloc_log(data, sizeof(char *) * (1 + nb_words(s, set)));
	w = ((i = 0), 0);
	while (s[i])
	{
		if ((i == 0 || is_sep(s[i - 1], set)) && s[i] && !is_sep(s[i], set))
		{
			tab[w++] = strdup_sep(data, s + i, set);
			if (!tab[w - 1])
				return (0);
		}
		i++;
	}
	tab[w] = 0;
	return (tab);
}
