/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push_swap.h                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 11:50:22 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:54:25 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# define PS_OPT_BLOCK 512

/* Mosis original linked list (unchanged). */
typedef struct s_stack
{
	int				n;
	int				rank;
	struct s_stack	*next;
}	t_stack;

/* Hilfsdaten: Laengste aufsteigende Teilfolge. */
typedef struct s_sort_mark
{
	int	length;
	int	parent;
	int	keep;
}	t_sort_mark;

/* Geringste Einfuegekosten zwischen A und B. */
typedef struct s_sort_move
{
	int	ra;
	int	rb;
	int	cost;
}	t_sort_move;

/* Optionaler Benchmark: alle Werte gehoeren zum laufenden Prozess. */
typedef struct s_ps_bench
{
	long			count[11];
	long			total;
	double			disorder;
	int				strategy;
	int				adaptive;
	int				enabled;
	int				optimizer_on;
	int				pending_len;
	unsigned char	pending[PS_OPT_BLOCK];
}	t_ps_bench;

/* Unabhaengige Stack-Befehle koennen neu angeordnet werden. */
typedef struct s_ps_pair
{
	unsigned char	a[PS_OPT_BLOCK];
	unsigned char	b[PS_OPT_BLOCK];
	int				na;
	int				nb;
	int				*dp;
}	t_ps_pair;

/* Mosis Parser, Fehlerbehandlung und bestehende Operationen. */
t_stack	*input_check(int argc, char **argv);
int		ps_is_space(char c);
int		ps_read_number(const char **str, int *number);
void	ps_append_number(t_stack **stack, int number);
void	ps_input_error(t_stack **stack);
void	free_stack(t_stack **stack);
void	ft_putstr(char *s);
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

/* Statistik: ft_putstr zaehlt nur gueltige Push_swap-Befehle. */
t_ps_bench	*ps_bench_data(void);
void		ps_bench_begin(int enabled);
void		ps_bench_set(double disorder, int strategy, int adaptive);
void		ps_bench_record(const char *operation);
int			ps_op_kind(const char *operation);
void		ps_bench_print(void);
void		ps_err_text(const char *s);
void		ps_err_number(long number);
void		ps_err_count(const char *name, long count, int last);

/* Strategie-Auswahl: kein Flag = Adaptive (<20%, <50%, sonst). */
void	sort_stack(t_stack **a, t_stack **b, const char *mode);
void	simple_ranked(t_stack **a, t_stack **b);
void	medium_ranked(t_stack **a, t_stack **b);
void	complex_ranked(t_stack **a, t_stack **b);

/* Ranking, Disorder, Rotation und Quickchecks. */
void	get_ranked(t_stack *a);
double	calc_disorder(t_stack *a);
int		calc_size(t_stack *a);
int		is_sorted(t_stack *a);
int		abs_steps(int value);
int		calc_rota_pos(int index, int size);
int		calc_rank_pos(t_stack *stack, int rank);
int		same_word(const char *a, const char *b);
int		quick_check(t_stack **a, t_stack **b);

/* Kleinere Teilbereiche: Top-Sortierung erhaelt den unteren Stack. */
void	sort_three_a(t_stack **a);
void	sort_three_b(t_stack **b);
void	sort_three_top_a(t_stack **a, t_stack **b);
void	sort_three_top_b(t_stack **a, t_stack **b);
void	sort_four_a(t_stack **a, t_stack **b, int low);
void	sort_four_b(t_stack **a, t_stack **b, int low);

/* Simple/Medium teilen ihre greedy Einfuegeloesung. */
void		mark_lis(t_stack *a, t_sort_mark *work, int size);
void		mark_run(t_stack *a, t_sort_mark *work, int size);
int			sort_greedy(t_stack **a, t_stack **b, long limit, int run);
t_sort_move	cheapest_move(t_stack *a, t_stack *b);
int			move_cost(int a_steps, int b_steps);
void		do_move(t_stack **a, t_stack **b, t_sort_move move);
void		rotate_a(t_stack **a, int steps);
void		rotate_b(t_stack **b, int steps);

/* Medium-Chunks und Complex-Partitionierung. */
void	sort_chunks(t_stack **a, t_stack **b, int size);
void	split_a(t_stack **a, t_stack **b, int count, int low);
void	split_b(t_stack **a, t_stack **b, int count, int low);

/* Complex optimiert den Ausgabestrom, nicht die Stack-Mutationen. */
void	ps_opt_begin(t_stack *a);
void	ps_opt_finish(t_stack *a);
int		ps_opt_capture(const char *op);
void	ps_opt_flush(t_ps_bench *bench);
void	ps_opt_join(t_ps_bench *bench, t_ps_pair *pair);
void	ps_opt_write(t_ps_bench *bench, int kind);

#endif
