/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push_swap.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 09:20:53 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:54:21 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Erlaubte Strategien. Ohne Flag wird Adaptive verwendet. */

static int	is_strategy(char *arg)
{
	return (same_word(arg, "--simple")
		|| same_word(arg, "--medium")
	|| same_word(arg, "--complex")
	|| same_word(arg, "--adaptive") || same_word(arg,"--count_only"));
}

/* Entfernt die optionalen Flags aus argv, ohne Zahlen zu kopieren.
** Uebrige Argumente werden nach vorne verschoben, argc angepasst.
** Mehrere Strategien oder doppeltes --bench gelten als Fehler.
** Ohne Strategiewahl bleibt mode = NULL => Adaptive. */
static int select_strategy(int * argc, char * *argv,
	const char	**mode, int *bench)
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
int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	const char	*mode;
	int			bench;

	if (argc < 2)
		return (0);
	if (!select_strategy(&argc, argv, &mode, &bench) || argc < 2)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	stack_b = NULL;
	stack_a = input_check(argc, argv);
	if (!stack_a)
		return (1);
	if(same_word(mode,"--count_only"))
	{
		bench = argc - 1 ;
		while(bench > 0)
		{
			char c ;
			c = bench / 10 +'0';
			write(1,&c,1);
			if(bench <= 99)
			{
				c = bench % 10 + '0';
				write(1,&c,1);
				return(0);
			}
			bench /= 10;
		}
		return(0);

	}
	ps_bench_begin(bench);
	sort_stack(&stack_a, &stack_b, mode);
	ps_bench_print();
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
