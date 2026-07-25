CXX = g++ -g -std=c++17

FILE = src/main.o src/data.o src/template.o src/test.o src/attend.o src/reports.o
EXE = UTGhalam

all: $(EXE)

$(EXE):$(FILE)
	g++ $^ -o $@

src/main.o: src/main.cpp src/data.hpp src/template.hpp src/test.hpp src/reports.hpp src/attend.hpp
	g++ -c $< -o $@

src/data.o: src/data.cpp
	g++ -c $< -o $@

src/template.o: src/template.cpp src/data.hpp src/template.hpp
	g++ -c $< -o $@

src/test.o: src/test.cpp src/data.hpp src/test.hpp src/template.hpp
	g++ -c $< -o $@

src/attend.o: src/attend.cpp src/attend.hpp src/data.hpp src/test.hpp src/template.hpp
	g++ -c $< -o $@

src/reports.o: src/reports.cpp src/data.hpp src/reports.hpp src/test.hpp src/template.hpp src/attend.hpp
	g++ -c $< -o $@
