CC=gcc
CCFLAGS= -Wall -lm
 
 
# Les différents répertoires contenant respectivement les fichiers : Sources *.c, Headers *.h, Objets *.o, l'exécutable
SRCDIR=./src
HEADDIR=./inc
LIBDIR=./obj
BINDIR=./bin

all: Executable
 

 
# Création des différents *.o à partir des *.c
obj/bmp_reader.o: src/bmp_reader.c inc/bmp_reader.h 
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/pass.o: src/pass.c inc/pass.h inc/pixel.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/list.o: src/list.c inc/list.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/pixel.o: src/pixel.c inc/pixel.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/main.o: src/main.c inc/bmp_reader.h inc/pass.h inc/point.h 
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/skel.o: src/skel.c inc/skel.h inc/list.h inc/pixel.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/matrix.o: src/matrix.c inc/pixel.h inc/matrix.h 
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/douglas.o: src/douglas.c inc/douglas.h inc/pixel.h inc/point.h inc/tree.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/point.o: src/point.c inc/pixel.h inc/point.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/tree.o: src/tree.c inc/tree.h inc/point.h inc/pixel.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/interface.o: src/interface.c inc/interface.h
	$(CC) -o $@ -c $< $(CCFLAGS)

obj/latex.o: src/latex.c inc/latex.h inc/tree.h
	$(CC) -o $@ -c $< $(CCFLAGS)

#Création de l'exécutable
Executable: obj/main.o obj/bmp_reader.o  obj/pass.o obj/skel.o obj/list.o obj/pixel.o obj/matrix.o obj/point.o obj/douglas.o obj/tree.o obj/interface.o obj/latex.o
	$(CC) -o $(BINDIR)/$@ $^ $(CCFLAGS)

# Nettoyage des objets => Tout sera recompilé !
clean:
	rm $(LIBDIR)/*.o
 
# Nettoyage complet => clean + effacement de l'exécutable
Clean: clean
	rm $(BINDIR)/*