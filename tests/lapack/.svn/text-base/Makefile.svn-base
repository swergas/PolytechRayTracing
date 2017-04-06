#LAPACK_PATH = /usr/lib/atlas

#FLAGS_DEBUG = `$(HOME)/Desktop/ProjetMAM4/itpp-4.2/bin/itpp-config --debug --cflags`
#FLAGS_OPT   = `$(HOME)/Desktop/ProjetMAM4/itpp-4.2/itpp-config --cflags`
FLAGS_OPT   = `/usr/bin/itpp-config --cflags`

#LIBS_DEBUG  = `$(HOME)/Desktop/ProjetMAM4/itpp-4.2/bin/itpp-config --debug --static --libs`
#LIBS_OPT    = `$(HOME)/Desktop/ProjetMAM4/itpp-4.2/itpp-config --static --libs`
LIBS_OPT   = `/usr/bin/itpp-config --static --libs`

#all: testlapack testzlapack test3 testzlapack2
all: testlapack test3 testzlapack2 hope

testlapack: testlapack.cpp
	g++ testlapack.cpp -o testlapack -llapack_atlas -llapack -lblas -latlas -lm -lc

testzlapack: testzlapack.cpp
	g++ testzlapack.cpp -o testzlapack -llapack_atlas -llapack -lblas -latlas -lm -lc

testzlapack2: testzlapack2.cpp
	g++ testzlapack2.cpp -o testzlapack2 -llapack_atlas -llapack -lblas -latlas -lm -lc


# http://rcabreral.blogspot.com/2010/05/complex-matrix-inverse-clapack.html
test3: test3.cpp
	#g++ test3.cpp -o test3 -L$(LAPACK_PATH) -llapack -lblas -lm
	g++ test3.cpp -o test3 -llapack -lblas -lm

hope: hope.cpp
	g++ $(FLAGS_OPT) hope.cpp -o hope $(LIBS_OPT) -llapack_atlas -llapack -lblas -latlas -lm -lc 

clean:
	rm -f test3 testlapack testzlapack testzlapack2 test3 hope

