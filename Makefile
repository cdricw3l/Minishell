NAME=minishell
GCC=gcc
CC=cc
GFLAGS= -Werror -Wall -Wextra
SRCS= $(wildcard srcs/*.c)
OBJS= $(SRCS: *.c=.o)
LINUX=Linux
#get the name of the systeme
OS= $(shell uname)
#get date format iso
DATE=$(shell date -Iseconds) 
# get current branch git
BRANCH=$(shell git branch --show-current) 
#memory log path
MEMORY_CHECK_PATH= error_managment/valgrind

$(NAME): $(OBJS)
	$(CC) $(GFLAGS) $(OBJS) -o $(NAME)

date :
	$(DATE)

run: $(NAME) 
ifeq ($(OS),Darwin)
	./$(NAME) > $(MEMORY_CHECK_PATH)/$(DATE)
else
	.valgrind --filename=$(MEMORY_CHECK_PATH)/$(DATE) --checkleak=full ./$(NAME)
endif

git:
	git add . && git commit -m $(COM)

clean:
	rm -f srcs/*.o

mclean:
	rm -f $(MEMORY_CHECK_PATH)/*

fclean: clean 
	rm -f $(NAME)

all: fclean $(NAME)

git: fclean
	git add . && git commit -m $(COM)/$(DATE) && git push origin $(BRANCH)

.PHONY:

