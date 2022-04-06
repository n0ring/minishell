SRC		=	main.c signals.c env_var.c builtins/builtins.c builtins/my_cd.c builtins/my_export.c builtins/my_unset.c\
			utils/free.c parsing/parse_args.c parsing/expansion/expansion.c parsing/expansion/quotes.c parsing/expansion/preprocessor.c\
			utils/ft_atoi_ll.c utils/miscellaneous.c utils/print.c builtins/my_exit.c initialization.c\
			parsing/input_parsing/parser_error_utils.c\
			parsing/input_parsing/get_app_path.c parsing/input_parsing/validation.c parsing/input_parsing/parser.c parsing/input_parsing/parser_utils.c\
			exec/execution.c exec/fork_utils.c exec/exec_utils.c exec/gnl/get_next_line.c exec/gnl/get_next_line_utils.c
SRC_LIB	=	libft/ft_lstadd_back.c libft/ft_lstadd_front.c libft/ft_lstclear.c libft/ft_lstdelone.c libft/ft_lstiter.c libft/ft_lstlast.c libft/ft_lstmap.c libft/ft_lstnew.c libft/ft_lstsize.c\
			libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_isspace.c libft/ft_itoa.c libft/ft_memccpy.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c libft/ft_strrev.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_strlen.c
OBJ		=	$(SRC:.c=.o)
NAME	=	minishell
LIBDIR	=	./libft
RLDIR	=	/Users/$(USER)/.brew/opt/readline/include/readline
LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -I$(RLDIR)
LFLAGS	=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline -lhistory -L $(LIBDIR) -lft
HEADER	=	minishell.h

.PHONY	:	all re clean fclean

all		:	$(NAME)

$(LIB)	:	$(SRC_LIB)
			make -s -C $(LIBDIR)

$(NAME)	:	$(OBJ)  Makefile
			$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)

%.o		:	%.c $(HEADER) $(LIB)
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			rm -f $(OBJ)
			make clean -C $(LIBDIR)

fclean	:	clean
			make fclean -C $(LIBDIR)
			rm -f $(NAME)

re		:	fclean all