##
## EPITECH PROJECT, 2023
## B-OOP-400-PAR-4-1-arcade-yann.lebib
## File description:
## Makefile
##

SHELL := /bin/bash

CORE_SRC = ./arcade_soft
GAME_SRC = $(shell find ./lib/games/ -maxdepth 1 -mindepth 1 -type d 2>/dev/null)
GRAPHIC_SRC = $(shell find ./lib/graphic_engine/ -maxdepth 1 -mindepth 1 -type d 2>/dev/null)

ECHO = echo -e
CAT = /usr/bin/cat
CLS_LINE = echo -ne "\r\033[0K"

DEFLT	=	"\033[00m"
PINK	=	"\033[0;36m"
GREEN	=	"\033[1;32m"
TEAL	=	"\033[1;36m"
RED 	=	"\033[0;31m"
BLUE	=	"\033[34m"
PURPLE	=	"\033[0;35m"
BLINK 	= 	"\033[1;92m"
SBLINK	= 	"\033[0m"
INVERT  =	"\033[7m"

all:
	@make core --no-print-directory; \
	make games --no-print-directory; \
	make graphicals --no-print-directory;

re: fclean all

core:
	@make -C $(CORE_SRC) --no-print-directory

games: .FORCE
	@for dir in $(GAME_SRC); do \
		$(ECHO) $(BLINK)$(PURPLE)"[COMPILING GAME $$dir]"$(DEFLT); \
		make so -C $$dir --no-print-directory; \
		cp $$dir/*.so ./lib; \
	done

graphicals: .FORCE
	@for dir in $(GRAPHIC_SRC); do \
		$(ECHO) $(BLINK)$(PURPLE)"[COMPILING GRAPHIC ENGINE $$dir]"$(DEFLT); \
		make so -C $$dir --no-print-directory; \
		cp $$dir/*.so ./lib; \
	done

clean:
	@find ./lib/ -name "*.o" -delete -or -name "*.d" -delete \
		-or -name "*~" -delete
	@find ./arcade_soft/ -name "*.o" -delete -or -name "*.d" -delete \
		-or -name "*~" -delete
	@$(ECHO) $(BLINK) "[CLEAN DONE]" $(DEFLT)

fclean: clean
	@rm -f unit_tests graphics_tests .graphics_tests.log
	@find ./lib/ -name "*.so" -delete
	@make fclean -C $(CORE_SRC) --no-print-directory
	@find $(GRAPHIC_SRC) -name "*.so" -delete
	@for dir in $(GRAPHIC_SRC); do \
		$(ECHO) $(BLINK)$(PURPLE)"[COMPILING GRAPHIC ENGINE $$dir]"$(DEFLT); \
		make fclean -C $$dir --no-print-directory; \
	done
	@find $(GAME_SRC) -name "*.so" -delete
	@for dir in $(GAME_SRC); do \
		$(ECHO) $(BLINK)$(PURPLE)"[COMPILING GAME $$dir]"$(DEFLT); \
		make fclean -C $$dir --no-print-directory; \
	done

TEST_FLAGS = -std=c++17 -Wall -Wextra -Werror -g \
	-Iglobal -Iarcade_soft/include -Ilib/common

# Build what can be built (a back end with a missing dependency is skipped
# by its tests), then run the unit tests and the graphics tests. The
# graphics tests need a terminal, given by script, and run without a screen.
tests_run:
	-@make all --no-print-directory
	@g++ $(TEST_FLAGS) tests/unit/*.cpp arcade_soft/src/Core.cpp \
		arcade_soft/src/DLLoader.cpp -ldl -o unit_tests
	@g++ $(TEST_FLAGS) tests/graphics/*.cpp arcade_soft/src/DLLoader.cpp \
		-ldl -o graphics_tests
	@$(ECHO) $(TEAL)"[UNIT TESTS]"$(DEFLT)
	@./unit_tests
	@$(ECHO) $(TEAL)"[GRAPHICS TESTS]"$(DEFLT)
	@rm -f .graphics_tests.log; \
	env -u DISPLAY -u WAYLAND_DISPLAY SDL_VIDEODRIVER=dummy CACA_DRIVER=ncurses \
		script -qec "./graphics_tests .graphics_tests.log" /dev/null \
		> /dev/null 2>&1 < /dev/null; \
	status=$$?; \
	cat .graphics_tests.log 2>/dev/null; \
	if [ $$status -ne 0 ]; then \
		$(ECHO) "\n"$(RED)"graphics tests exited with status $$status (139: segmentation fault)"$(DEFLT); \
	fi; \
	exit $$status

.PHONY: all re core games graphicals clean fclean tests_run

.FORCE:
