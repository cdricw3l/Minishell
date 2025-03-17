NAME= minishell

##########################  OS check

OS = $(shell uname)
ifeq ($(OS), Darwin)
CC=cc
GFLAGS= -Werror -Wall -Wextra -I.
else ifeq ($(OS), Linux)
CC=gcc
GFLAGS= -Werror -Wall -Wextra
endif

mode=0
PROD=0
TEST=1
PARSER=2
NOFLAGS=3

MEMORY_CHECK_PATH= error_managment/valgrind

SRCS_MAIN= srcs/main.c
SRCS_PARSER= $(wildcard srcs/parser/**/*.c) $(wildcard srcs/parser/*.c)


SRCS_EXECUTOR= $(wildcard srcs/executor/**/*.c) $(wildcard srcs/executor/*.c)
SRCS_SUB= $(wildcard srcs/subsystems/**/*.c) $(wildcard srcs/subsystems/*.c)
SRCS_TEST= $(wildcard unit_test/*.c)


ifeq ($(mode), $(NOFLAGS))
%.o:%.c
	$(CC) -c $< -o $@
else
%.o:%.c
	$(CC) $(GFLAGS) -c $< -o $@
endif

OBJS_MAIN=$(SRCS_MAIN:%.c=%.o)
OBJS_PARSER=$(SRCS_PARSER:%.c=%.o)
OBJS_EXECUTOR=$(SRCS_EXECUTOR:%.c=%.o)
OBJS_SUB=$(SRCS_SUB:%.c=%.o)

# Test env:

OBJS_TEST=$(SRCS_TEST:%.c=%.o)

DATE=$(shell date -Iseconds)
BRANCH=$(shell git branch --show-current)
gcom=
EMPTY=


ifeq ($(mode), $(PROD))
OBJS= $(OBJS_MAIN) $(OBJS_PARSER)
endif




.PHONY: clean fclean run git testenv

$(NAME): $(OBJS)
ifeq ($(mode), $(PROD))
	$(CC) $(GFLAGS) $(OBJS) -o $(NAME) -lreadline
else ifeq ($(mode), $(NOFLAGS))
recall:  $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
endif

run: $(NAME)
ifeq ($(OS), Darwin)
	./$(NAME)
else ifeq ($(OS), Linux)
	valgrind --leak-check=full --log-file=$(MEMORY_CHECK_PATH)/$(DATE) -s ./$(NAME)
endif



# cleaning rules

clean:
	rm -f $(OBJS) $(OBJS_TEST)

fclean: clean
	rm -f $(NAME) test_unit 

mclean:
	rm -f $(MEMORY_CHECK_PATH)/*
	

t: $(OBJS) $(OBJS_TEST)
ifeq ($(OS), Darwin)
	$(CC) $(GFLAGS) -fsanitize=address  $(OBJS) $(OBJS_TEST) -o test_unit 
	./test_unit
else ifeq ($(OS), Linux)
	$(CC) $(OBJS) $(OBJS_TEST)  -o $(NAME)
	valgrind --leak-check=full --log-file=filename  -s ./test_unit
endif



git: fclean
ifeq ($(gcom), $(EMPTY))
	git add .
	git commit -m $(NAME)/$(DATE)
else
	git add .
	git commit -m $(NAME)/$(gcom)/$(DATE)
endif
	git push origin $(BRANCH)


all: $(NAME)

re: clean fclean all
