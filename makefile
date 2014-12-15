CC=gcc
CFLAGS= -Wall -lm
 
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=./src
HEADDIR=./inc
LIBDIR=./obj
BINDIR=./bin

all: Executable
 

 
# Création des différents *.o à partir des *.c
obj/bmp_reader.o: src/bmp_reader.c inc/bmp_reader.h 
	$(CC) -o $@ -c $< $(CFLAGS)

obj/pass.o: src/pass.c inc/pass.h 
	$(CC) -o $@ -c $< $(CFLAGS)

obj/main.o: src/main.c inc/bmp_reader.h inc/pass.h 
	$(CC) -o $@ -c $< $(CFLAGS)

#Création de l'exécutable
Executable: obj/main.o obj/bmp_reader.o obj/pass.o
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS)

# Nettoyage des objets => Tout sera recompiler !
clean:
	rm $(LIBDIR)/*.o
 
# Nettoyage complet => clean + effacement du l'exécutable
Clean: clean
	rm $(BINDIR)/*