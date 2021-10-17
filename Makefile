CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wstrict-prototypes -std=c99 -lm
RM = rm -f
NAME = calc
SRC = *.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	$(RM) $(NAME)

re: clean all
