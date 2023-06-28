CC = gcc
CFLAGS = -Iinclude -g
SRC = src
OBJ = obj
BINDIR = bin
BIN_NAME = main.out
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
BIN = $(BINDIR)/$(BIN_NAME)

SUBMITNAME = terminalSnake.zip
zip = zip

all: create_dirs
all: $(BIN)

release: CFLAGS = -Iinclude -O2
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

create_dirs:
	@mkdir -p $(BINDIR) $(OBJ)

new: clean
new: all

submit:
	rm -f $(SUBMITNAME)
	zip $(SUBMITNAME) $(BIN)