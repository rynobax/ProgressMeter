all: clean build

clang: clean clang_build

clean:
	rm -f raytracer

build:
	g++ -Wall -O2 counter.cpp ProgressMeter.cpp -o counter

clang_build:
	clang++ -Wall counter.cpp ProgressMeter.cpp -o counter