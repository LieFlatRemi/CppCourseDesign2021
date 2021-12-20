#pragma once
#include"Data.h"
//管理群

class ManageGroupLYC {
protected:
	UserLYC* user;							//使用功能的用户指针
	UserLYC* cur = NULL;					//群查找结果的用户指针
	string key;
public:
	ManageGroupLYC(UserLYC*);
	~ManageGroupLYC();
	virtual void addGroup() = 0;			//加入群聊
	virtual void dropGroup() = 0;			//退出群聊
	virtual void administerGroup() = 0;		//管理群聊
	virtual void createGroup() = 0;			//创建群聊
};

//QQ独有的子群类
class ManageChildGroupLYC : public ManageGroupLYC {
private:
	QQGroupLYC* father;
public:
	ManageChildGroupLYC(UserLYC* ,QQGroupLYC* );
	~ManageChildGroupLYC();
	void addGroup();						//邀请群成员加入子群
	void dropGroup();
	void administerGroup();
	void createGroup();
};

//QQ群类
class QQManageGroupLYC : public ManageGroupLYC {
private:
	ManageChildGroupLYC* manageChildGroup = NULL;
public:
	QQManageGroupLYC(UserLYC *);
	~QQManageGroupLYC();
	void addGroup();
	void dropGroup();
	void administerGroup();
	void createGroup();
};

//微信群类
class WechatManageGroupLYC : public ManageGroupLYC {
private:
	WechatUserLYC* w_user = NULL;
public:
	WechatManageGroupLYC(UserLYC*);
	~WechatManageGroupLYC();
	void addGroup();
	void dropGroup();
	void administerGroup();
	void createGroup();
};

//微博群类
class WeiboManageGroupLYC : public ManageGroupLYC {
public:
	WeiboManageGroupLYC(UserLYC*);
	~WeiboManageGroupLYC();
	void addGroup();
	void dropGroup();
	void administerGroup();
	void createGroup();
};