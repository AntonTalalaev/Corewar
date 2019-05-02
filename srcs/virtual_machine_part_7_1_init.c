/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_7_1_init.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/02 14:04:46 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		init_visual_statistics(t_vm *vm)
{
	vm->visual.win2 = newwin(43, 75, 2, 64 * 3 + 4);
	box(vm->visual.win2, 0, 0);
	wattron(vm->visual.win2, WA_UNDERLINE |
	COLOR_PAIR(COLOR_MAGENTA + COLOR_BLACK * 10));
	mvwprintw(vm->visual.win2, 1, 2, "Fight statistics:");
	wattroff(vm->visual.win2, WA_UNDERLINE |
	COLOR_PAIR(COLOR_MAGENTA + COLOR_BLACK * 10));
	wattron(vm->visual.win2, COLOR_PAIR(COLOR_MAGENTA + COLOR_BLACK * 10));
	mvwprintw(vm->visual.win2, 4, 2, "%d fighters:", vm->num_bots);
	visual_statistics_print_bot_name(vm);
	update_visual_statistics(vm);
}

void		initialise_color_tool(void)
{
	init_pair(COLOR_YELLOW + COLOR_RED * 10, COLOR_YELLOW, COLOR_RED);
	init_pair(COLOR_RED + COLOR_GREEN * 10, COLOR_RED, COLOR_GREEN);
	init_pair(COLOR_GREEN + COLOR_BLUE * 10, COLOR_GREEN, COLOR_BLUE);
	init_pair(COLOR_BLUE + COLOR_YELLOW * 10, COLOR_BLUE, COLOR_YELLOW);
	init_pair(COLOR_BLUE + COLOR_RED * 10, COLOR_BLUE, COLOR_RED);
	init_pair(COLOR_YELLOW + COLOR_GREEN * 10, COLOR_YELLOW, COLOR_GREEN);
	init_pair(COLOR_RED + COLOR_BLUE * 10, COLOR_RED, COLOR_BLUE);
	init_pair(COLOR_GREEN + COLOR_YELLOW * 10, COLOR_GREEN, COLOR_YELLOW);
	init_pair(COLOR_GREEN + COLOR_RED * 10, COLOR_GREEN, COLOR_RED);
	init_pair(COLOR_BLUE + COLOR_GREEN * 10, COLOR_BLUE, COLOR_GREEN);
	init_pair(COLOR_YELLOW + COLOR_BLUE * 10, COLOR_YELLOW, COLOR_BLUE);
	init_pair(COLOR_RED + COLOR_YELLOW * 10, COLOR_RED, COLOR_YELLOW);
	init_pair(COLOR_WHITE + COLOR_WHITE * 10, COLOR_WHITE, COLOR_WHITE);
}

void		initialise_color(void)
{
	start_color();
	init_pair(COLOR_WHITE + 1 + COLOR_BLACK * 10, COLOR_WHITE,
	COLOR_BLACK | COLOR_WHITE);
	init_pair(COLOR_WHITE + COLOR_RED * 10, COLOR_WHITE, COLOR_RED);
	init_pair(COLOR_WHITE + COLOR_GREEN * 10, COLOR_WHITE, COLOR_GREEN);
	init_pair(COLOR_WHITE + COLOR_BLUE * 10, COLOR_WHITE, COLOR_BLUE);
	init_pair(COLOR_WHITE + COLOR_YELLOW * 10, COLOR_WHITE, COLOR_YELLOW);
	init_pair(COLOR_WHITE + COLOR_BLACK * 10, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_RED + COLOR_BLACK * 10, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_GREEN + COLOR_BLACK * 10, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_BLUE + COLOR_BLACK * 10, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_YELLOW + COLOR_BLACK * 10, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_MAGENTA + COLOR_BLACK * 10, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_CYAN + COLOR_BLACK * 10, COLOR_CYAN, COLOR_BLACK);
	init_pair(COLOR_RED + COLOR_RED * 10, COLOR_BLACK, COLOR_RED);
	init_pair(COLOR_GREEN + COLOR_GREEN * 10, COLOR_BLACK, COLOR_GREEN);
	init_pair(COLOR_BLUE + COLOR_BLUE * 10, COLOR_BLACK, COLOR_BLUE);
	init_pair(COLOR_YELLOW + COLOR_YELLOW * 10, COLOR_BLACK, COLOR_YELLOW);
	initialise_color_tool();
}

void		init_visualization(t_vm *vm)
{
	int		i;

	initscr();
	initialise_color();
	i = -1;
	while (++i < MEM_SIZE)
		vm->visual.map_color[i] = COLOR_WHITE;
	vm->visual.win_back = newwin(MEM_SIZE / 64 + 2, 64 * 3 + 2 + 77, 1, 1);
	wbkgd(vm->visual.win_back, COLOR_PAIR(COLOR_WHITE + 1 + COLOR_BLACK * 10));
	refresh();
	wrefresh(vm->visual.win_back);
	vm->visual.win = newwin(MEM_SIZE / 64, 64 * 3, 2, 2);
	refresh();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	nodelay(stdscr, TRUE);
	wmove(vm->visual.win, 0, 0);
}

void		init_varibles(int *bot_nr, int *count, int *i)
{
	*bot_nr = 0;
	*count = 0;
	*i = 0;
}
