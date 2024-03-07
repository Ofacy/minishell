# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 13:24:31 by bwisniew          #+#    #+#              #
#    Updated: 2024/03/07 19:13:14 by bwisniew         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
C_FLAGS = -g3 -Wall -Wextra -Werror -MMD -MP
SRCS_DIR = srcs
SRCS =	main.c env.c lexer.c 
OUTDIR = obj
OBJ = $(SRCS:%.c=$(OUTDIR)/%.o)
DEP = $(OBJ:.o=.d)
INCLUDE = includes libft/includes vector/includes
NAME = minishell
LIBFT = libft/libft.a
VECOTR = vector/libvct.a

all: $(NAME)

-include $(DEP)

$(NAME): $(LIBFT) $(VECOTR) $(OBJ)  
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(VECOTR)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.c $(LIBFT) $(VECOTR) | $(OUTDIR)
	$(CC) $(C_FLAGS) $(INCLUDE:%=-I %) -o $@ -c $<

$(LIBFT): FORCE
	make -C libft

$(VECOTR): FORCE
	make -C vector

$(OUTDIR):
	mkdir -p $(OUTDIR) 

clean:
	rm -rf $(OUTDIR)
	make -C libft clean
	make -C vector clean

fclean: clean
	rm -f $(NAME) $(LIBFT) $(VECOTR)

re: fclean $(NAME)

norm:
	norminette includes libft vector srcs

FORCE:

.PHONY: all clean fclean re norm FORCE
