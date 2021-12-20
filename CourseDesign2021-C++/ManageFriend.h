#pragma once
#include"Data.h"
//�������

class ManageFriendLYC {
protected:
	string key;
	UserLYC* user;
public:
	ManageFriendLYC(UserLYC*);
	~ManageFriendLYC();
	virtual void addFriend() = 0;			//��Ӻ���
	virtual void searchFriend() = 0;		//��ѯ����
	virtual void getAllFriends() = 0;		//��ȡ���к���
	void setFriendRemark();					//�޸��ǳ�
	void deleteFriend();					//ɾ������
};

class QQManageFriendLYC :public ManageFriendLYC
{
private:
	UserLYC* fri = NULL;
public:
	QQManageFriendLYC(UserLYC*);
	~QQManageFriendLYC();
	void addFriend();
	void searchFriend();
	void getAllFriends();
};

class WechatManageFriendLYC : public ManageFriendLYC {
private:
	WechatUserLYC* fri = NULL;
public:
	WechatManageFriendLYC(UserLYC*);
	~WechatManageFriendLYC();
	void addFriend();
	void searchFriend();
	void getAllFriends();
};

class WeiboManageFriendLYC : public ManageFriendLYC {
private:
	UserLYC* fri = NULL;
public:
	WeiboManageFriendLYC(UserLYC*);
	~WeiboManageFriendLYC();
	void addFriend();
	void searchFriend();
	void getAllFriends();
};