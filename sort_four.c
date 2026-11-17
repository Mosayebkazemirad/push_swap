/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_four.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 20:57:28 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:42 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Vier Raenge haben 4! = 24 Permutationen.
** Feste Befehlsfolgen sind hier kuerzer als weitere Rekursion.
** Kodierung: a=sa, b=sb, p=pa, q=pb.
** Keine ra/rb-Operation: tiefere Teilbereiche bleiben unberuehrt. */

/* Errechnet einen eindeutigen Index 0..23 aus vier Raengen.
** Durch Abzug von low funktionieren beliebige Vierer-Rangfenster,
** nicht nur die absoluten Raenge 0, 1, 2 und 3. */
static int	four_index(t_stack *stack, int low)
{
	int	values[4];
	int	index;
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		values[i++] = stack->rank - low;
		stack = stack->next;
	}
	index = 0;
	i = -1;
	while (++i < 4)
	{
		index *= (4 - i);
		j = i;
		while (++j < 4)
			if (values[i] > values[j])
				index++;
	}
	return (index);
}

/* Spielt eine kodierte, feste Folge von Push_swap-Befehlen.
** a=sa, b=sb, p=pa, q=pb; keine ganzen Rotationen. */
static void	do_four_moves(t_stack **a, t_stack **b, const char *steps)
{
	while (*steps)
	{
		if (*steps == 'a')
			sa(a);
		else if (*steps == 'b')
			sb(b);
		else if (*steps == 'p')
			pa(a, b);
		else if (*steps == 'q')
			pb(a, b);
		steps++;
	}
}

/* Behandelt eine obere Vierergruppe von A.
** Die Tabelle vermeidet Rotationen durch fremde Gruppen. */
void	sort_four_a(t_stack **a, t_stack **b, int low)
{
	static const char	*steps[24] = {
		"", "qqapp", "qap", "qqapap", "qaqapp", "qaqapap",
		"a", "qqappa", "qapa", "qqapapa", "qaqappa", "qaqapapa",
		"aqap", "qqbapap", "aqapa", "qqbapapa", "qaqbapap",
		"qaqbapapa", "aqaqapp", "aqaqapap", "aqaqappa",
		"aqaqapapa", "aqaqbapap", "aqaqbapapa"
	};

	do_four_moves(a, b, steps[four_index(*a, low)]);
}

/* Behandelt eine obere Vierergruppe von B.
** Nach der Folge liegen die vier Werte korrekt in A. */
void	sort_four_b(t_stack **a, t_stack **b, int low)
{
	static const char	*steps[24] = {
		"ppbpaqbapapa", "pbpbapapa", "ppbpaqapapa",
		"pbpapapa", "ppbapapa", "ppapapa", "ppbpaqbapap",
		"pbpbapap", "ppbpaqapap", "pbpapap", "ppbapap", "ppapap",
		"ppbpaqappa", "pbpappa", "ppbpaqapp", "pbpapp",
		"ppappa", "ppapp", "ppbpapa", "pppapa", "ppbpap",
		"pppap", "ppppa", "pppp"
	};

	do_four_moves(a, b, steps[four_index(*b, low)]);
}
