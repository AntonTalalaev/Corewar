/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassemble_part_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 01:57:33 by tsimonis          #+#    #+#             */
/*   Updated: 2019/05/01 04:14:43 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "vm.h"

void			check_magic_header(int fd_input)
{
	unsigned char	bytes[4];

	if (read(fd_input, bytes, 4) < 4)
		error_exit(e_cor_file_is_too_short, 1, 0);
	if ((bytes[0] << 24) + (bytes[1] << 16) + (bytes[2] << 8) + bytes[3] !=
		(unsigned int)COREWAR_EXEC_MAGIC)
		error_exit(e_incorrect_magic_header, 1, 0);
}

unsigned int	translate_to_header(t_header **header, int fd_input)
{
	unsigned int	size;

	check_magic_header(fd_input);
	read_champion_name(fd_input, header);
	read_null_before(fd_input);
	size = read_champion_exec_code_size(fd_input);
	read_champion_comment(fd_input, header);
	read_null_after(fd_input);
	return (size);
}

void			translate_to_main(t_main *main, int fd_input)
{
	unsigned char	bytes[4];
	int				read_bytes;
	int				args[3];
	int				num_arg;
	int				bytes_to_be_read;

	main->size_of_op = 0;
	read_bytes = 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4;
	while (read(fd_input, bytes, 1))
	{
		check_main_size_of_op(&main);
		read_num_of_op(&main, bytes, &read_bytes);
		main->size_of_op++;
		read_arg_type_code(fd_input, &read_bytes, &main, &args);
		num_arg = -1;
		while ((bytes_to_be_read = condition(&num_arg, &main, args)))
			if (read(fd_input, bytes, bytes_to_be_read) < bytes_to_be_read)
				error_exit(e_cor_file_is_too_short, 1, read_bytes);
			else if (args[num_arg] == 1)
				write_reg(bytes, &read_bytes, &main, num_arg);
			else if (args[num_arg] == 2)
				write_dir(bytes, &read_bytes, &main, num_arg);
			else if (args[num_arg] == 3)
				write_indir(bytes, &read_bytes, &main, num_arg);
	}
}

void			print_header_and_main(t_header *header, t_main *main)
{
	int		num_arg;

	ft_printf("%s \"%s\"\n", NAME_CMD_STRING, header->prog_name);
	ft_printf("%s \"%s\"\n", COMMENT_CMD_STRING, header->comment);
	if (main->num_of_op + 1)
		write(1, "\n", 1);
	while (main)
	{
		ft_printf("%s", g_op_tab[main->num_of_op].name);
		num_arg = -1;
		while (++num_arg < g_op_tab[main->num_of_op].num_of_args)
		{
			ft_printf(" %s", main->args[num_arg]);
			if (num_arg + 1 < g_op_tab[main->num_of_op].num_of_args)
				write(1, ",", 1);
		}
		write(1, "\n", 1);
		main = main->next;
	}
}

void			disassemble(char *filename)
{
	int				fd_input;
	t_header		*header;
	t_main			*main;
	unsigned int	given_size;
	unsigned int	actual_size;

	if (!endswith(filename, ".cor"))
		error_exit(e_incorrect_cor_file, 0, 0);
	if ((fd_input = open(filename, O_RDONLY)) < 0)
		error_exit(e_open_error, 0, 0);
	if (!(header = (t_header *)malloc(sizeof(t_header))))
		error_exit(e_malloc_error, 0, 0);
	if (!(main = (t_main *)malloc(sizeof(t_main))))
		error_exit(e_malloc_error, 0, 0);
	main->next = NULL;
	given_size = translate_to_header(&header, fd_input);
	translate_to_main(main, fd_input);
	actual_size = find_program_size(main);
	if (actual_size != given_size)
		error_exit(e_mismatched_sizes, 0, 0);
	print_header_and_main(header, main);
	close(fd_input);
	exit(0);
}
