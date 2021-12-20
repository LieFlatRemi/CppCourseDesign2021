#pragma once
#include"Data.h"
//管理好友

class ManageFriendLYC {
protected:
	string key;
	UserLYC* user;
public:
	ManageFriendLYC(UserLYC*);
	~ManageFriendLYC();
	virtual void addFriend() = 0;			//添加好友
	virtual void searchFriend() = 0;		//查询好友
	virtual void getAllFriends() = 0;		//获取所有好友
	void setFriendRemark();					//修改昵称
	void deleteFriend();					//删除好友
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