CXX = g++ -g -std=c++17

FILE = main.o data.o template.o test.o attend.o reports.o
EXE = program.out

all: $(EXE)

$(EXE):$(FILE)
	g++ $^ -o $@

main.o: main.cpp data.hpp template.hpp test.hpp reports.hpp attend.hpp
	g++ -c $< -o $@

data.o: data.cpp
	g++ -c $< -o $@

template.o: template.cpp data.hpp template.hpp
	g++ -c $< -o $@

test.o: test.cpp data.hpp test.hpp template.hpp
	g++ -c $< -o $@

attend.o: attend.cpp attend.hpp data.hpp test.hpp template.hpp
	g++ -c $< -o $@

reports.o: reports.cpp data.hpp reports.hpp test.hpp template.hpp attend.hpp
	g++ -c $< -o $@
