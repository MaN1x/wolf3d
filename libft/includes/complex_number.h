/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_number.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoss <mjoss@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:08:38 by mjoss             #+#    #+#             */
/*   Updated: 2020/11/02 16:46:18 by mjoss            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLEX_NUMBER_H
# define COMPLEX_NUMBER_H

typedef struct	s_comp_nbr
{
	double	re;
	double	im;
}				t_comp_nbr;

t_comp_nbr		init_comp_nbr(double real, double imaginary);
t_comp_nbr		comp_nbr_sum(t_comp_nbr nbr1, t_comp_nbr nbr2);
t_comp_nbr		comp_nbr_pow(t_comp_nbr nbr);

#endif
