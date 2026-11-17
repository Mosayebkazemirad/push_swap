/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 09:20:53 by mkazemir          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:35 by gkudelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Erlaubte Strategien. Ohne Flag wird Adaptive verwendet. */
static int	is_strategy(char *arg)
{
	return (same_word(arg, "--simple")
		|| same_word(arg, "--medium")
		|| same_word(arg, "--complex")
		|| same_word(arg, "--adaptive"));
}

/* Entfernt die optionalen Flags aus argv, ohne Zahlen zu kopieren.
** Uebrige Argumente werden nach vorne verschoben, argc angepasst.
** Mehrere Strategien oder doppeltes --bench gelten als Fehler.
** Ohne Strategiewahl bleibt mode = NULL => Adaptive. */
/*
این فانکشن چهار تا وردی داره که ورودی خام رو میگیره  با بنج خام و مد خام 
متغیر ولیو ای و ولیو یک هستن برای اینکه عبور کنیم استیتمنت ایف اول چک میکنیم ببینم کاربر فلگ بنج رو زده یا نه
اگر زده بود بنج یک میشه  اگر نزنده بود فرستاده میشه برای کنترل فلک های دیگه در ایف الس
اگر نزده بود وکتور ما به تریتب منظم میشه اگر زده بود
برای بار اول مد ما خالیه پس شرط ایف منفی میسه و استراٰژی
  در مد ذخیهر میشه اگر بار دوم بیاد حذف شرط درسته و خط میشه 
تعداد اکانتر ما به لیو تغییر میکنه که مقدار صحیح رو داشته باشیم.
و در نهایت اگر بنج صفر یا یک باشه عمل درسته اگر بیشتر شده باشه خطا میشه
*/
static int	select_strategy(int *argc, char **argv,
		const char **mode, int *bench)
{
	int	i;
	int	values;

	i = 1;
	values = 1;
	*mode = NULL;
	*bench = 0;
	while (i < *argc)
	{
		if (same_word(argv[i], "--bench"))
			(*bench)++;
		else if (is_strategy(argv[i]))
		{
			if (*mode)
				return (0);
			*mode = argv[i];
		}
		else
			argv[values++] = argv[i];
		i++;
	}
	*argc = values;
	return (*bench <= 1);
}

/* Regulärer Einstieg: Flags lesen, beide Stacks initialisieren,
** Zahlen pruefen, sort_stack() starten und Speicher freigeben.
** stdout bleibt fuer Stack-OPs, stderr fuer Fehler und --bench.
** Ranking und Disorder werden von sort_stack() einmal bestimmt. */
/*مین برای شروع طراحی شده  که بنچ ها رو تشخیص بده ابندا 
میفرسته برای تعیین ا ستراتژی در یک فانکشن استیت.*/
int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	const char	*mode;
	int			bench;

	if (argc < 2)
		return (0);
	/* فرستاده میشه برای فانکشن های بالا*/
	if (!select_strategy(&argc, argv, &mode, &bench) || argc < 2)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	stack_b = NULL;
	/* check_input میریم برای بررسی کد که پارسینگ کنیم  در فایل */
	stack_a = input_check(argc, argv);
	if (!stack_a)
		return (1);
	/*
	 وارد این فایل میشیم bench_stateوقتی کاربر برنامه را با فلگ 
	 --bench اجرا می‌کند (مثلاً ./push_swap --bench 3 2 1)،
	  در تابع select_strategy متغیر bench برابر 1 شده است.
	  این تابع دقیقاً قبل از شروع مرتب‌سازی فراخوانی می‌شود تا سیستم آمارگیری را آماده کند:
	*/
	ps_bench_begin(bench);
	/*
	اینجا شروع برنامه است که وارد فایل sorting می شیم*/
	sort_stack(&stack_a, &stack_b, mode);
	ps_bench_print();
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
