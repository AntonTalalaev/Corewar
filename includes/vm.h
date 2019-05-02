/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:23:14 by mwunsch           #+#    #+#             */
/*   Updated: 2019/05/02 14:02:47 by mwunsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include <ncurses.h>
# include "op.h"

# define TAB			"0123456789abcdef"

/*
**	typedef struct			s_process
**	{
**		int					location; // позиция
**		int					location_prev; // позиция на предыдущем ходу
**		int					location_arg; // нужно при чтении команд
**		int					carry; // флаг carry
**		int					reg[REG_NUMBER]; // регистры
**		int					cycles_before_live;
**		// количество циклов после последнего выполнения операция live
**		int					cycles_before_execution;
**		// количество циклов, оставшихся до исполнения команды
**		int					master; // игрок, породивший каретку
**		int					command; // номер команды (может измениться)
**		int					num_in_list;
**		// номер процесса в листе, как если бы мы ничего не удаляли из него
**		struct s_process	*next; // лист, поэтому next
**	}						t_process;
*/

typedef struct			s_process
{
	int					location;
	int					location_prev;
	int					location_arg;
	int					carry;
	int					reg[REG_NUMBER];
	int					cycles_before_live;
	int					cycles_before_execution;
	int					master;
	int					command;
	int					num_in_list;
	struct s_process	*next;
}						t_process;

/*
**	typedef struct			s_bot
**	{
**		char				*name; // имя
**		char				*comment; // коммент
**		unsigned int		weapon_size; // размер исполняемого кода
**		unsigned char		*weapon; // исполняемый код
**	}						t_bot;
*/

typedef struct			s_bot
{
	char				*name;
	char				*comment;
	unsigned int		weapon_size;
	unsigned char		*weapon;
}						t_bot;

/*
**	typedef struct			s_visual
**	{
**		WINDOW				*win; // arena (map)
**		WINDOW				*win2; // statistics
**		WINDOW				*win3; // chat
**		WINDOW				*win4; // game over window border
**		WINDOW				*win5; // game over window inner
**		int					start_point_statistics;
**		int					map_color[MEM_SIZE + 1]; // to store map colors
**	}						t_visual;
*/

typedef struct			s_visual
{
	WINDOW				*win;
	WINDOW				*win2;
	WINDOW				*win3;
	WINDOW				*win4;
	WINDOW				*win5;
	WINDOW				*win_back;
	int					start_point_statistics;
	int					map_color[MEM_SIZE + 1];
}						t_visual;

/*
**	typedef struct			s_vm
**	{
**		t_bot				bot[MAX_PLAYERS]; // боты
**		int					num_bots; // количество игроков
**		unsigned char		*map; // карта
**		t_process			*process; // каретки
**		t_process			*cur_process; // current кареткa
**		int					nbr_all_cycles;
**		// количество прошедших с начала игры циклов
**		int					live_counter;
**		// количество выполненных операций live
**		// за последний период длиной в cycles_to_die
**		int					cycle_to_die; // длительность периода до проверки
**		int					last_alive_bot;
**		// игрок, указанный в этой переменной, последним подал сигнал live
**		int					nbr_live_checks;
**		// количество проведенных проверок live
**		int					flag_a;
**		// -a flag for aff operationFight statistics:
**		int					aff_value; // for aff operation
**		int					flag_d; // -d flag - 64b
**		int					flag_v; // -v flag for visualiser
**		int					flag_info; // -info flag for debug printing
**		int					nbr_cycles; // for -dump flag
**		int					num_process;
**		// количество процессов (нужна только для визуализации),
**		//хотя также и для corewar
**		int					all_processes;
**		// переменная для присвоения номера каждому процессу
**		t_visual			visual;
**		int					count_enter_kill;
**	}						t_vm;
*/

typedef struct			s_vm
{
	t_bot				bot[MAX_PLAYERS];
	int					num_bots;
	unsigned char		*map;
	t_process			*process;
	t_process			*cur_process;
	int					nbr_all_cycles;
	int					live_counter;
	int					cycle_to_die;
	int					last_alive_bot;
	int					nbr_live_checks;
	int					flag_a;
	int					aff_value;
	int					flag_d;
	int					flag_v;
	int					flag_info;
	int					nbr_cycles;
	int					num_process;
	int					all_processes;
	t_visual			visual;
	int					count_enter_kill;
}						t_vm;

int						get_next_bot_index(t_vm *vm);
void					add_bot(char *file, int i, t_vm *vm);
int						skip_flags(char **argv, int i);
void					num_bots_checker(t_vm *vm);
void					add_bots(int argc, char **argv, t_vm *vm);
t_process				*new_process(int location, int master, t_vm *vm);
t_process				*add_process(int location, int master,
						t_process *prev, t_vm *vm);
void					bots_to_map(t_vm *vm);
void					get_flag_dump(char *flag, t_vm *vm);
void					get_flag_n(char *num, char *file, t_vm *vm);
int						get_flags(int argc, char **argv, int i, t_vm *vm);
void					flags_checker(int argc, char **argv, t_vm *vm);
void					parsing(int argc, char **argv, t_vm *vm);
void					error_exit(int x, int a, int b);
void					ft_print_memory(const void *addr, int size, int fl);
void					bots_checker(t_vm *vm);
void					kill_process(t_process *prev, t_process *cur,
						t_vm *vm, int first);
