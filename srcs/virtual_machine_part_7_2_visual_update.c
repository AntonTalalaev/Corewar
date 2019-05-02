/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_7_2_visual_update.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/01 15:05:30 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		update_visual_statistics_tool(t_vm *vm, int line)
{
	int		n;

	mvwprintw(vm->visual.win2, line++, 2, "Cycles to die %d left",
	vm->cycle_to_die);
	line++;
	mvwprintw(vm->visual.win2, line++, 2, "Cycle %d", vm->nbr_all_cycles);
	line++;
	mvwprintw(vm->visual.win2, line++, 2, "Last said that he is not dead yet:");
	n = 0;
	wmove(vm->visual.win2, line, 2);
	if (vm->last_alive_bot == -1)
		mvwprintw(vm->visual.win2, line, 2, "...silence of the Lambs");
	else
		visual_statistics_print_ustr(vm->visual.win2,
		vm->bot[vm->last_alive_bot].name, line);
	refresh();
	wrefresh(vm->visual.win2);
}

void		update_visual_statistics(t_vm *vm)
{
	int		line;

	line = vm->visual.start_point_statistics;
	wmove(vm->visual.win2, line, 2);
	wclrtobot(vm->visual.win2);
	box(vm->visual.win2, 0, 0);
	wattron(vm->visual.win2, COLOR_PAIR(COLOR_MAGENTA + COLOR_BLACK * 10));
	mvwprintw(vm->visual.win2, line++, 2, "Processes in fight %d",
	vm->num_process);
	visual_statistics_print_dump_counter(vm, &line);
	line++;
	if (vm->flag_a)
		mvwprintw(vm->visual.win2, line++, 2, "Aff operation:  %-4c%-4d%#x",
		vm->aff_value, vm->aff_value, vm->aff_value);
	else
		mvwprintw(vm->visual.win2, line++, 2, "Aff operation: unavailable");
	line++;
	update_visual_statistics_tool(vm, line);
}

void		visual_update_by_process(t_process *p, t_vm *vm)
{
	p->location = modulo_mem_size(p->location);
	wmove(vm->visual.win, p->location_prev / 64, p->location_prev % 64 * 3);
	wattron(vm->visual.win,
	COLOR_PAIR(vm->visual.map_color[p->location_prev] + COLOR_BLACK * 10));
	waddch(vm->visual.win, TAB[vm->map[p->location_prev] / 16]);
	waddch(vm->visual.win, TAB[vm->map[p->location_prev] % 16]);
	wattroff(vm->visual.win,
	COLOR_PAIR(vm->visual.map_color[p->location_prev] + COLOR_BLACK * 10));
	wmove(vm->visual.win, p->location / 64, p->location % 64 * 3);
	wattron(vm->visual.win,
	COLOR_PAIR(vm->visual.map_color[p->location] + (p->master + 1) * 10));
	waddch(vm->visual.win, TAB[vm->map[p->location] / 16]);
	waddch(vm->visual.win, TAB[vm->map[p->location] % 16]);
	wattroff(vm->visual.win,
	COLOR_PAIR(vm->visual.map_color[p->location] + (p->master + 1) * 10));
	p->location_prev = p->location;
	refresh();
	wrefresh(vm->visual.win);
}
