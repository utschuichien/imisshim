#include "list.h"
#include "movie.h"
#include "room.h"
#include "showTime.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <conio.h>
static int count = 0;
using namespace std;
void readFileForShowTime();
void createNewShowTimeForMovie(string movieId);
void createNewSuatchieuForRoom(string roomId);
void removeShowTime(string id);
void editShowTimeForMovie(string old_id, string new_id);
void editShowTimeForRoom(string old_id, string new_id);
// quan ly phim
list<movie> MovieManagement;
// add new movie
void addMovie(const movie &newMovie)
{
    MovieManagement.insert(newMovie);
    ++count;
}
// remove a movie
bool removeMovie(string id)
{
    movie *m = MovieManagement.search(id);
    if (m == NULL)
    {
        cout << "\nnot found , check again : ";
        return false;
    }

    MovieManagement.remove(*m);
    return true;
}
// edit a movie
bool editMovie(string &id, string &newId)
{
    movie *m = MovieManagement.search(id);
    if (m == NULL)
    {
        cout << "\nnot found check again : \n";
        return false;
    }

    movie newMovie;
    cin >> newMovie;
    newId = newMovie.getId();
    MovieManagement.edit(*m, newMovie);
    return true;
}
// list of movies
void printListMovies()
{
    node<movie> *current = MovieManagement.getHead();
    int widthTable = MovieManagement.getSize();
    int count = 0;
    string table[widthTable][6];

    while (current != NULL)
    {

        table[count][0] = current->data.getId();
        table[count][1] = current->data.getTitle();
        table[count][2] = current->data.getGenre();
        table[count][3] = to_string(current->data.getLenght());
        table[count][4] = current->data.getAge();
        table[count][5] = to_string(current->data.getYear());
        count++;
        current = current->next;
    }

    int width[6] = {0};
    // Duyệt qua mảng 2 chiều để tính độ rộng của mỗi cột
    for (int i = 0; i < widthTable; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (table[i][j].length() > width[j])
            {
                width[j] = table[i][j].length();
            }
        }
    }
    // In ra dòng ngăn cách trên cùng của khung
    cout << "\t\t\t+";
    for (int j = 0; j < 6; j++)
    {
        cout << setw(width[j] + 2) << setfill('-') << "-";
        cout << "+";
    }
    cout << endl;
    // In ra tiêu đề của bảng
    cout << "\t\t\t|";
    cout << setw(width[0] + 2) << setfill(' ') << left << "MA" << "|";
    cout << setw(width[1] + 2) << setfill(' ') << left << "TEN PHIM" << "|";
    cout << setw(width[2] + 2) << setfill(' ') << left << "THE LOAI" << "|";
    cout << setw(width[3] + 2) << setfill(' ') << left << "DODAI" << "|";
    cout << setw(width[4] + 2) << setfill(' ') << left << "DO TUOI" << "|";
    cout << setw(width[5] + 2) << setfill(' ') << left << "NAM" << "|";
    cout << endl;

    // In ra nội dung của bảng
    for (int i = 0; i < widthTable; i++)
    {
        cout << "\t\t\t|";
        for (int j = 0; j < 6; j++)
        {
            cout << setw(width[j] + 2) << setfill(' ') << left << table[i][j] << "|";
        }
        cout << endl;
    }

    // In ra dòng ngăn cách dưới cùng của khung
    cout << "\t\t\t+";
    for (int j = 0; j < 6; j++)
    {
        cout << setw(width[j] + 2) << setfill('-') << "-";
        // In ra dấu "+"
        cout << "+";
    }
    cout << endl;
}
bool checkPrimarykeyForMovie(const string &id)
{
    node<movie> *current = MovieManagement.getHead();

    while (current != NULL)
    {
        if (current->data.getId() == id)
        {
            return false; // nếu trùng khóa chính trả về false
        }
        current = current->next;
    }
    return true;
}
void readFileMovie()
{
    ifstream file;

    file.open("Movie_information.txt");

    if (!file.is_open())
    {
        cout << "can not open file, check again\n";
    }
    // id,title,genre,lenght,age,year
    else
    {
        string line;
        movie token;
        int pos;

        try
        {
            while (getline(file, line))
            {
                pos = line.find(';');

                token.setId(line.substr(0, pos));

                line.erase(0, pos + 1);

                pos = line.find(';');

                token.setTitle(line.substr(0, pos));

                line.erase(0, pos + 1);

                pos = line.find(';');

                token.setGenre(line.substr(0, pos));

                line.erase(0, pos + 1);

                pos = line.find(';');

                token.setLenght(stoi(line.substr(0, pos)));

                line.erase(0, pos + 1);

                pos = line.find(';');

                token.setAge(line.substr(0, pos));

                line.erase(0, pos + 1);

                token.setYear(stoi(line));

                addMovie(token);
            }
        }
        catch (const std::exception &e)
        {
            cout << "error: " << e.what() << endl;
            cout << "check again file\n";
        }
    }
    file.close();
}

