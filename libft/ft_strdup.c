/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 18:52:42 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/09 22:21:47 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*new;
	char	*tmp;

	new = (char*)malloc(((ft_strlen(s1) + 1) * sizeof(char)));
	tmp = new;
	if (new != NULL)
	{
		while (*s1)
		{
			*new = *s1;
			new++;
			s1++;
		}
		*new = '\0';
	}
	return (tmp);
}
