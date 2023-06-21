CC = gcc
CFLAGS = -Iinclude
SRC = src
OBJ = obj
BINDIR = bin
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN = $(BINDIR)/main.out

SUBMITNAME = tSnake.zip
zip = zip

all: $(BIN)

release: CFLAGS = -O2
release: new

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lncurses

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@	

link: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)

clean:
	rm $(BINDIR)/* $(OBJ)/*

new: clean
new: all

submit:
	rm -f $(SUBMITNAME)
	zip $(SUBMITNAME) $(BIN)