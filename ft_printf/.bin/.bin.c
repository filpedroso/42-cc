void	num_flag_help(int *count_p, t_flags flags, int cont_len, int num)
{
	if (!flags.l_just)
	{
		if (flags.precision >= cont_len) && flags.precision <= flags.width)
		{
			*count_p += print_many('0', (flags.precision - cont_len));
			*count_p += print_many(flags.zero_pad, (flags.width - flags.precision));
		}
		else if (flags.precision >= flags.width && flags.width > cont_len)
			*count_p += print_many('0', (flags.width - cont_len));
		else if (flags.precision <= cont_len && flags.width > cont_len)
			*count_p += print_many(flags.zero_pad, (flags.width - cont_len));
	}
	*count_p += ft_printnbr(num);
	else if (flags.l_just)
	{
		if (flags.precision >= cont_len) && flags.precision <= flags.width)
		{
			*count_p += print_many('0', (flags.precision - cont_len));
			*count_p += print_many(' ', (flags.width - flags.precision));
		}
		else if (flags.precision >= flags.width && flags.width > cont_len)
			*count_p += print_many('0', (flags.width - cont_len));
		else if (flags.precision <= cont_len && flags.width > cont_len)
			*count_p += print_many(' ', (flags.width - cont_len));
	}
}