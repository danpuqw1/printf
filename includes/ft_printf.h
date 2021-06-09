/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteemo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:26:43 by dteemo            #+#    #+#             */
/*   Updated: 2020/03/03 13:26:45 by dteemo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# define MAX(a, b)		b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)		a & ((a - b) >> 31) | b & (~(a - b) >> 31)
# define ABS(a)			(a < 0) ? -a : a
# define DABS(a)		(a < 0.0f) ? -a : a
# define STRERR			strerror
# define PF_RED			"\033[31m"
# define PF_GREEN		"\033[32m"
# define PF_YELLOW		"\033[33m"
# define PF_BLUE		"\033[34m"
# define PF_PURPLE		"\033[35m"
# define PF_CYAN		"\033[36m"
# define PF_EOC			"\033[0m"
# define F_SHARP		(1 << 0)
# define F_SPACE		(1 << 1)
# define F_PLUS			(1 << 2)
# define F_MINUS		(1 << 3)
# define F_ZERO			(1 << 4)
# define F_WILDCARD		(1 << 5)
# define F_UPCASE		(1 << 6)
# define F_SHORT		(1 << 7)
# define F_SHORT2		(1 << 8)
# define F_LONG			(1 << 9)
# define F_LONG2		(1 << 10)
# define F_INTMAX		(1 << 11)
# define F_SIZE_T		(1 << 12)
# define F_MIN_LEN		(1 << 13)
# define F_APP_PRECI	(1 << 14)
# define F_POINTER		(1 << 15)
# define BUF_SIZE		64

typedef struct			s_printf
{
	int					len;
	short				f;
	short				n;
	int					min_length;
	int					precision;
	int					padding;
	int					printed;
	int					fd;
	int					buffer_index;
	char				buff[BUF_SIZE];
	va_list				ap;
	char				*format;
	unsigned			c;
	int					np;
}						t_printf;

int						ft_printf(const char *format, ...);
int						ft_dprintf(int fd, const char *format, ...);
void					parse_optionals(t_printf *p);
void					cs_not_found(t_printf *p);
void					pf_putnb(t_printf *p);
void					pf_putnb_base(int base, t_printf *p);
void					itoa_printf(intmax_t d, t_printf *p, int len);
void					itoa_base_printf(uintmax_t d, int b, t_printf *p);
void					itoa_base_fill(uintmax_t tmp, int base, char *str,
						t_printf *p);
void					pf_putstr(t_printf *p);
void					pf_putwstr(t_printf *p);
void					pf_character(t_printf *p, unsigned c);
void					ft_printf_putstr(char *s, t_printf *p);
void					pf_putwchar(t_printf *p, unsigned int w, int wl, int n);
void					print_pointer_address(t_printf *p);
void					color(t_printf *p);
void					pf_putdouble(t_printf *p);
void					buffer(t_printf *p, void *new_elem, size_t size);
void					buffer_flush(t_printf *p);
int						ft_strchri(char *s, int c, int i);
void					padding(t_printf *p, int n);
int						ft_strchri_lu(char *s, int c, int i);
size_t					ft_wcharlen(unsigned wc);
size_t					ft_wstrlen(unsigned *s);
char					*convert_f(long double f, int pres);
long double				del_z(long double f);
int						cnv_z(long double f, char *res);
int						get_len(long double f);
void					field_width_precision(t_printf *p);
void					conversion_specifier_prev(t_printf *p);
char					*del_f(char *a);
void					itoa_base_zero_sharp(char s[1024], uintmax_t n,
int b, t_printf *p);
void					get_printed(char s[1024], uintmax_t n,
int b, t_printf *p);

#endif
