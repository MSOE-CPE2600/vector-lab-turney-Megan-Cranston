CC=gcc
CFLAGS=-c
LDFLAGS=
SOURCES=main.c logic.c fileio.c operations.c commands.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=vector_lab

all: $(SOURCES) $(EXECUTABLE)

# pull in dependencies for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d