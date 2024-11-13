#pragma once
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;
class room
{
protected:
    string roomId;
    int capacity; 
public:
    room();
    room(string id, int capa);
    ~room();

    //cac phuong thuc getter setter
    string getId();
    int getCapacity();

    void setRoomId(string id);
    void setCapacity(int capa);

    //cac toan tu ==, =, <<, >>
    bool operator==(const room &);
    //toan tu gan 
    const room& operator=(const room &);
    //toan tu nhap xuat
    friend ostream& operator << (ostream& o, const room &);
    friend istream& operator >> (istream& i, room &);
};