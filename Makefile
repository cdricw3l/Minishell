NAME= minishell

##########################  OS check

OS = $(shell uname)
ifeq ($(OS), Darwin)
CC=cc
GFLAGS= -Werror -Wall -Wextra
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
SRCS_PARSER= $(wildcard srcs/parser/**/*.c) $(wildcard srcs/parser/lexer/**/*.c) $(wildcard srcs/parser/*.c)


SRCS_EXECUTOR= $(wildcard srcs/executor/**/*.c) $(wildcard srcs/executor/*.c)
SRCS_SUB= $(wildcard srcs/subsystems/**/*.c) $(wildcard srcs/subsystems/*.c)
SRCS_TEST= $(wildcard test_unit/*.c)

LIBFT= libft

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
else ifeq ($(mode), $(TEST))
OBJS= $(OBJS_PARSER) 
endif


.PHONY: clean fclean run git testenv

$(NAME): $(OBJS)
ifeq ($(mode), $(PROD))
	$(CC) $(GFLAGS) $(OBJS) -L$(LIBFT) -lft -o $(NAME) -lreadline
else ifeq ($(mode), $(NOFLAGS))
recall:  $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
endif

run: $(NAME)
ifeq ($(OS), Darwin)
	bin/$(NAME)
else ifeq ($(OS), Linux)
	valgrind --leak-check=full --log-file=$(MEMORY_CHECK_PATH)/$(DATE) -s bin/$(NAME)
endif

# cleaning rules

clean:
	rm -f $(OBJS) $(OBJS_TEST)
	rm -f test_unit/test_unit

fclean: clean
	rm -f bin/$(NAME) bin/test.exe

mclean:
	rm -f $(MEMORY_CHECK_PATH)/*


t: $(OBJS) $(OBJS_TEST)
ifeq ($(OS), Darwin)
	$(CC) $(GFLAGS) -fsanitize=address  $(OBJS) $(OBJS_TEST) -L$(LIBFT) -lft  -lreadline -o bin/test.exe
	bin/test.exe
else ifeq ($(OS), Linux)
	$(CC) $(GFLAGS) $(OBJS) $(OBJS_TEST) -L$(LIBFT) -lft -lreadline -o bin/test.exe
	valgrind --leak-check=full --log-file=filename  -s ./bin/test.exe
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
