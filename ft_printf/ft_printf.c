/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 16:15:42 by imustafa          #+#    #+#             */
/*   Updated: 2021/11/14 16:20:02 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int		i;
	char	*n;

	i = 0;
	n = "(null)";
	if (s == NULL)
	{
		while (n[i] != '\0')
		{
			ft_putchar(n[i]);
			i++;
		}
		return (i);
	}
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_numlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ft_sign(int n)
{
	if (n < 0)
	{
		n = n * (-1);
		return (1);
	}
	else
		return (0);
}

int	ft_putnbr(int n)
{
	int	i;

	i = ft_numlen(n) + ft_sign(n);
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	if (n < 0 && n != -2147483648)
	{
		ft_putchar('-');
		ft_putnbr(n * -1);
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	if (n < 10 && n >= 0)
	{
		ft_putchar(n + '0');
	}
	return (i);
}

int	ft_hexlen(unsigned long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

int	ft_puthex(unsigned int hex)
{
	int	i;

	i = ft_hexlen(hex);
	if (hex > 15)
	{
		ft_puthexs(hex / 16);
		ft_puthexs(hex % 16);
	}
	if (hex <= 15 && hex >= 0)
	{
		if (hex > 9)
		{
			ft_putchar((hex - 9) + 96);
		}
		else
			ft_putchar(hex + '0');
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		tchar;
	char	spf;

	va_start(args, format);
	i = 0;
	tchar = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			spf = format[i + 1];
			if (spf == 's')
			{
				tchar += ft_putstr(va_arg(args, char *));
				i++;
			}
			if (spf == 'd')
			{
				tchar += ft_putnbr(va_arg(args, int));
				i++;
			}
			if (spf == 'x')
			{
				tchar += ft_puthex(va_arg(args, unsigned int));
				i++;
			}
		}
		else
		{
			tchar += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	return (tchar);
}