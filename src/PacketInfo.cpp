//
// Created by 孙璋亮 on 2019-08-30.
//

#include "PacketInfo.h"


std::vector<UserInfo *> *PacketInfo::getUsers() {
    if (Members)
        return Members;
    else {
        Members = new std::vector<UserInfo *>;
        return Members;
    }
}

std::string PacketInfo::getName() {
    return PacketName;
}

int PacketInfo::getPriority() {
    return PacketId;
}


const std::string &PacketInfo::getPacketName() const {
    return PacketName;
}

int PacketInfo::getPacketId() const {
    return PacketId;
}

std::vector<UserInfo *> *PacketInfo::getMembers() const {
    return Members;
}

PacketInfo::~PacketInfo() {
//    if (Members != nullptr)
//        delete Members;
}

void PacketInfo::AddUser(UserInfo *user) {
    if (Members!= nullptr)
    {
        Members->push_back(user);
    }
    else
    {
        Members=new std::vector<UserInfo *>;
        Members->push_back(user);
    }
}

PacketInfo::PacketInfo(const std::string &packetName, int packetId) : PacketName(packetName), PacketId(packetId) {}

void PacketInfo::DeleteMember(UserInfo *oldmember) {
    auto member=Members->begin();
    for (;member!=Members->end();member++)
        if (*member==oldmember){
            break;
        }
    if (member!=Members->end())
        Members->erase(member);
}

void PacketInfo::setPacketName(const std::string &packetName) {
    PacketName = packetName;
}
