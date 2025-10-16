# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 11:43:38 by rel-qoqu          #+#    #+#              #
#    Updated: 2025/10/16 14:22:46 by rel-qoqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project
NAME			:= ezprompt
LIB_NAME		:= lib$(NAME).a
LIB_NAME_DBG	:= lib$(NAME)_debug.a
LIB_NAME_ASAN	:= lib$(NAME)_asan.a

# Compiler and tools
CC				:= cc
AR				:= ar
RANLIB			:= ranlib
RMF				:= rm -f
RMR				:= rm -rf
MKDIR			:= mkdir -p

# Dirs
SRC_DIR			:= src
INC_DIR			:= include
BUILD_DIR		:= build
BUILD_DIR_REL	:= $(BUILD_DIR)/release
BUILD_DIR_DBG	:= $(BUILD_DIR)/debug
BUILD_DIR_ASAN	:= $(BUILD_DIR)/asan

# Source files (all C files in src/)
UTILS_FILES		:= $(addprefix utils/, ft_bzero.c ft_calloc.c ft_memcpy.c ft_memset.c \
						ft_putnbr_fd.c ft_putstr.c ft_strdup.c ft_strlen.c ft_strncmp.c)
SRCS_FILES		:= arrow.c ensure_capacity.c free.c init.c next_read.c \
					prompt.c prompt_size.c resize.c skip.c
SRCS			:= $(addprefix $(SRC_DIR)/, $(SRCS_FILES) $(UTILS_FILES))

# Object and dependencies
OBJS_REL		:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR_REL)/%.o,$(SRCS))
OBJS_DBG		:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR_DBG)/%.o,$(SRCS))
OBJS_ASAN		:= $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR_ASAN)/%.o,$(SRCS))
DEPS_REL		:= $(OBJS_REL:.o=.d)
DEPS_DBG		:= $(OBJS_DBG:.o=.d)
DEPS_ASAN		:= $(OBJS_ASAN:.o=.d)

# Common flags
WARN_FLAGS		:= -Wall -Wextra -Werror -Winline -pedantic -std=c99 -Wshadow -Wconversion \
					-Wsign-conversion -Wundef -Wnull-dereference -Wpadded
DEPS_FLAGS		:= -MMD -MP
INC_FLAGS		:= -I$(INC_DIR)
C_FLAGS			:= $(WARN_FLAGS) $(DEPS_FLAGS) $(INC_FLAGS) -D_DEFAULT_SOURCE -D_XOPEN_SOURCE=700

# Release flags
C_FLAGS_RELEASE	:= $(C_FLAGS) -O3 -DNDEBUG

# Debug flags (no sanitizers)
C_FLAGS_DEBUG	:= $(C_FLAGS) -O0 -g3 -DDEBUG -fno-omit-frame-pointer

# AddressSanitizer flags
C_FLAGS_ASAN	:= $(C_FLAGS) -O1 -g3 -DDEBUG -fno-omit-frame-pointer -fsanitize=address

# Colors
RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
PURPLE			= \033[0;35m
CYAN			= \033[0;36m
WHITE			= \033[0;37m
RESET			= \033[0m

# Default target: release static library
all: $(LIB_NAME)

# Archive release library
$(LIB_NAME): $(OBJS_REL)
	@printf "$(CYAN)Archiving $(LIB_NAME)...$(RESET)\n"
	@$(AR) rcs $@ $(OBJS_REL)
	@$(RANLIB) $@
	@printf "$(GREEN)✓ $(LIB_NAME) built successfully!$(RESET)\n"

# Archive debug library (no sanitizers)
debug: $(LIB_NAME_DBG)

$(LIB_NAME_DBG): $(OBJS_DBG)
	@printf "$(CYAN)Archiving $(LIB_NAME_DBG)...$(RESET)\n"
	@$(AR) rcs $@ $(OBJS_DBG)
	@$(RANLIB) $@
	@printf "$(GREEN)✓ $(LIB_NAME_DBG) built successfully!$(RESET)\n"

# Archive ASan instrumented library
asan: $(LIB_NAME_ASAN)

$(LIB_NAME_ASAN): $(OBJS_ASAN)
	@printf "$(CYAN)Archiving $(LIB_NAME_ASAN)...$(RESET)\n"
	@$(AR) rcs $@ $(OBJS_ASAN)
	@$(RANLIB) $@
	@printf "$(GREEN)✓ $(LIB_NAME_ASAN) built successfully!$(RESET)\n"
	@printf "$(YELLOW)Note: link your final executable with -fsanitize=address as well.$(RESET)\n"

# Object rules
$(BUILD_DIR_REL)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR_REL)
	@$(MKDIR) $(dir $@)
	@printf "$(YELLOW)Compiling (release) $<...$(RESET)\n"
	@$(CC) $(C_FLAGS_RELEASE) -c $< -o $@

$(BUILD_DIR_DBG)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR_DBG)
	@$(MKDIR) $(dir $@)
	@printf "$(YELLOW)Compiling (debug) $<...$(RESET)\n"
	@$(CC) $(C_FLAGS_DEBUG) -c $< -o $@

$(BUILD_DIR_ASAN)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR_ASAN)
	@$(MKDIR) $(dir $@)
	@printf "$(YELLOW)Compiling (asan) $<...$(RESET)\n"
	@$(CC) $(C_FLAGS_ASAN) -c $< -o $@

# Ensure build dirs exist
$(BUILD_DIR_REL):
	@$(MKDIR) $@

$(BUILD_DIR_DBG):
	@$(MKDIR) $@

$(BUILD_DIR_ASAN):
	@$(MKDIR) $@

# Cleaning
clean:
	@printf "$(RED)Cleaning build artifacts...$(RESET)\n"
	@$(RMR) $(BUILD_DIR)
	@printf "$(GREEN)✓ Clean completed!$(RESET)\n"

fclean: clean
	@printf "$(RED)Removing libraries...$(RESET)\n"
	@$(RMF) $(LIB_NAME) $(LIB_NAME_DBG) $(LIB_NAME_ASAN)
	@printf "$(GREEN)✓ Full clean completed!$(RESET)\n"

re: fclean all

# Help command
help:
	@printf "$(BLUE)Available targets:$(RESET)\n"
	@printf "  $(GREEN)all$(RESET)     - Build the release static library ($(LIB_NAME))\n"
	@printf "  $(GREEN)debug$(RESET)   - Build the debug static library ($(LIB_NAME_DBG))\n"
	@printf "  $(GREEN)asan$(RESET)    - Build the AddressSanitizer static library ($(LIB_NAME_ASAN))\n"
	@printf "  $(GREEN)clean$(RESET)   - Remove build directories\n"
	@printf "  $(GREEN)fclean$(RESET)  - Remove build directories and libraries\n"
	@printf "  $(GREEN)re$(RESET)      - Rebuild everything (fclean + all)\n"
	@printf "  $(GREEN)norm$(RESET)    - Run norminette (Check 42 norm)\n"
	@printf "  $(GREEN)help$(RESET)    - Show this help\n"

# For norminette (42 compliant style)
norm:
	@norminette $(INC_DIR)/ezprompt.h
	@norminette $(SRCS)

.PHONY: all debug asan clean fclean re help norm

# Include generated dependencies
-include $(DEPS_REL) $(DEPS_DBG) $(DEPS_ASAN)

# QoL
.SUFFIXES:
.SECONDARY: $(OBJS_REL) $(OBJS_DBG) $(OBJS_ASAN)
