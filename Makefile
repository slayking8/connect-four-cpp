conn: conn.cpp
	g++ -Wextra -Wall conn.cpp -o game

clean:
	rm game
