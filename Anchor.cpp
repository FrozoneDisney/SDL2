#include "Anchor.hpp"

Vector2f Anchor::getDir()
{
	return dir;
}

void Anchor::changeDir(Vector2f newdir)
{
	dir.x = newdir.x;
	dir.y = newdir.y;

	if (newdir.x >= 1)
		setAngle(90);

	if (newdir.x <= -1)
		setAngle(270);

	if (newdir.y >= 1)
		setAngle(180);

	if (newdir.y <= -1)
		setAngle(0);
}