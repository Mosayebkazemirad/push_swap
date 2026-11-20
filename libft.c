/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   libft.c                                           :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 09:37:53 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:48 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Gemeinsamer Ausgabeweg fuer die elf Stack-Operationen.
** Bei Complex kann ps_opt_capture() eine Operation puffern.
** Nur tatsaechlich gedruckte OPs werden fuer --bench gezaehlt.
** Dadurch sieht der Checker denselben Strom wie die Statistik. */

void	ft_putstr(char *s)
{
	int	len;

	if (!s || ps_opt_capture(s))
		return ;
	ps_bench_record(s);
	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}