void writeFileMovie()
{
    ofstream file;
    file.open("Movie_information.txt");
    if (!file.is_open())
    {
        cout << "can not open file, check again\n";
    }
    else
    {
        node<movie> *current = MovieManagement.getHead();
        while (current != NULL)
        {
            file << current->data.getId() << ";" << current->data.getTitle() << ";" << current->data.getGenre() << ";" << current->data.getLenght() << ";" << current->data.getAge() << ";" << current->data.getYear() << endl;

            current = current->next;
        }

        file.close();
    }
}
void startForMovie()
{
    system("cls");
    readFileMovie();
    char tt;

    do
    {

        printListMovies();
        cout << endl;
        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(218);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(191) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t";
        cout << char(179) << " 1 " << char(179) << "   ADD MOVIE    " << char(179);
        cout << "                     " << char(179) << " 2 " << char(179) << "  REMOVE MOVIE  " << char(179) << endl;

        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(192);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(217) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(218);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(191) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t";
        cout << char(179) << " 3 " << char(179) << "   EDIT MOVIE   " << char(179);
        cout << "                     " << char(179) << " 4 " << char(179) << "   LIST MOVIE   " << char(179) << endl;

        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(192);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(217) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t\t\t\t";

        cout << char(218);
        for (int i = 0; i < 15; i++)
            cout << char(196);
        cout << char(191);
        cout << endl;
        cout << "\t\t\t\t\t\t";
        cout << char(179) << " 5 " << char(179) << "   BACK    " << char(179) << endl;
        cout << "\t\t\t\t\t\t" << char(192);
        for (int i = 0; i < 15; i++)
            cout << char(196);
        cout << char(217) << endl;

        tt = getche();

        switch (tt)
        {
        case '1':
        {
            movie new_movie;
            cout << endl;
            cin >> new_movie;
            readFileForShowTime();
            string newId;
            while (checkPrimarykeyForMovie(new_movie.getId()) != true)
            {
                cout << "\nPrimary key is exist , retype!!! \n";
                cout << "Id: ";
                cin >> newId;
                new_movie.setId(newId);
            }
            addMovie(new_movie);
            createNewShowTimeForMovie(new_movie.getId());
            writeFileMovie();
            break;
        }
        case '2':
        {
            string id;
            readFileForShowTime();
            cout << "\nMovie id : ";
            cin >> id;
            while (removeMovie(id) != true)
            {
                cin >> id;
                continue;
            }
            removeShowTime(id);
            writeFileMovie();
            break;
        }
        case '3':
        {
            string id;
            readFileForShowTime();
            string newId;
            cout << "\nMovie id : ";
            cin >> id;
            while (editMovie(id, newId) != true)
            {
                cin >> id;
                continue;
            }
            editShowTimeForMovie(id, newId);
            writeFileMovie();
            break;
        }
        case '4':
        {
            cout << "\n";
            system("cls");
            printListMovies();
            cout << "\t\t\tpress any key to continue";
            getch();
            break;
        }
        case '5':
        {
            return;
        }
        default:
            cout << "\a";
        }
        system("cls");
    } while (tt != 5);
}
// quan ly phong chieu phim
list<room> RoomManagement;
void addRoom(const room &newRoom)
{
    // them room dua vao template doubly linked list
    RoomManagement.insert(newRoom);
}
bool removeRoom(string id)
{
    room *r = RoomManagement.search(id);
    if (r == NULL)
    {
        cout << "\nnot found , check again : ";
        return false;
    }

    RoomManagement.remove(*r);
    return true;
}
bool editRoom(string &id, string &newId)
{
    room *m = RoomManagement.search(id);
    if (m == NULL)
    {
        cout << "\nnot found check again : \n";
        return false;
    }

    room newRoom;
    cin >> newRoom;
    newId = newRoom.getId();
    RoomManagement.edit(*m, newRoom);
    return true;
}

