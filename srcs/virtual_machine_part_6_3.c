/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:06:00 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 11:10:17 by tsimonis         ###   ########.fr       */
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

int		check_registry(int num_of_op, int num_arg,
						int (*args)[4])
{
	(*args)[num_arg] = 1;
	if (g_op_tab[num_of_op].args[num_arg] & T_REG)
		return (0);
	else
		return ((*args)[num_arg]);
}

int		check_dir(int num_of_op, int num_arg,
					int (*args)[4])
{
	(*args)[num_arg] = 2;
	if (g_op_tab[num_of_op].args[num_arg] & T_DIR)
		return (0);
	else
		return ((*args)[num_arg]);
}

int		check_indir(int num_of_op, int num_arg,
					int (*args)[4])
{
	(*args)[num_arg] = 3;
	if (g_op_tab[num_of_op].args[num_arg] & T_IND)
		return (0);
	else
		return ((*args)[num_arg]);
}

int		find_size_of_args(int args[4], int num_of_op, int num_arg)
{
	int		i;
	int		sum;

	sum = 0;
	i = 0;
	while (i < num_arg)
	{
		if (args[i] == 1)
			sum += 1;
		else if (args[i] == 2)
			sum += g_op_tab[num_of_op].size_of_t_dir;
		else if (args[i] == 3)
			sum += IND_SIZE;
		i++;
	}
	return (sum);
}

void	read_correct_arguments(int num_of_op, t_process *process,
								t_vm *vm, int args[4])
{
	if (!num_of_op)
		process->cycles_before_live++;
	if (num_of_op == 0)
		live_operation(num_of_op, process, vm);
	else if (num_of_op == 1 || num_of_op == 12)
		ld_operation(num_of_op, process, vm, args);
	else if (num_of_op == 2)
		st_operation(process, vm, args);
	else if (num_of_op == 3 || num_of_op == 4)
		add_sub_operations(num_of_op, process, vm);
	else if (num_of_op == 5 || num_of_op == 6 || num_of_op == 7)
		and_or_xor_operations(num_of_op, process, vm, args);
	else if (num_of_op == 8)
		zjmp_operation(num_of_op, process, vm);
	else if (num_of_op == 9 || num_of_op == 13)
		ldi_operation(num_of_op, process, vm, args);
	else if (num_of_op == 10)
		sti_operation(num_of_op, process, vm, args);
	else if (num_of_op == 11 || num_of_op == 14)
		fork_operation(num_of_op, process, vm);
	else if (num_of_op == 15)
		aff_operation(process, vm);
}
