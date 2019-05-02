/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_5_3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:57:15 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 10:57:37 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int			cycle_to_die_check(t_vm *vm)
{
	if (vm->live_counter >= NBR_LIVE || vm->nbr_live_checks >= (MAX_CHECKS - 1))
	{
		vm->nbr_live_checks = 0;
		return (CYCLE_DELTA);
	}
	vm->nbr_live_checks++;
	return (0);
}

void		set_command(t_vm *vm, t_process *p)
{
	unsigned char	bytes[1];

	if (vm->flag_v)
		random_chat(vm);
	ft_memcpy_overflow(bytes, vm->map, 1, p->location);
	p->command = bytes[0];
	if (bytes[0] >= 0x01 && bytes[0] <= 0x10)
		p->cycles_before_execution =
		g_op_tab[bytes[0] - 1].cycles_before_execution;
}
