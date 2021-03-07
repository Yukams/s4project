CC  = gcc
CFLAGS=-std=c99 -Werror -Wextra -Wall -ansi -pedantic

CDIR = src/main/C
TESTDIR = src/test/C
BINDIR = bin

# TRANSACTION
TRANS_MAIN = $(TESTDIR)/create_transaction.c
TRANS_C = $(CDIR)/transaction.c
TRANS_ALL = $(TRANS_MAIN) $(TRANS_C)

# TESTS Transaction
# ------------------------------------------------------------
transaction: $(TRANS_ALL)
	$(CC) $(TRANS_ALL) -o $(BINDIR)/transaction
	mv *.o $(BINDIR)/

clean:
	rm -rf *.o