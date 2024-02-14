# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 13:24:31 by bwisniew          #+#    #+#              #
#    Updated: 2024/02/14 13:28:57 by bwisniew         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
C_FLAGS = -Wall -Wextra -Werror -MMD -MP
SRCS_DIR = srcs
SRCS =	main.c env.c promt.c
OUTDIR = obj
OBJ = $(SRCS:%.c=$(OUTDIR)/%.o)
DEP = $(OBJ:.o=.d)
INCLUDE = includes libft/includes
NAME = minishell
LIBFT = libft/libft.a

all: $(NAME)

-include $(DEP)

$(NAME): $(LIBFT) $(OBJ)  
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(OUTDIR)/%.o: $(SRCS_DIR)/%.c $(LIBFT) | $(OUTDIR)
	$(CC) $(C_FLAGS) $(INCLUDE:%=-I %) -o $@ -c $<

$(LIBFT): FORCE
	make -C libft

$(OUTDIR):
	mkdir -p $(OUTDIR) 

clean:
	rm -rf $(OUTDIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean $(NAME)

norm:
	norminette includes libft srcs

FORCE:

.PHONY: all clean fclean re libft norm FORCE