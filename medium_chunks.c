/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   medium_chunks.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/13 20:57:28 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:58 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Fallback von Medium: nacheinander Rangfenster nach B schieben.
** Zum Schluss die Raenge absteigend aus B nach A holen.
** Die Fensterbreite betraegt aufgerundet sqrt(n). */

/* Ermittelt die aufgerundete Quadratwurzel ohne sqrt().
** Verwendet long, damit chunk * chunk nicht ueberlaeuft. */

static int	get_chunk_size(int size)
{
	int	chunk;

	chunk = 1;
	while ((long) chunk * chunk < size)
		chunk++;
	return (chunk);
}

/* Verarbeitet aufsteigende Rangfenster der Chunkgroesse.
** Passende Werte gehen mit pb nach B; sonst rotiert A. */

static void	fill_chunks(t_stack **a, t_stack **b, int n, int step)
{
	int	low;
	int	goal;
	int	done;

	low = 0;
	while (low < n)
	{
		goal = step;
		if (goal > n - low)
			goal = n - low;
		done = 0;
		while (done < goal)
		{
			if ((*a)->rank >= low && (*a)->rank < low + goal)
			{
				pb(a, b);
				done++;
			}
			else
				ra(a);
		}
		low += step;
	}
}

/* Schiebt die Rangfenster nach B und holt die Raenge
** anschliessend vom groessten zum kleinsten zurueck.
** Achtung: wiederholte Max-Suche ist teuer im Worst Case. */

void	sort_chunks(t_stack **a, t_stack **b, int size)
{
	int	rank;
	int	pos;

	fill_chunks(a, b, size, get_chunk_size(size));
	rank = size - 1;
	while (rank >= 0)
	{
		pos = calc_rank_pos(*b, rank);
		rotate_b(b, calc_rota_pos(pos, calc_size(*b)));
		pa(a, b);
		rank--;
	}
}
