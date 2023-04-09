##
## EPITECH PROJECT, 2023
## B-OOP-400-PAR-4-1-arcade-yann.lebib
## File description:
## Makefile
##

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
	@find ./lib/ -name "*.o" -delete \
		-or -name "*~" -delete
	@find ./arcade_soft/ -name "*.o" -delete \
		-or -name "*~" -delete
	@$(ECHO) $(BLINK) "[CLEAN DONE]" $(DEFLT)

fclean: clean
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

.FORCE:
