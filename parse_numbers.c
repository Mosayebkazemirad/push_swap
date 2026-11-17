/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkudelka <gkudelka@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 11:23:06 by gkudelka          #+#    #+#             */
/*   Updated: 2026/11/14 13:09:30 by gkudelka         ###   ########.fr       */
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
		// اینجا لیمتون یه اینت مکس هست که منهای عدد میشه تقسیم بر ده 
		// معنیش اینکه اگر به ولیو یک عدد دیگه اضافشه سریز میکنه  و از سریز جلوگیری میکنیم 
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
	// این تکنیک استفاده شده برای اینکه اگر منفی شده اینت مین بفرستیم اگر مثبت بود اینت مکس بفرستیم
	//اگر عدد منفی باشد چون در لانگ کست کردیم یه واخد اضافه میشه در فانکشن بعدی منفیش میکنم 
	if (!read_digits(str, (long)INT_MAX + (sign < 0), number, sign))
		return (0);
	// اگر فانکشن قبلی برعکس تعیین شده میگه اگر صفره یک بفرست که اونجا برعکس بشه 
	// پ خطا مخسوب نشه اگر فاصله است بازم درسته اگر فاصه نیست . صفرم نیست پس اشتباه 
	return (!**str || ps_is_space(**str));
}