// doc ghi file
void readFileRoom()
{
    ifstream file;
    file.open("room.txt");

    if (!file.is_open())
    {
        cout << "\n Can not open file!!! Check again!\n";
    }
    else
    {
        string line;
        room token;
        int pos;
        try
        {
            while (getline(file, line))
            {
                pos = line.find(';');
                token.setRoomId(line.substr(0, pos));
                line.erase(0, pos + 1);
                token.setCapacity(stoi(line));
                addRoom(token);
            }
        }
        catch (const std::exception &e)
        {
            cout << "error: " << e.what() << endl;
            cout << "check file again\n";
        }
    }
    file.close();
}
void writeFileForRoom()
{
    ofstream file;
    file.open("room.txt");
    if (!file.is_open())
    {
        cout << "can not open file!!! Check again!";
    }
    else
    {
        node<room> *current = RoomManagement.getHead();
        while (current != NULL)
        {
            file << current->data.getId() << ";" << current->data.getCapacity() << endl;
            current = current->next;
        }
        file.close();
    }
}
bool checkPrimarykeyForRoom(const string &id)
{
    node<room> *current = RoomManagement.getHead();
    while (current != NULL)
    {
        if (current->data.getId() == id)
        {
            return false;
        }
        current = current->next;
    }
    return true;
}
// in danh sach phong chieu co trong rap
void printListRoom()
{
    node<room> *current = RoomManagement.getHead();
    while (current != NULL)
    {
        cout << "Ma phong: " << current->data.getId() << " " << "Suc chua: " << current->data.getCapacity() << endl;
        current = current->next;
    }
}
void startForRoom()
{
    system("cls");
    readFileRoom();
    char tt;

    do
    {

        printListRoom();
        cout << endl;
        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(218);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(191) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t";
        cout << char(179) << " 1 " << char(179) << "   ADD ROOM    " << char(179);
        cout << "                     " << char(179) << " 2 " << char(179) << "  REMOVE ROOM  " << char(179) << endl;

        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(192);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(217) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(218);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(191) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t";
        cout << char(179) << " 3 " << char(179) << "   EDIT ROOM   " << char(179);
        cout << "                     " << char(179) << " 4 " << char(179) << "   LIST ROOM   " << char(179) << endl;

        cout << "\t\t\t";
        for (int j = 0; j <= 1; j++)
        {
            cout << char(192);
            for (int i = 0; i < 20; i++)
                cout << char(196);
            cout << char(217) << "                     ";
        }
        cout << endl;
        cout << "\t\t\t\t\t\t";

        cout << char(218);
        for (int i = 0; i < 15; i++)
            cout << char(196);
        cout << char(191);
        cout << endl;
        cout << "\t\t\t\t\t\t";
        cout << char(179) << " 5 " << char(179) << "   BACK    " << char(179) << endl;
        cout << "\t\t\t\t\t\t" << char(192);
        for (int i = 0; i < 15; i++)
            cout << char(196);
        cout << char(217) << endl;

        tt = getche();

        switch (tt)
        {
        case '1':
        {
            room new_room;
            cout << endl;
            cin >> new_room;
            readFileForShowTime();
            string newId;
            while (checkPrimarykeyForRoom(new_room.getId()) != true)
            {
                cout << "\nPrimary key is exist , retype!!! \n";
                cout << "Id: ";
                cin >> newId;
                new_room.setRoomId(newId);
            }
            createNewSuatchieuForRoom(new_room.getId());
            addRoom(new_room);
            writeFileForRoom();
            break;
        }
        case '2':
        {
            string id;
            readFileForShowTime();
            cout << "\nRoom id : ";
            cin >> id;
            while (removeRoom(id) != true)
            {
                cin >> id;
                continue;
            }
            removeShowTime(id);
            writeFileForRoom();
            break;
        }
        case '3':
        {
            string id;
            string newId;
            readFileForShowTime();
            cout << "\nMovie id : ";
            cin >> id;
            while (editRoom(id, newId) != true)
            {
                cin >> id;
                continue;
            }
            editShowTimeForRoom(id, newId);
            writeFileForRoom();

            break;
        }
        case '4':
        {
            cout << "\n";
            system("cls");
            printListRoom();
            cout << "\t\t\tpress any key to continue";
            getch();
            break;
        }
        case '5':
        {
            return;
        }
        default:
            cout << "\a";
        }
        system("cls");

    } while (tt != 5);
}
// quan ly suat chieu
list<showTime> showTimeManagement;
char S[9][9];

