/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_opt_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:23:06 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:34 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Benachbarte A/B-Operationen duerfen zusammengefasst werden. */
static int	paired_op(int a, int b)
{
	if (a == 0 && b == 1)
		return (2);
	if (a == 5 && b == 6)
		return (7);
	if (a == 8 && b == 9)
		return (10);
	return (-1);
}

/* Dynamic Programming ueber zwei Operationslisten.
** Die Tabelle merkt die groesste Anzahl kombinierbarer Paare
** ab den jeweiligen Positionen in A und B. */
static void	fill_table(t_ps_pair *pair)
{
	int	i;
	int	j;
	int	stride;

	stride = pair->nb + 1;
	i = pair->na;
	while (i-- > 0)
	{
		j = pair->nb;
		while (j-- > 0)
		{
			if (paired_op(pair->a[i], pair->b[j]) >= 0)
				pair->dp[i * stride + j]
					= pair->dp[(i + 1) * stride + j + 1] + 1;
			else if (pair->dp[(i + 1) * stride + j]
				>= pair->dp[i * stride + j + 1])
				pair->dp[i * stride + j] = pair->dp[(i + 1) * stride + j];
			else
				pair->dp[i * stride + j] = pair->dp[i * stride + j + 1];
		}
	}
}

/* Rekonstruiert einen Ausgabestrom mit moeglichst vielen ss/rr/rrr.
** Die Reihenfolge INNERHALB von A bzw. B bleibt dabei unveraendert;
** nur voneinander unabhaengige Stack-Aktionen werden verschachtelt. */
static void	write_joined(t_ps_bench *bench, t_ps_pair *pair)
{
	int	i;
	int	j;
	int	stride;

	i = 0;
	j = 0;
	stride = pair->nb + 1;
	while (i < pair->na && j < pair->nb)
	{
		if (paired_op(pair->a[i], pair->b[j]) >= 0)
			ps_opt_write(bench, paired_op(pair->a[i++], pair->b[j++]));
		else if (pair->dp[(i + 1) * stride + j]
			>= pair->dp[i * stride + j + 1])
			ps_opt_write(bench, pair->a[i++]);
		else
			ps_opt_write(bench, pair->b[j++]);
	}
	while (i < pair->na)
		ps_opt_write(bench, pair->a[i++]);
	while (j < pair->nb)
		ps_opt_write(bench, pair->b[j++]);
}

/* Versucht die Paarbildung mit einer temporaeren DP-Tabelle.
** Schlaegt malloc fehl, bleiben beide Listen einzeln und korrekt.
** So ist die Optimierung optional, nicht Voraussetzung der Sortierung. */
void	ps_opt_join(t_ps_bench *bench, t_ps_pair *pair)
{
	int	i;

	if (pair->na && pair->nb)
		pair->dp = malloc(sizeof(int) * (size_t)(pair->na + 1)
				* (pair->nb + 1));
	if (pair->dp)
	{
		i = 0;
		while (i < (pair->na + 1) * (pair->nb + 1))
			pair->dp[i++] = 0;
		fill_table(pair);
		write_joined(bench, pair);
		free(pair->dp);
		return ;
	}
	i = 0;
	while (i < pair->na)
		ps_opt_write(bench, pair->a[i++]);
	i = 0;
	while (i < pair->nb)
		ps_opt_write(bench, pair->b[i++]);
}
