//
// Created by 孙璋亮 on 2019-08-30.
//

#include "ChatInfo.h"

//todo:
std::vector<MessageInfo *> *ChatInfo::getMsgList() {
    if (MessageList!= nullptr)
        return MessageList;
    else{
        return new std::vector<MessageInfo *>;
    }
}

//todo
int ChatInfo::getChatWith() {
    return Totype;
}

//todo
UserInfo *ChatInfo::getUser() {
    return ToUser;
}

//todo
GroupInfo *ChatInfo::getGroup() {
    return ToGroup;
}

ChatInfo::~ChatInfo() {
//    if (MessageList)
//        delete MessageList;
}

void ChatInfo::AddMessage(MessageInfo *msg) {
    if (MessageList!= nullptr) {
        MessageList->push_back(msg);
    } else{
        MessageList=new std::vector<MessageInfo *>;
        MessageList->push_back(msg);
    }
//    if (LastContent->getCreateTime() < msg->getCreateTime())
//        LastContent=msg;
}


GroupInfo *ChatInfo::getToGroup() const {
    return ToGroup;
}

int ChatInfo::getUnreadNumbers() const {
    return UnreadNumbers;
}

void ChatInfo::setToUser(UserInfo *toUser) {
    ToUser = toUser;
}

int ChatInfo::getTotype() const {
    return Totype;
}

UserInfo *ChatInfo::getToUser() const {
    return ToUser;
}

void ChatInfo::setToGroup(GroupInfo *toGroup) {
    ToGroup = toGroup;
}

void ChatInfo::setTotype(int totype) {
    Totype = totype;
}
