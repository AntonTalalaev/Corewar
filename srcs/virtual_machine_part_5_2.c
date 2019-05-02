/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_5_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 10:51:51 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/02 13:16:37 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void		print_line(t_vm *vm, int *n, int *line, int print_len)
{
	int i;

	i = -1;
	if (print_len == 70)
		while (++i < print_len)
			waddch(vm->visual.win5, vm->bot[vm->last_alive_bot].name[*n + i]);
	else
		mvwprintw(vm->visual.win5, *line, (71 - print_len) / 2,
		vm->bot[vm->last_alive_bot].name + *n);
	*n += print_len;
	(*line)++;
}

void		check_live_process(t_vm *vm)
{
	t_process	*p;

	while ((p = vm->process) && p->cycles_before_live >= vm->cycle_to_die)
	{
		if (vm->flag_info)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			p->num_in_list, p->cycles_before_live, (int)(vm->cycle_to_die));
		kill_process(p, p, vm, 1);
	}
	while (p && p->next)
	{
		if (p->next->cycles_before_live >= vm->cycle_to_die)
		{
			if (vm->flag_info)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				p->next->num_in_list, p->next->cycles_before_live,
				(int)(vm->cycle_to_die));
			kill_process(p, p->next, vm, 0);
		}
		else
			p = p->next;
	}
}

void		print_result(t_vm *vm, int fl, int i, int cycle_to_die)
{
	if (i >= cycle_to_die)
		check_live_process(vm);
	if (fl && vm->num_process)
	{
		if (vm->flag_d == 64 || vm->flag_d == 32)
			ft_print_memory(vm->map, MEM_SIZE, vm->flag_d);
		exit(0);
	}
	else if (vm->last_alive_bot == -1)
	{
		ft_printf("Game over!\nNo one survived...\n");
		exit(0);
	}
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		vm->last_alive_bot + 1, vm->bot[vm->last_alive_bot].name);
}

void		condition_in_visualization(t_vm *vm)
{
	int	n;
	int	line;
	int len_name;

	if (!(vm->last_alive_bot == -1))
	{
		mvwprintw(vm->visual.win5, 3,
		(73 - ft_strlen("Winner is player №1")) / 2, "Winner is player #%i",
		vm->last_alive_bot + 1);
		n = 0;
		line = 4;
		wmove(vm->visual.win5, ++line, 0);
		len_name = ft_strlen(vm->bot[vm->last_alive_bot].name);
		while (vm->bot[vm->last_alive_bot].name[n] != '\0')
			if (len_name / 70 > 0)
			{
				print_line(vm, &n, &line, 70);
				len_name -= 70;
			}
			else
				print_line(vm, &n, &line, len_name % 70);
	}
	else
		mvwprintw(vm->visual.win5, 3, 30, "No winner...\n");
}

void		end_game(t_vm *vm, int fl, int i, int cycle_to_die)
{
	if (vm->flag_v)
	{
		update_visual_statistics(vm);
		vm->visual.win4 = newwin(10, 75, 56, 64 * 3 + 4);
		wbkgd(vm->visual.win4, COLOR_PAIR(COLOR_RED
						+ (vm->last_alive_bot + 1) * 10));
		vm->visual.win5 = newwin(8, 71, 57, 64 * 3 + 6);
		wbkgd(vm->visual.win5, COLOR_PAIR((vm->last_alive_bot + 1)
						+ COLOR_BLACK * 10));
		mvwprintw(vm->visual.win5, 1, (72 - ft_strlen("Game Over")) /
		2, "Game Over");
		condition_in_visualization(vm);
		refresh();
		wrefresh(vm->visual.win4);
		wrefresh(vm->visual.win5);
		wrefresh(vm->visual.win3);
		while (getch() != ' ')
			;
		endwin();
	}
	print_result(vm, fl, i, cycle_to_die);
}
