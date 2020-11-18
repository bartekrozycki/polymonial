.PHONY = poly clean

poly: testpoly.o
	g++ -g -Wall $^ -o $@

testpoly.o: testpoly.cpp poly.h
	g++ -g -c -Wall $< -o $@

clean:
	-rm testpoly.o