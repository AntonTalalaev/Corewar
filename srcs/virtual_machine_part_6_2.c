/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_6_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 11:01:38 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/02 08:33:29 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

int		modulo_mem_size(int value)
{
	if (value >= 0)
		return (value % MEM_SIZE);
	else
		return (MEM_SIZE + (value % MEM_SIZE));
}

void	print_adv(int right, int left, t_vm *vm)
{
	if (right > left)
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", right - left, left, right);
	else
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", MEM_SIZE - left + right,
		left, left + (MEM_SIZE - left + right));
	while (left != right)
	{
		print_hex(vm->map[left]);
		write(1, " ", 1);
		left = modulo_mem_size(left + 1);
	}
	write(1, "\n", 1);
}

void	apply_operation(t_process *process, t_vm *vm)
{
	process->location = modulo_mem_size(process->location);
	if (0x01 <= process->command && process->command <= 0x10)
		process_operation(process->command - 1, process, vm);
	else
		process->location++;
	process->location = modulo_mem_size(process->location);
}

void	ft_memcpy_overflow(const void *dst, const void *src, int n, int start)
{
	int	cntr;
	int i;

	if (!dst || !src)
		return ;
	i = start;
	cntr = 0;
	while (cntr < n)
	{
		((unsigned char *)dst)[cntr] =
		((unsigned char *)src)[modulo_mem_size(i)];
		cntr++;
		i++;
	}
}

void	ft_cpymem_overflow(t_vm *vm, const void *src, int n, int start)
{
	int			cntr;
	int			i;
	const void	*dst;

	dst = vm->map;
	if (!dst || !src)
		return ;
	i = -1;
	cntr = modulo_mem_size(start);
	while (++i < n)
	{
		((unsigned char *)dst)[cntr] = ((unsigned char *)src)[i];
		if (vm->flag_v)
		{
			wmove(vm->visual.win, cntr / 64, cntr % 64 * 3);
			wattron(vm->visual.win, COLOR_PAIR(vm->cur_process->master +
			1 + COLOR_BLACK * 10));
			waddch(vm->visual.win, TAB[vm->map[cntr] / 16]);
			waddch(vm->visual.win, TAB[vm->map[cntr] % 16]);
			wattroff(vm->visual.win, COLOR_PAIR(vm->cur_process->master +
			1 + COLOR_BLACK * 10));
			vm->visual.map_color[cntr] = vm->cur_process->master + 1;
		}
		cntr = modulo_mem_size(cntr + 1);
	}
}
