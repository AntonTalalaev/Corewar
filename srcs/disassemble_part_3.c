/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble_part_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:57:33 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 03:34:10 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

/*
** 1 => r
** 2 => direct
** 3 => indirect
*/

static void		check_reg(t_main **main, int num_arg,
						int read_bytes, int (*args)[3])
{
	if (!(g_op_tab[(*main)->num_of_op].args[num_arg] & T_REG))
		error_exit(e_incorrect_argument, 1, read_bytes);
	else
		(*args)[num_arg] = 1;
}

static void		check_direct(t_main **main, int num_arg,
						int read_bytes, int (*args)[3])
{
	if (!(g_op_tab[(*main)->num_of_op].args[num_arg] & T_DIR))
		error_exit(e_incorrect_argument, 1, read_bytes);
	else
		(*args)[num_arg] = 2;
}

static void		check_indirect(t_main **main, int num_arg,
						int read_bytes, int (*args)[3])
{
	if (!(g_op_tab[(*main)->num_of_op].args[num_arg] & T_IND))
		error_exit(e_incorrect_argument, 1, read_bytes);
	else
		(*args)[num_arg] = 3;
}

static void		check_nulls(int *num_arg, unsigned char bytes[4],
							int *read_bytes)
{
	while (++(*num_arg) < 4)
		if (((bytes[0] >> (6 - *num_arg * 2)) & 3))
			error_exit(e_incorrect_argument, 1, *read_bytes);
	(*read_bytes)++;
}

void			read_arg_type_code(int fd_input, int *read_bytes,
									t_main **main, int (*args)[3])
{
	unsigned char	bytes[4];
	int				num_arg;

	if (g_op_tab[(*main)->num_of_op].arg_type_code)
	{
		if (!read(fd_input, bytes, 1))
			error_exit(e_cor_file_is_too_short, 1, *read_bytes);
		(*read_bytes)++;
		num_arg = -1;
		while (++num_arg < g_op_tab[(*main)->num_of_op].num_of_args)
			if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 1)
				check_reg(main, num_arg, *read_bytes, args);
			else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 2)
				check_direct(main, num_arg, *read_bytes, args);
			else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 3)
				check_indirect(main, num_arg, *read_bytes, args);
			else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 0)
				error_exit(e_incorrect_argument, 1, *read_bytes);
		check_nulls(&num_arg, bytes, read_bytes);
		(*main)->size_of_op++;
	}
	else
		(*args)[0] = 2;
}
