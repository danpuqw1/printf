/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:25:54 by dteemo            #+#    #+#             */
/*   Updated: 2020/03/03 13:25:55 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	color(t_printf *p)
{
	int len;

	p->printed = 5;
	if (!ft_strncmp(p->format, "{red}", (len = 5)))
		buffer(p, PF_RED, p->printed);
	else if (!ft_strncmp(p->format, "{green}", (len = 7)))
		buffer(p, PF_GREEN, p->printed);
	else if (!ft_strncmp(p->format, "{yellow}", (len = 8)))
		buffer(p, PF_YELLOW, p->printed);
	else if (!ft_strncmp(p->format, "{blue}", (len = 6)))
		buffer(p, PF_BLUE, p->printed);
	else if (!ft_strncmp(p->format, "{purple}", (len = 8)))
		buffer(p, PF_PURPLE, p->printed);
	else if (!ft_strncmp(p->format, "{cyan}", (len = 6)))
		buffer(p, PF_CYAN, p->printed);
	else if (!ft_strncmp(p->format, "{eoc}", (len = 5)))
		buffer(p, PF_EOC, --p->printed);
	else if (!(len = 0))
		p->printed = 0;
	p->format += len - 1;
	p->len += p->printed;
}

void	pf_putdb_zero(t_printf *p, char zn, char *a, int len)
{
	int i;

	i = 0;
	if (p->f & F_PLUS || zn == '-')
	{
		buffer(p, &zn, 1);
		i++;
	}
	if (!(p->f & F_PLUS) && p->f & F_SPACE)
	{
		buffer(p, " ", 1);
		i++;
	}
	while (p->min_length - len - i > 0)
	{
		buffer(p, "0", 1);
		i++;
	}
	buffer(p, a, len);
	ft_memdel((void**)&a);
}

void	pf_putdb_minus(t_printf *p, char zn, char *a, int len)
{
	int i;

	i = 0;
	if (p->f & F_PLUS || zn == '-')
	{
		buffer(p, &zn, 1);
		i++;
	}
	if (!(p->f & F_PLUS) && p->f & F_SPACE)
	{
		buffer(p, " ", 1);
		i++;
	}
	buffer(p, a, len);
	while (p->min_length - len - i > 0)
	{
		buffer(p, " ", 1);
		i++;
	}
	ft_memdel((void**)&a);
}

void	pf_putdb_def(t_printf *p, char zn, char *a, int len)
{
	int i;

	i = 0;
	if (p->f & F_PLUS || zn == '-')
		i++;
	while (p->min_length - len - i > 0)
	{
		buffer(p, " ", 1);
		i++;
	}
	if (p->f & F_PLUS || zn == '-')
		buffer(p, &zn, 1);
	buffer(p, a, len);
	ft_memdel((void**)&a);
}

void	pf_putdouble(t_printf *p)
{
	long double	n;
	char		*a;
	int			len;
	char		zn;

	n = (p->f & F_LONG2) ? (long double)va_arg(p->ap, long double)
			: (double)va_arg(p->ap, double);
	a = (p->np == 1) ? convert_f(n, -1) : convert_f(n, p->precision);
	zn = (a[0] == '-') ? '-' : '+';
	if (zn == '-')
		a = del_f(a);
	len = ft_strlen(a);
	if (p->f & F_ZERO)
	{
		pf_putdb_zero(p, zn, a, len);
		return ;
	}
	if (p->f & F_MINUS)
	{
		pf_putdb_minus(p, zn, a, len);
		return ;
	}
	pf_putdb_def(p, zn, a, len);
}
