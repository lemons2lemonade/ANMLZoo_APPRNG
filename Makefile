CC=g++-5
FLAGS=-O3 --std=c++11 -pthread -DDEBUG=false -g
VASIM=../../VASim
MNRL=$(VASIM)/MNRL/C++
LIBMNRL=$(MNRL)/libmnrl.a
PUGI=$(VASIM)/pugixml-1.6/src
LIBVASIM=$(VASIM)/libvasim.a
IDIRS=-I $(VASIM)/include -I $(MNRL)/include -I $(PUGI)

all:
	$(CC) $(IDIRS) $(FLAGS)  prng_automata.cpp $(LIBVASIM) $(LIBMNRL)  -o example
