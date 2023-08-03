CC = gcc
CFLAGS = -Wall -Wextra -Iinc
SRCDIR = src
BUILDDIR = build
DEFINES =

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))

TARGET = $(BUILDDIR)/executable

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(DEFINES) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(DEFINES) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)