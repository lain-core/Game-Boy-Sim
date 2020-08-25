CXX = g++
CXXFLAGS = -Wall -g

gb: 
	$(CXX) $(CXXFLAGS) gb.cpp -o gb

clean:
	rm -f *.o ./gb
