/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxim <maxim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:23:51 by maxim             #+#    #+#             */
/*   Updated: 2020/08/01 19:04:45 by maxim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	letter_to_integer(char l)
{
	if (l == 'A' || l == 'a')
		return (10);
	else if (l == 'B' || l == 'b')
		return (11);
	else if (l == 'C' || l == 'c')
		return (12);
	else if (l == 'D' || l == 'd')
		return (13);
	else if (l == 'E' || l == 'e')
		return (14);
	else if (l == 'F' || l == 'f')
		return (15);
	return (0);
}

int			ft_atoi_hex(const char *str)
{
	int out;

	out = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (ft_strncmp(str, "0x", 2) == 0)
		str += 2;
	while ((*str >= '0' && *str <= '9') || (*str >= 'A' && *str <= 'F') ||
											(*str >= 'a' && *str <= 'f'))
	{
		if (letter_to_integer(*str))
			out = out * 16 + letter_to_integer(*str);
		else
			out = out * 16 + *str - '0';
		str++;
	}
	return (out);
}
