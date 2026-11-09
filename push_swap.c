/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   push_swap.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/04 09:20:53 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/09 13:42:27 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		size;

	if (argc < 2)
		return (0);
	stack_a = input_check(argc, argv);
	if (!stack_a)
		return (1);
	if (is_sorted(stack_a))
	{
		return (0);
	};
	get_ranked(stack_a);
	size = (int) calc_size(stack_a);
	if (size <= 3)
		simple_algo(&stack_a, &stack_b);
	else if (size <= 100)
		medium_algo(&stack_a, &stack_b);
	else
		complex_algo(&stack_a, &stack_b);
	stack_b = NULL;
	return (0);
}

/*#include "push_swap.h"
#include <stdio.h>

//hilf function
static void	print_stack(t_stack *stack, char name)
{
printf("Stack %c: ", name);
if (!stack)
{
printf("(EMPTY)\n");
return ;
}
while (stack)
{
printf("[%d] -> ", stack->n);
stack = stack->next;
}
printf("NULL\n");
}

int	main(int argc, char **argv)
{
t_stack	*stack_a;
t_stack	*stack_b;

if (argc < 2)
{
printf("error\n");
return (0);
}

printf("\t===create stack A===");
stack_a = input_check(argc, argv);
stack_b = NULL;

printf("Result\n");
print_stack(stack_a, 'A');
print_stack(stack_b, 'B');

printf("\n ========Test sa (Swap A)========= ");
printf("\n\t run stack a:\n");
sa(&stack_a);
print_stack(stack_a, 'A');
print_stack(stack_b, 'B');

printf("\n ========test pb (Push to B)====== ");
printf("\n\t run pb (move 2 items B):\n");
int io = 0;
while(io++ < 5)
pb(&stack_a, &stack_b);
print_stack(stack_a, 'A');
print_stack(stack_b, 'B');
last->next

printf("\n ========test pb (Push to A)====== ");
printf("\n\t run pb (move 2 items !):\n");
pa(&stack_a, &stack_b);
print_stack(stack_a, 'A');
print_stack(stack_b, 'B');

printf("\n ========Test sa (Swap A , B)======== ");
printf("\n\t run stack a:\n");
ss(&stack_a, &stack_b);
print_stack(stack_a, 'A');
print_stack(stack_b, 'B');

printf("\n =========Test sb (Swap B)========= ");
printf("\n\t run stack a:\n");
sb(&stack_b);
print_stack(stack_b, 'B');

printf("\n ======test ra (Rotate A)======== ");
printf("\n\t run ra (move first to the end ):\n");
print_stack(stack_a, 'A');
ra(&stack_a);
print_stack(stack_a, 'A');

printf("\n ======test rb (Rotate B)======== ");
printf("\n\t run rb (move end to the frist ):\n");
print_stack(stack_b, 'B');
rb(&stack_b);
print_stack(stack_b, 'B');

printf("\n ======test rra (RevRotate A)======== ");
printf("\n\t run rra (move end to the frist ):\n");
print_stack(stack_a, 'A');
rra(&stack_a);
print_stack(stack_a, 'A');

printf("\n ======test rrb (RevRotate B)======== ");
printf("\n\t run rrb (move end to the frist ):\n");
print_stack(stack_b, 'B');
rra(&stack_b);
print_stack(stack_b, 'B');

printf("\n ======test rrr (RevRotate A , B)======== ");
printf("\n\t run rrr (move end to the frist ):\n");
print_stack(stack_a, 'A');
print_stack(stack_b, 'B');
rrr(&stack_a, &stack_b);
print_stack(stack_a, 'A');
print_stack(stack_b, 'B');

printf("\nclean memory (Exit) =");
printf("\n ree is success voll \n");
return (0);
}*/
