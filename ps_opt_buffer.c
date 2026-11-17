/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_opt_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:20:13 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:32 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Swap ist sein eigenes Inverses; ra/rra und rb/rrb heben sich auf. */
static int	is_inverse(int left, int right)
{
	return ((left == 0 && right == 0) || (left == 1 && right == 1)
		|| (left == 5 && right == 8) || (left == 8 && right == 5)
		|| (left == 6 && right == 9) || (left == 9 && right == 6));
}

/* Entfernt direkt aufeinanderfolgende inverse Aktionen
** desselben Stacks, bevor A- und B-Aktionen zusammengefuehrt werden.
** Beispiel: ra + rra = keine Ausgabe. */
static void	add_single(unsigned char *steps, int *len, int op)
{
	if (*len && is_inverse(steps[*len - 1], op))
		(*len)--;
	else
		steps[(*len)++] = (unsigned char)op;
}

/* Ein Pufferblock enthaelt ausschliesslich Einzel-Stack-OPs.
** Da A- und B-Aktionen unabhaengig sind, koennen wir sie getrennt
** kuerzen und danach mittels ss/rr/rrr zusammenfuehren.
** Die interne Reihenfolge jedes Stacks muss erhalten bleiben. */
void	ps_opt_flush(t_ps_bench *bench)
{
	t_ps_pair	pair;
	int			i;

	pair.na = 0;
	pair.nb = 0;
	pair.dp = NULL;
	i = 0;
	while (i < bench->pending_len)
	{
		if (bench->pending[i] == 0 || bench->pending[i] == 5
			|| bench->pending[i] == 8)
			add_single(pair.a, &pair.na, bench->pending[i]);
		else
			add_single(pair.b, &pair.nb, bench->pending[i]);
		i++;
	}
	ps_opt_join(bench, &pair);
	bench->pending_len = 0;
}
