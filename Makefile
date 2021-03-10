CC  = gcc
SYS = -Wall -pedantic -DUNIX
INC = -I.

MAINDIR = src/main/C
TESTDIR = src/test/C
UTILDIR = utils/C_Packages/Sha256
OBJDIR = obj
BINDIR = bin

# TRANSACTION
TRANS_MAIN = create_transaction.o
TRANS_C = transaction.o
TRANS_ALL = $(TRANS_MAIN) $(TRANS_C)

# BLOCK
BLOCK_MAIN = create_block.o
BLOCK_C = block.o
UTIL_256 = sha256.o
UTIL_256_MORE = sha256_utils.o
BLOCK_ALL = $(UTIL_256_MORE) $(UTIL_256) $(BLOCK_MAIN) $(BLOCK_C) $(TRANS_C)


# TESTS Transaction
# ------------------------------------------------------------
transaction: $(TRANS_ALL)
	$(CC) -o $(BINDIR)/transaction $(TRANS_ALL)
	mv *.o $(OBJDIR)/

block: $(BLOCK_ALL)
	$(CC) -o $(BINDIR)/block $(BLOCK_ALL)
	mv *.o $(OBJDIR)/

%.o: $(TESTDIR)/%.c
	$(CC) -o $@ -c $< $(SYS) $(INC)
%.o: $(MAINDIR)/%.c
	$(CC) -o $@ -c $< $(SYS) $(INC)
%.o: $(UTILDIR)/%.c
	$(CC) -o $@ -c $< $(SYS) $(INC)

clean:
	rm -f *.o
	rm -f $(OBJDIR)/*.o