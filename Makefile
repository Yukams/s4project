CC  = gcc
# -std=gnu99
SYS = -Wall -pedantic -DUNIX
INC = -I.

MAINDIR = src/main/C
TESTDIR = src/test/C
BINDIR = bin

# TRANSACTION
TRANS_MAIN = $(TESTDIR)/create_transaction.o
TRANS_C = $(MAINDIR)/transaction.o
TRANS_ALL = $(TRANS_MAIN) $(TRANS_C)

# BLOCK
BLOCK_MAIN = $(TESTDIR)/create_block.o
BLOCK_C = $(MAINDIR)/block.o
BLOCK_ALL = $(BLOCK_MAIN) $(BLOCK_C) $(TRANS_C)

# TESTS Transaction
# ------------------------------------------------------------
transaction: $(TRANS_ALL)
	$(CC) -o $(BINDIR)/transaction $(TRANS_ALL)
	mv *.o $(BINDIR)/

block: $(BLOCK_ALL)
	$(CC) -o $(BINDIR)/block $(BLOCK_ALL)
	mv *.o $(BINDIR)/

# '%' matches filename
# $@  for the pattern-matched target
# $<  for the pattern-matched dependency
%.o: $(MAINDIR)/%.c
	$(CC) -o $@ -c $< $(SYS) $(INC)

clean:
	rm -rf *.o