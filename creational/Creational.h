#pragma once
#include <map>

enum class Direction 
{
    North,
    South,
    East,
    West,
};

class MapSite
{
public:
    virtual void enter() = 0;
};

class Room : public MapSite
{
public:
    Room(int roomNr);

    MapSite* getSide(Direction direction);
    void setSide(Direction direction, MapSite* mapSite);

    void enter() override;

    int roomNr() const;
private:
    std::map<Direction, MapSite*> m_sides;
    int m_roomNr;
};

class Wall : public MapSite
{
public:
    void enter() override;
};

class Door : public MapSite
{
public:
    Door(Room* pRoom1, Room* pRoom2);
    Room* otherSideOfRoom(Room* pRoom);

    void enter() override;
private:
    Room* m_room1 = nullptr;
    Room* m_room2 = nullptr;
    bool m_isOpen = false;
};

class Maze
{
public:
    void addRoom(Room* pRoom);
    Room* roomNr(int) const;
private:
    std::map<int, Room*> m_rooms;
};

class MazeGame
{
public:
    Maze* createMaze();
};