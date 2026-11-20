/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   rating_buster.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/12 12:10:58 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:54:32 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Zaehlt die Knoten in einem Stack. */

int	calc_size(t_stack *a)
{
	int	count;

	count = 0;
	while (a)
	{
		count++;
		a = a->next;
	}
	return (count);
}

/* Rank jedes Knotens = Anzahl kleinerer Werte.
** Danach liegen die Raenge lueckenlos zwischen 0 und n-1.
** Funktioniert auch fuer negative Werte und INT_MIN. */

void	get_ranked(t_stack *a)
{
	t_stack	*current;
	t_stack	*scan;
	int		rank;

	current = a;
	while (current)
	{
		rank = 0;
		scan = a;
		while (scan)
		{
			if (scan->n < current->n)
				rank++;
			scan = scan->next;
		}
		current->rank = rank;
		current = current->next;
	}
}

/* Disorder = Anzahl der Inversionen / n*(n-1)/2.
** Eine Inversion liegt vor, wenn ein groesserer Rang vor einem
** kleineren steht. 0.0 = sortiert, 1.0 = umgekehrt sortiert.
** Dieser Wert wird vor der ersten Stack-Operation bestimmt. */

double	calc_disorder(t_stack *a)
{
	t_stack	*scan;
	long	inv;
	long	pairs;

	pairs = (long) calc_size(a);
	if (pairs < 2)
		return (0.0);
	pairs = pairs * (pairs - 1) / 2;
	inv = 0;
	while (a)
	{
		scan = a->next;
		while (scan)
		{
			if (a->rank > scan->rank)
				inv++;
			scan = scan->next;
		}
		a = a->next;
	}
	return ((double) inv / (double) pairs);
}
