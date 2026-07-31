CXX = g++ -g -std=c++20
FILES = obj/main.o obj/readMapFile.o obj/runGame.o obj/drawGameBoard.o obj/getPath.o obj/Ballon.o obj/WaveManager.o obj/tower.o obj/menuPage.o obj/bullet.o obj/checkCollisions.o obj/score.o 
EXE = TD

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

obj/main.o: src/main.cpp src/readMapFile.hpp src/runGame.hpp src/constance.hpp src/include.hpp src/menuPage.hpp
	$(CXX) -c $< -o $@

obj/runGame.o: src/runGame.cpp src/Ballon.hpp src/checkCollisions.hpp src/menuPage.hpp src/getPath.hpp src/waveConfigs.hpp src/score.hpp src/WaveManager.hpp src/tower.hpp src/bullet.hpp src/constance.hpp src/include.hpp
	$(CXX) -c $< -o $@

obj/readMapFile.o: src/readMapFile.cpp src/constance.hpp src/include.hpp
	$(CXX) -c $< -o $@	

obj/drawGameBoard.o: src/drawGameBoard.cpp src/constance.hpp src/include.hpp src/WaveManager.hpp
	$(CXX) -c $< -o $@

obj/getPath.o: src/getPath.cpp src/include.hpp 
	$(CXX) -c $< -o $@

obj/menuPage.o: src/menuPage.cpp src/constance.hpp src/include.hpp
	$(CXX) -c $< -o $@

obj/Ballon.o: src/Ballon.cpp src/Ballon.hpp src/include.hpp src/constance.hpp
	$(CXX) -c $< -o $@

obj/WaveManager.o: src/WaveManager.cpp src/waveConfigs.hpp src/Ballon.hpp src/include.hpp
	$(CXX) -c $< -o $@

obj/tower.o: src/tower.cpp src/tower.hpp src/include.hpp src/drawGameBoard.hpp  src/bullet.hpp
	$(CXX) -c $< -o $@

obj/bullet.o: src/bullet.cpp src/bullet.hpp src/include.hpp src/constance.hpp
	$(CXX) -c $< -o $@

obj/checkCollisions.o: src/checkCollisions.cpp src/checkCollisions.hpp src/include.hpp src/Ballon.hpp src/bullet.hpp src/score.hpp
	$(CXX) -c $< -o $@

obj/score.o:src/score.cpp src/score.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)