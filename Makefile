BIN=/Users/kegank/projects/tic_tac_toe/bin
SRC=/Users/kegank/projects/tic_tac_toe/src
OBJ=/Users/kegank/projects/tic_tac_toe/obj

VER=c++11

${BIN}/tictactoe: ${OBJ}/tictactoe.o ${OBJ}/board.o ${OBJ}/gameplay.o ${OBJ}/translateCmd.o
	clang -std=${VER} -o ${BIN}/tictactoe ${OBJ}/tictactoe.o ${OBJ}/board.o ${OBJ}/gameplay.o ${OBJ}/translateCmd.o


${OBJ}/tictactoe.o: ${SRC}/tictactoe.cpp
	clang -std=${VER} -c ${SRC}/tictactoe.cpp
	mv tictactoe.o ${OBJ}/tictactoe.o


${OBJ}/board.o: ${SRC}/board.cpp ${SRC}/board.hpp
	clang -std=${VER} -c ${SRC}/board.cpp ${SRC}/board.hpp 
	mv board.o ${OBJ}/board.o


${OBJ}/gameplay.o: ${SRC}/gameplay.cpp ${SRC}/gameplay.hpp
	clang -std=${VER} -c ${SRC}/gameplay.cpp ${SRC}/gameplay.hpp 
	mv gameplay.o ${OBJ}/gameplay.o

${OBJ}/translateCmd.o: ${SRC}/translateCmd.cpp ${SRC}/translateCmd.hpp
	clang -std=${VER}  -c ${SRC}/translateCmd.cpp ${SRC}/translateCmd.hpp
	mv translateCmd.o ${OBJ}/translateCmd.o