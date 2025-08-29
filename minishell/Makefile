# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpiovano <bpiovano@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/03 10:52:25 by viceda-s          #+#    #+#              #
#    Updated: 2025/08/29 17:20:17 by bpiovano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
READLINE    = -lreadline
READLINE_INCLUDE = -I/opt/homebrew/opt/readline/include
READLINE_LIB = -L/opt/homebrew/opt/readline/lib

# Directories
SRCDIR      = src
OBJDIR      = obj
INCDIR      = inc
LIBFTDIR    = libft

# Libft
LIBFT       = $(LIBFTDIR)/libft.a

# Headers
HEADERS     = $(INCDIR)/minishell.h \
              $(INCDIR)/lexer.h \
              $(INCDIR)/parser.h \
              $(INCDIR)/executor.h \
              $(INCDIR)/builtins.h

# Source files
SRCFILES    = main.c \
              init.c \
              prompt.c \
              signals.c \
              cleanup.c \
              utils.c \
              lexer/lexer.c \
              lexer/tokenizer.c \
              lexer/tokenizer_utils.c \
              lexer/token_utils.c \
              lexer/quote_handler.c \
              parser/parser.c \
              parser/parse_utils.c \
              parser/parse_helpers.c \
              parser/ast_builder.c \
              parser/syntax_checker.c \
              parser/syntax_utils.c \
              parser/ast_utils.c \
              expander/expander.c \
              expander/expander_utils.c \
              expander/env_expansion.c \
              expander/exit_code.c \
              executor/executor.c \
              executor/command_exec.c \
              executor/handle_error.c \
              executor/path_resolver.c \
              executor/arg_expansion.c \
              executor/pipe_handler.c \
              executor/redirect_handler.c \
              executor/redirect_utils.c \
              executor/heredoc.c \
              executor/process_manager.c \
              builtins/builtin_handler.c \
              builtins/echo.c \
              builtins/cd.c \
              builtins/pwd.c \
              builtins/export.c \
              builtins/export_utils.c \
              builtins/unset.c \
              builtins/env.c \
              builtins/exit.c \
              environment/env_manager.c \
              environment/env_utils.c \
              environment/path_resolver.c \
              utils/error_handler.c \
              utils/memory_utils.c \
              utils/string_utils.c \
              utils/debug.c

# Complete path creation
SRC         = $(addprefix $(SRCDIR)/, $(SRCFILES))
OBJ         = $(addprefix $(OBJDIR)/, $(SRCFILES:.c=.o))

# Progress tracking
TOTAL_FILES = $(words $(SRCFILES))

# Colors for output
GREEN       = \033[0;32m
RED         = \033[0;31m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
NC          = \033[0m

# Main rules
all: banner $(NAME)

banner:
	@echo "\033[36m╔══════════════════════════════════════════════════════════════════════════╗\033[0m"
	@echo "\033[36m║                                                                          ║\033[0m"
	@echo "\033[36m║    \033[32m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗\033[36m        ║\033[0m"
	@echo "\033[36m║    \033[32m████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║\033[36m        ║\033[0m"
	@echo "\033[36m║    \033[32m██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║\033[36m        ║\033[0m"
	@echo "\033[36m║    \033[32m██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║\033[36m        ║\033[0m"
	@echo "\033[36m║    \033[32m██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\033[36m   ║\033[0m"
	@echo "\033[36m║    \033[32m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\033[36m   ║\033[0m"
	@echo "\033[36m║                                                                          ║\033[0m"
	@echo "\033[36m║                   \033[35mCreated by viceda-s and bpiovano\033[36m                       ║\033[0m"
	@echo "\033[36m║                                                                          ║\033[0m"
	@echo "\033[36m╚══════════════════════════════════════════════════════════════════════════╝\033[0m"
	@echo ""

$(NAME): $(LIBFT) $(OBJDIR) $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -lft $(READLINE_LIB) $(READLINE) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(NC)"
	@echo ""
	@echo "\033[32m</> Minishell is ready to use! Run ./minishell to start 🎉\033[0m"
	@echo ""

# Object compilation with progress
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	@mkdir -p $(dir $@)
	@current=$$(echo "$(OBJ)" | tr ' ' '\n' | grep -n "$@" | cut -d: -f1); \
	percentage=$$((current * 100 / $(TOTAL_FILES))); \
	printf "$(BLUE)[%3d%%]$(NC) $(YELLOW)Compiling $(notdir $<)...$(NC)\n" "$$percentage"
	@$(CC) $(CFLAGS) $(READLINE_INCLUDE) -I$(INCDIR) -I$(LIBFTDIR)/include -c $< -o $@

# Object directory creation
$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/lexer
	@mkdir -p $(OBJDIR)/parser
	@mkdir -p $(OBJDIR)/expander
	@mkdir -p $(OBJDIR)/executor
	@mkdir -p $(OBJDIR)/builtins
	@mkdir -p $(OBJDIR)/environment
	@mkdir -p $(OBJDIR)/utils

# Libft compilation
$(LIBFT):
	@echo "$(YELLOW)Compiling libft...$(NC)"
	@make -C $(LIBFTDIR)
	@echo "$(GREEN)✓ libft compiled!$(NC)"

# Cleanup
clean:
	@echo "$(RED)Removing object files...$(NC)"
	@rm -rf $(OBJDIR)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re
