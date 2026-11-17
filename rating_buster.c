/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rating_buster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 12:10:58 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:38 by gkudelka         ###   ########.fr       */
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
/*
اینجا رتبه بندی میکنیم  که جایگاه هر لیست کجاست
اینجور دو هد درست میکنم اولی رو با کل لیست مقایسه میشماریم از چند عضو کوچکتره اون میشه جایگاهش
*/
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
/*
 برای فهمیدن درصد بهم ریختیگی طول رو پیدا می  کنیم بعدش اکر زیر  دو بود خب صفر درست چون فقط
 یک عضو داره اگر بالای دو بود مثلا پنج بود ضرب در پنج منهای یک می کنیم میشه 
 بیست تقیسم بر دو میشه ده یعنی ما ده جفت مقایهسه داریم 
 همه رو باهم مقایسه میکنم جند جفت نامرتب داریم 
 ۱-۲ ۱-۳ ۱-۴ ۱-۵ ۲-۳ ۲-۴ ۲-۵ ۳-۴ ۳-۵ ۴-۵
 میمشاریم چندتاشون از چندشون بزرگ تره  تعدا بهم ریختی رو تقییم بر کل میکینم 
 مثلا
 ۳/۱۰ = ۰.۳
*/
double	calc_disorder(t_stack *a)
{
	t_stack	*scan;
	long	inv;
	long	pairs;

	pairs = (long)calc_size(a);
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
	return ((double)inv / (double)pairs);
}
