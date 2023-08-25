CC = g++
CFLAGS = -Wall -std=c++11

SOURCES = app.cpp funciones.cpp
HEADERS = funciones.h
EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $@

clean:
	rm -rf $(EXECUTABLE)

