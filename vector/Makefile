# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 16:22:00 by bwisniew          #+#    #+#              #
#    Updated: 2024/03/18 19:25:46 by bwisniew         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
C_FLAGS=-g3 -Wall -Wextra -Werror -MMD -MP
LIBC=ar
LIBC_FLAG=crs 
SRC=	vector_add.c vector_free.c vector_init.c vector_realloc.c \
		vector_search.c vector_foreach.c vector_remove.c \
		vector_addstr.c vector_addi.c
OUTDIR=obj
OBJ=$(SRC:%.c=$(OUTDIR)/%.o)
DEP=$(OBJ:.o=.d)
INCLUDE=includes
NAME=libvct.a

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJ)
	$(LIBC) $(LIBC_FLAG) $(NAME) $(OBJ)

$(OUTDIR)/%.o: %.c | $(OUTDIR)
	$(CC) $(C_FLAGS) -I $(INCLUDE) -c -o $@ $<

$(OUTDIR):
	mkdir -p $@

clean:
	rm -rf $(OUTDIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re