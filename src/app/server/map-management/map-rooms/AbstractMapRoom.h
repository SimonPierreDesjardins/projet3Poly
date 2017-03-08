#ifndef ABSTRACT_MAP_ROOM_H
#define ABSTRACT_MAP_ROOM_H

class AbstractMapRoom
{
public:	
	AbstractMapRoom() = default;
	virtual ~AbstractMapRoom() = 0;
};

inline AbstractMapRoom::~AbstractMapRoom()
{
}

#endif // ABSTRACT_MAP_ROOM