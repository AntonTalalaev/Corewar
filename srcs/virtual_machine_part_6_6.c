/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_6.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 12:34:38 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/02 10:52:34 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			live_operation(int num_of_op, t_process *process, t_vm *vm)
{
	int				num;
	unsigned char	bytes[4];

	vm->live_counter++;
	process->cycles_before_live = 0;
	ft_memcpy_overflow(bytes, vm->map,
	g_op_tab[num_of_op].size_of_t_dir, process->location_arg);
	if (g_op_tab[num_of_op].size_of_t_dir == 4)
		num = (bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3];
	else
		num = (short int)((bytes[0] << 8) + bytes[1]);
	if (vm->flag_info)
		ft_printf("P %4d | live %d\n", process->num_in_list, num);
	if (num < 0 && -num <= vm->num_bots)
	{
		vm->last_alive_bot = -num - 1;
		if (vm->flag_info)
			ft_printf("Player %d (%s) is said to be alive\n",
			-num, vm->bot[-num - 1].name);
	}
	process->location_arg = modulo_mem_size(process->location_arg +
	g_op_tab[num_of_op].size_of_t_dir);
	if (vm->flag_info)
		print_adv(process->location_arg, process->location, vm);
}

int				read_indirect_for_ld(int num_of_op, t_process *process,
									t_vm *vm)
{
	int				dir_or_indir;
	unsigned char	bytes[4];

	ft_memcpy_overflow(bytes, vm->map, IND_SIZE, process->location_arg);
	if (num_of_op == 1)
		dir_or_indir = ((short int)((bytes[0] << 8) + bytes[1]) % IDX_MOD);
	else
		dir_or_indir = (short int)((bytes[0] << 8) + bytes[1]);
	ft_memcpy_overflow(bytes, vm->map, g_op_tab[num_of_op].size_of_t_dir,
	process->location + dir_or_indir);
	process->location_arg = modulo_mem_size(process->location_arg + IND_SIZE);
	return (read_dir_value(num_of_op, bytes));
}

void			ld_operation(int num_of_op, t_process *process,
							t_vm *vm, int args[4])
{
	int				dir_or_indir;
	int				num_of_reg;

	dir_or_indir = 0;
	if (args[0] == 2)
		dir_or_indir = read_direct_argument(num_of_op, process, vm);
	else if (args[0] == 3)
		dir_or_indir = read_indirect_for_ld(num_of_op, process, vm);
	num_of_reg = write_registry_argument(process, vm, dir_or_indir);
	process->carry = (!dir_or_indir);
	if (vm->flag_info)
	{
		ft_printf("P %4d | %s %d r%d\n", process->num_in_list,
		num_of_op == 1 ? "ld" : "lld", dir_or_indir, num_of_reg);
		print_adv(process->location_arg, process->location, vm);
	}
}

short int		read_indirect_for_st(t_vm *vm, t_process *process,
									int value_from_reg)
{
	unsigned char	bytes[4];
	short int		address;

	ft_memcpy_overflow(bytes, vm->map, IND_SIZE, process->location_arg);
	address = ((short int)((bytes[0] << 8) + bytes[1]));
	bytes[0] = (value_from_reg >> 24) & 0xFF;
	bytes[1] = (value_from_reg >> 16) & 0xFF;
	bytes[2] = (value_from_reg >> 8) & 0xFF;
	bytes[3] = value_from_reg & 0xFF;
	ft_cpymem_overflow(vm, bytes, 4, process->location + address % IDX_MOD);
	process->location_arg = modulo_mem_size(process->location_arg + IND_SIZE);
	return (address);
}

void			st_operation(t_process *process, t_vm *vm, int args[4])
{
	int				value_from_reg;
	int				first_num_of_reg;
	int				second_num_of_reg;
	short int		address;

	first_num_of_reg = read_registry_argument(process, vm, &value_from_reg);
	if (args[1] == 1)
		second_num_of_reg = write_registry_argument(process,
		vm, value_from_reg);
	else
		address = read_indirect_for_st(vm, process, value_from_reg);
	if (vm->flag_info)
	{
		if (args[1] == 1)
			ft_printf("P %4d | st r%d %d\n", process->num_in_list,
			first_num_of_reg, second_num_of_reg);
		else
			ft_printf("P %4d | st r%d %d\n", process->num_in_list,
			first_num_of_reg, address);
		print_adv(process->location_arg, process->location, vm);
	}
}
