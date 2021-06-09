/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:23:51 by dteemo            #+#    #+#             */
/*   Updated: 2020/03/03 13:23:54 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flags(t_printf *p)
{
	while ((p->n = ft_strchri("# +-0*", *p->format, -1)) > -1 && ++p->format)
		p->f |= (1 << p->n);
	((p->f & F_MINUS) && !(p->f & F_WILDCARD)) ? p->f &= ~F_ZERO : 0;
	(p->f & F_PLUS) ? p->f &= ~F_SPACE : 0;
	if (p->f & F_WILDCARD)
	{
		p->f &= ~F_WILDCARD;
		if ((p->n = (int)va_arg(p->ap, int)) < 0)
		{
			p->f |= F_MINUS;
			p->n = -p->n;
		}
		else
			p->f &= ~F_MINUS;
		if (!(p->f & F_APP_PRECI))
			p->min_length = p->n;
		else
		{
			p->precision = (!(p->f & F_MINUS)) ? p->n : 0;
			p->f = (!p->n) ? p->f | F_APP_PRECI : p->f & ~F_APP_PRECI;
		}
	}
}

static void	conversion_specifier(t_printf *p)
{
	p->c = *p->format;
	if (!(ft_strchr("sdDifFcCoOuUbBxXSpnm{", p->c)) || p->c == 0)
	{
		cs_not_found(p);
		return ;
	}
	conversion_specifier_prev(p);
	if (p->c == 'S')
		pf_putwstr(p);
	else if (p->c == 'p')
		print_pointer_address(p);
	else if (p->c == 'n')
		*va_arg(p->ap, int *) = p->len;
	else if (p->c == 'm')
		ft_printf_putstr(STRERR(errno), p);
	else if (p->c == '{')
		color(p);
}

void		get_r(t_printf *p)
{
	while (42)
	{
		if (*p->format == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? F_LONG2 : F_LONG;
		else if (*p->format == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format) ? F_SHORT2 : F_SHORT;
		else if (*p->format == 'L')
			p->f |= F_LONG2;
		else if (*p->format == 'j')
			p->f |= F_INTMAX;
		else if (*p->format == 'z')
			p->f |= F_SIZE_T;
		else
			break ;
		++p->format;
	}
}

void		parse_optionals(t_printf *p)
{
	p->f = 0;
	p->min_length = 0;
	p->precision = -1;
	p->np = 0;
	parse_flags(p);
	field_width_precision(p);
	if (p->precision == -1)
	{
		p->precision = 1;
		p->np = 1;
	}
	get_r(p);
	parse_flags(p);
	(p->f & F_PLUS) ? p->f &= ~F_SPACE : 0;
	if (ft_strchr("CDSUOBX", *p->format))
		p->f |= (*p->format != 'X') ? F_LONG : F_UPCASE;
	conversion_specifier(p);
}

void		cs_not_found(t_printf *p)
{
	if ((p->padding = p->min_length - 1) > 0)
	{
		padding(p, 0);
		buffer(p, p->format, 1);
		padding(p, 1);
		return ;
	}
	if (*p->format != '\0')
		buffer(p, p->format, 1);
}
