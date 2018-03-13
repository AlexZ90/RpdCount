all:
	mkdir -p bin
	gcc --std=c++11 -o bin/rpdCount src/main.cpp src/commonFunctions.cpp src/compareresults.cpp src/RpdRecord.cpp -Iinclude -lc -lstdc++
