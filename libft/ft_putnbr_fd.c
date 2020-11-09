/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:50:05 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/09 22:15:11 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	tmp;

	tmp = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		tmp *= -1;
	}
	if (tmp <= 9)
		ft_putchar_fd(tmp + '0', fd);
	else
	{
		ft_putnbr_fd(tmp / 10, fd);
		ft_putchar_fd(tmp % 10 + '0', fd);
	}
}
