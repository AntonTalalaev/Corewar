/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble_part_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:57:33 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 04:31:29 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			check_main_size_of_op(t_main **main)
{
	if ((*main)->size_of_op)
	{
		if (!((*main)->next = (t_main *)malloc(sizeof(t_main))))
			error_exit(e_malloc_error, 0, 0);
		*main = (*main)->next;
		(*main)->size_of_op = 0;
		(*main)->next = NULL;
	}
}

void			read_num_of_op(t_main **main, unsigned char bytes[4],
								int *read_bytes)
{
	(*main)->num_of_op = bytes[0];
	if ((*main)->num_of_op > NUM_OF_OPS || !(*main)->num_of_op)
		error_exit(e_incorrect_operation_number, 1, *read_bytes);
	(*main)->num_of_op--;
	(*read_bytes)++;
}

int				condition(int *num_arg, t_main **main,
							int args[3])
{
	int				bytes_to_be_read;

	if (++(*num_arg) < g_op_tab[(*main)->num_of_op].num_of_args &&
		(bytes_to_be_read = 1 * (args[*num_arg] == 1)
		+ g_op_tab[(*main)->num_of_op].size_of_t_dir * (args[*num_arg] == 2)
		+ 2 * (args[*num_arg] == 3)))
	{
		(*main)->size_of_op += bytes_to_be_read;
		return (bytes_to_be_read);
	}
	return (0);
}
