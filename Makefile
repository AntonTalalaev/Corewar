# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwunsch <mwunsch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 17:36:37 by bsprigga          #+#    #+#              #
#    Updated: 2019/05/01 15:27:59 by mwunsch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re rebuild_lib re1 fclean1

NAME_ASM = asm
NAME_VM = corewar

INCLUDES := ./includes \
			./libft/includes

DIR_ASM := assembler
DIR_VM := virtual_machine

CC = clang
FLAGS := -Wall -Werror -Wextra -g
VPATH := . srcs

SRCS_ASM =	main.c \
			read_champion_part_1.c \
			read_champion_part_1_1.c \
			read_champion_part_2.c \
			read_champion_part_2_1.c \
			read_champion_part_3.c \
			read_champion_part_4.c \
			read_champion_part_5.c \
			read_champion_part_6.c \
			read_champion_part_7.c \
			read_champion_part_8.c \
			read_champion_part_9.c \
			read_champion_part_10.c \
			translate_to_byte_code_part_1.c \
			translate_to_byte_code_part_2.c \
			translate_to_byte_code_part_3.c \
			dump_champion.c \
			disassemble_part_1.c \
			disassemble_part_2.c \
			disassemble_part_3.c \
			disassemble_part_4.c \
			disassemble_part_5.c \
			op.c \
			support_part_1.c \
			support_part_2.c \
			support_part_3.c \
			support_part_4.c

SRCS_VM =	virtual_machine_part_1.c \
			virtual_machine_part_2_flags_1.c \
			virtual_machine_part_2_flags_2.c \
			virtual_machine_part_3.c \
			virtual_machine_part_4.c \
			virtual_machine_part_5_1.c \
			virtual_machine_part_5_2.c \
			virtual_machine_part_5_3.c \
			virtual_machine_part_6_1.c \
			virtual_machine_part_6_2.c \
			virtual_machine_part_6_3.c \
			virtual_machine_part_6_4.c \
			virtual_machine_part_6_5.c \
			virtual_machine_part_6_6.c \
			virtual_machine_part_6_7.c \
			virtual_machine_part_6_8.c \
			virtual_machine_part_7.c \
			virtual_machine_part_7_1_init.c \
			virtual_machine_part_7_2_visual_update.c \
			virtual_machine_part_7_3_print_bot_name.c \
			virtual_machine_part_8_chat.c \
			dump_champion.c \
			disassemble_part_1.c \
			disassemble_part_2.c \
			disassemble_part_3.c \
			disassemble_part_4.c \
			disassemble_part_5.c \
			op.c \
			support_part_1.c \
			support_part_2.c \
			support_part_4.c \
			ft_print_memory.c
OBJECTS_ASM = $(SRCS_ASM:%.c=$(DIR_ASM)/%.o)
OBJECTS_VM = $(SRCS_VM:%.c=$(DIR_VM)/%.o)

all: $(NAME_ASM) $(NAME_VM)

$(NAME_ASM): libft/libft.a $(OBJECTS_ASM)
	$(CC) $(FLAGS) $(OBJECTS_ASM) $(addprefix -I,$(INCLUDES)) -L./libft -lft -o $@

$(NAME_VM): libft/libft.a $(OBJECTS_VM)
	$(CC) $(FLAGS) -lcurses $(OBJECTS_VM) $(addprefix -I,$(INCLUDES)) -L./libft -lft -o $@

libft/libft.a:
	$(MAKE) -C libft

$(DIR_ASM)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDES))

$(DIR_VM)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDES))

clean:
	rm -f $(OBJECTS_ASM) $(OBJECTS_VM)

fclean: clean
	rm -f $(NAME_ASM) $(NAME_VM)

re: fclean all

rebuild_lib:
	$(MAKE) re -C libft

re1: rebuild_lib fclean all

clean1: clean
	$(MAKE) clean -C libft

fclean1: fclean
	$(MAKE) fclean -C libft
