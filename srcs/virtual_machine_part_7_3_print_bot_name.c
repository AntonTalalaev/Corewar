/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_7_3_print_bot_name.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/01 15:08:59 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		visual_statistics_print_bot_name_red(t_vm *vm)
{
	wattron(vm->visual.win2, COLOR_PAIR(COLOR_RED + COLOR_BLACK * 10));
	vm->visual.start_point_statistics =
	visual_statistics_print_ustr(vm->visual.win2, "(1)(RED)",
	vm->visual.start_point_statistics);
}

void		visual_statistics_print_bot_name_green(t_vm *vm)
{
	wattron(vm->visual.win2, COLOR_PAIR(COLOR_GREEN +
	COLOR_BLACK * 10));
	vm->visual.start_point_statistics =
	visual_statistics_print_ustr(vm->visual.win2, "(2)(GREEN)",
	vm->visual.start_point_statistics);
}

void		visual_statistics_print_bot_name_yellow(t_vm *vm)
{
	wattron(vm->visual.win2, COLOR_PAIR(COLOR_YELLOW +
	COLOR_BLACK * 10));
	vm->visual.start_point_statistics =
	visual_statistics_print_ustr(vm->visual.win2, "(3)(YELLOW)",
	vm->visual.start_point_statistics);
}

void		visual_statistics_print_bot_name_blue(t_vm *vm)
{
	wattron(vm->visual.win2, COLOR_PAIR(COLOR_BLUE + COLOR_BLACK * 10));
	vm->visual.start_point_statistics =
	visual_statistics_print_ustr(vm->visual.win2, "(4)(BLUE)",
	vm->visual.start_point_statistics);
}

void		visual_statistics_print_bot_name(t_vm *vm)
{
	int		i;

	vm->visual.start_point_statistics = 5;
	i = -1;
	wmove(vm->visual.win2, vm->visual.start_point_statistics, 2);
	while (++i < vm->num_bots)
	{
		if (!vm->bot[i].weapon)
			break ;
		if (i == 0)
			visual_statistics_print_bot_name_red(vm);
		else if (i == 1)
			visual_statistics_print_bot_name_green(vm);
		else if (i == 2)
			visual_statistics_print_bot_name_yellow(vm);
		else if (i == 3)
			visual_statistics_print_bot_name_blue(vm);
		vm->visual.start_point_statistics =
		visual_statistics_print_ustr(vm->visual.win2, vm->bot[i].name,
		vm->visual.start_point_statistics);
		wattron(vm->visual.win2, COLOR_PAIR(COLOR_MAGENTA + COLOR_BLACK * 10));
	}
	++vm->visual.start_point_statistics;
}
