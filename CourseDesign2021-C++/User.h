#pragma once
#include<iostream>
#include<string>
#include<stdbool.h>
#include<set>
#include<map>
#include"Tools.h"

using namespace std;

//预先声明
class GroupLYC;

//用户抽象类
class UserLYC
{
protected:
	string userId;								//号码id，微X平台总ID
	string nickName;							//昵称
	string birthDate;							//出生日期
	string passwd;								//密码
	int createYear;								//账号注册年份，用于计算T龄
	string address;								//所在地
	map<string, string> friendList;				//好友列表。key为id，value为昵称
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
	void setFriendRemark(string, string);					//重设好友昵称
	void addFriend(string, string);							//添加好友
	bool deleteFriend(string);								//删除好友
	virtual UserLYC* searchFriend(string) = 0;				//查询好友
	map<string, string>& getFriendList();					//获取所有好友
	virtual void getRecoFriend() = 0;						//获取推荐好友
	void addGroup(GroupLYC*);								//加入群
	virtual void exitGroup(GroupLYC*) = 0;					//退出群
	virtual void printBriefInfo();							//提供简短信息
	virtual void printDetailInfo();							//提供详细信息
};

//QQ用户类
class QQUserLYC : public UserLYC {
private:
	bool isBind;													//该id是否与微信实现了绑定
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

//微信用户类
class WechatUserLYC :public UserLYC {
private:
	string wcId;													//微信独立id
public:
	WechatUserLYC(string, string);
	WechatUserLYC(string, string, string);
	~WechatUserLYC();
	void printBriefInfo();											//提供简短信息
	void printDetailInfo();											//提供详细信息
	void getRecoFriend();
	void exitGroup(GroupLYC*);
	void bindWithQQ(string qid);									//与QQ ID进行绑定
	void resetBind();												//QQ ID解绑
	UserLYC* searchFriend(string);
	string getWechatId();											//获取微信独立id
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


