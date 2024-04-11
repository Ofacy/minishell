# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 17:41:39 by bwisniew          #+#    #+#              #
#    Updated: 2024/03/21 19:30:08 by lcottet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
C_FLAGS=-Wall -Wextra -Werror -MMD -MP
LIBC=ar
LIBC_FLAG=crs 
SRC=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
		ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
		ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstnew.c \
		ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_printf.c \
		ft_convert.c ft_putnbr_base.c ft_putptr.c ft_putchar.c ft_putstr.c \
		get_next_line.c get_next_line_utils.c ft_freesplit.c ft_strcmp.c \
		ft_isspace.c ft_dprintf.c ft_convert_fd.c ft_putnbr_base_fd.c \
		ft_putptr_fd.c
OUTDIR=obj
OBJ=$(SRC:%.c=$(OUTDIR)/%.o)
DEP=$(OBJ:.o=.d)
INCLUDE=includes
NAME=libft.a

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
