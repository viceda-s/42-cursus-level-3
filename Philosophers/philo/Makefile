# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/27 12:00:00 by viceda-s          #+#    #+#              #
#    Updated: 2025/07/27 16:46:19 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -pthread

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc

SOURCES		= main.c args_parser.c simulation_init.c mutex_manager.c \
			  philosopher_thread.c philosopher_actions.c simulation_monitor.c \
			  time_utils.c simulation_utils.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# Colors
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
NC			= \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@echo "$(YELLOW)Creating object directory...$(NC)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Object files cleaned.$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)$(NAME) removed.$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
