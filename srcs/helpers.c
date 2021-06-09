/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:54:34 by dteemo            #+#    #+#             */
/*   Updated: 2020/03/03 13:54:39 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_strchri(char *s, int c, int i)
{
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

int		ft_strchri_lu(char *s, int c, int i)
{
	i = -1;
	while (s[++i])
		if (s[i] == c || s[i] == c + 32)
			return (i);
	return (-1);
}

size_t	ft_wcharlen(unsigned wc)
{
	if (wc < 0x80)
		return (1);
	else if (wc < 0x800)
		return (2);
	else if (wc < 0x10000)
		return (3);
	return (4);
}

size_t	ft_wstrlen(unsigned *s)
{
	size_t	len;

	len = 0;
	while (*s != L'\0')
	{
		len += ft_wcharlen(*s);
		++s;
	}
	return (len);
}

char	*del_f(char *a)
{
	char	*r;
	int		i;

	i = 0;
	r = (char *)malloc(ft_strlen(a));
	while (a[i + 1] != '\0')
	{
		r[i] = a[i + 1];
		i++;
	}
	r[i] = '\0';
	free(a);
	return (r);
}