void createtable()
{
    S[0][0] = ' ';
    int index = 0;
    for (int i = 1; i < 9; i++)
    {
        S[i][0] = 'A' + index;
        index++;
    }
    for (int i = 1; i < 9; i++)
    {
        S[0][i] = '0' + i;
    }
    for (int i = 1; i < 9; i++)
    {
        for (int j = 1; j < 9; j++)
        {
            S[i][j] = '0';
        }
    }
}
void addShowTime(showTime s)
{
    showTimeManagement.insert(s);
}

// end read and wrie file
string getmoviedate(string maphim, string masuat, string maphong)
{ // truyen vao ma phim va id cua suat chieu, => truyen them ma phong
    node<showTime> *current = showTimeManagement.getHead();
    while (current != NULL)
    {
        if (current->data.getId() == masuat && current->data.getMovieId() == maphim && current->data.getRoomId() == maphong)
        {
            return current->data.getDate();
        }
        else
            current = current->next;
    }
    return "";
}
string getmovietime(string maphim, string masuat, string maphong)
{ // truyen vao ma phim va id cua suat chieu, => truyen them ma phong
    node<showTime> *current = showTimeManagement.getHead();
    while (current != NULL)
    {
        if (current->data.getId() == masuat && current->data.getMovieId() == maphim && current->data.getRoomId() == maphong)
        {
            return current->data.getTime();
        }
        else
            current = current->next;
    }
    return "";
}
void setmovieseat(string maphim, string masuat, string maphong, string seat)
{ // set cho ngoi trong rap chieu phim
    node<showTime> *current = showTimeManagement.getHead();
    while (current != NULL)
    {
        if (current->data.getId() == masuat && current->data.getMovieId() == maphim && current->data.getRoomId() == maphong)
        {
            current->data.setSeatInfor(seat);
            return;
        }
        else
            current = current->next;
    }

}

string getmoviename(string id)
{
    ifstream inFile("Movie_information.txt");
    if (!inFile)
    {
        cout << "File wa doko? ";
    }
    string line;
    string moviename;
    while (getline(inFile, line))
    {
        if (line.find(id) == 0)
        {
            istringstream ss(line);

            getline(getline(ss, moviename, ';'), moviename, ';');
        }
    }
    inFile.close();

    return moviename;
}
string getCurrentDate()
{
    time_t now = time(0);
    tm *localTime = localtime(&now);

    ostringstream oss;
    oss << put_time(localTime, "%d/%m");
    return oss.str();
}

