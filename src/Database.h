//
// Created by 袁瑞泽 on 2019-08-31.
//

#ifndef COURIER_CLIENT_DATABASE_H
#define COURIER_CLIENT_DATABASE_H

#include <string>
#include<vector>
#include"sqlite3.h"
#include"UserInfo.h"
#include"GroupInfo.h"
#include"MessageInfo.h"
#include"PacketInfo.h"

class database {
private:
	sqlite3 *db;
	std::string username;
	char *remessage;
	char **result;
	int nrow;
	int ncol;
public:
	std::string getusername()
	{
		return username;
	}
	void setusername(char *_username)
	{
		username = _username;
	}

	std::string getfile(std::string username);

	database(char* _username);

	~database();


	//user_info 好友表操作
	int add_user(UserInfo _user);//添加一个用户信息

	int update_user(std::vector<UserInfo> _userve);//添加多个信息会覆盖之前信息

	int synchro_user(std::vector<UserInfo> _userve);//添加多个用户信息，已存在的用户信息忽略

	std::vector<UserInfo> search_user_all();//查找全部好友信息

	std::vector<UserInfo> search_user_id(int _userid);//查找_userid的用户信息

	int change_user_packet(int _userid, int _packetid);//更改_userid的用户分组为_packetid

	int drop_user_all();//删除所有用户信息

	int drop_user_id(unsigned int _id);//删除_id用户信息

	int drop_user_tb();//删除user_info_tb


	//group_info 群组表操作
	int add_group(GroupInfo _group);//添加一条群组信息

	int update_group(std::vector<GroupInfo> _groupve);//添加一条群组信息

	void add_group_user(unsigned int _groupid, unsigned int _userid);//群里增加一个用户

	std::vector<GroupInfo> search_group_all();//查找所有群组信息

	GroupInfo search_group_id(int _groupid);//查找_groupid的群组信息

	int drop_group_all();//删除所有群组信息

	int drop_group_id(unsigned int _id);//删除_id的群组信息

	int drop_group_user(unsigned int _groupid, unsigned int _userid);//删除群组中的_userid的人，不会更改group表信息

	int drop_group_tb();//删除整个group表

	std::vector<GroupInfo> getGroupInfo(char** result, int nrow, int ncol);

	//message_info 消息表操作
	int add_message(MessageInfo _message);//添加一条消息信息

	std::vector<MessageInfo> search_message_all();//查询所有消息记录

	std::vector<MessageInfo> search_message_id(unsigned int _id, int _type);//查询_id的消息记录 type1为个人 2为群聊

	std::vector<MessageInfo> search_message_localid(unsigned int _localid);//查询本地id为_localid的消息信息，localid自增
	
	std::vector<MessageInfo> synchro_message(std::vector<MessageInfo> _meve);//同步消息信息，返回新增加的消息

	int drop_message_all();//删除所有消息信息

	int drop_message_id(unsigned int _id, int _type);//删除_id _type的消息信息

	int drop_message_tb();//删除整个消息信息表


	//packet_info 分组信息表操作
	int add_packet(int _groupid, std::string packet);//增加一个用户分组

	int drop_packet(int _groupid);//删除_groupid的用户分组

	std::string search_packetid(int _packetid);//查找_packetid的名称

	int drop_packet_all();//删除全部packet表

	//history_info 历史信息表操作
	int add_history(unsigned int _userid, int _isgroup);

	int change_history(unsigned int _userid, int _isgroup, int _lastid);

	std::pair<int, int> search_history(unsigned int _userid, int _isgroup);


	//group_user_id 操作
	int add_group_user_id(int _groupid, int _userid);//增加用户群聊信息

	int change_group_identity(int _groupid, int _userid, int _identity);//修改群员身份

	std::vector<unsigned int> search_group_user_id(int _groupid);//查找_groupid下全部群员id
	
	int drop_group_user_all();//删除所有群聊用户信息

	int drop_group_user_groupid(int _groupid);//删除_groupid的群聊用户信息

	int drop_group_user_userid(int _groupid, int _userid);//从_groupid中删除_userid
};

#endif //COURIER_CLIENT_DATABASE_H