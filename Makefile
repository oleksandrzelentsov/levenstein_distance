CC=gcc
CFLAGS=-c -Wall --std=c11 -Iinclude/
LDFLAGS=
SOURCES=main.c levenstein_distance.c helper.c file_input.c cfg.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=bin/levenstein-distance
PYTHON_EXECUTABLE=python3
TESTS_ROOT=tests
TEST_RESULTS=results

vpath %.c src
vpath %.h include


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p bin
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: $(OBJECTS)
	rm $(OBJECTS)

test: $(EXECUTABLE)
	"$(PYTHON_EXECUTABLE)" -mrobot --variable APP_EXECUTABLE_NAME:"$(realpath $(EXECUTABLE))" --pythonpath "$(TESTS_ROOT)/resources" -d "$(TEST_RESULTS)" "$(TESTS_ROOT)/testcases/*.robot"
