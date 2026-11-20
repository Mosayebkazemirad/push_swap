/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parse_numbers.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: mkazemir <mkazemir@learner.42.tech>       #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/11/14 11:23:06 by mkazemir         #+#    #+#              */
/*   Updated: 2026/11/20 09:54:01 by mkazemir        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* Akzeptiert Leerzeichen und ASCII-Whitespace (Tab bis CR).
** Deshalb funktionieren auch gequotete Zahlenfolgen in argv. */

int	ps_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/* Liest mindestens eine Ziffer, sonst Fehler.
** Prueft VOR value * 10 + digit auf Ueberlauf, damit selbst sehr
** lange Zahlentexte keinen undefinierten Integer-Ueberlauf ausloesen. */

static int	read_digits(const char **str, long limit, int *number, int sign)
{
	long	value;
	int		digit;

	if (**str < '0' || **str > '9')
		return (0);
	value = 0;
	while (**str >= '0' && **str <= '9')
	{
		digit = **str - '0';
		if (value > (limit - digit) / 10)
			return (0);
		value = value * 10 + digit;
		(*str)++;
	}
	*number = (int)(value * sign);
	return (1);
}

/* Liest +/- und danach eine gueltige 32-Bit-Zahl.
** Fuer negative Zahlen erlaubt der Betrag auch INT_MAX + 1,
** damit INT_MIN korrekt eingelesen werden kann.
** Danach muss Leerraum oder das Ende des Arguments folgen. */

int	ps_read_number(const char **str, int *number)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	if (!read_digits(str, (long) INT_MAX + (sign < 0), number, sign))
		return (0);
	return (!**str || ps_is_space(**str));
}
