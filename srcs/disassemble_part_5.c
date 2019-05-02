/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble_part_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:57:33 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/30 18:07:33 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			write_reg(unsigned char bytes[4], int *read_bytes,
						t_main **main, int num_arg)
{
	char *tmp;

	if (!(tmp = ft_itoa_long(bytes[0])))
		error_exit(e_malloc_error, 0, 0);
	if (bytes[0] > REG_NUMBER || !bytes[0])
		error_exit(e_incorrect_argument, 1, *read_bytes);
	(*main)->args[num_arg] = ft_strjoin("r", tmp);
	(*read_bytes)++;
	free(tmp);
}

void			write_dir(unsigned char bytes[4], int *read_bytes,
						t_main **main, int num_arg)
{
	int		num;
	char	*tmp;

	if (g_op_tab[(*main)->num_of_op].size_of_t_dir == 4)
		num = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
	else
		num = (bytes[0] << 8) + bytes[1];
	if (!(tmp = ft_itoa_long(num)))
		error_exit(e_malloc_error, 0, 0);
	(*main)->args[num_arg] = ft_strjoin("%", tmp);
	*read_bytes += g_op_tab[(*main)->num_of_op].size_of_t_dir;
	free(tmp);
}

void			write_indir(unsigned char bytes[4], int *read_bytes,
						t_main **main, int num_arg)
{
	int	num;

	num = (bytes[0] << 8) + bytes[1];
	(*main)->args[num_arg] = ft_itoa_long(num);
	*read_bytes += 2;
}