string GetTomorrowDate()
{
    // Lấy thời gian hiện tại
    time_t currentTime = time(nullptr);
    tm *localTime = localtime(&currentTime);
    localTime->tm_mday += 1;
    mktime(localTime);
    ostringstream oss;
    oss << setw(2) << setfill('0') << localTime->tm_mday << '/'
        << setw(2) << setfill('0') << localTime->tm_mon + 1;
    return oss.str();
}
bool CheckTime(const string &targetTime)
{
    time_t currentTime;
    time(&currentTime);
    struct tm *timeinfo;
    timeinfo = localtime(&currentTime);
    int targetHour, targetMinute;
    sscanf(targetTime.c_str(), "%dH%d", &targetHour, &targetMinute);
    if (timeinfo->tm_hour > targetHour || (timeinfo->tm_hour == targetHour && timeinfo->tm_min >= targetMinute))
    {
        return true; // Nếu thời gian hiện tại đã vượt qua thời gian target
    }
    else
    {
        return false;
    }
}

int CompareDate(const string &dateString)
{
    time_t currentTime = time(nullptr);
    tm *localTime = localtime(&currentTime);
    tm inputDate = {};
    istringstream iss(dateString);
    char delimiter;
    iss >> inputDate.tm_mday >> delimiter >> inputDate.tm_mon;
    inputDate.tm_mon -= 1;
    if (localTime->tm_mon > inputDate.tm_mon ||
        (localTime->tm_mon == inputDate.tm_mon && localTime->tm_mday > inputDate.tm_mday))
    {
        return 0; // trước ngày hiện tại
    }
    else if (localTime->tm_mon == inputDate.tm_mon && localTime->tm_mday == inputDate.tm_mday)
    {
        return 1; // là ngày hiện tại
    }
    else
    {
        return 2; // sau ngày hiện tại
    }
}
void print_Pre_seat(string seat)
{
    createtable();
    istringstream ss(seat);
    string field;
    while (getline(ss, field, ';'))
    {
        char hangghe = field[0];
        int hang = hangghe - 64;
        char soghe = field[1];
        int ghe = soghe - '0';
        if (S[hang][ghe] == '0')
        {
            S[hang][ghe] = 'X';
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << S[i][j] << "   ";
        }
        cout << endl
             << endl;
    }
}

string pickseat()
{
    cout << "Pick the seat you desire: ";
    string seat;
    bool booking = false;
    while (booking == false)
    {
        cin >> seat;
        char hangghe = seat[0];
        int hang = hangghe - 64;
        char soghe = seat[1];
        int ghe = soghe - '0';
        if (ghe >= 9 || hangghe > 'H' || seat.size() >= 3)
        {
            cout << "Check again: ";
        }
        else if (S[hang][ghe] == '0')
        {
            S[hang][ghe] = 'X';
            break;
        }
        else
        {
            cout << "Someone else had booked this seat. Please pick another seat!: ";
        }
    }
    return seat;
}

// edit id lai cho movie => sua lai trong suat chieu
// edit id lai cho room => sua lai trong suat chieu

