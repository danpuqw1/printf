/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:24:38 by dteemo            #+#    #+#             */
/*   Updated: 2020/03/03 13:24:42 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putnb(t_printf *p)
{
	intmax_t	n;

	if (p->f & F_LONG || p->f & F_LONG2)
		n = (p->f & F_LONG2) ? ((intmax_t)va_arg(p->ap, long long)) :
			((intmax_t)va_arg(p->ap, long));
	else if (p->f & F_INTMAX)
		n = (va_arg(p->ap, intmax_t));
	else if (p->f & F_SIZE_T)
		n = ((intmax_t)va_arg(p->ap, ssize_t));
	else if (p->f & F_SHORT || p->f & F_SHORT2)
		n = (p->f & F_SHORT2) ? (intmax_t)((char)va_arg(p->ap, int)) :
			(intmax_t)((short)va_arg(p->ap, int));
	else
		n = ((intmax_t)va_arg(p->ap, int));
	(p->f & F_ZERO && !(p->f & F_APP_PRECI)) ? p->precision = p->min_length : 0;
	itoa_printf(n, p, 0);
}

void	pf_putnb_base(int base, t_printf *p)
{
	uintmax_t	n;

	if (p->f & F_LONG || p->f & F_LONG2)
		n = (p->f & F_LONG2) ? ((intmax_t)va_arg(p->ap, unsigned long long)) :
			((intmax_t)va_arg(p->ap, unsigned long));
	else if (p->f & F_SHORT || p->f & F_SHORT2)
		n = (p->f & F_SHORT2) ? (uintmax_t)((unsigned char)va_arg(p->ap, int))
			: (uintmax_t)((unsigned short)va_arg(p->ap, int));
	else if (p->f & F_INTMAX)
		n = (va_arg(p->ap, uintmax_t));
	else if (p->f & F_SIZE_T)
		n = ((uintmax_t)va_arg(p->ap, size_t));
	else
		n = (uintmax_t)va_arg(p->ap, unsigned int);
	itoa_base_printf(n, base, p);
}

void	itoa_printf(intmax_t n, t_printf *p, int len)
{
	char		s[1024];
	uintmax_t	tmp;

	tmp = ABS(n);
	while (tmp)
	{
		tmp /= 10;
		++len;
	}
	if ((n < 0 || p->f & F_PLUS || p->f & F_SPACE) && p->f & F_ZERO
	&& p->min_length <= p->precision)
		--p->precision;
	p->printed = MAX(len, p->precision);
	if (n < 0 || p->f & F_PLUS || p->f & F_SPACE)
		++p->printed;
	p->padding = (p->printed > p->min_length) ? 0 : p->min_length - p->printed;
	padding(p, 0);
	tmp = ABS(n);
	itoa_base_fill(tmp, 10, s, p);
	(p->f & F_SPACE) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & F_PLUS && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, p->printed);
	padding(p, 1);
}

void	itoa_base_printf(uintmax_t n, int b, t_printf *p)
{
	char		s[1024];
	int			ext;

	get_printed(s, n, b, p);
	if (p->printed == -1)
		return ;
	(p->f & F_ZERO) ? p->precision = p->min_length : 0;
	ext = (p->printed >= p->precision) ? 0 : 1;
	p->printed = MAX(p->precision, p->printed);
	((p->f & F_SHARP) && b == 8 && !ext) ? --p->min_length : 0;
	((p->f & F_SHARP) && b == 8 && !n && (p->f & F_APP_PRECI)) ?
	++p->printed : 0;
	((p->f & F_SHARP) && b == 16 && !(p->f & F_ZERO)) ? p->min_length -= 2 : 0;
	p->padding = MAX(0, (p->min_length - p->printed));
	padding(p, 0);
	if ((n || (p->f & F_POINTER))
		&& (p->f & F_SHARP) && ((b == 8 && !ext) || (b == 16)))
		buffer(p, "0", 1);
	if ((n || (p->f & F_POINTER)) && (p->f & F_SHARP) && b == 16)
		buffer(p, (p->f & F_UPCASE) ? "X" : "x", 1);
	itoa_base_fill(n, b, s, p);
	buffer(p, s, p->printed);
	padding(p, 1);
}

void	itoa_base_fill(uintmax_t tmp, int b, char s[BUF_SIZE], t_printf *p)
{
	int		len;

	len = p->printed;
	p->c = 'a' - 10 - ((p->f & F_UPCASE) >> 1);
	while (len--)
	{
		s[len] = tmp % b + ((tmp % b < 10) ? '0' : p->c);
		tmp /= b;
	}
	((p->f & F_APP_PRECI && p->f & F_ZERO && p->min_length
	== p->precision)) ? s[0] = ' ' : 0;
}
