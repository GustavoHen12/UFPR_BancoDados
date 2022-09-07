CC=c++
CFLAGS = -g
LDFLAGS = -lm

all: escalona

escalona: escalona.o seriabilidade.o transacao.o
	$(CC) -o escalona escalona.o seriabilidade.o transacao.o $(CFLAGS) $(LDFLAGS)

escalona.o: escalona.cpp seriabilidade.h
	$(CC) -c escalona.cpp $(CFLAGS)

seriabilidade.o: seriabilidade.cpp seriabilidade.h transacao.h 
	$(CC) -c seriabilidade.cpp $(CFLAGS) $(LDFLAGS)

transacao.o: transacao.cpp transacao.h
	$(CC) -c transacao.cpp $(CFLAGS)

clean:
	-rm -f *~ *.o
	
purge: clean
	-rm -f escalona