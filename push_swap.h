/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 11:50:22 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/05 11:51:12 by mkazemir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

/* Structures */
typedef struct s_stack
{
	int				n;
	int				rank;
	struct s_stack	*next;
	struct  s_stack *previous;
}	t_stack;

/* Initialization and Parsing */
t_stack	*input_check(int argc, char **argv);

/* Stack Operations */
void	sa(t_stack **stack_a);
void	sb(t_stack **stack_b);
void	ss(t_stack **stack_a, t_stack **stack_b);
void	pa(t_stack **stack_a, t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	ra(t_stack **stack_a);
void	rb(t_stack **stack_b);
void	rr(t_stack **stack_a, t_stack **stack_b);
void	rra(t_stack **stack_a);
void	rrb(t_stack **stack_b);
void	pb(t_stack **stack_a, t_stack **stack_b);
void	rrr(t_stack **stack_a, t_stack **stack_b);


/* Utils and Libft */
long	ft_atoi(const char *nptr);
void	ft_putstr(char *s);

/* Ranking and Sorting */
void	get_ranked(t_stack *stack);
int		is_sorted(t_stack *stack);
void	simple_algo(t_stack **a, t_stack **b);
void	medium_algo(t_stack **a, t_stack **b);
void	complex_algo(t_stack **a, t_stack **b);
void	restore_a(t_stack **a, t_stack **b, int size);
void	restore_binary(t_stack **a, t_stack **b);

/* Sorting Utilities */
unsigned int	calc_size(t_stack *stack);
int			calc_rota(t_stack *stack, int rank);
int			find_max_rank(t_stack *stack);
int			get_chunk_size(int n);
void		call_ra(t_stack **a, int rota);
void		call_rra(t_stack **a, int rota);
#endif
