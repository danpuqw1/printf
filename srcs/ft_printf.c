/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:22:28 by dteemo            #+#    #+#             */
/*   Updated: 2020/03/03 13:22:30 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format)
				break ;
			parse_optionals(&p);
		}
		else
			buffer(&p, p.format, 1);
		p.format = (*p.format == '\0') ? p.format : p.format + 1;
	}
	write(p.fd, p.buff, p.buffer_index);
	va_end(p.ap);
	return (p.len);
}

int		ft_dprintf(int fd, const char *format, ...)
{
	t_printf	p;

	ft_bzero(&p, sizeof(p));
	p.fd = fd;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format)
				break ;
			parse_optionals(&p);
		}
		else
			buffer(&p, p.format, 1);
		++p.format;
	}
	write(p.fd, p.buff, p.buffer_index);
	va_end(p.ap);
	return (p.len);
}

void	buffer(t_printf *p, void *new, size_t size)
{
	int			diff;
	long long	new_i;

	new_i = 0;
	while (BUF_SIZE - p->buffer_index < (int)size)
	{
		diff = BUF_SIZE - p->buffer_index;
		ft_memcpy(&(p->buff[p->buffer_index]), &(new[new_i]), diff);
		size -= diff;
		new_i += diff;
		p->buffer_index += diff;
		p->len += diff;
		write(p->fd, p->buff, p->buffer_index);
		p->buffer_index = 0;
	}
	ft_memcpy(&(p->buff[p->buffer_index]), &(new[new_i]), size);
	p->buffer_index += size;
	p->len += size;
}

void	print_pointer_address(t_printf *p)
{
	void	*pointer;

	pointer = va_arg(p->ap, void *);
	p->f &= ~F_SHARP;
	p->min_length -= (p->f & F_ZERO ? 2 : 0);
	p->padding = (p->printed > p->min_length - 3) ? 0 :
		p->min_length - 3 - p->printed;
	p->f |= F_SHARP;
	p->f |= F_POINTER;
	itoa_base_printf((uintmax_t)pointer, 16, p);
}

void	padding(t_printf *p, int n)
{
	char	c;

	if (!p->padding)
		return ;
	c = 32 | (p->f & F_ZERO);
	if (ft_strchr("idDxXoOuUf", p->c) && p->precision < p->min_length)
		c = 32;
	if (!n && !(p->f & F_MINUS))
		while (p->padding--)
			buffer(p, &c, 1);
	else if (n && (p->f & F_MINUS))
		while (p->padding--)
			buffer(p, &c, 1);
}
