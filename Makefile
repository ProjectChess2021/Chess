CXX=g++
CXXFLAGS=-std=c++14 -MMD -g
OBJECTS=bishop.0 blackSide.o board.o bot.o king.o knight.o pawn.o piece.o position.o queen.o rook.o side.o whiteSide.o window.o
DEPENDS=${OBJECTS:.o=.d}
EXEC = projectChess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}
.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
