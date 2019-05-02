/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_5.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:59:49 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 14:56:31 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void	shift_location_arg(t_process *process, int args[4],
							int num_of_op, t_vm *vm)
{
	process->location_arg = modulo_mem_size(process->location_arg
	+ find_size_of_args(args, num_of_op, g_op_tab[num_of_op].num_of_args));
	if (vm->flag_info)
		print_adv(process->location_arg, process->location, vm);
}

int		check_all_args(t_vm *vm, t_process *process,
						int num_of_op, int (*args)[4])
{
	unsigned char	bytes[4];
	int				num_arg;
	int				incorrect_args;

	incorrect_args = 0;
	ft_memcpy_overflow(bytes, vm->map, 1, process->location_arg);
	process->location_arg = modulo_mem_size(process->location_arg + 1);
	num_arg = -1;
	while (++num_arg < g_op_tab[num_of_op].num_of_args)
	{
		if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 1)
		{
			if (!(incorrect_args += check_registry(num_of_op, num_arg, args)))
			{
				ft_memcpy_overflow(bytes + 1, vm->map, 1, process->location_arg
				+ find_size_of_args(*args, num_of_op, num_arg));
				if (bytes[1] == 0 || bytes[1] > REG_NUMBER)
					incorrect_args++;
			}
		}
		else
			incorrect_args += else_branch(bytes, num_arg, args, num_of_op);
	}
	return (incorrect_args);
}

void	process_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int				args[4];
	int				incorrect_args;

	process->location_arg = process->location;
	process->location_arg = modulo_mem_size(process->location_arg + 1);
	incorrect_args = 0;
	if (g_op_tab[num_of_op].arg_type_code)
	{
		incorrect_args = check_all_args(vm, process, num_of_op, &args);
		if (incorrect_args)
			shift_location_arg(process, args, num_of_op, vm);
	}
	if (!incorrect_args)
		read_correct_arguments(num_of_op, process, vm, args);
	process->location = process->location_arg;
}

int		else_branch(unsigned char bytes[4], int num_arg,
					int (*args)[4], int num_of_op)
{
	int		incorrect_args;

	incorrect_args = 0;
	if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 2)
		incorrect_args += check_dir(num_of_op, num_arg, args);
	else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 3)
		incorrect_args += check_indir(num_of_op, num_arg, args);
	else if (((bytes[0] >> (6 - num_arg * 2)) & 3) == 0)
	{
		(*args)[num_arg] = 0;
		incorrect_args++;
	}
	return (incorrect_args);
}
