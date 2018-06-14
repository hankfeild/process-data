all: bin/sum

sum: bin/sum
bin/sum: src/sum.cpp bin
	g++ src/sum.cpp -o bin/sum

bin:
	mkdir -p bin
