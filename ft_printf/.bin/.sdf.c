




if there is a - it is left justified, can be zero padded if precision is bigger than content
whatever pads precision makes, it counts back to the final width in 

static void	flag_work(const char **str, va_list *args_p, int *count_p)
{
	t_flags	flags;
	int		cont_len;

	init_flags(&flags);
	parse_flags(str, &flags);
	while (is_flag(**str))
		(*str)++;
	cont_len = content_len(str, args_p);
	if (**str == 's' && flags.precision >= 0 && cont_len > flags.precision)
		cont_len = flags.precision;
	if (!flags.left_justify && !flags.zero_padding && flags.width > cont_len)
		*count_p += print_many(' ', flags.width - cont_len);
	if (!flags.left_justify && ((flags.precision == -1 && flags.zero_padding && flags.width > cont_len) || flags.precision > flags.width))
		*count_p += print_many('0', flags.width - cont_len);
	else if ((flags.precision > cont_len) && (flags.precision < flags.width))
		*count_p += print_many('0', flags.precision - cont_len);
	conv_work(str, args_p, count_p);
	if (flags.left_justify && (flags.precision > cont_len))
		*count_p += print_many(' ', flags.precision - cont_len);
}








static void	flag_work(const char **str, va_list *args_p, int *count_p)
{
	t_flags	flags;
	int		cont_len;
	int		padding_len;

	init_flags(&flags);
	parse_flags(str, &flags);
	while (is_flag(**str))
		(*str)++;
	cont_len = content_len(str, args_p);
	if (**str == 's' && flags.precision >= 0 && cont_len > flags.precision)
		cont_len = flags.precision;
	padding_len = (flags.width - cont_len);
	if (padding_len < 0)
		padding_len = 0;
	if (!flags.left_justify && !flags.zero_padding)
		*count_p += print_many(' ', padding_len);
	if (!flags.left_justify && (flags.precision > -1 || flags.zero_padding))
		*count_p += print_many('0', padding_len);
	else if (flags.precision > cont_len && (flags.precision + cont_len) > flags.width)
		*count_p += print_many('0', flags.precision - cont_len);
	conv_work(str, args_p, count_p);
	if (flags.left_justify)
	{
		if (flags.precision > cont_len)
			*count_p += print_many(' ', padding_len - (flags.precision - cont_len));
		else
			*count_p += print_many(' ', padding_len);
	}
}