test : 
# Question 1
	g++ -c Q1.cpp
	g++ -g -o debug1 Q1.o
	g++ -O3 -o optimize1 Q1.o

# Question 2
	g++ -c Q2.cpp
	g++ -g -o debug2 Q2.o
	g++ -O3 -o optimize2 Q2.o

# Question3 
	g++ -c Q3.cpp
	g++ -g -o debug3 Q3.o
	g++ -O3 -o optimize3 Q3.o