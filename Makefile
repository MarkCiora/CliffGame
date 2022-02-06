
objects = main.o GameWindow.o helper.o Vec2.o Matrix2D.o Tex.o PhysicsObject.o Game.o VisualObject.o VisualLine.o

all : $(objects)
	g++ -Isrc/Include -Lsrc/lib $(objects) -o main -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

main.o: main.cpp
	g++ -Isrc/Include -Lsrc/lib -c main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

GameWindow.o: GameWindow.h GameWindow.cpp
	g++ -Isrc/Include -Lsrc/lib -c GameWindow.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

helper.o: helper.h helper.cpp
	g++ -Isrc/Include -Lsrc/lib -c helper.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

Vec2.o: Vec2.h Vec2.cpp
	g++ -Isrc/Include -Lsrc/lib -c Vec2.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

Matrix2D.o: Matrix2D.h Matrix2D.cpp
	g++ -Isrc/Include -Lsrc/lib -c Matrix2D.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

Tex.o: Tex.h Tex.cpp
	g++ -Isrc/Include -Lsrc/lib -c Tex.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

PhysicsObject.o: PhysicsObject.h PhysicsObject.cpp
	g++ -Isrc/Include -Lsrc/lib -c PhysicsObject.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

Game.o: Game.h Game.cpp
	g++ -Isrc/Include -Lsrc/lib -c Game.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

VisualObject.o: VisualObject.h VisualObject.cpp
	g++ -Isrc/Include -Lsrc/lib -c VisualObject.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

VisualLine.o: VisualLine.h VisualLine.cpp
	g++ -Isrc/Include -Lsrc/lib -c VisualLine.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

clean:
	-del $(objects) main.exe