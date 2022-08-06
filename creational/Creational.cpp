#include "Creational.h"

#include <iostream>

Room::Room(int roomNr) : m_roomNr(roomNr)
{
    m_sides[Direction::East] = nullptr;
    m_sides[Direction::West] = nullptr;
    m_sides[Direction::North] = nullptr;
    m_sides[Direction::South] = nullptr;
}

MapSite* Room::getSide(Direction direction)
{
    return m_sides[direction];
}

void Room::setSide(Direction direction, MapSite* mapSite)
{
    m_sides[direction] = mapSite;
}

int Room::roomNr() const
{
    return m_roomNr;
}

void Room::enter()
{

}

void Wall::enter()
{

}

Door::Door(Room* pRoom1, Room* pRoom2)
{

}

Room* Door::otherSideOfRoom(Room* pRoom)
{

}

void Door::enter()
{

}


void Maze::addRoom(Room* pRoom)
{
    if (pRoom) {
        m_rooms[pRoom->roomNr()] = pRoom;
    } else {
        std::cerr << "Null room object received unable to add room \n";
    }
}

Room* Maze::roomNr(int roomNr) const
{
    for (const auto& room : m_rooms) {
        if (room.second) {
            if (roomNr == room.second->roomNr()) {
                return room.second;
            }
        }
    }

    return nullptr;
}

Maze* MazeGame::createMaze()
{
    Maze* pMaze = new Maze;
    Room* pRoom1 = new Room(1);
    Room* pRoom2 = new Room(2);
    Door* pDoor = new Door(pRoom1, pRoom2);

    pMaze->addRoom(pRoom1);
    pMaze->addRoom(pRoom2);

    pRoom1->setSide(Direction::North, new Wall);
    pRoom1->setSide(Direction::East, pDoor);
    pRoom1->setSide(Direction::South, new Wall);
    pRoom1->setSide(Direction::West, new Wall);

    pRoom2->setSide(Direction::North, new Wall);
    pRoom2->setSide(Direction::East, new Wall);
    pRoom2->setSide(Direction::South, new Wall);
    pRoom2->setSide(Direction::West, pDoor);

    return pMaze;
}