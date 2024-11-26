/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagWorks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:20:52 by fpedroso          #+#    #+#             */
/*   Updated: 2024/11/24 19:09:27 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_flags(const char **format, t_flags *flags);
static void	conv_work(const char **str, va_list *args_p, int *count_p);

void	flag_work(const char **str, va_list *args_p, int *count_p, int cont_len)
{
	t_flags	flags;
	int		sign;

	sign = 1;
	init_flags(&flags);
	parse_flags(str, &flags);
	while (is_flag(**str))
		(*str)++;
	if (flags.has_flag && !flags.l_just)
	{
		flags_right(flags, cont_len, count_p);
		conv_work(str, args_p, count_p);
		return ;
	}
	else if (flags.has_flag && flags.l_just)
	{
		conv_work(str, args_p, count_p);
		flags_left(flags, cont_len, count_p);
	}
}

int	flags_left(t_flags flags, int cont_len, int *count_p)
{
	va_list	copy_list;
	
	if (flags.conv == 'i' || flags.conv == 'd')
	{
		va_copy(copy_list, *args_p);
		if (va_arg(copy_list, int) < 0)
		{
			*count_p = ft_printchar('-');
			sign = -sign;
		}
	}
	int	prec_len;

	if (flags.precision > cont_len)
		prec_len = flags.precision;
	else
		prec_len = cont_len;
	if (!flags.l_just && flags.width > prec_len)
		*count_p += print_many(' ', flags.width - prec_len);
	if (flags.precision > cont_len)
		*count_p += print_many('0', flags.precision - cont_len);
	if (flags.l_just && flags.width > prec_len)
		*count_p += print_many(' ', flags.width - prec_len);
}

static void	parse_flags(const char **format, t_flags *flags)
{
	while (**format && (ft_isdigit(**format) || is_flag(**format)))
	{
		flags->has_flag = 1;
		if (**format == '-')
		{
			flags->l_just = 1;
			flags->zero_pad = 0;
		}
		else if (**format == '0' && flags->width == 0 && flags->l_just == 0)
			flags->zero_pad = 1;
		else if (**format == '.')
		{
			flags->precision = ft_atoi(*format + 1);
			*format += -1 + num_len(flags->precision);
		}
		else if (ft_isdigit(**format) && flags->precision == -1)
		{
			flags->width = ft_atoi(*format);
			*format += -1 + num_len(flags->width);
		}
		(*format)++;
	}
	if (is_conversion(**format))
		flags->conv = **format;
}

static void	conv_work(const char **str, va_list *args_p, int *count_p)
{
	if (is_conversion(**str))
	{
		if (**str == 'c')
			*count_p += ft_printchar(va_arg(*args_p, int));
		else if (**str == 's')
			*count_p += ft_printstr(va_arg(*args_p, char *));
		else if (**str == 'i' || **str == 'd')
			*count_p += ft_printnbr(va_arg(*args_p, int));
		else if (**str == 'u')
			*count_p += ft_printnbr(va_arg(*args_p, unsigned int));
		else if (**str == 'p')
		{
			ft_printstr("0x");
			*count_p += 2 + print_hex((uintptr_t)va_arg(*args_p, void *), 0,
					'x');
		}
		else if (**str == 'x' || **str == 'X')
			*count_p += print_hex((uintptr_t)va_arg(*args_p, unsigned int), 0,
					**str);
		(*str)++;
	}
}
// TODO
// arriving at flag_works, possible cases:
// there are no flags, proceed to conv_work
// a special case for strings:
//		precision crops, width aligns
// 		zero pad gets ignored and pad is done with spaces normally
// a special case for i and d
//		if it's negative, the sign gets printed first, count_p is incremented
// cases with left justification overrides zero padding 
// 		and change the order of printing, conv_work being called first
// some functions must have redundant logic, if I separate by type there's redundant logic in left justication
// if I separate by left justifcation or not there will be redundant logic for strings and integer cases
// minus sign can be printed before everything, but conv_work should not re-print it if this is the case