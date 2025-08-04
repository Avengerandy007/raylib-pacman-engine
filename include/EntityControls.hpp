#include "../Raylib/include/raylib.h"
class Controller{
	int speed;
public:
	Vector2 dir;

	void Move(Vector2& pos);
};

class TileCollider{
};

class InputHandler{
public:
	void ChangeDirection(Vector2& dir);
};
