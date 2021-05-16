CC  = gcc
SYS = -Wall -pedantic -DUNIX
INC = -I.


MAINDIR = src/main
TESTDIR = src/test
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

BLOCK_DEP = $(UTIL_256_MORE) $(UTIL_256) $(TRANS_DEP) $(BLOCK_C)
BLOCK_ALL = $(BLOCK_DEP) $(BLOCK_MAIN)


# CHAIN
CHAIN_MAIN = create_blockchain.o
CHAIN_C = blockchain.o

CHAIN_DEP = $(BLOCK_DEP) $(CHAIN_C)
CHAIN_ALL = $(CHAIN_DEP) $(CHAIN_MAIN)


# COINBASE
COIN_C = coinbase.o

COIN_DEP = $(CHAIN_DEP) $(COIN_C)


# DISPLAY
DISPLAY_C = display.o

DISPLAY_DEP = $(COIN_DEP) $(DISPLAY_C)


# MAIN
MAIN_C = main.o

MAIN_ALL = $(DISPLAY_DEP) $(MAIN_C)


#########
# BUILD #
#########

transaction: $(TRANS_ALL)
	$(CC) -o $(BINDIR)/transaction $(TRANS_ALL)
	mv *.o $(OBJDIR)/

block: $(BLOCK_ALL)
	$(CC) -o $(BINDIR)/block $(BLOCK_ALL)
	mv *.o $(OBJDIR)/

chain: $(CHAIN_ALL)
	$(CC) -o $(BINDIR)/chain $(CHAIN_ALL)
	mv *.o $(OBJDIR)/


main: $(MAIN_ALL)
	$(CC) -o $(BINDIR)/main $^
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
