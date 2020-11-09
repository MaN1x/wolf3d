/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_numbers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:10:15 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/02 16:45:23 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "complex_number.h"

t_comp_nbr	init_comp_nbr(double real, double imaginary)
{
	t_comp_nbr	nbr;

	nbr.re = real;
	nbr.im = imaginary;
	return (nbr);
}

t_comp_nbr	comp_nbr_sum(t_comp_nbr nbr1, t_comp_nbr nbr2)
{
	t_comp_nbr	result;

	result.re = nbr1.re + nbr2.re;
	result.im = nbr1.im + nbr2.im;
	return (result);
}

t_comp_nbr	comp_nbr_pow(t_comp_nbr nbr)
{
	t_comp_nbr	result;

	result.re = pow(nbr.re, 2.0) - pow(nbr.im, 2.0);
	result.im = 2 * nbr.re * nbr.im;
	return (result);
}
