#pragma once
#include"Group.h"

//�����ƽ̨���ݣ������û����ݡ�Ⱥ�����ݵ�

class QQUserCollections {
private:
	static map<string, UserLYC*> users;
public:
	static map<string, UserLYC*>& getMap();									//��ȡ�û����ϵĹ�ϣ��
	static UserLYC* getUser(string id);										//����id������ָ���û�����
	static int nextRegisterId;												//��ʾ��һ��ע���û���id�ţ�˳λ
	static void addUser(string name, string pwd);							//�û�ע��
	static void addUserFromFile(string name, string pwd, string id);		//���ļ�����
};

class QQGroupCollections{
private:
	static map<string, GroupLYC*> groups;
public:
	static int nextGroupId;													//��ʾ��һ���½�Ⱥ��Ⱥ�ţ�˳λ
	static void deleteGroup(string id);										//��ɢȺ
	static GroupLYC* getGroup(string id);									//����id��ѯȺ
	static map<string, GroupLYC*>& getMap();								//��ȡȺ���ϵĹ�ϣ��
	static void addNewGroup(string id, string name);						//�½�Ⱥ
	static void addGroupFromFile(QQGroupLYC*);								//���ļ�����Ⱥ
};

class WechatUserCollections {
private:
	static map<string, UserLYC*> users;										//keyΪ΢�Ŷ���id
public:
	static int nextWcId;													//��һ��ע���û���΢�Ŷ���id
	static map<string, UserLYC*>& getMap();									//��ȡ�û����ϵĹ�ϣ��
	static UserLYC* getUser(string id);										//����id������ָ���û�����
	static UserLYC* getBindUser(string id);									//���ݰ�id��ѯ�û�
	static void addUser(string name, string pwd);							//�û�ע��
	static void addUserFromFile(string name, string pwd, string id);		//���ļ�����
};

class WechatGroupCollections{
private:
	static map<string, GroupLYC*> groups;
public:
	static int nextGroupId;													//��ʾ��һ���½�Ⱥ��Ⱥ�ţ�˳λ
	static void deleteGroup(string id);										//��ɢȺ
	static GroupLYC* getGroup(string id);									//����id��ѯȺ
	static map<string, GroupLYC*>& getMap();								//��ȡȺ���ϵĹ�ϣ��
	static void addNewGroup(string id, string name);						//�½�Ⱥ
	static void addGroupFromFile(WechatGroupLYC*);							//���ļ�����Ⱥ
};

class WeiboUserCollections {
private:
	static map<string, UserLYC*> users;
public:
	static map<string, UserLYC*>& getMap();									//��ȡ�û����ϵĹ�ϣ��
	static UserLYC* getUser(string id);										//����id������ָ���û�����
	static void addUser(string name, string pwd);							//�û�ע��
	static void addUserFromFile(string name, string pwd, string id);		//���ļ�����
};

class WeiboGroupCollections {
private:
	static map<string, GroupLYC*> groups;
public:
	static void deleteGroup(string id);										//��ɢȺ
	static GroupLYC* getGroup(string id);									//����id��ѯȺ
	static map<string, GroupLYC*>& getMap();								//��ȡȺ���ϵĹ�ϣ��
	static int nextGroupId;													//��ʾ��һ���½�Ⱥ��Ⱥ�ţ�˳λ
	static void addNewGroup(string id, string name);						//�½�Ⱥ
	static void addGroupFromFile(WeiboGroupLYC*);							//���ļ�����Ⱥ
};