#pragma once
#include"User.h"

//Ⱥ������
class GroupLYC
{
protected:
	string id;											//Ⱥ��
	string hostId;										//Ⱥ��id
	set<string> members;								//Ⱥ��Ա
	string name;										//Ⱥ��
public:
	GroupLYC(string hostId, string name);
	~GroupLYC();
	string getId();
	string getHostId();
	void setName(string name);							//����Ⱥ��
	string getName();									//��ȡȺ��
	set<string>& getMembersSet();						//��ȡmembers��Set	
	virtual void getMembers() = 0;						//��ӡȫ��Ⱥ��Ա
	void addMember(string id);							//���Ⱥ��Ա
	void removeMember(string id);						//ɾ��Ⱥ��Ա
	virtual UserLYC* searchMember(string id) = 0;		//����id��ѯȺ��Ա
	void printInfo();									//��ӡȺ��Ϣ
};

//=====================QQȺ���й���Ա�ƶȣ�����ʱ�����飨��Ⱥ������Ⱥ��������ƶ�==========================

class QQChildGroupLYC;									//Ԥ������

//QQȺ
class QQGroupLYC : public GroupLYC {
private:
	set<string> managers;								//����Ա
	set<string> requests;								//��Ⱥ����
	map<string, QQChildGroupLYC*> childs;				//��Ⱥ
	int childId = 101;									//��Ⱥ��
public:
	QQGroupLYC(string, string);
	QQGroupLYC(string, string, string);
	~QQGroupLYC();
	void getMembers();
	UserLYC* searchMember(string id);
	void setChildId(int id);
	int getChildId();
	QQChildGroupLYC* searchChilds(string id);			//������Ⱥ
	void createChilds(string hostId, string name);		//�½���Ⱥ
	void deleteChilds(string id);						//��ɢ��Ⱥ
	void addChildsFromFile(QQChildGroupLYC* group);		//���ļ�¼����Ⱥ
	set<string>& getManagersSet();
	set<string>& getRequestsSet();
	map<string, QQChildGroupLYC*>& getChildsMap();
	void addManager(string id);							//��ӹ���Ա
	void deleteManager(string id);						//ɾ������Ա
	bool searchManager(string id);						//��֤һ���û��Ƿ�Ϊ����Ա
	void passRequest(string id);						//ͨ����Ⱥ����
	void addRequest(string id);							//��Ӽ�Ⱥ����
	void handleRequest();								//�����Ⱥ����
};

//QQ��Ⱥ
class QQChildGroupLYC : public GroupLYC {
private:
	string father;					//��Ⱥ
public:
	QQChildGroupLYC(string, string, QQGroupLYC*);
	QQChildGroupLYC(string, string, string, QQGroupLYC*);
	~QQChildGroupLYC();
	void getMembers();
	string getFather();
	UserLYC* searchMember(string id);
}; 

/*=====================΢��Ⱥ������Ⱥ����Ȩ��ֻ��������Ⱥ==========================*/

class WechatGroupLYC : public GroupLYC {
public:
	WechatGroupLYC(string, string);
	WechatGroupLYC(string, string, string);
	~WechatGroupLYC();
	void getMembers();
	UserLYC* searchMember(string id);
};

/*=====================΢��Ⱥ������Ⱥ����Ȩ��Ⱥ��������Ⱥ==========================*/

class WeiboGroupLYC :public GroupLYC {
public:
	WeiboGroupLYC(string, string);
	WeiboGroupLYC(string, string, string);
	~WeiboGroupLYC();
	void getMembers();
	UserLYC* searchMember(string id);
};