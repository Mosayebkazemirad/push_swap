/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:26:12 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:44 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Betrag einer Schrittzahl, ohne die Richtung zu beachten. */
int	abs_steps(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}

/* Wandelt einen Index in die kuerzere Drehrichtung um.
** Negativ bedeutet rueckwaerts rotieren. */
// میخوام بفهمم صفر در نیمه بالاییه یا نمیه پایینی اگر پایینی بود عدد منفی میفرستیم اگ بالایی مثبت
int	calc_rota_pos(int index, int size)
{
	if (index > size / 2)
		return (index - size);
	return (index);
}

/* Vergleicht Flag-Texte ohne libft/strcmp.
** NULL wird als kein Treffer behandelt. */
int	same_word(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return (*a == *b);
}

/* Prueft, ob die urspruenglichen Zahlen in A sortiert sind. */
int	is_sorted(t_stack *a)
{
	while (a && a->next)
	{
		if (a->n > a->next->n)
			return (0);
		a = a->next;
	}
	return (1);
}

/* Position eines Rangs, ohne den Stack zu veraendern. */
/* Sucht die Position eines Rangs ohne Stack-Aenderung. */
int	calc_rank_pos(t_stack *stack, int rank)
{
	int	pos;

	pos = 0;
	while (stack && stack->rank != rank)
	{
		pos++;
		stack = stack->next;
	}
	return (pos);
}
