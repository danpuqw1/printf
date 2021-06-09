/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:06:00 by dteemo            #+#    #+#             */
/*   Updated: 2019/08/21 13:06:02 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_all9(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '9' && s[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

int		round_helper(const char *s, char *res, int i, int round_pl)
{
	while (i >= 0)
	{
		if (s[i] == '.')
		{
			res[i + round_pl] = '.';
			i--;
			continue;
		}
		if (s[i] != '9')
		{
			res[i + round_pl] = s[i] + 1;
			i--;
			break ;
		}
		else
			res[i + round_pl] = '0';
		i--;
	}
	return (i);
}

char	*round_res(char *s)
{
	int		i;
	char	*res;
	int		round_pl;

	i = ft_strlen(s) - 1;
	round_pl = 0;
	if (is_all9(s) == 1)
	{
		res = (char *)malloc(sizeof(char) * (i + 3));
		round_pl = 1;
	}
	else
		res = (char *)malloc(sizeof(char) * (i + 2));
	res[i + round_pl + 1] = '\0';
	i = round_helper(s, res, i, round_pl);
	while (i >= 0)
	{
		res[i + round_pl] = s[i];
		i--;
	}
	if (round_pl == 1)
		res[0] = '1';
	ft_memdel((void**)&s);
	return (res);
}

char	*get_dr(long double f, int i, char *res, int lend)
{
	res[i++] = '.';
	f = del_z(f);
	while (lend-- > 0)
	{
		f *= 10;
		res[i++] = (int)f + '0';
		f = del_z(f);
	}
	res[i] = '\0';
	f *= 10;
	if ((int)f > 4)
		res = round_res(res);
	return (res);
}

char	*convert_f(long double f, int pres)
{
	char	*res;
	int		lend;
	int		i;

	if (pres == -1)
		lend = 6;
	else
		lend = pres;
	if (lend != 0)
		res = (char*)malloc(sizeof(char) * (get_len(f) + lend + 2));
	else
		res = (char*)malloc(sizeof(char) * (get_len(f) + lend + 1));
	i = cnv_z(f, res);
	if (lend == 0)
	{
		res[i] = '\0';
		f = del_z(f);
		f *= 10;
		if ((int)f > 4)
			res = round_res(res);
		return (res);
	}
	return (get_dr(f, i, res, lend));
}
