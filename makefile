CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp simulation.cpp
PROG = genetic_tsp

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
