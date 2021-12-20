#pragma once
#include<iostream>
#include<string>
#include"Tools.h"
#include"Data.h"
#include"ManageUserMsg.h"
#include"ManageGroup.h"
#include"ManageFriend.h"
using namespace std;

//微X菜单抽象类，实现各级菜单，并根据用户的输入调用业务函数
class MenuViewLYC 
{
protected:
	string key;										//读取用户的输入
	UserLYC* user;
	ManageUserMsgLYC* manageUserMsg;				//个人资料管理
	ManageFriendLYC* manageFriend;					//好友管理
	ManageGroupLYC* manageGroup;					//群管理
public:
	MenuViewLYC();
	~MenuViewLYC();
	void showFriendMenu();							//好友管理
	virtual void showGroupMenu() = 0;				//群管理
	virtual void registerMenu() = 0;				//用户开通界面
	virtual bool loginMenu() = 0;					//用户登录界面
	virtual bool userMenu(UserLYC*) = 0;			//用户界面
	virtual void showUserMsgMenu();					//管理用户个人信息(修改资料、其他平台账号开通)
	virtual bool changeApp() = 0;					//切换应用
};

class QQViewLYC : public MenuViewLYC
{
public:
	QQViewLYC(string);
	~QQViewLYC();
	void showGroupMenu();					//群管理
	void registerMenu(); 					//用户开通界面
	bool loginMenu();						//用户登录界面
	bool userMenu(UserLYC*);				//用户界面
	bool changeApp();						//切换应用
};

class WechatViewLYC : public MenuViewLYC
{
public:
	WechatViewLYC(string);
	~WechatViewLYC();
	void showGroupMenu();					//群管理
	void registerMenu(); 					//用户开通界面
	bool loginMenu();						//用户登录界面
	void showUserMsgMenu();
	bool userMenu(UserLYC*);				//用户界面
	bool changeApp();						//切换应用
};

class WeiboViewLYC : public MenuViewLYC
{
public:
	WeiboViewLYC(string);
	~WeiboViewLYC();
	void showGroupMenu();					//群管理
	void registerMenu(); 					//用户开通界面
	bool loginMenu();						//用户登录界面
	bool userMenu(UserLYC*);				//用户界面
	bool changeApp();						//切换应用
};

//总客户端
class Client {
private:
	string key;
	MenuViewLYC* menu;
public:
	Client();
	~Client();
};