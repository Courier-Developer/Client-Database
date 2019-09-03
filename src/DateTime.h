//
// Created by ervinxie on 8/30/19.
//

#ifndef COURIER_CLIENT_DATETIME_H
#define COURIER_CLIENT_DATETIME_H

#include <string>

class DateTime {
public:
    int t[6]={};
    int &y = t[0];
    int &M = t[1];
    int &d = t[2];
    int &h = t[3];
    int &m = t[4];
    int &s = t[5];

    DateTime(){}
    DateTime(int y, int M, int d, int h, int m, int s){
        t[0]=y;
        t[1]=M;
        t[2]=d;
        t[3]=h;
        t[4]=m;
        t[5]=s;
    }

    DateTime(std::string timestr,std::string format="%d-%d-%d %d:%d:%d"){
        sscanf(timestr.c_str(), format.c_str(), &y, &M, &d, &h, &m, &s);
    }

    bool operator<(const DateTime &b) const{
        for (int i = 0; i < 6; i++) {
            if (t[i] < b.t[i]) {
                return true;
            } else if (t[i] == b.t[i]) {
                return false;
            }
        }
        return false;
    }

    void setDateTime(std::string datetime, std::string format="%d-%d-%d %d:%d:%d") {
        sscanf(datetime.c_str(), format.c_str(), &y, &M, &d, &h, &m, &s);
    }

    std::string getString() {
        char temp[50] = {};
        sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d", y, M, d, h, m, s);
        return std::string(temp);
    }

    constexpr static int md[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    bool is_leap() { return y % 400 == 0 || (y % 4 == 0 && y % 100 != 0); }

    int getMd() {
        if (is_leap() && M == 2)
            return 29;
        else
            return md[M];
    }
};


#endif //COURIER_CLIENT_DATETIME_H