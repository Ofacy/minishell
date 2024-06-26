# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 13:24:31 by bwisniew          #+#    #+#              #
#    Updated: 2024/04/08 18:50:53 by lcottet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

C_FLAGS = -g3 -Wall -Wextra -Werror -MMD -MP

SRCS_DIR = srcs

SRCS =	main.c env.c prompt.c error.c env_utils.c mshell_utils.c signal.c

PARSER_SRCS = lexer.c syntax.c token_utils.c

EXEC_SRCS =	path.c exec.c exec_fd.c here_doc.c fork.c exec_utils.c wait.c \
			close.c exec_builtins.c filetype.c here_doc_utils.c

EXPAND_SRCS = expander_token.c expander_len.c expander_split.c expander.c \
				expander_join.c expander_file.c

BUILTINS_SRCS = env.c pwd.c unset.c cd.c echo.c builtin_utils.c export.c exit.c

SRCS += $(PARSER_SRCS:%.c=parser/%.c) $(EXEC_SRCS:%.c=exec/%.c)  $(BUILTINS_SRCS:%.c=builtins/%.c) $(EXPAND_SRCS:%.c=expander/%.c)

OUTDIR = obj

OBJ = $(SRCS:%.c=$(OUTDIR)/%.o)

DEP = $(OBJ:%.o=%.d)

INCLUDE = includes libft/includes vector/includes

NAME = minishell

LIBFT = libft/libft.a

VECTOR = vector/libvct.a

TESTER = ./run.sh
TESTER_DIR = ./tester

all: $(NAME)

$(NAME): $(LIBFT) $(VECTOR) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(VECTOR) -lreadline

$(OUTDIR)/%.o: $(SRCS_DIR)/%.c $(LIBFT) $(VECTOR)
	@mkdir -p $(@D)
	$(CC) $(C_FLAGS) $(INCLUDE:%=-I %) -o $@ -c $<

$(LIBFT): FORCE
	make -C libft

$(VECTOR): FORCE
	make -C vector

valgrind: $(NAME)
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=./mask_readline_leaks.supp ./minishell

clean:
	rm -rf $(OUTDIR)
	make -C libft clean
	make -C vector clean

fclean: clean
	rm -f $(NAME) $(LIBFT) $(VECTOR) $(TESTER_DIR)/tests/*.sh

re: fclean $(NAME)

norm:
	norminette includes libft vector srcs

$(TESTER_DIR)/tests/0.sh: $(TESTER_DIR)/extract.py $(TESTER_DIR)/Minishell.csv
	rm -rf tester/tests/*.sh
	cd $(TESTER_DIR) && python3 extract.py

test-extract: $(TESTER_DIR)/tests/0.sh

test: $(NAME) test-extract
	cd $(TESTER_DIR) && bash $(TESTER)

FORCE:

-include $(DEP)

.PHONY: all clean fclean re norm FORCE valgrind test test-extract
