# === Compiler and flags ===
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I../includes

# === Files ===
NAME    = test
LIB     = ../libstructsalad.a
SRC     = main.c

# === Default rule ===
all: $(LIB) $(NAME)

# Compile the library from the parent directory first
$(LIB):
	$(MAKE) -C ..

# Then build the test executable
$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIB)

# === Cleaning rules ===
clean:
	rm -f $(NAME)

fclean: clean
	$(MAKE) -C .. fclean

re: fclean all
