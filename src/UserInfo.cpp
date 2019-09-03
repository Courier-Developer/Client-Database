//
// Created by 孙璋亮 on 2019-08-30.
//

#include "UserInfo.h"


unsigned int UserInfo::getUserId() const {
    return UserId;
}

std::string UserInfo::getUserName() {
    return UserName;
}

std::string UserInfo::getNickName() {
    return NickName;
}

std::string UserInfo::getAvatarPath() {
    return AvatorPath;
}

std::string UserInfo::getSignature() {
    return Signature;
}

// todo:
ChatInfo *UserInfo::getChat() {
    if (InChat)
        return InChat;
    else
    {
        InChat=new ChatInfo;
        InChat->setTotype(1);
        InChat->setToUser(this);
        return InChat;
    }
}


const std::string &UserInfo::getAvatorPath() const {
    return AvatorPath;
}

int UserInfo::getStatus() const {
    return Status;
}

void UserInfo::setUserId(unsigned int UserId) {
    UserInfo::UserId = UserId;
}

void UserInfo::setUserName(const std::string &UserName) {
    UserInfo::UserName = UserName;
}

void UserInfo::setNickName(const std::string &NickName) {
    UserInfo::NickName = NickName;
}

void UserInfo::setSignature(const std::string &Signature) {
    UserInfo::Signature = Signature;
}

int UserInfo::getPacket() const {
    return packet;
}

void UserInfo::setAvatorPath(const std::string &AvatorPath) {
    UserInfo::AvatorPath = AvatorPath;
}

void UserInfo::setStatus(int status) {
    UserInfo::Status = status;
}

UserInfo::UserInfo() {}

UserInfo::~UserInfo() {
//    if (InChat)
//        delete InChat;
//    if (InGroups)
//        delete InGroups;
}

UserInfo::UserInfo(unsigned int userId, const std::string &userName, const std::string &nickName,
                   const std::string &signature, const std::string &avatorPath, int status, int packet) : UserId(
        userId), UserName(userName), NickName(nickName), Signature(signature), AvatorPath(avatorPath), Status(status),
                                                                                                          packet(packet) {}

void UserInfo::setInPacket(PacketInfo *inPacket) {
    InPacket = inPacket;
}


void UserInfo::setInGroup(GroupInfo *inGroup) {
    if (InGroups) {
        InGroups->push_back(inGroup);
    } else {
        InGroups = new std::vector<GroupInfo *>;
        InGroups->push_back(inGroup);
    }
}

bool UserInfo::HasChat() const {
    return InChat != nullptr;
}

PacketInfo *UserInfo::getInPacket() const {
    return InPacket;
}

std::vector<GroupInfo *> *UserInfo::getInGroups() {
    if (InGroups)
        return InGroups;
    else {
        return InGroups=new std::vector<GroupInfo *>;
    }
}

void UserInfo::setPacket(int packet) {
    UserInfo::packet = packet;
}





