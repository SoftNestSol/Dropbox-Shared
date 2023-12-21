CC = gcc
CFLAGS = -Wall -g
SRCDIR = syscalls
BINDIR = executables
MAINDIR = main
SOURCES = $(wildcard $(SRCDIR)/*.c)
EXECUTABLES = $(patsubst $(SRCDIR)/%.c, $(BINDIR)/%, $(SOURCES))

.PHONY: all clean

all: $(EXECUTABLES) shell

$(BINDIR)/%: $(SRCDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

shell: $(MAINDIR)/console.c | $(BINDIR)
	$(CC) $(CFLAGS) $< -o $(BINDIR)/shell

clean:
	rm -f $(BINDIR)/* $(BINDIR)/shell
