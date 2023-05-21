CC = gcc
CFLAGS = -pthread

PROGRAMS = building_h2o

compile: clean $(PROGRAMS)

run: $(PROGRAMS)
	./$(PROGRAMS)

compile-and-run: compile run

clean:
	rm -f *~ $(PROGRAMS)