void intro_manager()
{
    system("cls");
    cout << "\t\t";
    for (int i = 0; i < 60; i++)
        cout << char(219);
    for (int k = 0; k < 12; k++)
    {
        cout << endl
             << "\t\t" << char(219);

        switch (k)
        {
        case 1:
            cout << "                        ";
            cout << "MANAGEMENT                        ";
            break;
        case 3:
        case 7:
            cout << "  " << char(218);
            for (int j = 0; j < 23; j++)
                cout << char(196);
            cout << char(191);
            cout << "    " << char(218);
            for (int j = 0; j < 23; j++)
                cout << char(196);
            cout << char(191) << "  ";
            break;
        case 4:
            cout << "  " << char(179);
            ;
            cout << " 1 " << char(179) << "  Movie Management " << char(179);
            cout << "    ";
            cout << char(179) << " 2 " << char(179);
            cout << "  Room Management " << char(179) << "  ";
            break;
        case 5:
        case 9:
            cout << "  " << char(192);
            for (int j = 0; j < 23; j++)
                cout << char(196);
            cout << char(217);
            cout << "    " << char(192);
            for (int j = 0; j < 23; j++)
                cout << char(196);
            cout << char(217) << "  ";
            break;
        case 8:
            cout << "  " << char(179);
            cout << " 3 " << char(179) << " Revenues Management" << char(179);
            cout << "    ";
            cout << char(179) << " 4 " << char(179);
            cout << "       Exit        " << char(179) << "  ";
            break;
        case 0:
        case 2:
        case 6:
        case 10:
        case 11:
            for (int i = 0; i < 58; i++)
                cout << " ";
            break;
        }

        cout << char(219);
    }
    cout << endl
         << "\t\t";
    for (int i = 0; i < 60; i++)
        cout << char(219);
    cout << endl;
}
void run()
{

    do
    {
        bool check, out_the_loop = false; // điều kiện thoát vòng lặp
        // string nameStaff = "";
        // intro();
        // accManagement acc;
        // acc.checkLogin(check, nameStaff); // check = true gọi đến quản lí , false gọi đến nhân viên đặt vé
        while (out_the_loop == false)
        {
            char tt; // lựa chọn 1 là quản lí phim, 2 là quản lí nhân viên
            intro_manager();

            tt = getche();
            switch (tt)
            {

            case '1':
            {
                startForMovie();
                break;
            }

            case '2':
            {

                startForRoom();
                break;
            }
            case '3':
            {
                // Revenue revenue;
                // revenue.total_inDay();
                break;
            }
            case '4':
            {
                out_the_loop = true;
                break;
            }

            default:
                cout << "\a";
            }
        }
        // if (check == true)
        // {

        //     while (out_the_loop == false)
        //     {
        //         char tt; // lựa chọn 1 là quản lí phim, 2 là quản lí nhân viên
        //         intro_manager();

        //         tt = getche();
        //         switch (tt)
        //         {

        //         case '1':
        //         {
        //             movieManagement movie;
        //             movie.start();
        //             break;
        //         }

        //         case '2':
        //         {

        //             staffManager staff;
        //             staff.start();
        //             break;
        //         }
        //         case '3':
        //         {
        //             Revenue revenue;
        //             revenue.total_inDay();
        //             break;
        //         }
        //         case '4':
        //         {
        //             out_the_loop = true;
        //             break;
        //         }

        //         default:
        //             cout << "\a";
        //         }
        //     }
        // }

        // else
        // {
        //     while (out_the_loop == false)
        //     {
        //         char tt;
        //         intro_staff();

        //         tt = getche();
        //         switch (tt)
        //         {

        //         case '1':
        //         {
        //             Booking booking;
        //             booking.Datve(nameStaff);
        //             break;
        //         }

        //         case '2':
        //         {
        //             out_the_loop = true;
        //             break;
        //         }

        //         default:
        //             cout << "\a";
        //         }
        //     }
        // }

    } while (1);
}
int main()
{
    run();

    return 0;
}
void readFileForShowTime()
{
    ifstream inFile("showTime.txt");
    if (inFile.is_open() == false)
    {
        cerr << "File not found , check again";
        return;
    }
    string line;
    showTime s;
    bool checkseat = false;
    while (getline(inFile, line))
    {
        if (checkseat == true)
        {

            s.setSeatInfor(line);
            addShowTime(s);
            checkseat = false;
            continue;
        }
        else if (line.find("S") != string::npos)
        {
            istringstream iss(line);
            string token;

            getline(iss, token, ';');
            s.setShowTimeId(token); // Mã suất chiếu

            getline(iss, token, ';');
            s.setMovieId(token); // Mã phim

            getline(iss, token, ';');
            s.setRoomId(token); // Mã phòng chiếu

            getline(iss, token, ';');
            s.setTime(token); // Thời gian chiếu

            getline(iss, token, ';');
            s.setDate(token); // Ngày chiếu

            checkseat = true;
        }
    }
}
void writeFileForShowTime()
{
    ofstream outfile("showTime.txt");
    node<showTime> *current = showTimeManagement.getHead();
    while (current != NULL)
    {
        outfile << current->data.getId() << ";" << current->data.getMovieId() << ";" << current->data.getRoomId() << ";" << current->data.getTime() << ";" << current->data.getDate();
        outfile << "\n";
        outfile << current->data.getSeatInfor();
        outfile << "\n\n";
        current = current->next;
    }

    outfile.close();
}
void createNewShowTimeForMovie(string movieId)
{

    readFileRoom();
    ofstream outFile("showTime.txt", ios::app);
    node<room> *currentRoom = RoomManagement.getHead();
    string roomId = "R" + to_string(count);
    
        showTime s;
        int timehour = 7;
        string timeminute = "H30";
        int numberOfShowTimes = 6;
        for (int i = 0; i < 6; i++)
        {
            string showTimeId = "S" + to_string(i + 1);
            string time = to_string(timehour) + timeminute;
            timehour += 2;
            string date = getCurrentDate();
            string seat_infor = "";

            // tao them mot suat chieu khi them phong, moi phim duoc dua vao phong do => duyet qua tat ca cac phim
            showTime s(showTimeId, movieId,roomId , time, date, seat_infor);
            outFile << s.getId() << ";" << s.getMovieId() << ";" << s.getRoomId() << ";" << s.getTime() << ";" << s.getDate() << ";" << s.getSeatInfor();
            outFile << endl
                    << endl
                    << endl;
            showTimeId = "";
       
    }
    outFile.close();
}
void createNewSuatchieuForRoom(string roomId)
{
    readFileMovie();
    ofstream outFile("suatchieu.txt", ios::app);
    // node<movie>* currentMovie = mm.getHead();
    showTime s;
    int timehour = 7;
    string timeminute = "H30";
    int numberOfShowTimes = 6;
    // can mot string cho movieId
    string movieId = "MP";
    // lay so phim dang co trong rap
    int numberOfMovies = MovieManagement.getSize();
    for (int j = 0; j < numberOfMovies; j++)
    {
        movieId += to_string(j + 1);
        for (int i = 0; i < numberOfMovies * 2; i++)
        {
            string showTimeId = "S" + to_string(i + 1);
            string time = to_string(timehour) + timeminute;
            time += 2;
            string date = getCurrentDate();
            string seat_infor = "";

            // tao them mot suat chieu khi them phong, moi phim duoc dua vao phong do => duyet qua tat ca cac phim
            showTime s(showTimeId, movieId, roomId, time, date, seat_infor);
            outFile << s.getId() << ";" << s.getMovieId() << ";" << s.getRoomId() << ";" << s.getTime() << ";" << s.getSeatInfor();
            outFile << endl
                    << endl
                    << endl;
        }
    }
    outFile.close();
}
void removeShowTime(string id)
{
    ifstream inFile("showTime.txt");
    if (!inFile.is_open())
    {
        cerr << "Could not open file for reading." << endl;
        return;
    }

    string line;
    string updatedFileContent;
    bool skipNextLine = false;

    // Đọc từng dòng trong file
    while (getline(inFile, line))
    {
        if (skipNextLine)
        {
            // Nếu dòng trước chứa ID cần xóa, bỏ qua dòng hiện tại
            skipNextLine = false;
            continue;
        }

        // Kiểm tra nếu dòng này chứa ID cần xóa
        if (line.find(id) != string::npos)
        {
            skipNextLine = true; // Đánh dấu để bỏ qua dòng tiếp theo
        }
        else
        {
            // Nếu không chứa ID, thêm dòng vào nội dung cập nhật
            updatedFileContent += line + "\n";
        }
    }

    inFile.close();

    // Mở file để ghi đè với nội dung đã cập nhật
    ofstream outFile("showTime.txt");
    if (!outFile.is_open())
    {
        cerr << "Could not open file for writing." << endl;
        return;
    }
    outFile << updatedFileContent;
    outFile.close();
}
void editShowTimeForMovie(string old_id, string new_id)
{
    node<showTime> *current = showTimeManagement.getHead();
    while (current != NULL)
    {
        if (current->data.getMovieId() == old_id)
        {
            current->data.setMovieId(new_id);
            current = current->next;
        }
        else
            current = current->next;
    }
    writeFileForShowTime();
}
void editShowTimeForRoom(string old_id, string new_id)
{
    node<showTime> *current = showTimeManagement.getHead();
    while (current != NULL)
    {
        if (current->data.getRoomId() == old_id)
        {
            current->data.setRoomId(new_id);
            current = current->next;
        }
        else
            current = current->next;
    }
    writeFileForShowTime();
}