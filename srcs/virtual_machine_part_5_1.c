/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_5_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:51:04 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/02 10:48:51 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		exec_process(t_vm *vm)
{
	t_process		*p;

	p = vm->process;
	while (p)
	{
		vm->cur_process = p;
		p->cycles_before_live++;
		if (!(p->cycles_before_execution))
			set_command(vm, p);
		if (p->cycles_before_execution > 0)
			p->cycles_before_execution--;
		if (!(p->cycles_before_execution))
			apply_operation(p, vm);
		if (vm->flag_v)
			visual_update_by_process(p, vm);
		p->location = p->location % MEM_SIZE;
		p = p->next;
	}
}

void		space_waiting(t_vm *vm)
{
	int		c;

	c = getch();
	if (c == ' ')
	{
		nodelay(stdscr, FALSE);
		while (1)
			if (getch() == ' ')
			{
				nodelay(stdscr, TRUE);
				break ;
			}
			else if (c == KEY_EXIT)
				exit(0);
	}
	else if (c == 'd')
		vm->nbr_cycles = 0;
	else if (c == KEY_EXIT)
		exit(0);
}

int			first_part_of_cycle(t_vm *vm, int *i)
{
	int		tmp;

	if (vm->flag_v)
		space_waiting(vm);
	if (*i >= vm->cycle_to_die)
	{
		check_live_process(vm);
		if (!(vm->num_process))
			return (1);
		tmp = cycle_to_die_check(vm);
		vm->cycle_to_die -= tmp;
		if (vm->flag_info && vm->cycle_to_die < CYCLE_TO_DIE && tmp)
			ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
		vm->live_counter = 0;
		*i = 0;
	}
	if (vm->flag_info)
		ft_printf("It is now cycle %d\n", vm->nbr_all_cycles + 1);
	exec_process(vm);
	(*i)++;
	vm->nbr_all_cycles++;
	return (0);
}

void		last_part_of_fight(t_vm *vm, int i)
{
	int		tmp;

	check_live_process(vm);
	tmp = cycle_to_die_check(vm);
	vm->cycle_to_die -= tmp;
	if (vm->flag_info && vm->cycle_to_die < CYCLE_TO_DIE && tmp)
		ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
	if (vm->flag_v)
		update_visual_statistics(vm);
	end_game(vm, 0, i, vm->cycle_to_die);
}

void		lets_fight(t_vm *vm)
{
	int		i;

	i = 0;
	while (vm->process && vm->cycle_to_die > 0)
	{
		if (first_part_of_cycle(vm, &i))
			break ;
		if (vm->nbr_cycles != -1
			&& (!(vm->nbr_cycles) || --vm->nbr_cycles == 0))
		{
			if (vm->process && vm->cycle_to_die > 0)
				end_game(vm, 1, i, vm->cycle_to_die);
			else
				end_game(vm, 0, i, vm->cycle_to_die);
		}
		if (vm->flag_v)
			update_visual_statistics(vm);
	}
	last_part_of_fight(vm, i);
}
