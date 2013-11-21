CC=g++
OPTS=-g

all: main.o traceread.o predictor.o
	$(CC) $(OPTS) -lm -o predictor main.o traceread.o predictor.o

main.o: main.c traceread.h predictor.h
	$(CC) $(OPTS) -c main.c

traceread.o: traceread.h traceread.c
	$(CC) $(OPTS) -c traceread.c

predictor.o: predictor.h predictor.c
	$(CC) $(OPTS) -c predictor.c

clean:
	rm -f *.o predictor;