void					lets_fight(t_vm *vm);
void					ft_memcpy_overflow(const void *dst, const void *src,
						int n, int start);
void					apply_operation(t_process *process, t_vm *vm);
void					process_operation(int num_of_op, t_process *process,
						t_vm *vm);
void					ld_operation(int num_of_op, t_process *process,
						t_vm *vm, int args[4]);
void					add_sub_operations(int num_of_op, t_process *process,
						t_vm *vm);
void					and_or_xor_operations(int num_of_op, t_process *process,
						t_vm *vm, int args[4]);
int						read_indirect_argument(t_process *process, t_vm *vm);
void					ldi_operation(int num_of_op, t_process *process,
						t_vm *vm, int args[4]);
void					fork_operation(int num_of_op, t_process *process,
						t_vm *vm);
void					aff_operation(t_process *process, t_vm *vm);
void					sti_operation(int num_of_op, t_process *process,
						t_vm *vm, int args[4]);
void					zjmp_operation(int num_of_op, t_process *process,
						t_vm *vm);
void					st_operation(t_process *process, t_vm *vm,
						int args[4]);
void					live_operation(int num_of_op, t_process *process,
						t_vm *vm);
int						write_registry_argument(t_process *process, t_vm *vm,
						int value);
int						read_registry_argument(t_process *process, t_vm *vm,
						int *read_value);
void					read_correct_arguments(int num_of_op,
						t_process *process, t_vm *vm, int args[4]);
int						else_branch(unsigned char bytes[4], int num_arg,
						int (*args)[4], int num_of_op);
void					print_curses(unsigned char *addr, t_vm *vm);
void					visual_update_by_process(t_process *p, t_vm *vm);
void					init_chat(t_vm *vm);
void					chatting(t_vm *vm, char *name, int fl);
void					random_chat(t_vm *vm);
int						visual_statistics_print_ustr(WINDOW *win, char *str,
						int line);
void					init_visual_statistics(t_vm *vm);
void					update_visual_statistics(t_vm *vm);
void					print_hex(unsigned char hex);
void					error_exit6(int value, int num_line, int symbol);
void					update_curses_win1(unsigned char *addr, t_vm *vm);
int						modulo_mem_size(int value);
void					num_bots_checker(t_vm *vm);
int						skip_flags(char **argv, int i);
void					print_line(t_vm *vm, int *n, int *line, int print_len);
void					check_live_process(t_vm *vm);
void					print_result(t_vm *vm, int fl, int i, int cycle_to_die);
void					condition_in_visualization(t_vm *vm);
void					end_game(t_vm *vm, int fl, int i, int cycle_to_die);
int						cycle_to_die_check(t_vm *vm);
void					set_command(t_vm *vm, t_process *p);
void					ft_cpymem_overflow(t_vm *vm, const void *src,
						int n, int start);
void					print_adv(int right, int left, t_vm *vm);
int						check_registry(int num_of_op, int num_arg,
						int (*args)[4]);
int						check_dir(int num_of_op, int num_arg,
						int (*args)[4]);
int						check_indir(int num_of_op, int num_arg,
						int (*args)[4]);
int						find_size_of_args(int args[4], int num_of_op,
						int num_arg);
void					read_correct_arguments(int num_of_op,
						t_process *process, t_vm *vm, int args[4]);
int						read_dir_value(int num_of_op, unsigned char bytes[4]);
int						read_direct_argument(int num_of_op, t_process *process,
						t_vm *vm);
int						read_indirect_argument(t_process *process, t_vm *vm);
int						read_registry_argument(t_process *process, t_vm *vm,
						int *read_value);
int						write_registry_argument(t_process *process, t_vm *vm,
						int value);
void					process_operation(int num_of_op,
						t_process *process, t_vm *vm);
void					init_visualization(t_vm *vm);
void					init_varibles(int *bot_nr, int *count, int *i);
void					init_visual_statistics(t_vm *vm);
void					visual_statistics_print_bot_name(t_vm *vm);
void					update_visual_statistics(t_vm *vm);
void					visual_update_by_process(t_process *p, t_vm *vm);
void					visual_statistics_print_dump_counter(t_vm *vm,
						int *line);
void					visual_statistics_print_bot_name(t_vm *vm);
void					ft_print_memory(const void *addr, int size, int base);
void					live_operation(int num_of_op, t_process *process,
						t_vm *vm);
void					ld_operation(int num_of_op, t_process *process,
						t_vm *vm, int args[4]);
void					st_operation(t_process *process, t_vm *vm,
						int args[4]);
void					add_sub_operations(int num_of_op,
						t_process *process, t_vm *vm);
void					and_or_xor_operations(int num_of_op,
						t_process *process, t_vm *vm, int args[4]);
int						find_first_value(t_vm *vm, t_process *process,
						int args[4], int num_of_op);
void					zjmp_operation(int num_of_op, t_process *process,
						t_vm *vm);
void					ldi_operation(int num_of_op, t_process *process,
						t_vm *vm, int args[4]);
int						find_second_value(t_vm *vm, t_process *process,
						int args[4], int num_of_op);

#endif
