/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/01 15:29:57 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				print_hex(unsigned char hex)
{
	char			*tab;

	tab = "0123456789abcdef";
	ft_putchar(tab[hex / 16]);
	ft_putchar(tab[hex % 16]);
}

static void			make_hexs(unsigned char *line, int base)
{
	int				i;

	i = -1;
	while (++i < base)
	{
		print_hex(line[i]);
		ft_putchar(' ');
	}
}

void				ft_print_memory(const void *addr, int size, int base)
{
	unsigned char	*tmp;
	int				curline;

	curline = 0;
	tmp = (unsigned char*)addr;
	if (base != 32)
		base = 64;
	while (curline * base < size)
	{
		ft_printf("0x%04x : ", curline * base);
		make_hexs(tmp, base);
		write(1, "\n", 1);
		tmp += base;
		curline++;
	}
}
