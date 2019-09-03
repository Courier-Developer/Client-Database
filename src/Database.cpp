//
// Created by 袁瑞泽 on 2019-08-31.
//

#include"Database.h"
#include<iostream>
#include<string>

std::vector<UserInfo> getUserInfo(char** result, int nrow, int ncol)
{
	std::vector<UserInfo> ve;
	int cnt = ncol;
	unsigned int userid;
	int status, packet;
	std::string username, nickname, signature, avatorpath;
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			switch (j)
			{
			case 0:userid = atoi(result[cnt++]); break;
			case 1:username = result[cnt++]; break;
			case 2:nickname = result[cnt++]; break;
			case 3:signature = result[cnt++]; break;
			case 4:avatorpath = result[cnt++]; break;
			case 5:status = atoi(result[cnt++]); break;
			case 6:packet = atoi(result[cnt++]); break;
			}
		}
		UserInfo tmp(userid, username, nickname, signature, avatorpath, status, packet);
		ve.push_back(tmp);
	}
	return ve;
}

std::vector<MessageInfo> getMessageInfo(char** result, int nrow, int ncol)
{
	std::vector<MessageInfo> ve;
	int cnt = ncol;
	unsigned int SenderId, ReceiverId;
	int status, type, ContentKind, messageid;
	std::string Content;
	DateTime date;
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			switch (j)
			{
			case 0:break;
			case 1:SenderId = atoi(result[cnt++]); break;
			case 2:ReceiverId = atoi(result[cnt++]); break;
			case 3:Content = result[cnt++]; break;
			case 4:status = atoi(result[cnt++]); break;
			case 5:type = atoi(result[cnt++]); break;
			case 6:ContentKind = atoi(result[cnt++]); break;
			case 7:date.setDateTime(result[cnt++]); break;
			case 8:messageid = atoi(result[cnt++]); break;
			}
		}
		MessageInfo tmp(SenderId, ReceiverId, messageid, Content, status, type, ContentKind, date);
		ve.push_back(tmp);
	}
	return ve;
}

std::vector<GroupInfo> database::getGroupInfo(char** result, int nrow, int ncol)
{
	std::vector<GroupInfo> ve;
	int cnt = ncol;
	unsigned int groupid;
	std::string nickname, avatorpath, notice;
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			switch (j)
			{
			case 0:groupid = atoi(result[cnt++]); break;
			case 1:nickname = result[cnt++]; break;
			case 2:avatorpath = result[cnt++]; break;
			case 3:notice = result[cnt++]; break;
			}
		}
		std::vector<unsigned  int>veid = search_group_user_id(groupid);
		GroupInfo tmp(groupid, nickname, avatorpath, notice, veid);
		ve.push_back(tmp);
	}
	return ve;
}

std::vector<unsigned int> getGroup_User_Id_Info(char** result, int nrow, int ncol)
{
	std::vector<unsigned int> ve;
	int cnt = ncol;
	unsigned int userid;
	for (int i = 0; i < nrow; i++)
	{
		for (int j = 0; j < ncol; j++)
		{
			switch (j)
			{
			case 0: userid = atoi(result[cnt++]); break;
			}
		}
		ve.push_back(userid);
	}
	return ve;
}

//获取数据库地址
std::string database::getfile(std::string username)
{
	return username += "_db";
}

//添加一组好友信息
int database::add_user(UserInfo _user)
{
	//printf("%d\n", _user.getid());
	std::string sql = "replace into user_info_tb values ("
		+ std::to_string(_user.getUserId()) + ", '"
		+ _user.getUserName() + "', '"
		+ _user.getNickName() + "', '"
		+ _user.getSignature() + "', '"
		+ _user.getAvatarPath() + "', "
		+ std::to_string(_user.getStatus()) + ", "
		+ std::to_string(_user.getPacket()) + ")";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	printf("%s\n", remessage);
	return ret;
}

