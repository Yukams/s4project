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

TRANS_DEP = $(TRANS_C)
TRANS_ALL = $(TRANS_DEP) $(TRANS_MAIN)


# BLOCK
BLOCK_MAIN = create_block.o
BLOCK_C = block.o
UTIL_256 = sha256.o
UTIL_256_MORE = sha256_utils.o

BLOCK_DEP = $(UTIL_256_MORE) $(UTIL_256) $(BLOCK_C) $(TRANS_DEP)
BLOCK_ALL = $(BLOCK_DEP) $(BLOCK_MAIN)


# CHAIN
CHAIN_MAIN = create_blockchain.o
CHAIN_C = blockchain.o

CHAIN_DEP = $(BLOCK_DEP) $(CHAIN_C)
CHAIN_ALL = $(CHAIN_DEP) $(CHAIN_MAIN)


# TESTS Transaction
# ------------------------------------------------------------
transaction: $(TRANS_ALL)
	$(CC) -o $(BINDIR)/transaction $(TRANS_ALL)
	mv *.o $(OBJDIR)/

block: $(BLOCK_ALL)
	$(CC) -o $(BINDIR)/block $(BLOCK_ALL)
	mv *.o $(OBJDIR)/

chain: $(CHAIN_ALL)
	$(CC) -o $(BINDIR)/chain $(CHAIN_ALL)
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