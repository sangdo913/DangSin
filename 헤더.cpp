#include "Çì´õ.h"

Test::Test()
{
	lineCount = 0;

	point3 temp = { 0.f, 0.f, 0.f };

	memcpy(color, temp, sizeof(point3));


	for (int i = 0; i < 20; i++)
	{
		line[i].setColor(color);
		if (i < 5) way[i].setColor({ 1.f,1.f,1.f });
	}

}

void Test::clearLine()
{
	for (int i = 0; i < 20; i++)
	{
		line[i].setStart(Vector3(0, 0, 0));
		line[i].setEnd(Vector3(0, 0, 0));
		if (i < 5)
		{
			way[i].setStart(Vector3(0, 0, 0));
			way[i].setEnd(Vector3(0, 0, 0));
		}
	}

	lineCount = 0;
}

void Test::setColor(const point3& colorIn)
{
	for (int i = 0; i < 20; i++)
	{
		line[i].setColor(colorIn);
	}
}

void Test::clearWay()
{
	for (int i = 0; i < 5; i++)
	{
		way[i].setStart(Vector3(0, 0, 0));
		way[i].setEnd(Vector3(0, 0, 0));
	}
}
