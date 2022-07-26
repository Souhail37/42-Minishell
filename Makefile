# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ababouel <ababouel@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/10 23:35:29 by ababouel          #+#    #+#              #
#    Updated: 2022/07/26 01:27:31 by ababouel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAGENTA = \033[35m
RED = \e[1;31m
YELLOW = \e[93;5;226m
CURVE = \e[33;3m
RESET =  \e[0m
GRAY	=	\e[33;2;37m
GREEN = \033[0;32m
CC = cc 
CFLAGS = -Wall -Werror -Wextra
BDIR = build
FILES = main main_tool main_toolbis lexer/lexer lexer/lexerbis lexer/token lexer/lexerlst lexer/lexerlst parse/parstree\
		parse/parselst/parsetool parse/parselst/parsecmd parse/parselst/parsepipe parse/parselst/parseio parse/filter_token\
		tools/ft_split tools/ft_strncmp tools/lsnode tools/free_env tools/ft_strdup tools/ft_strjoin tools/freestack tools/ft_isalpha\
		tools/ft_itoa tools/ft_strchr exec/built exec/cd exec/echo exec/export exec/export2 exec/unset exec/pwd_env exec/ft_which exec/execution exec/exectool\
		exec/export_tools exec/heredoc env_var/tool_env/dup_env env_var/tool_env/rm_val env_var/tool_env/search_val env_var/tool_env/sorting\
		env_var/env_var env_var/env_var_tools\
		errors/tokens_check errors/errors
		
NAME = minishell
OBJ = $(addprefix $(BDIR)/, $(FILES:=.o))
INC = -I ./inc -I /Users/sismaili/.brew/opt/readline/include
HEADERS = inc/minishell.h inc/lib.h inc/token.h  inc/lexer.h inc/exec.h

all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(GRAY)-COMPILING Minishell...\n"
	@$(CC) $(CFLAGS) $^ -o $@ -lreadline -L /Users/sismaili/.brew/opt/readline/lib 
	@printf "$(GREEN)Done !"

$(BDIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
clean:
	@printf "$(RED)Deleting build\n"
	@rm -rf build

fclean: clean
	@printf "$(RED)Deleting minishell\n"
	@rm -rf minishell 

re: fclean all

.PHONY : re all clean fclean
