/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:37:51 by viceda-s          #+#    #+#             */
/*   Updated: 2025/06/13 15:56:53 by viceda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *) big);
	while (big[i] && i < len)
	{
		j = 0;
		while (little [j] && big[i + j] && i + j < len
			&& big[i + j] == little[j])
			j++;
		if (!little[j])
			return ((char *) big + i);
		i++;
	}
	return (NULL);
}
