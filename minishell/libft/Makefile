# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: viceda-s <viceda-s@student.42luxembourg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 14:02:31 by viceda-s          #+#    #+#              #
#    Updated: 2025/08/26 16:17:14 by viceda-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# =========================
#        CONFIGURATION
# =========================

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
AR			= ar rcs
RM			= rm -f

INCLUDES	= -Iinclude

OBJS_DIR	= obj
SRCS_DIR	= src
CHAR_DIR	= $(SRCS_DIR)/char
STRING_DIR	= $(SRCS_DIR)/string
MEMORY_DIR	= $(SRCS_DIR)/memory
CONVER_DIR	= $(SRCS_DIR)/conversion
FD_DIR		= $(SRCS_DIR)/fd
LIST_DIR	= $(SRCS_DIR)/list
PRINTF_DIR	= $(SRCS_DIR)/ft_printf
GNL_DIR		= $(SRCS_DIR)/gnl

# =========================
#       SOURCE FILES
# =========================

SRCS		= \
$(CHAR_DIR)/ft_isalpha.c \
$(CHAR_DIR)/ft_isdigit.c \
$(CHAR_DIR)/ft_isalnum.c \
$(CHAR_DIR)/ft_isascii.c \
$(CHAR_DIR)/ft_isprint.c \
$(CHAR_DIR)/ft_toupper.c \
$(CHAR_DIR)/ft_tolower.c \
\
$(STRING_DIR)/ft_strlen.c \
$(STRING_DIR)/ft_strlcpy.c \
$(STRING_DIR)/ft_strlcat.c \
$(STRING_DIR)/ft_strchr.c \
$(STRING_DIR)/ft_strrchr.c \
$(STRING_DIR)/ft_strncmp.c \
$(STRING_DIR)/ft_strnstr.c \
$(STRING_DIR)/ft_strdup.c \
$(STRING_DIR)/ft_substr.c \
$(STRING_DIR)/ft_strjoin.c \
$(STRING_DIR)/ft_strtrim.c \
$(STRING_DIR)/ft_split.c \
$(STRING_DIR)/ft_strmapi.c \
$(STRING_DIR)/ft_striteri.c \
\
$(MEMORY_DIR)/ft_memset.c \
$(MEMORY_DIR)/ft_bzero.c \
$(MEMORY_DIR)/ft_memcpy.c \
$(MEMORY_DIR)/ft_memmove.c \
$(MEMORY_DIR)/ft_memchr.c \
$(MEMORY_DIR)/ft_memcmp.c \
$(MEMORY_DIR)/ft_calloc.c \
\
$(FD_DIR)/ft_putchar_fd.c \
$(FD_DIR)/ft_putstr_fd.c \
$(FD_DIR)/ft_putendl_fd.c \
$(FD_DIR)/ft_putnbr_fd.c \
\
$(CONVER_DIR)/ft_atoi.c \
$(CONVER_DIR)/ft_itoa.c \
\
$(LIST_DIR)/ft_lstnew.c \
$(LIST_DIR)/ft_lstadd_front.c \
$(LIST_DIR)/ft_lstsize.c \
$(LIST_DIR)/ft_lstlast.c \
$(LIST_DIR)/ft_lstadd_back.c \
$(LIST_DIR)/ft_lstdelone.c \
$(LIST_DIR)/ft_lstclear.c \
$(LIST_DIR)/ft_lstiter.c \
$(LIST_DIR)/ft_lstmap.c \
\
$(PRINTF_DIR)/ft_printf.c \
$(PRINTF_DIR)/ft_printf_numbers.c \
$(PRINTF_DIR)/ft_printf_utils.c \
\
$(GNL_DIR)/get_next_line_bonus.c

# =========================
#      BONUS FILES
# =========================

BONUS_SRCS	= \
$(GNL_DIR)/get_next_line_bonus.c \
\
$(LIST_DIR)/ft_lstnew.c \
$(LIST_DIR)/ft_lstadd_front.c \
$(LIST_DIR)/ft_lstsize.c \
$(LIST_DIR)/ft_lstlast.c \
$(LIST_DIR)/ft_lstadd_back.c \
$(LIST_DIR)/ft_lstdelone.c \
$(LIST_DIR)/ft_lstclear.c \
$(LIST_DIR)/ft_lstiter.c \
$(LIST_DIR)/ft_lstmap.c

# =========================
#     OBJECT FILES
# =========================

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
BONUS_OBJS	= $(addprefix $(OBJS_DIR)/, $(BONUS_SRCS:.c=.o))

# Progress tracking
TOTAL_FILES = $(words $(SRCS))

# =========================
#         COLORS
# =========================

GREEN		= \033[0;32m
YELLOW		= \033[1;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
RESET		= \033[0m

# =========================
#          RULES
# =========================

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(CHAR_DIR)
	@mkdir -p $(OBJS_DIR)/$(STRING_DIR)
	@mkdir -p $(OBJS_DIR)/$(MEMORY_DIR)
	@mkdir -p $(OBJS_DIR)/$(CONVER_DIR)
	@mkdir -p $(OBJS_DIR)/$(FD_DIR)
	@mkdir -p $(OBJS_DIR)/$(LIST_DIR)
	@mkdir -p $(OBJS_DIR)/$(PRINTF_DIR)
	@mkdir -p $(OBJS_DIR)/$(GNL_DIR)

$(NAME): $(OBJS_DIR) $(OBJS)
	@echo -e "$(GREEN)[OK] Building $(NAME)...$(RESET)"
	@$(AR) $(NAME) $(OBJS)
	@echo -e "$(GREEN)[OK] Library compiled successfully!$(RESET)"

bonus: $(OBJS_DIR) $(OBJS) $(BONUS_OBJS)
	@echo -e "$(GREEN)[OK] Building $(NAME) with bonus...$(RESET)"
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo -e "$(GREEN)[OK] Bonus $(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)/%.o: %.c
	@current=$$(find $(OBJS_DIR) -name "*.o" 2>/dev/null | wc -l | tr -d ' '); \
	current=$$((current + 1)); \
	percentage=$$((current * 100 / $(TOTAL_FILES))); \
	printf "$(BLUE)[%3d%%]$(RESET) $(YELLOW)Compiling $(notdir $<)...$(RESET)\n" "$$percentage"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	@$(RM) -r $(OBJS_DIR)
	@echo -e "$(GREEN)[OK] Object files removed!$(RESET)"

fclean: clean
	@echo -e "$(RED)Cleaning library...$(RESET)"
	@$(RM) $(NAME)
	@echo -e "$(GREEN)[OK] Full clean completed!$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
