NAME := philo

CC := gcc

CFLAGS := -Wall -Werror -Wextra

HEADER := src/philosophers.h

OBJ :=	obj/philosophers.o\
		obj/philosophers_check.o\
		obj/philosophers_thread.o\
		obj/utils.o\
		obj/input.o\

SRC :=	philosophers.c\
		philosophers_thread.c\
		philosophers_check.c\
		utils.c\
		input.c\

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

obj/%.o: src/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)
	rmdir obj

fclean:
	@make clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re, bonus