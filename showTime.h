#pragma once
#include "list.h"

class showTime {
    private:
    string showTimeId; //ma suat chieu
    string movieId;
    string roomId;
    string time;
    string date;
    string seat_infor;

    public:
    showTime(string = "", string ="", string = "", string = "", string ="", string = "");
    ~showTime();
    
    string getId();
    string getMovieId();
    string getRoomId();
    string getTime();
    string getDate();
    string getSeatInfor();


    void setShowTimeId(string);
    void setMovieId(string);
    void setRoomId(string);
    void setTime(string);
    void setDate(string);
    void setSeatInfor(string);

    bool operator==(const showTime &m);
    friend ostream& operator<<(ostream& os, const showTime& m);
    friend istream& operator>>(istream& is, showTime& m);
    const showTime& operator = (const showTime &m);

};