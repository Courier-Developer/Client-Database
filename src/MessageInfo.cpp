//
// Created by 孙璋亮 on 2019-08-30.
//

#include "MessageInfo.h"

//todo:
UserInfo *MessageInfo::getSender() {
    return Sender;
}
// todo:
ChatInfo *MessageInfo::getChat() {
    return InChat;
}

int MessageInfo::getType() {
    return type;
}

DateTime MessageInfo::getCreateTime() {
    return CreatedTime;
}

std::string MessageInfo::getContent() {
    return Content;
}

int MessageInfo::getStatus() {
    return Status;
}

unsigned int MessageInfo::getSenderId() const {
    return SenderId;
}

unsigned int MessageInfo::getReceiverId() const {
    return ReceiverId;
}

MessageInfo::MessageInfo(unsigned int senderId, unsigned int receiverId, const std::string &content, int status,
                         int type, int contentKind, const DateTime &createdTime) : SenderId(senderId),
                                                                                   ReceiverId(receiverId),
                                                                                   Content(content), Status(status),
                                                                                   type(type), ContentKind(contentKind),
                                                                                   CreatedTime(createdTime) {}

void MessageInfo::setStatus(int status) {
    Status = status;
}

int MessageInfo::getContentKind() const {
    return ContentKind;
}

const DateTime &MessageInfo::getCreatedTime() const {
    return CreatedTime;
}

ChatInfo *MessageInfo::getInChat() const {
    return InChat;
}

MessageInfo::MessageInfo() {}

MessageInfo::~MessageInfo() {

}

MessageInfo::MessageInfo(unsigned int senderId, unsigned int receiverId, int messageId, const std::string &content,
                         int status, int type, int contentKind, const DateTime &createdTime) : SenderId(senderId),
                                                                                               ReceiverId(receiverId),
                                                                                               MessageId(messageId),
                                                                                               Content(content),
                                                                                               Status(status),
                                                                                               type(type),
                                                                                               ContentKind(contentKind),
                                                                                               CreatedTime(
                                                                                                       createdTime) {}

int MessageInfo::getMessageId() const {
    return MessageId;
}

void MessageInfo::setMessageId(int messageId) {
    MessageId = messageId;
}

void MessageInfo::setSender(UserInfo *sender) {
    Sender = sender;
}

void MessageInfo::setInChat(ChatInfo *inChat) {
    InChat = inChat;
}
