/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:01:17 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 14:44:08 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void	write_to_map_sti(unsigned char (*bytes)[4], int value_to_be_written)
{
	(*bytes)[0] = (value_to_be_written >> 24) & 0xFF;
	(*bytes)[1] = (value_to_be_written >> 16) & 0xFF;
	(*bytes)[2] = (value_to_be_written >> 8) & 0xFF;
	(*bytes)[3] = value_to_be_written & 0xFF;
}

void	sti_operation(int num_of_op, t_process *process, t_vm *vm, int args[4])
{
	unsigned char	bytes[4];
	int				value_to_be_written;
	int				second_value;
	int				third_value;
	int				num_of_reg;

	num_of_reg = read_registry_argument(process, vm, &value_to_be_written);
	second_value = find_second_value(vm, process, args, num_of_op);
	if (args[2] == 1)
		read_registry_argument(process, vm, &third_value);
	else
		third_value = read_direct_argument(num_of_op, process, vm);
	write_to_map_sti(&bytes, value_to_be_written);
	ft_cpymem_overflow(vm, bytes, 4, modulo_mem_size(process->location
	+ (second_value + third_value) % IDX_MOD));
	if (vm->flag_info)
	{
		ft_printf("P %4d | sti r%d %d %d\n", process->num_in_list, num_of_reg,
		second_value, third_value);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		second_value, third_value, second_value + third_value,
		process->location + (second_value + third_value) % IDX_MOD);
		print_adv(process->location_arg, process->location, vm);
	}
}

void	fork_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int	reg_nr;
	int	dir_arg;

	vm->process = add_process(process->location, process->master,
	vm->process, vm);
	vm->process->carry = process->carry;
	reg_nr = -1;
	while (++reg_nr < REG_NUMBER)
		vm->process->reg[reg_nr] = process->reg[reg_nr];
	dir_arg = read_direct_argument(num_of_op, process, vm);
	vm->process->location = process->location +
	(dir_arg % IDX_MOD) * (num_of_op == 11) + dir_arg * (num_of_op != 11);
	vm->process->location_prev = process->location;
	vm->process->location_arg = process->location_arg;
	vm->process->cycles_before_live = process->cycles_before_live;
	vm->process->cycles_before_execution = process->cycles_before_execution;
	vm->process->command = process->command;
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s %d (%d)\n", process->num_in_list,
		num_of_op == 11 ? "fork" : "lfork", dir_arg, process->location +
		(num_of_op == 11) * (dir_arg % IDX_MOD) + (num_of_op == 14) * dir_arg);
		print_adv(process->location_arg, process->location, vm);
	}
}

void	aff_operation(t_process *process, t_vm *vm)
{
	read_registry_argument(process, vm, &(vm->aff_value));
	vm->aff_value = (unsigned char)vm->aff_value;
	if (vm->flag_a)
		if (!(vm->flag_v))
			ft_printf("Aff: %c\n", vm->aff_value);
	if (vm->flag_info)
		print_adv(process->location_arg, process->location, vm);
}
