/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:39:18 by student           #+#    #+#             */
/*   Updated: 2020/07/09 21:39:23 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	field_width_precision(t_printf *p)
{
	if (48 < *p->format && *p->format < 58)
	{
		p->min_length = MAX(1, ft_atoi(p->format));
		while (47 < *p->format && *p->format < 58)
			++p->format;
	}
	if (*p->format == '.')
	{
		++p->format;
		p->precision = MAX(ft_atoi(p->format), 0);
		while (47 < *p->format && *p->format < 58)
			++p->format;
		p->f |= F_APP_PRECI;
	}
	while (*p->format == '.' || (48 < *p->format && *p->format < 58))
		++p->format;
}

void	conversion_specifier_prev(t_printf *p)
{
	if (p->c == 's')
		(p->f & F_LONG || p->f & F_LONG2) ? pf_putwstr(p) : pf_putstr(p);
	else if (ft_strchr("dDi", p->c))
		pf_putnb(p);
	else if (p->c == 'f' || p->c == 'F')
		(p->f & F_APP_PRECI && !p->precision) ? pf_putnb(p) : pf_putdouble(p);
	else if (p->c == 'c' || p->c == 'C')
		pf_character(p, va_arg(p->ap, unsigned));
	else if (ft_strchr("oOuUbBxX", p->c))
		pf_putnb_base(ft_strchri_lu(".b..ou..x", p->c, -1) << 1, p);
}

void	itoa_base_zero_sharp2(char s[1024], int pa, int b, t_printf *p)
{
	int ext;
	int i;

	i = 0;
	ext = MAX(p->precision, p->printed);
	while (p->min_length - ext - pa - i > 0)
	{
		buffer(p, " ", 1);
		i++;
	}
	if (b == 16)
		buffer(p, (p->f & F_UPCASE) ? "0X" : "0x", 2);
	i = 0;
	while (p->precision - p->printed - i > 0)
	{
		buffer(p, "0", 1);
		i++;
	}
	buffer(p, s, p->printed);
}

void	itoa_base_zero_sharp(char s[1024], uintmax_t n, int b, t_printf *p)
{
	int pa;
	int i;

	if (b == 16 && p->c != 'p')
		pa = 2;
	else
		pa = 0;
	itoa_base_fill(n, b, s, p);
	if (!(p->f & F_APP_PRECI))
	{
		if (b == 16)
			buffer(p, (p->f & F_UPCASE) ? "0X" : "0x", 2);
		i = 0;
		while (p->min_length - p->printed - i - pa > 0)
		{
			buffer(p, "0", 1);
			i++;
		}
		buffer(p, s, p->printed);
		return ;
	}
	itoa_base_zero_sharp2(s, pa, b, p);
}

void	get_printed(char s[1024], uintmax_t n, int b, t_printf *p)
{
	uintmax_t	tmp;

	p->printed = 0;
	tmp = n;
	while (tmp && ++p->printed)
		tmp /= b;
	if (p->f & F_ZERO && p->f & F_SHARP)
	{
		itoa_base_zero_sharp(s, n, b, p);
		p->printed = -1;
		return ;
	}
}
