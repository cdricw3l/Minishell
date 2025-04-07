NAME= minishell

##########################  OS check

OS = $(shell uname)
ifeq ($(OS), Darwin)
CC=cc
GFLAGS= -Werror -Wall -Wextra -I./srcs/parser/tokenizer -I./srcs/exec
else ifeq ($(OS), Linux)
CC=gcc
GFLAGS= -Werror -Wall -Wextra -I./srcs/parser/tokenizer -I./srcs/exec
endif

TEST=1
PARSER=2

MEMORY_CHECK_PATH= error_managment/valgrind

SRCS_MAIN= srcs/main.c
SRCS_PARSER=  $(wildcard srcs/parser/lexer/**/*.c) $(wildcard srcs/parser/tokenizer/*.c) $(wildcard srcs/parser/*.c)
SRCS_EXEC= $(wildcard srcs/exec/*.c) #Nami changed
SRCS_EXEC_BIS= $(wildcard srcs/execution/*.c)
SRCS_BUILTIN= $(wildcard srcs/builtin/*.c)
SRCS_TEST= $(wildcard test_unit/*.c)

LIBFT= libft

ifeq ($(NOFLAGS), 1)
%.o:%.c
	$(CC) -c $< -o $@
else
%.o:%.c
	$(CC) $(GFLAGS)  -g -c $< -o $@
endif

OBJS_MAIN=$(SRCS_MAIN:%.c=%.o)
OBJS_PARSER=$(SRCS_PARSER:%.c=%.o)
OBJS_EXEC=$(SRCS_EXEC:%.c=%.o)
OBJS_EXEC_BIS=$(SRCS_EXEC_BIS:%.c=%.o)
OBJS_BUILTIN=$(SRCS_BUILTIN:%.c=%.o)

# Test env:

OBJS_TEST=$(SRCS_TEST:%.c=%.o)

DATE=$(shell date -Iseconds)
BRANCH=$(shell git branch --show-current)
gcom=
EMPTY=


ifeq ($(mode), $(PROD))
OBJS= $(OBJS_MAIN) $(OBJS_PARSER) $(OBJS_EXEC) $(OBJS_EXEC_BIS) $(OBJS_BUILTIN)# Added OBJS_EXEC
else ifeq ($(mode), $(TEST))
OBJS= $(OBJS_PARSER) $(OBJS_EXEC) # Added OBJS_EXEC
endif


.PHONY: clean fclean run git testenv var lib t

$(NAME): $(OBJS)
	$(CC) $(GFLAGS) $(OBJS) -L$(LIBFT) -lft -o $(NAME) -lreadline
ifeq ($(mode), $(NOFLAGS))
recall:  $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
endif

run: $(NAME)
ifeq ($(OS), Darwin)
	bin/$(NAME)
else ifeq ($(OS), Linux)
	valgrind --leak-check=full --log-file=$(MEMORY_CHECK_PATH)/$(DATE) -s ./$(NAME)
	valgrind --leak-check=full --log-file=$(MEMORY_CHECK_PATH)/$(DATE) -s ./$(NAME)
endif

# cleaning rules

clean:
	rm -f $(OBJS) $(OBJS_TEST)
	rm -f test_unit/test_unit

fclean: clean
	rm -f bin/$(NAME) bin/test
	rm -f valg_test 

mclean:
	rm -f $(MEMORY_CHECK_PATH)/*


t: $(OBJS) 
# check if the PROD variable env value. The PROD variable define the path file for compilation especialy for the main().
ifeq ($(PROD), 0)
	@echo "\033[44m *** Start $(NAME) in test env \033[0m"
else
	@echo "\033[0;32m *** Start $(NAME) in prod env \033[0m"
endif
# Check the NOFLAGS variable. If NOFLAGS=1, No flags are used for the compilation and a warning message is displayed.
ifeq ($(NOFLAGS), 1)
	@echo "\033[41m *** NO FLAGS! \033[0m\n"
endif
# check if the of is darwin/mac
ifeq ($(OS), Darwin)
	@$(CC) $(GFLAGS) -fsanitize=address  $(OBJS) -L $(LIBFT) -lft  -lreadline -o bin/test
	@bin/test
else ifeq ($(OS), Linux)
	@$(CC) $(GFLAGS) -g $(OBJS) -L$(LIBFT) -lft -lreadline -o bin/test
	@valgrind --leak-check=full --log-file=valg_test  -s ./bin/test
endif


git: fclean
ifeq ($(gcom), $(EMPTY))
	git add .
	git commit -m $(NAME)/$(DATE)
else
	git add .
	git commit -m $(NAME)/$(gcom)/$(DATE)
endif
	git push  $(BRANCH)


all: $(NAME)

re: clean fclean all

lib:
	cd libft   && make bonus

