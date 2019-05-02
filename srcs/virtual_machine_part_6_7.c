/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_7.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:28:45 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 14:49:30 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			add_sub_operations(int num_of_op, t_process *process,
									t_vm *vm)
{
	int				first_value;
	int				second_value;
	int				value_to_be_written;
	int				num_of_regs[3];

	num_of_regs[0] = read_registry_argument(process, vm, &first_value);
	num_of_regs[1] = read_registry_argument(process, vm, &second_value);
	if (num_of_op == 3)
		value_to_be_written = first_value + second_value;
	else
		value_to_be_written = first_value - second_value;
	num_of_regs[2] = write_registry_argument(process, vm, value_to_be_written);
	process->carry = (!value_to_be_written);
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s r%d r%d r%d\n", process->num_in_list,
		num_of_op == 3 ? "add" : "sub", num_of_regs[0],
		num_of_regs[1], num_of_regs[2]);
		print_adv(process->location_arg, process->location, vm);
	}
}

void			find_resulting_value_and_or_xor(int num_of_op,
				int *value_to_be_written, int first_value, int second_value)
{
	if (num_of_op == 5)
		*value_to_be_written = first_value & second_value;
	else if (num_of_op == 6)
		*value_to_be_written = first_value | second_value;
	else
		*value_to_be_written = first_value ^ second_value;
}

int				find_first_value(t_vm *vm, t_process *process,
								int args[4], int num_of_op)
{
	int			first_value;

	if (args[0] == 1)
		read_registry_argument(process, vm, &first_value);
	else if (args[0] == 2)
		first_value = read_direct_argument(num_of_op, process, vm);
	else
		first_value = read_indirect_argument(process, vm);
	return (first_value);
}

int				find_second_value(t_vm *vm, t_process *process,
								int args[4], int num_of_op)
{
	int			second_value;

	if (args[1] == 1)
		read_registry_argument(process, vm, &second_value);
	else if (args[1] == 2)
		second_value = read_direct_argument(num_of_op, process, vm);
	else
		second_value = read_indirect_argument(process, vm);
	return (second_value);
}

void			and_or_xor_operations(int num_of_op, t_process *process,
										t_vm *vm, int args[4])
{
	int			first_value;
	int			second_value;
	int			value_to_be_written;
	int			num_of_reg;

	first_value = find_first_value(vm, process, args, num_of_op);
	second_value = find_second_value(vm, process, args, num_of_op);
	find_resulting_value_and_or_xor(num_of_op, &value_to_be_written,
	first_value, second_value);
	num_of_reg = write_registry_argument(process, vm, value_to_be_written);
	process->carry = (!value_to_be_written);
	if (vm->flag_info)
	{
		if (num_of_op == 5)
			ft_printf("P %4d | and %d %d r%d\n", process->num_in_list,
			first_value, second_value, num_of_reg);
		else if (num_of_op == 6)
			ft_printf("P %4d | or %d %d r%d\n", process->num_in_list,
			first_value, second_value, num_of_reg);
		else
			ft_printf("P %4d | xor %d %d r%d\n", process->num_in_list,
			first_value, second_value, num_of_reg);
		print_adv(process->location_arg, process->location, vm);
	}
}
