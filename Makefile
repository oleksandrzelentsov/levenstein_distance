CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c levenstein_distance.h
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS)

test:
	python3.5 -mrobot --variable APP_EXECUTABLE_NAME:$(realpath $(EXECUTABLE)) --pythonpath tests/resources -d results tests/testcases/*.robot
