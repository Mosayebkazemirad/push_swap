/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   bench_output.c                                    :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/14 10:11:32 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:53:15 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Prozent mit zwei Nachkommastellen, kaufmaennisch gerundet. */

static void	print_disorder(t_ps_bench *bench)
{
	long	percent;

	percent = (long)(bench->disorder * 10000.0 + 0.5);
	ps_err_text("[bench] disorder: ");
	ps_err_number(percent / 100);
	ps_err_text(".");
	if (percent % 100 < 10)
		ps_err_text("0");
	ps_err_number(percent % 100);
	ps_err_text("%\n");
}

/* Beim Flag --adaptive steht zuerst "Adaptive", danach die
** tatsaechlich gewaehlte Komplexitaetsklasse (Simple/Medium/Complex).
** Erzwungene Modi erhalten ihren eigenen Strategienamen. */

static void	print_strategy(t_ps_bench *bench)
{
	ps_err_text("[bench] strategy: ");
	if (bench->adaptive)
		ps_err_text("Adaptive / ");
	else if (bench->strategy == 1)
		ps_err_text("Simple / ");
	else if (bench->strategy == 2)
		ps_err_text("Medium / ");
	else
		ps_err_text("Complex / ");
	if (bench->strategy == 1)
		ps_err_text("O(n²)\n");
	else if (bench->strategy == 2)
		ps_err_text("O(n√n)\n");
	else
		ps_err_text("O(n log n)\n");
}

/* Erste Zeile mit den Operationen sa bis pb. */

static void	print_counts_one(t_ps_bench *bench)
{
	ps_err_text("[bench] ");
	ps_err_count("sa: ", bench->count[0], 0);
	ps_err_count("sb: ", bench->count[1], 0);
	ps_err_count("ss: ", bench->count[2], 0);
	ps_err_count("pa: ", bench->count[3], 0);
	ps_err_count("pb: ", bench->count[4], 1);
}

/* Zweite Zeile mit den Operationen ra bis rrr. */

static void	print_counts_two(t_ps_bench *bench)
{
	ps_err_text("[bench] ");
	ps_err_count("ra: ", bench->count[5], 0);
	ps_err_count("rb: ", bench->count[6], 0);
	ps_err_count("rr: ", bench->count[7], 0);
	ps_err_count("rra: ", bench->count[8], 0);
	ps_err_count("rrb: ", bench->count[9], 0);
	ps_err_count("rrr: ", bench->count[10], 1);
}

/* Druckt die geforderten fuenf Benchmark-Zeilen auf stderr.
** Der Checker liest ausschliesslich die Operationen auf stdout.
** Ohne --bench wird hier ueberhaupt nichts ausgegeben. */

void	ps_bench_print(void)
{
	t_ps_bench	*bench;

	bench = ps_bench_data();
	if (!bench->enabled)
		return ;
	print_disorder(bench);
	print_strategy(bench);
	ps_err_text("[bench] total_ops: ");
	ps_err_number(bench->total);
	ps_err_text("\n");
	print_counts_one(bench);
	print_counts_two(bench);
}
