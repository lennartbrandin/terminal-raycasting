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
	
gprof:
	$(CC) $(CFLAGS) -pg -o $(TARGET) $(FILES) $(LDFLAGS) # -O0 
	./$(TARGET)
	gprof $(TARGET) gmon.out > analysis.txt
	# rm gmon.out

perf:
	$(CC) $(CFLAGS) -o $(TARGET) $(FILES) $(LDFLAGS)
	perf record ./$(TARGET)
	perf report

perf-pg:
	$(CC) $(CFLAGS) -pg -o $(TARGET) $(FILES) $(LDFLAGS)
	perf record ./$(TARGET)
	perf report

valgrind:
	$(CC) $(CFLAGS) -pg -O0 -o $(TARGET) $(FILES) $(LDFLAGS)
	valgrind --tool=callgrind ./$(TARGET)
	rm $(TARGET)