//添加多个信息会覆盖之前信息
int database::update_user(std::vector<UserInfo> _userve)
{
	//printf("%d\n", _user.getid());
	int ret;
	for (auto _user : _userve)
	{
		std::string sql = "replace into user_info_tb values ("
			+ std::to_string(_user.getUserId()) + ", '"
			+ _user.getUserName() + "', '"
			+ _user.getNickName() + "', '"
			+ _user.getSignature() + "', '"
			+ _user.getAvatarPath() + "', "
			+ std::to_string(_user.getStatus()) + ", "
			+ std::to_string(_user.getPacket()) + ")";
		
		ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
		printf("%s\n", remessage);
	}
	return ret;
}

//添加多个用户信息，已存在的用户信息忽略
int database::synchro_user(std::vector<UserInfo> _userve)
{
	//printf("%d\n", _user.getid());
	int ret;
	for (auto _user : _userve)
	{
		std::string sql = "insert into user_info_tb values ("
			+ std::to_string(_user.getUserId()) + ", '"
			+ _user.getUserName() + "', '"
			+ _user.getNickName() + "', '"
			+ _user.getSignature() + "', '"
			+ _user.getAvatarPath() + "', "
			+ std::to_string(_user.getStatus()) + ", "
			+ std::to_string(_user.getPacket()) + ")";

		ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
		printf("%s\n", remessage);
	}
	return ret;
}

