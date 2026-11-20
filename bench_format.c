/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   bench_format.c                                    :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/14 10:10:23 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:10 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Bench ausschliesslich auf stderr schreiben, nie in den OP-Stream. */

void	ps_err_text(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	write(2, s, len);
}

/* Dezimalausgabe von nichtnegativen long-Werten nach stderr.
** Wird fuer den Prozentwert und die Operationen verwendet. */

void	ps_err_number(long number)
{
	char	buffer[22];
	int		i;

	i = 22;
	if (number == 0)
		buffer[--i] = '0';
	while (number > 0)
	{
		buffer[--i] = '0' + number % 10;
		number /= 10;
	}
	write(2, buffer + i, 22 - i);
}

/* Das letzte Zahlenfeld bekommt \n, sonst ein Leerzeichen. */

void	ps_err_count(const char *name, long count, int last)
{
	ps_err_text(name);
	ps_err_number(count);
	if (last)
		ps_err_text("\n");
	else
		ps_err_text(" ");
}
