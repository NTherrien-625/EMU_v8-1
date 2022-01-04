cpuTester: cpuTester.o cpu.o
	g++ -o cpuTester cpuTester.o cpu.o

cpuTester.o: cpuTester.cpp
	g++ -c cpuTester.cpp

cpu.o: cpu.cpp cpu.hpp
	g++ -c cpu.cpp

clean:
	rm -f *.o *~ *.bin