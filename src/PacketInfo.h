//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_PACKETINFO_H
#define COURIER_CLIENT_PACKETINFO_H

#include "predeclare.h"
#include "UserInfo.h"
//分组类
class PacketInfo {

private:
//    std::vector<unsigned int> MemberId; //成员ID
    std::string PacketName;
    int PacketId;   //分组id
    std::vector<UserInfo *> *Members= nullptr;
public:

    const std::string &getPacketName() const;

    PacketInfo(const std::string &packetName, int packetId);

    int getPacketId() const;

    std::vector<UserInfo *> *getMembers() const;

    std::vector<UserInfo *> *getUsers();

    std::string getName();

    virtual ~PacketInfo();

    int getPriority();

    void AddUser(UserInfo *user);

    void DeleteMember(UserInfo *oldmember);

    void setPacketName(const std::string &packetName);
};


#endif //COURIER_CLIENT_PACKETINFO_H
