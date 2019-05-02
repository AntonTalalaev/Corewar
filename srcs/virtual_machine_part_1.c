/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine_part_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:41:34 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/02 13:12:32 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

t_params		*g_params;

void			introduction_of_contestants(t_vm *vm)
{
	int			i;

	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < vm->num_bots)
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
		i + 1, vm->bot[i].weapon_size, vm->bot[i].name, vm->bot[i].comment);
}

void			vm_init(t_vm *vm)
{
	int			i;

	vm->process = NULL;
	vm->num_process = 0;
	vm->all_processes = 0;
	vm->nbr_cycles = -1;
	vm->live_counter = 0;
	vm->nbr_live_checks = 0;
	vm->nbr_all_cycles = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->flag_a = 0;
	vm->flag_d = -1;
	vm->flag_v = 0;
	vm->flag_info = 0;
	vm->last_alive_bot = -1;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		vm->bot[i].name = NULL;
		vm->bot[i].weapon = NULL;
		vm->bot[i].weapon_size = 0;
	}
	if (!(vm->map = ft_memalloc(MEM_SIZE)))
		error_exit(e_malloc_error, 0, 0);
	vm->count_enter_kill = 0;
}

void			free_vm(t_vm *vm)
{
	int		i;

	i = -1;
	while (++i < vm->num_bots)
	{
		free(vm->bot[i].comment);
		free(vm->bot[i].name);
		free(vm->bot[i].weapon);
	}
	free(vm->map);
}

int				main(int argc, char **argv)
{
	t_vm	vm;

	if (argc < 2)
		error_exit(e_no_arguments_for_corewar, 0, 0);
	vm_init(&vm);
	flags_checker(argc, argv, &vm);
	add_bots(argc, argv, &vm);
	bots_to_map(&vm);
	introduction_of_contestants(&vm);
	if (vm.flag_v)
	{
		print_curses(vm.map, &vm);
		init_visual_statistics(&vm);
		init_chat(&vm);
		random_chat(&vm);
	}
	lets_fight(&vm);
	free_vm(&vm);
	return (0);
}
