# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 10:53:13 by emalungo          #+#    #+#              #
#    Updated: 2025/03/16 00:08:50 by emalungo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

FILES = ft_atoi ft_bzero ft_isalnum ft_isalpha ft_tolower \
		ft_isascii ft_isdigit ft_isprint ft_memchr ft_memcpy \
		ft_memcmp ft_memset ft_strchr ft_strlcat ft_toupper \
		ft_strlcpy ft_strlen ft_strncmp ft_calloc ft_strrchr \
		ft_memmove ft_strdup ft_strnstr ft_strjoin ft_putchar_fd \
		ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_strmapi \
		ft_strtrim ft_substr ft_split ft_itoa ft_striteri get_next_line ft_realloc

FILES_B = 	ft_lstadd_back ft_lstadd_front ft_lstclear \
 			ft_lstdelone ft_lstiter ft_lstlast \
 			ft_lstmap ft_lstnew ft_lstsize


SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))


.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus: $(OBJS_B)
	$(AR) $(NAME) $^

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re
