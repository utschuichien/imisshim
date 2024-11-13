#include "showTime.h"

showTime::showTime(string masuat, string maphim, string maphong, string gio, string ngay, string ghengoi) : showTimeId(masuat), movieId(maphim), roomId(maphong), time(gio), date(ngay), seat_infor(ghengoi) {}

showTime::~showTime() {}

string showTime::getId()
{
    return this->showTimeId;
}

string showTime::getMovieId()
{
    return this->movieId;
}

string showTime::getRoomId() {
    return this->roomId;
}
string showTime::getTime() {
    return this->time;
}
string showTime::getDate() {
    return this->date;
}
string showTime::getSeatInfor() {
    return this->seat_infor;
}

void showTime::setShowTimeId(string masuat) {
    this->showTimeId = masuat;
}
void showTime::setMovieId(string maphim) {
    this->movieId = maphim;
}
void showTime::setRoomId(string maphong) {
    this->roomId = maphong;
}
void showTime::setTime(string gio) {
    this->time = gio;
}
void showTime::setDate(string ngay) {
    this->date = ngay;
}
void showTime::setSeatInfor(string ghengoi) {
    this->seat_infor = ghengoi;
}
const showTime &showTime::operator=(const showTime &s)
{
    this->showTimeId = s.showTimeId;
    this->movieId = s.movieId;
    this->roomId = s.roomId;
    this->date = s.date;
    this->seat_infor = s.seat_infor;
    this->time = s.time;
    return *this;
}

istream &operator>>(istream &i, showTime &s)
{
    cout << "Show Time ID: ";
    i >> s.showTimeId;
    i.ignore();
    cout << "Movie ID: ";
    i >> s.movieId;
    cout << "Room ID: ";
    i >> s.roomId;
    cout << "Time: ";
    i >> s.time;
    cout << "Date: ";
    i >> s.date;
    cout << "Seat: ";
    i >> s.seat_infor;

    return i;
}

bool showTime::operator==(const showTime &s)
{
    return (this->showTimeId == s.showTimeId);
}

ostream &operator<<(ostream &o, const showTime &s)
{
    o << "Show Time ID: " << s.showTimeId << " Movie ID: " << s.movieId << "Room ID: " << s.roomId << " Time: " << s.time << " Date: " << s.date << endl;
    o << s.seat_infor;
    return o;
}
