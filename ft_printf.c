/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:55:31 by iecharak          #+#    #+#             */
/*   Updated: 2023/02/27 18:31:54 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_putchar_l(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr_l(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	else if (n < 0)
	{
		n *= -1;
		i += ft_putchar_l('-');
		i += ft_putnbr_l(n);
	}
	else if (n <= 9)
	{
		i += ft_putchar_l(n + '0');
	}
	else
	{
		i += ft_putnbr_l(n / 10);
		i += ft_putnbr_l(n % 10);
	}
	return (i);
}

int	ft_putstr_l(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (ft_putstr_l("(null)"));
	while (s[i])
	{
		ft_putchar_l(s[i]);
		i++;
	}
	return (i);
}

static int	check_format(va_list p, char c)
{
	if (c == 's')
		return (ft_putstr_l(va_arg(p, char *)));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_l(va_arg(p, int)));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	p;
	int		l;
	int		i;
	int		persent;

	l = 0;
	i = 0;
	persent = 0;
	va_start(p, s);
	while (s[i])
	{
		if (s[i] != '%')
			l += ft_putchar_l(s[i]);
		else if (s[i++] == '%')
			persent = 1;
		if (persent && s[i])
		{
			l += check_format(p, s[i]);
			persent = 0;
		}
		i++;
	}
	va_end(p);
	return (l);
}
