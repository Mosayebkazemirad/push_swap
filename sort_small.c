/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 20:56:14 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:42 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Sonderfall fuer hoechstens fuenf Elemente.
** Kleinste Raenge nach B, verbleibende drei sortieren,
** danach alle Werte nach A zurueckholen. */
/*
ماینجا ما پزیشن صفر و یک رو پیدا میکنیم میفرستیم اسکت 
ب بعد سه تای باقی ماندع رو با تری مرتب میکینم و بعد برمیگردونیم به استک ا 
*/
static int	sort_small(t_stack **a, t_stack **b)
{
	int	n;
	int	rank;
	int	pos;

	n = calc_size(*a);
	if (n > 5)
		return (0);
	if (n == 2 && (*a)->rank > (*a)->next->rank)
		sa(a);
	rank = 0;
	while (n > 3 && rank < n - 3)
	{
		//sort_utils پیدا کردن پزیشن
		pos = calc_rank_pos(*a, rank);
		rotate_a(a, calc_rota_pos(pos, calc_size(*a)));
		pb(a, b);
		rank++;
	}
	if (n >= 3)
		sort_three_a(a);
	while (*b)
		pa(a, b);
	return (1);
}

/* Vergleicht auch das letzte mit dem ersten Element.
** Genau ein Rangabstieg bedeutet eine zyklisch sortierte Folge,
** die nur noch bis Rang 0 rotiert werden muss. */
/*
ممکنه عدد ها حلقه باشن کنترل میکنیم ببینم اگر بریک از یک بیشتر شد دیگه حلقه نیستن
*/
static int	cyclic_sorted(t_stack *a)
{
	t_stack	*head;
	int		breaks;

	head = a;
	breaks = 0;
	while (a->next)
	{
		if (a->rank > a->next->rank)
			breaks++;
		a = a->next;
	}
	// اینجا حلقه  اول  و اخر رو چک میکنیم ببینم شرط برقراره 
	if (a->rank > head->rank)
		breaks++;
	return (breaks == 1);
}

/* Sucht die erste Abweichung vom erwarteten Rang an dieser Stelle.
** Nur bei genau zwei falschen Positionen kommt ein Tausch infrage. */
/* 
کار این تابع این است که کل پشته a را از بالا تا پایین اسکن کند و
 مطمئن شود که فقط و فقط ۲ عدد 
 در کل پشته سر جای خودشان نیستند، و هم‌زمان جایِ اولی را برگرداند.
*/
static int	first_bad_position(t_stack *a)
{
	int	position;
	int	first;
	int	wrong;

	first = -1;
	wrong = 0;
	position = 0;
	while (a)
	{
		if (a->rank != position)
		{
			if (first == -1)
				first = position;
			wrong++;
		}
		position++;
		a = a->next;
	}
	if (wrong != 2)
		return (-1);
	return (first);
}

/* Prueft, ob zwei benachbarte Raenge vertauscht sind.
** Dann reicht: zur Stelle drehen, sa, zurueckdrehen. */
/*
این تابع یک میانبر بهینه‌سازی (Fast-Path) است
: چک می‌کند آیا کل پشته a فقط با جابه‌جا کردن دو عددِ کنار هم (sa) 
به طور کامل مرتب می‌شود یا نه —
 تا برای یک جابه‌جایی ساده، الکی سراغ الگوریتم‌های سنگین 
 (LIS، Chunk یا Radix) نرویم!
*/

static int	check_one_swap(t_stack **a)
{
	t_stack	*node;
	int		first;
	int		rotate;
	//
	first = first_bad_position(*a);
	if (first < 0)
		return (0);
	node = *a;
	rotate = first;
	while (rotate-- > 0)
		node = node->next;
	if (!node->next || node->rank != first + 1
		|| node->next->rank != first)
		return (0);
	rotate = calc_rota_pos(first, calc_size(*a));
	rotate_a(a, rotate);
	sa(a);
	rotate_a(a, -rotate);
	return (1);
}

/* Gemeinsame Abkuerzung vor den grossen Algorithmen.
** Sortiert, zyklisch sortiert, ein Swap oder <=5 Werte?
** 1 = fertig; 0 = Hauptstrategie wird noch gebraucht. */
int	quick_check(t_stack **a, t_stack **b)
{
	t_stack	*scan;
	int		pos;
	// sort_utilsمیفرستیم به فایل 
	if (is_sorted(*a))
		return (1);
	//میفرستیم استیت میخوایم ببین ایا عدد یک حلقه هستن یا نه اگر
	//اکر نبود وارد ایف میشیم اگه حلقه بودن ادامه میدم 
	if (!cyclic_sorted(*a))
	{
		// اگر مرتب حلقه نباشه وارد میشه  همین فانکشن بالایی
 		if (calc_size(*a) > 3 && check_one_swap(a))
			return (1);
		return (sort_small(a, b));
	}
	scan = *a;
	pos = 0;
	// اگر حلقه بودن اعداد پوزیشن صفر رو پیدا میکنم  میفرستیم برای 
	while (scan && scan->rank != 0)
	{
		pos++;
		scan = scan->next;
	}
	// sort_utils  در این دو فایل قرار دارندcall_rotations
	rotate_a(a, calc_rota_pos(pos, calc_size(*a)));
	return (1);
}
