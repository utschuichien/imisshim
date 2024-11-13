#include "room.h"
using namespace std;
room::room() {
    this->roomId = "";
    this->capacity = 0;
}
room::room(string id, int capa) {
    this->roomId = id;
    this->capacity = capa;
}
room::~room() {

}

// cac phuong thuc getter setter
string room::getId() {
    return this->roomId;
}
int room::getCapacity() {
    return this->capacity;
}

void room::setRoomId(string id) {
    this->roomId = id;
}
void room::setCapacity(int capa) {
    this->capacity = capa;
}

// cac toan tu ==, =, <<, >>
bool room::operator==(const room &r) {
    return this->roomId == r.roomId;
}
// toan tu gan
const room& room::operator=(const room &r) {
    this->roomId = r.roomId;
    this->capacity = r.capacity;
    return *this;
}
// toan tu nhap xuat
ostream &operator<<(ostream &o, const room &r) {
    o << "roomId: " << r.roomId << " capacity: " << r.capacity << endl;
    return o;
}
istream &operator>>(istream &i, room &r) {
    cout << "Enter roomId: ";
    i >> r.roomId;
    cout << "Enter room capacity: ";
    i >> r.capacity;
    return i;
}