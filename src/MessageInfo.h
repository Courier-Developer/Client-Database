//
// Created by 孙璋亮 on 2019-08-30.
//

#ifndef LOGIC_PART_MESSAGEINFO_H
#define LOGIC_PART_MESSAGEINFO_H

#include "predeclare.h"


class MessageInfo {
private:
    unsigned int SenderId;
    unsigned int ReceiverId;
    int MessageId;
    std::string Content;
    int Status; //是否发送成功
    int type;      //1 个人 2 群聊
    int ContentKind;   //消息类型 1 文本消息 2 文件
    DateTime CreatedTime;
    UserInfo *Sender = nullptr;
    ChatInfo *InChat = nullptr;
public:
    void setSender(UserInfo *sender);

public:
    int getMessageId() const;

    void setMessageId(int messageId);

    MessageInfo(unsigned int senderId, unsigned int receiverId, int messageId, const std::string &content, int status,
                int type, int contentKind, const DateTime &createdTime);

    MessageInfo(unsigned int senderId, unsigned int receiverId, const std::string &content, int status, int type,
                int contentKind, const DateTime &createdTime);

    UserInfo *getSender();

    ChatInfo *getChat();

    int getType();

    DateTime getCreateTime();

    unsigned int getSenderId() const;

    unsigned int getReceiverId() const;

    int getContentKind() const;

    void setInChat(ChatInfo *inChat);

    const DateTime &getCreatedTime() const;

    ChatInfo *getInChat() const;

    std::string getContent();

    int getStatus();

    void setStatus(int status);

    virtual ~MessageInfo();

    MessageInfo();
};


#endif //LOGIC_PART_MESSAGEINFO_H
