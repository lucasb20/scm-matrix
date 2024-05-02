CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c pgm.c
OBJS = $(SRCS:.c=.o)
TARGET = hello.out

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: all

clean:
	rm -f $(OBJS) $(TARGET)