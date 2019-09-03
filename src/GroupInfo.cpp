//
// Created by 孙璋亮 on 2019-08-30.
//

#include "GroupInfo.h"


// todo:
std::vector<UserInfo *> *GroupInfo::getUsers() {
    if (Members)
        return Members;
    else
        return Members=new std::vector<UserInfo *>;
}

// todo:
ChatInfo *GroupInfo::getChat() {
    if (chat)
        return chat;
    else {
        chat = new ChatInfo;
        chat->setTotype(2);
        chat->setToGroup(this);;
        return chat;
    }
}

unsigned int GroupInfo::getGroupId() {
    return GroupId;
}

std::string GroupInfo::getNickName() {
    return NickName;
}

std::string GroupInfo::getAvatarPath() {
    return AvatorPath;
}

std::string GroupInfo::getNotice() {
    return Notice;
}

GroupInfo::GroupInfo() {
    chat = nullptr;
    Members = nullptr;
};

GroupInfo::~GroupInfo() {
//    if (chat)
//        delete chat;
//    if (Members)
//        delete Members;
}

const std::vector<unsigned int> &GroupInfo::getMemberId() const {
    return MemberId;
}

void GroupInfo::AddUser(UserInfo *user) {
    if (Members) {
        Members->push_back(user);
    } else {
        Members = new std::vector<UserInfo *>;
        Members->push_back(user);
    }
}

GroupInfo::GroupInfo(unsigned int groupId, const std::string &nickName, const std::string &avatorPath,
                     const std::string &notice, const std::vector<unsigned int> &memberId) : GroupId(groupId),
                                                                                             NickName(nickName),
                                                                                             AvatorPath(avatorPath),
                                                                                             Notice(notice),
                                                                                             MemberId(memberId) {}

bool GroupInfo::HasChat() const {
    return chat != nullptr;
}

//删除成员，此处使用了auto
void GroupInfo::delete_member(UserInfo *member) {
    auto mark=getUsers()->end();
    for (auto it=getUsers()->begin();it!=getUsers()->end();it++){
        if ((*it)==member)
        {
            mark=it;
            break;
        }
    }
    if (mark!=getUsers()->end())
        getUsers()->erase(mark);

    auto userid=getMemberId().end();
    userid=MemberId.end();
    int hasid=member->getUserId();
    for (auto id=MemberId.begin();id!=MemberId.end();id++){
        if(*id==hasid) {
            userid = id;
            break;
        }
    }
    if (userid!=MemberId.end())
        MemberId.erase(userid);
}

void GroupInfo::setNickName(const std::string &nickName) {
    NickName = nickName;
}

void GroupInfo::setAvatorPath(const std::string &avatorPath) {
    AvatorPath = avatorPath;
}

void GroupInfo::setNotice(const std::string &notice) {
    Notice = notice;
}
