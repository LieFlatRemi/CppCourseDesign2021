#pragma once
#include<iostream>
#include<string>
#include<stdbool.h>
#include<set>
#include<map>
#include"Tools.h"

using namespace std;

//Ԥ������
class GroupLYC;

//�û�������
class UserLYC
{
protected:
	string userId;								//����id��΢Xƽ̨��ID
	string nickName;							//�ǳ�
	string birthDate;							//��������
	string passwd;								//����
	int createYear;								//�˺�ע����ݣ����ڼ���T��
	string address;								//���ڵ�
	map<string, string> friendList;				//�����б�keyΪid��valueΪ�ǳ�
public:
	UserLYC(string nickName, string passwd);
	~UserLYC();
	string getUserId();
	string getNickName();
	string getBirth();
	string getPasswd();
	int getTAge();
	int getCreateYear();
	string getAddress();
	void setUserId(string);
	void setCreateYear(int);
	void setNickName(string);
	void setBirth(string);
	void setAddress(string);
	void setPasswd(string);
	void setFriendRemark(string, string);					//��������ǳ�
	void addFriend(string, string);							//��Ӻ���
	bool deleteFriend(string);								//ɾ������
	virtual UserLYC* searchFriend(string) = 0;				//��ѯ����
	map<string, string>& getFriendList();					//��ȡ���к���
	virtual void getRecoFriend() = 0;						//��ȡ�Ƽ�����
	void addGroup(GroupLYC*);								//����Ⱥ
	virtual void exitGroup(GroupLYC*) = 0;					//�˳�Ⱥ
	virtual void printBriefInfo();							//�ṩ�����Ϣ
	virtual void printDetailInfo();							//�ṩ��ϸ��Ϣ
};

//QQ�û���
class QQUserLYC : public UserLYC {
private:
	bool isBind;													//��id�Ƿ���΢��ʵ���˰�
public:
	QQUserLYC(string, string);
	QQUserLYC(string, string, string);
	~QQUserLYC();
	void getRecoFriend();
	void exitGroup(GroupLYC*);
	UserLYC* searchFriend(string);
	void setIsBind(bool isBind);
	bool getIsBind();
};

//΢���û���
class WechatUserLYC :public UserLYC {
private:
	string wcId;													//΢�Ŷ���id
public:
	WechatUserLYC(string, string);
	WechatUserLYC(string, string, string);
	~WechatUserLYC();
	void printBriefInfo();											//�ṩ�����Ϣ
	void printDetailInfo();											//�ṩ��ϸ��Ϣ
	void getRecoFriend();
	void exitGroup(GroupLYC*);
	void bindWithQQ(string qid);									//��QQ ID���а�
	void resetBind();												//QQ ID���
	UserLYC* searchFriend(string);
	string getWechatId();											//��ȡ΢�Ŷ���id
};

class WeiboUserLYC :public UserLYC {
public:
	WeiboUserLYC(string, string);
	WeiboUserLYC(string, string, string);
	~WeiboUserLYC();
	void getRecoFriend();
	UserLYC* searchFriend(string);
	void exitGroup(GroupLYC*);
};


