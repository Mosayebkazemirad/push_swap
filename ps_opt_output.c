/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_opt_output.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:40:21 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:35 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Schreibt eine optimierte OP direkt nach stdout.
** Nicht ft_putstr() verwenden: das wuerde erneut den Optimizer
** aufrufen. Bench zaehlt erst diesen finalen Ausgabestrom. */
void	ps_opt_write(t_ps_bench *bench, int kind)
{
	const char	*names[11] = {"sa\n", "sb\n", "ss\n", "pa\n",
		"pb\n", "ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};
	int			len;

	len = 0;
	while (names[kind][len])
		len++;
	write(1, names[kind], len);
	if (bench->enabled)
	{
		bench->count[kind]++;
		bench->total++;
	}
}
