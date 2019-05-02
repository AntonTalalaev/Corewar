/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/01 15:23:43 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		visual_statistics_print_dump_counter(t_vm *vm, int *line)
{
	(*line)++;
	if (vm->nbr_cycles == -1)
		mvwprintw(vm->visual.win2, (*line)++, 2, "Dump counter: unavailable");
	else
		mvwprintw(vm->visual.win2, (*line)++, 2,
		"Dump counter: %d", vm->nbr_cycles);
}

void		print_curses_put_hex(t_vm *vm, unsigned char *addr, int i)
{
	waddch(vm->visual.win, TAB[addr[i] / 16]);
	waddch(vm->visual.win, TAB[addr[i] % 16]);
	waddch(vm->visual.win, ' ');
}

void		print_curses_new_line(t_vm *vm, int i)
{
	waddch(vm->visual.win, '\n');
	wmove(vm->visual.win, i / 64, 0);
}

void		print_curses(unsigned char *addr, t_vm *vm)
{
	int		i;
	int		bot_nr;
	int		count;

	count = 0;
	init_varibles(&bot_nr, &count, &i);
	init_visualization(vm);
	while (i < MEM_SIZE)
	{
		if (bot_nr < vm->num_bots && i == MEM_SIZE / vm->num_bots * bot_nr)
		{
			count = vm->bot[bot_nr].weapon_size;
			wattron(vm->visual.win, COLOR_PAIR(bot_nr + 1 + COLOR_BLACK * 10));
		}
		if (count > 0)
			vm->visual.map_color[i] = bot_nr + 1;
		print_curses_put_hex(vm, addr, i);
		if (--count == 0)
			wattroff(vm->visual.win, COLOR_PAIR(++bot_nr + COLOR_BLACK * 10));
		i++;
		if (i % 64 == 0)
			print_curses_new_line(vm, i);
	}
	refresh();
	wrefresh(vm->visual.win);
}
