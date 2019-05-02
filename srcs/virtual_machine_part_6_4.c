/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:10:45 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 14:56:06 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int				read_dir_value(int num_of_op, unsigned char bytes[4])
{
	int			value;

	if (g_op_tab[num_of_op].size_of_t_dir == 4)
		value = (bytes[0] << 24) + (bytes[1] << 16) +
		(bytes[2] << 8) + bytes[3];
	else
		value = (short int)((bytes[0] << 8) + bytes[1]);
	return (value);
}

int				read_direct_argument(int num_of_op, t_process *process,
									t_vm *vm)
{
	int				dir_arg;
	unsigned char	bytes[DIR_SIZE];

	ft_memcpy_overflow(bytes, vm->map, g_op_tab[num_of_op].size_of_t_dir,
	process->location_arg);
	dir_arg = read_dir_value(num_of_op, bytes);
	process->location_arg = modulo_mem_size(process->location_arg +
	g_op_tab[num_of_op].size_of_t_dir);
	return (dir_arg);
}

int				read_indirect_argument(t_process *process, t_vm *vm)
{
	int				indir_arg;
	unsigned char	bytes[DIR_SIZE];
	short int		bias;

	ft_memcpy_overflow(bytes, vm->map, IND_SIZE, process->location_arg);
	bias = (bytes[0] << 8) + bytes[1];
	ft_memcpy_overflow(bytes, vm->map, 4, process->location +
	(bias % IDX_MOD));
	indir_arg = (bytes[0] << 24) + (bytes[1] << 16) +
	(bytes[2] << 8) + bytes[3];
	process->location_arg = modulo_mem_size(process->location_arg + IND_SIZE);
	return (indir_arg);
}

int				read_registry_argument(t_process *process, t_vm *vm,
										int *read_value)
{
	unsigned char	bytes[1];

	ft_memcpy_overflow(bytes, vm->map, 1,
	modulo_mem_size(process->location_arg));
	process->location_arg = modulo_mem_size(process->location_arg + 1);
	*read_value = process->reg[bytes[0] - 1];
	return (bytes[0]);
}

int				write_registry_argument(t_process *process,
										t_vm *vm, int value)
{
	unsigned char	bytes[1];

	ft_memcpy_overflow(bytes, vm->map, 1, process->location_arg);
	process->location_arg = modulo_mem_size(process->location_arg + 1);
	process->reg[bytes[0] - 1] = value;
	return (bytes[0]);
}
