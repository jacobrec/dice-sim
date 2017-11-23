BIN = bin
OBJDIR = $(BIN)/objs
TO_COMPILE = freq.c list.c tokenizer.c parser.c drawAsciiTree.c
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(TO_COMPILE))

CC = gcc
$(shell   mkdir -p $(BIN))
$(shell   mkdir -p $(OBJDIR))


all: $(OBJS)
	$(CC) main.c $(OBJS) -g -o $(BIN)/dice


$(OBJDIR)/%.o: %.c %.h
	$(CC) -g -c $< -o $@

clean:
	@rm -rf bin/
