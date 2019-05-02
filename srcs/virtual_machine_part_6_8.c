/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_8.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:21:45 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 16:50:56 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			zjmp_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int		dir_argument;

	dir_argument = read_direct_argument(num_of_op, process, vm);
	if (process->carry)
	{
		process->location_arg = process->location + dir_argument % IDX_MOD;
		if (vm->flag_info)
			ft_printf("P %4d | zjmp %d OK\n",
			process->num_in_list, dir_argument);
	}
	else
	{
		if (vm->flag_info)
		{
			ft_printf("P %4d | zjmp %d FAILED\n",
			process->num_in_list, dir_argument);
			print_adv(process->location_arg, process->location, vm);
		}
	}
}

int				read_second_ldi_argument(int num_of_op, t_process *process,
										t_vm *vm, int args[4])
{
	int				second_value;

	if (args[1] == 1)
		read_registry_argument(process, vm, &second_value);
	else
		second_value = read_direct_argument(num_of_op, process, vm);
	return (second_value);
}

int				find_ldi_bias(int num_of_op, int first_value,
								int second_value)
{
	int		bias;

	if (num_of_op == 9)
		bias = (first_value + second_value) % IDX_MOD;
	else
		bias = first_value + second_value;
	return (bias);
}

int				write_value_ldi(t_vm *vm, t_process *process,
								int bias, int *num_of_reg)
{
	unsigned char	bytes[4];
	int				value_to_be_written;

	ft_memcpy_overflow(bytes, vm->map, 4, process->location + bias);
	value_to_be_written =
	(bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
	*num_of_reg = write_registry_argument(process, vm, value_to_be_written);
	return (value_to_be_written);
}

void			ldi_operation(int num_of_op, t_process *process,
								t_vm *vm, int args[4])
{
	int				first_value;
	int				second_value;
	int				value_to_be_written;
	int				bias;
	int				num_of_reg;

	first_value = find_first_value(vm, process, args, num_of_op);
	second_value = read_second_ldi_argument(num_of_op, process, vm, args);
	bias = find_ldi_bias(num_of_op, first_value, second_value);
	value_to_be_written = write_value_ldi(vm, process, bias, &num_of_reg);
	process->carry = num_of_op == 13 ? (!value_to_be_written) : process->carry;
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s %d %d r%d\n", process->num_in_list,
		num_of_op == 9 ? "ldi" : "lldi", first_value, second_value, num_of_reg);
		if (num_of_op == 9)
			ft_printf("       | -> load from %d + %d = %d (with pc and mod \
%d)\n", first_value, second_value, first_value + second_value,
			modulo_mem_size(process->location + bias));
		else
			ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			first_value, second_value, first_value + second_value,
			modulo_mem_size(process->location + bias));
		print_adv(process->location_arg, process->location, vm);
	}
}
