/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_8_chat.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/02 13:18:31 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		init_chat(t_vm *vm)
{
	vm->visual.win3 = newwin(11, 75, 45, 64 * 3 + 4);
	wattron(vm->visual.win3, COLOR_PAIR(COLOR_CYAN + COLOR_BLACK * 10));
	box(vm->visual.win3, 0, 0);
	mvwprintw(vm->visual.win3, 1, 1, "Chating...");
	refresh();
	wrefresh(vm->visual.win3);
}

void		random_chat(t_vm *vm)
{
	srand(time(NULL));
	if (rand() % 15 == 0)
		chatting(vm, vm->bot[rand() % (vm->num_bots)].name, rand() % 8 + 1);
}

int			visual_statistics_print_ustr(WINDOW *win, char *str, int line)
{
	int		n;

	wmove(win, line, 2);
	n = 0;
	while (str[n] != '\0')
	{
		if (!((n + 1) % 70) || str[n] == '\n')
			wmove(win, ++line, 2);
		if (str[n] == '\n')
		{
			n++;
			continue ;
		}
		waddch(win, str[n]);
		n++;
	}
	return (line + 1);
}

void		chatting_ext(t_vm *vm, int line, int fl)
{
	if (fl == 4)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"Fighting with him was like trying to solve a\
		crossword and realizing there's no right answer.\"", line);
	else if (fl == 5)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"اك أمل دائماً لمن يحارب.. أما من يست فلا أمل ل\"", line);
	else if (fl == 6)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"I find your lack of faith disturbing.\"", line);
	else if (fl == 7)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"I’ve got a bad feeling about this.\"", line);
	else if (fl == 8)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"Death is the solution to all problems.\"", line);
	else if (fl == 9)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"I have no idea what i'm doing...\"", line);
}

void		chatting(t_vm *vm, char *name, int fl)
{
	int		line;

	wmove(vm->visual.win3, 3, 1);
	wclrtobot(vm->visual.win3);
	line = visual_statistics_print_ustr(vm->visual.win3, name, 3) + 1;
	box(vm->visual.win3, 0, 0);
	refresh();
	wrefresh(vm->visual.win3);
	if (fl == 1)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"Nobody can hurt me without my permition.\"", line);
	else if (fl == 2)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"I'm still alive!\"", line);
	else if (fl == 3)
		visual_statistics_print_ustr(vm->visual.win3,
		"\"Fighting for peace is like screwing for virginity.\"", line);
	else
		chatting_ext(vm, line, fl);
	wclrtobot(vm->visual.win3);
	box(vm->visual.win3, 0, 0);
	refresh();
	wrefresh(vm->visual.win3);
}
