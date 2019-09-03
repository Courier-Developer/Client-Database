//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef COURIER_CLIENT_CHATINFO_H
#define COURIER_CLIENT_CHATINFO_H

#include "predeclare.h"


class ChatInfo{
private:
    int Totype;
    std::vector<MessageInfo *> *MessageList = nullptr;
    UserInfo *ToUser= nullptr;
    GroupInfo *ToGroup=nullptr;
    int UnreadNumbers; //未读消息数量
//    MessageInfo *LastContent;
public:
    std::vector<MessageInfo *> *getMsgList();

    int getChatWith(); //1.个人 2.群

    UserInfo *getUser();

    GroupInfo *getGroup();

    ~ChatInfo();

    void AddMessage(MessageInfo * msg);

    GroupInfo *getToGroup() const;

    int getUnreadNumbers() const;

    void setToUser(UserInfo *toUser);

    void setToGroup(GroupInfo *toGroup);

    int getTotype() const;

    UserInfo *getToUser() const;

    void setTotype(int totype);
};


#endif //COURIER_CLIENT_CHATINFO_H
