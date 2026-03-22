# **************************************************************************** #
#                       Philosophers by viceda-s                              #
# **************************************************************************** #

# =========================
#        CONFIGURATION
# =========================

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

INCLUDES	= -Iinc

OBJS_DIR	= obj
SRC_DIR		= src

# =========================
#       SOURCE FILES
# =========================

SRCS		= \
$(SRC_DIR)/main.c \
$(SRC_DIR)/args_parser.c \
$(SRC_DIR)/mutex_manager.c \
$(SRC_DIR)/philosopher_actions.c \
$(SRC_DIR)/philosopher_thread.c \
$(SRC_DIR)/simulation_init.c \
$(SRC_DIR)/simulation_monitor.c \
$(SRC_DIR)/utils.c

# =========================
#     OBJECT FILES
# =========================

OBJS		= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
TOTAL_SRCS	= $(words $(SRCS))
CURRENT		= 0

# =========================
#         COLORS
# =========================

PURPLE		= \033[38;5;135m
MAGENTA		= \033[0;35m
GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
BOLD		= \033[1m
RESET		= \033[0m

# =========================
#          RULES
# =========================

all: print_header $(NAME)

print_header:
	@echo "$(PURPLE)           █████       ████  ████                             █████$(RESET)"
	@echo "$(PURPLE)           ░░███       ░░░  ░░███                            ░░███$(RESET)"
	@echo "$(PURPLE) ████████  ░███████   █████  ░███   ██████   █████  ████████  ░███████    ██████  ████████   █████ $(RESET)"
	@echo "$(PURPLE) ░░███░░███ ░███░░███ ░░███  ░███  ███░░███ ███░░  ░░███░░███ ░███░░███  ███░░███░░███░░███ ███░░  $(RESET)"
	@echo "$(PURPLE)  ░███ ░███ ░███ ░███  ░███  ░███ ░███ ░███░░█████  ░███ ░███ ░███ ░███ ░███████  ░███ ░░░ ░░█████$(RESET)"
	@echo "$(PURPLE)  ░███ ░███ ░███ ░███  ░███  ░███ ░███ ░███ ░░░░███ ░███ ░███ ░███ ░███ ░███░░░   ░███      ░░░░███$(RESET)"
	@echo "$(PURPLE)  ░███████  ████ █████ █████ █████░░██████  ██████  ░███████  ████ █████░░██████  █████     ██████ $(RESET)"
	@echo "$(PURPLE)  ░███░░░  ░░░░ ░░░░░ ░░░░░ ░░░░░  ░░░░░░  ░░░░░░   ░███░░░  ░░░░ ░░░░░  ░░░░░░  ░░░░░     ░░░░░░$(RESET)"
	@echo "$(PURPLE)  ░███                                              ░███                                 𝙗𝙮 𝙫𝙞𝙘𝙚𝙙𝙖-𝙨 $(RESET)"
	@echo "$(PURPLE) █████                                             █████$(RESET)"
	@echo "$(PURPLE) ░░░░░                                             ░░░░░$(RESET)"
	@echo ""
	@echo "$(BOLD)$(PURPLE)By: viceda-s$(RESET)"
	@echo ""

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -pthread -o $(NAME)
	@echo "$(BOLD)$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"
	@echo ""

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval CURRENT=$(shell find $(OBJS_DIR) -name '*.o' 2>/dev/null | wc -l))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT) * 100 / $(TOTAL_SRCS)))))
	@$(eval FILLED=$(shell echo $$(($(PERCENT) / 2))))
	@$(eval EMPTY=$(shell echo $$((50 - $(FILLED)))))
	@if [ $(CURRENT) -eq 0 ]; then printf "\n$(BOLD)$(BLUE)Compiling $(NAME):$(RESET)\n"; fi
	@printf "[$(MAGENTA)"
	@for i in $$(seq 1 $(FILLED)); do printf "█"; done
	@printf "$(RESET)"
	@for i in $$(seq 1 $(EMPTY)); do printf "░"; done
	@printf "$(RESET)] $(YELLOW)%3d%%$(RESET) %-20s\r" $(PERCENT) "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@if [ $(CURRENT) -eq $$(($(TOTAL_SRCS) - 1)) ]; then \
		printf "[$(MAGENTA)"; \
		for i in $$(seq 1 50); do printf "█"; done; \
		printf "$(RESET)] $(GREEN)100%%$(RESET)                    \n"; \
	fi

clean:
	@printf "\n$(BOLD)$(RED)Cleaning:$(RESET)\n"
	@printf "[$(RED)██████████████████████████████████████████████████$(RESET)] $(YELLOW)Removing objects...$(RESET)\r"
	@$(RM) -r $(OBJS_DIR)
	@printf "[$(GREEN)██████████████████████████████████████████████████$(RESET)] $(GREEN)100%%$(RESET)                         \n"
	@echo "$(BOLD)$(GREEN)✓ Clean completed!$(RESET)"
	@echo ""

fclean: clean
	@printf "$(BOLD)$(RED)Full cleaning:$(RESET)\n"
	@printf "[$(RED)██████████████████████████████████████████████████$(RESET)] $(YELLOW) Removing executables...$(RESET)\r"
	@$(RM) $(NAME)
	@printf "[$(GREEN)██████████████████████████████████████████████████$(RESET)] $(GREEN)100%%$(RESET)                             \n"
	@echo "$(BOLD)$(GREEN)✓ Full clean completed!$(RESET)"
	@echo ""

re: fclean all

.PHONY: all clean fclean re print_header