//搜索所有好友信息
std::vector<UserInfo> database::search_user_all()
{
	std::string sql = "select * from user_info_tb";
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<UserInfo> ve = getUserInfo(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve;
}

//搜索_id好友信息
std::vector<UserInfo> database::search_user_id(int _id)
{
	std::string sql = "select * from user_info_tb where userid = " + std::to_string(_id);
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<UserInfo> ve = getUserInfo(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve;
}

//更改用户分组
int database::change_user_packet(int _userid, int _packetid)
{
	std::string sql = "update user_info_tb set packetid = " + std::to_string(_packetid) 
		+ " where userid = " + std::to_string(_userid);
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除所有好友信息
int database::drop_user_all()
{
	std::string sql = "delete from user_info_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除特定id的好友信息
int database::drop_user_id(unsigned int _id)
{
	std::string sql = "delete from user_info_tb where userid = " + std::to_string(_id);
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除好友表
int database::drop_user_tb()
{
	std::string sql = "drop table user_info_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//group_info操作
//添加一个群组
int database::add_group(GroupInfo _group)
{
	std::string sql = "insert into group_info_tb values ( "
		+ std::to_string(_group.getGroupId()) + " , '"
		+ _group.getNickName() + "', '"
		+ _group.getAvatarPath() + "', '"
		+ _group.getNotice() + "')";

	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	printf("%s\n", remessage);
	//添加群聊中用户分组信息
	for (auto tmp : _group.getMemberId())
	{
		add_group_user(_group.getGroupId(), tmp);
	}
	return ret;
}

//添加多个群组
int database::update_group(std::vector<GroupInfo> _groupve)
{
	int ret;
	for (auto _group : _groupve)
	{
		std::string sql = "insert into group_info_tb values ("
			+ std::to_string(_group.getGroupId()) + ", '"
			+ _group.getNickName() + "', '"
			+ _group.getAvatarPath() + "', '"
			+ _group.getNotice() + "')";

		ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
		printf("%s\n", remessage);
		//添加群聊中用户分组信息
		for (auto tmp : _group.getMemberId())
		{
			add_group_user(_group.getGroupId(), tmp);
		}
	}
	return ret;
}

//群里增加一个用户
void database::add_group_user(unsigned int _groupid, unsigned int _userid)
{
	add_group_user_id(_groupid, _userid);
}

//搜索所有群组信息
std::vector<GroupInfo> database::search_group_all()
{
	std::string sql = "select * from group_info_tb";
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<GroupInfo> ve = getGroupInfo(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve;
}

//搜索所有群组信息
GroupInfo database::search_group_id(int _groupid)
{
	std::string sql = "select * from group_info_tb where groupid = " + std::to_string(_groupid);
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<GroupInfo> ve = getGroupInfo(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve[0];
}

//删除所有群组信息
int database::drop_group_all()
{
	std::string sql = "delete from group_info_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	drop_group_user_all();
	return ret;
}

//删除某一群组
int database::drop_group_id(unsigned int _id)
{
	std::string sql = "delete from group_info_tb where groupid = " + std::to_string(_id);
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	drop_group_user_groupid(_id);
	return ret;
}

//删除某一群组中某个人
int database::drop_group_user(unsigned int _groupid, unsigned int _userid)
{
	return drop_group_user_userid(_groupid, _userid);
}

//删除群组表
int database::drop_group_tb()
{
	std::string sql = "drop table group_info_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//group_user_id 操作
//添加用户-群聊信息
int database::add_group_user_id(int _groupid, int _userid)
{
	std::string sql = "insert into group_user_id_tb values ("
		+ std::to_string(_groupid) + ", "
		+ std::to_string(_userid) + ", "
		+ std::to_string(0) + ")";

	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	printf("%s\n", remessage);
	return ret;
}

//修改群员身份
int database::change_group_identity(int _groupid, int _userid, int _identity)
{
	std::string sql = "update group_user_id_tb set identity = "
		+ std::to_string(_identity) + " where groupid =  "
		+ std::to_string(_groupid) + " and userid =  "
		+ std::to_string(_userid) + ")";

	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	printf("%s\n", remessage);
	return ret;
}

//查询群组中用户id
std::vector<unsigned int> database::search_group_user_id(int _groupid)
{
	std::string sql = "select userid from group_user_id_tb where groupid = " + std::to_string(_groupid);
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<unsigned int> ve = getGroup_User_Id_Info(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve;
}

//删除所有群组用户信息
int database::drop_group_user_all()
{
	std::string sql = "delete from group_user_id_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除_id群组信息
int database::drop_group_user_groupid(int _groupid)
{
	std::string sql = "delete from group_user_id_tb where groupid = " + std::to_string(_groupid);
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除_id群组的群员_userid信息
int database::drop_group_user_userid(int _groupid, int _userid)
{
	std::string sql = "delete from group_user_id_tb where groupid = " + std::to_string(_groupid) + "and userid = " + std::to_string(_userid);
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}


//message_info操作
//增加message
int database::add_message(MessageInfo _message)
{
	//printf("%d\n", _user.getid());
	std::string sql = "insert into message_info_tb values ( NULL, "
		+ std::to_string(_message.getSenderId()) + ", "
		+ std::to_string(_message.getReceiverId()) + ", '"
		+ _message.getContent() + "', "
		+ std::to_string(_message.getStatus()) + ", "
		+ std::to_string(_message.getType()) + ", "
		+ std::to_string(_message.getContentKind()) + ", '"
		+ _message.getCreateTime().getString() + "' ,"
		+ std::to_string(_message.getMessageId()) + " )";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	printf("%s\n", remessage);
	return ret;
}

//搜索所有消息信息
std::vector<MessageInfo> database::search_message_all()
{
	std::string sql = "select * from message_info_tb order by createtime asc";
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<MessageInfo> ve = getMessageInfo(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve;
}

//同步消息信息
std::vector<MessageInfo> database::synchro_message(std::vector<MessageInfo> _meve)
{
	std::vector<MessageInfo> ve;
	for (auto tmpmes : _meve)
	{
		std::string sql = "select * from message_info_tb where messageid = " + std::to_string(tmpmes.getMessageId());
		int ret;
		ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
		//debug
		printf("%s\n", remessage);
		printf("nrow: %d ncol: %d\n", nrow, ncol);
		if (!nrow)//如果没有信息
		{
			add_message(tmpmes);
			ve.push_back(tmpmes);
		}
		sqlite3_free_table(result);
	}
	return ve;
}

//搜索_id信息
std::vector<MessageInfo> database::search_message_id(unsigned int _id, int _type)
{
	std::string sql = "select * from message_info_tb where receiverid = " + std::to_string(_id) + "and type = " + std::to_string(_type) + "order by createtime asc";
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<MessageInfo> ve = getMessageInfo(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve;
}

//搜索_localid信息
std::vector<MessageInfo> database::search_message_localid(unsigned int _localid)
{
	std::string sql = "select * from message_info_tb where localid = " + std::to_string(_localid) + "order by createtime asc";
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	std::vector<MessageInfo> ve = getMessageInfo(result, nrow, ncol);
	sqlite3_free_table(result);
	return ve;
}

//删除特定id的消息信息
int database::drop_message_id(unsigned int _id, int  _type)
{
	std::string sql = "delete from message_info_tb where ( senderid = " + std::to_string(_id) + " or receiverid = " + std::to_string(_id) + " ) and type = " + std::to_string(_type);
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除所有消息信息
int database::drop_message_all()
{
	std::string sql = "delete from message_info_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除信息表
int database::drop_message_tb()
{
	std::string sql = "drop table message_info_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}


//packet_info 分组信息表操作
//添加一个分组
int database::add_packet(int _groupid, std::string packet)
{
	std::string sql = "insert into packet_info_tb values ("
		+ std::to_string(_groupid) + ", '"
		+ packet + "')";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除一个分组
int database::drop_packet(int _groupid)
{
	std::string sql = "delete from packet_info_tb where packetid = "
		+ std::to_string(_groupid);
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//删除全部packet表
int database::drop_packet_all()
{
	std::string sql = "delete from packet_info_tb";
	int ret;
	ret = sqlite3_exec(db, sql.c_str(), NULL, NULL, &remessage);
	//debug
	printf("%s\n", remessage);
	return ret;
}

//查找_packetid的名称
std::string database::search_packetid(int _packetid)
{
	std::string sql = "select packetname frome packet_info_tb where packetid = "
		+ std::to_string(_packetid);
	int ret;
	ret = sqlite3_get_table(db, sql.c_str(), &result, &nrow, &ncol, &remessage);
	//debug
	printf("%s\n", remessage);
	printf("nrow: %d ncol: %d\n", nrow, ncol);
	sqlite3_free_table(result);
	return result[ncol];
}

//构造函数，创建数据库和表格
database::database(char* _username)
{
	setusername(_username);
	std::string filepath = getfile(username);
	if (SQLITE_OK == sqlite3_open(filepath.c_str(), &db))//数据库不存在
	{
		//user_info
		const char* sql = "create table if not exists user_info_tb\
					(   userid unsigned int primary key,\
						username varchar(100),\
						nickname varchar(100),\
						signature varchar(100),\
						avatorpath varchar(100),\
						status int,\
						packetid int)";
		sqlite3_exec(db, sql, NULL, NULL, &remessage);
		//debug
		printf("user_info_tb : %s\n", remessage);

		//message_info
		sql = "create table if not exists message_info_tb\
					(	localid integer primary key autoincrement,\
						senderid unsigned int,\
						receiverid unsigned int,\
						content varchar(100), \
						status int,\
						type int, \
						kind int, \
						createtime varchar(100),\
						messageid int)";
		sqlite3_exec(db, sql, NULL, NULL, &remessage);
		//debug
		printf("message_info : %s\n", remessage);

		//group_info
		sql = "create table if not exists group_info_tb\
					(	groupid unsigned int primary key,\
						nickname varchar(100),\
						avatorpath varchar(100),\
						notice varchar(100))";
		sqlite3_exec(db, sql, NULL, NULL, &remessage);
		//debug
		printf("group_info : %s\n", remessage);

		//history_info 1:group 0:user
		sql = "create table if not exists history_info_tb\
					(	localid unsigned int primary key,\
						userid unsigned int,\
						isgroup int,\
						lastid int,\
						unreadcnt int)";
		sqlite3_exec(db, sql, NULL, NULL, &remessage);
		//debug
		printf("history_info : %s\n", remessage);

		//packet_info
		sql = "create table if not exists packet_info_tb\
					(	packetid unsigned int primary key,\
						packetname varchar(100))";
		sqlite3_exec(db, sql, NULL, NULL, &remessage);
		//debug
		printf("packet_info : %s\n", remessage);

		//group_user_id_tb
		sql = "create table if not exists group_user_id_tb\
					(	groupid unsigned int,\
						userid unsigned int,\
						identity int,\
						primary key(groupid,userid))";
		sqlite3_exec(db, sql, NULL, NULL, &remessage);
		//debug
		printf("group_user_id : %s\n", remessage);

		drop_group_all();

		drop_group_user_all();

		drop_message_all();

		drop_user_all();

		drop_packet_all();
	}
}

//析构函数，关闭数据库
database::~database()
{
	sqlite3_close(db);
}