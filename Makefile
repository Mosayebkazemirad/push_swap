NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror

MOSIS_SRC = push_swap.c check_input.c libft.c push.c rotate.c \
            rev_rotate.c swap.c
PARSE_SRC = parse_numbers.c parse_stack.c
ALGOS_SRC = call_rotations.c complex_algo.c find_lis.c get_move.c \
            greedy_sort.c medium_algo.c medium_chunks.c rating_buster.c \
            simple_algo.c sort_four.c sort_small.c sort_three.c \
            sort_utils.c sorting.c split_b.c
BENCH_SRC = bench_state.c bench_output.c bench_format.c
OPT_SRC = ps_opt_control.c ps_opt_buffer.c ps_opt_join.c ps_opt_output.c
SRCS = $(MOSIS_SRC) $(PARSE_SRC) $(ALGOS_SRC) $(BENCH_SRC) $(OPT_SRC)
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re
