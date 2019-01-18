#####################################################
#makefile EQP 25-43									#
#auteur:William Glazer								#
#compilation de la librarie							#
#####################################################

#include vars globales
include ../Makefile_commun

#vars de compilation
src=$(wildcard *.cpp)
obj=$(src:.cpp=.o)
trg=librobot.a

#CFLAGS globaux inchangés
CFLAGS=  $(CFLAGS_commun)
	

#Commande de compilation
all:$(trg) clean

#transformation en librarie .a
$(trg):$(obj)
	avr-ar $(LDFLAGS) $(trg) $(obj)

#Transforme .cpp en .o
%.o:%.cpp
	avr-gcc $(CFLAGS) -c $<

#nettoyages
clean:
	rm -rf ./*.o
	rm -rf *.d
	
clA:
	make clean
	rm -rf *.a
