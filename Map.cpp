#include "Map.h"
#include "Game.h"
#include <fstream>
#include "ECS.h"
#include "Components.h"

extern Manager manager;

Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp),mapScale(ms),tileSize(ts)
{
	scaledSize = ms * ts;
}

Map::~Map()
{
}

void Map::loadMap(std::string path, int sizex, int sizey)
{
	char tile;
	std::fstream mapfile;

	mapfile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizey; y++)
	{
		for (int x = 0; x < sizex; x++)
		{
			int a, b;
			mapfile.get(tile);
			a = atoi(&tile);
			mapfile.get(tile);
			b = atoi(&tile);
			srcY = (a * 10 + b) * tileSize;

			mapfile.get(tile);
			srcX = atoi(&tile) * tileSize;

			addTile(srcX, srcY, x * scaledSize, y * scaledSize);
			mapfile.ignore();
		}
	}

	mapfile.ignore();

	for (int y = 0; y < sizey; y++)
	{
		for (int x = 0; x < sizex; x++)
		{
			mapfile.get(tile);
			if (tile == '1')
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			mapfile.ignore();
		}
	}

	mapfile.close();
}

void Map::addTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos,tileSize, mapScale, mapFilePath);
	tile.addGroup(Game::groupMap);
}
