g++ -std=c++11 -Ofast -march=native -o simulate ../src/Board.cpp ../src/Marker.cpp ../src/Ring.cpp ../src/Solver.cpp ../src/simulate.cpp ../src/Util.cpp
x1=$(expr $1)
for value1 in `seq 1 $x1`
do
	for value2 in `seq 1 $x1`
	do
		echo $value2
		./simulate $value1 $value2 > $value1'_'$value2'.txt'
	done
done
