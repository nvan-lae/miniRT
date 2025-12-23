/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:12:42 by jvan-der          #+#    #+#             */
/*   Updated: 2025/04/18 19:45:43 by jvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*joined;
	char	*start;
	int		i;

	i = 0;
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (free(s1), NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	start = joined;
	if (!joined)
		return (NULL);
	while (s1[i])
		*joined++ = s1[i++];
	i = 0;
	while (s2[i])
		*joined++ = s2[i++];
	*joined = '\0';
	return (free(s1), start);
}
