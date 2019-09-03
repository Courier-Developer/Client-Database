//
// Created by Ԭ���� on 2019-08-31.
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


	//user_info ���ѱ����
	int add_user(UserInfo _user);//���һ���û���Ϣ

	int update_user(std::vector<UserInfo> _userve);//��Ӷ����Ϣ�Ḳ��֮ǰ��Ϣ

	int synchro_user(std::vector<UserInfo> _userve);//��Ӷ���û���Ϣ���Ѵ��ڵ��û���Ϣ����

	std::vector<UserInfo> search_user_all();//����ȫ��������Ϣ

	std::vector<UserInfo> search_user_id(int _userid);//����_userid���û���Ϣ

	int change_user_packet(int _userid, int _packetid);//����_userid���û�����Ϊ_packetid

	int drop_user_all();//ɾ�������û���Ϣ

	int drop_user_id(unsigned int _id);//ɾ��_id�û���Ϣ

	int drop_user_tb();//ɾ��user_info_tb


	//group_info Ⱥ������
	int add_group(GroupInfo _group);//���һ��Ⱥ����Ϣ

	int update_group(std::vector<GroupInfo> _groupve);//���һ��Ⱥ����Ϣ

	void add_group_user(unsigned int _groupid, unsigned int _userid);//Ⱥ������һ���û�

	std::vector<GroupInfo> search_group_all();//��������Ⱥ����Ϣ

	GroupInfo search_group_id(int _groupid);//����_groupid��Ⱥ����Ϣ

	int drop_group_all();//ɾ������Ⱥ����Ϣ

	int drop_group_id(unsigned int _id);//ɾ��_id��Ⱥ����Ϣ

	int drop_group_user(unsigned int _groupid, unsigned int _userid);//ɾ��Ⱥ���е�_userid���ˣ��������group����Ϣ

	int drop_group_tb();//ɾ������group��

	std::vector<GroupInfo> getGroupInfo(char** result, int nrow, int ncol);

	//message_info ��Ϣ�����
	int add_message(MessageInfo _message);//���һ����Ϣ��Ϣ

	std::vector<MessageInfo> search_message_all();//��ѯ������Ϣ��¼

	std::vector<MessageInfo> search_message_id(unsigned int _id, int _type);//��ѯ_id����Ϣ��¼ type1Ϊ���� 2ΪȺ��

	std::vector<MessageInfo> search_message_localid(unsigned int _localid);//��ѯ����idΪ_localid����Ϣ��Ϣ��localid����
	
	std::vector<MessageInfo> synchro_message(std::vector<MessageInfo> _meve);//ͬ����Ϣ��Ϣ�����������ӵ���Ϣ

	int drop_message_all();//ɾ��������Ϣ��Ϣ

	int drop_message_id(unsigned int _id, int _type);//ɾ��_id _type����Ϣ��Ϣ

	int drop_message_tb();//ɾ��������Ϣ��Ϣ��


	//packet_info ������Ϣ�����
	int add_packet(int _groupid, std::string packet);//����һ���û�����

	int drop_packet(int _groupid);//ɾ��_groupid���û�����

	std::string search_packetid(int _packetid);//����_packetid������

	int drop_packet_all();//ɾ��ȫ��packet��

	//history_info ��ʷ��Ϣ�����
	int add_history(unsigned int _userid, int _isgroup);

	int change_history(unsigned int _userid, int _isgroup, int _lastid);

	std::pair<int, int> search_history(unsigned int _userid, int _isgroup);


	//group_user_id ����
	int add_group_user_id(int _groupid, int _userid);//�����û�Ⱥ����Ϣ

	int change_group_identity(int _groupid, int _userid, int _identity);//�޸�ȺԱ���

	std::vector<unsigned int> search_group_user_id(int _groupid);//����_groupid��ȫ��ȺԱid
	
	int drop_group_user_all();//ɾ������Ⱥ���û���Ϣ

	int drop_group_user_groupid(int _groupid);//ɾ��_groupid��Ⱥ���û���Ϣ

	int drop_group_user_userid(int _groupid, int _userid);//��_groupid��ɾ��_userid
};

#endif //COURIER_CLIENT_DATABASE_H