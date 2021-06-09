/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:09:24 by dteemo            #+#    #+#             */
/*   Updated: 2019/09/09 10:09:26 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_len(long double f)
{
	int				i;
	long long int	a;

	a = (long long int)f;
	i = 0;
	if (a < 0)
		i++;
	while (a != 0)
	{
		a /= 10;
		i++;
	}
	return (i);
}

char		*rev_s(char *s)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = (char*)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (s[0] == '-')
	{
		while (i < len - 1)
		{
			s[i] = s[i + 1];
			i++;
		}
		s[i] = '-';
		i = 0;
	}
	while (i < len)
	{
		res[i] = s[len - i - 1];
		i++;
	}
	res[i] = '\0';
	free(s);
	return (res);
}

char		*ft_litoa(long long int a)
{
	char	*res;
	int		i;

	if (a < -9223372036854775807)
		return (ft_strdup("-9223372036854775808"));
	res = (char*)malloc(sizeof(char) * 21);
	i = 0;
	if (a < 0)
	{
		res[i++] = '-';
		a *= -1;
	}
	if (a == 0)
		res[i++] = '0';
	while (a > 0)
	{
		res[i] = a % 10 + '0';
		a = a / 10;
		i++;
	}
	res[i] = '\0';
	res = rev_s(res);
	return (res);
}

int			cnv_z(long double f, char *res)
{
	long long int	a;
	char			*cnv;
	int				i;

	a = (long long int)f;
	cnv = ft_litoa(a);
	i = 0;
	if (f < 0 && cnv[0] != '-')
		res[i++] = '-';
	while (*cnv != '\0')
	{
		res[i] = *cnv++;
		i++;
	}
	return (i);
}

long double	del_z(long double f)
{
	long double		res;
	long long int	a;

	a = (long long int)f;
	res = f - a;
	if (res < 0)
		res *= -1;
	return (res);
}
