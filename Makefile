FILES = raycast.c vector.c game.c colors.c screen.c main.c input.c
TARGET = solution

IDIR = .

CC = gcc
CFLAGS = -D _DEFAULT_SOURCE -std=c99 -Wall -Wextra -I$(IDIR)
LDFLAGS = -lm


.PHONY: clean all
all: $(TARGET)

$(TARGET): $(FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES) $(LDFLAGS)

clean:
	rm $(TARGET)
	
