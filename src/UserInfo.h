//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_USEEINFO_H
#define COURIER_CLIENT_USEEINFO_H

#include "predeclare.h"


class UserInfo  {
private:
    unsigned int UserId;
    std::string UserName;
    std::string NickName;
    std::string Signature;
    std::string AvatorPath;
    int Status;  //登录状态，是否在线 1在线 0不在线
    int packet;  //所属分组号  0没有好友关系 -1为黑名单 1，2，3，4...为分组
    ChatInfo *InChat = nullptr;
    PacketInfo *InPacket = nullptr;
    std::vector<GroupInfo *> *InGroups = nullptr;

public:
    const std::string &getAvatorPath() const;

    void setUserId(unsigned int UserId);

    void setUserName(const std::string &UserName);

    UserInfo(unsigned int userId, const std::string &userName, const std::string &nickName,
             const std::string &signature, const std::string &avatorPath, int status, int packet);

    virtual ~UserInfo();

    UserInfo();

    void setNickName(const std::string &NickName);

    void setSignature(const std::string &Signature);

    void setAvatorPath(const std::string &AvatorPath);

    void setStatus(int status);

    int getStatus() const;

    unsigned int getUserId() const;

    std::string getUserName();

    std::string getNickName();

    std::string getAvatarPath();

    std::string getSignature();

    ChatInfo *getChat();

    void setInPacket(PacketInfo *inPacket);

    void setInGroup(GroupInfo *inGroup);

    void setPacket(int packet);

    int getPacket() const;

    bool HasChat() const;

    PacketInfo *getInPacket() const;

    std::vector<GroupInfo *> *getInGroups();
};


#endif //COURIER_CLIENT_USEEINFO_H
