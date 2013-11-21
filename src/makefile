CC=g++
OPTS=-g

all: maing.o main21264.o traceread.o predictorg.o predictor21264.o
	$(CC) $(OPTS) -lm -o predictorg maing.o traceread.o predictorg.o
	$(CC) $(OPTS) -lm -o predictor21264 main21264.o traceread.o predictor21264.o

maing.o: main.c traceread.h predictorg.h predictor21264.h
	$(CC) $(OPTS) -D_G_ -o maing.o -c main.c

main21264.o: main.c traceread.h predictor21264.h predictorg.h
	$(CC) $(OPTS) -o main21264.o -c main.c

traceread.o: traceread.h traceread.c
	$(CC) $(OPTS) -c traceread.c

predictorg.o: predictorg.h predictorg.c
	$(CC) $(OPTS) -c predictorg.c

predictor21264.o: predictor21264.h predictor21264.c
	$(CC) $(OPTS) -c predictor21264.c

clean:
	rm -f *.o predictor;
