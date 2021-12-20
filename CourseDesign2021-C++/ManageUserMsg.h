#pragma once
#include"Data.h"
using namespace std;

//管理用户个人信息类

class ManageUserMsgLYC
{
protected:
	UserLYC* user;
	string key;								//获取用户输入
public:
	ManageUserMsgLYC(UserLYC* );
	~ManageUserMsgLYC(); 
	void showDetailedData();				//个人详细资料
	void changeUserData();					//修改基本资料
	void changePasswd();					//修改密码
	virtual void registerOtherUser();		//开通其他平台账号
};

class WechatManageUserMsgLYC : public ManageUserMsgLYC
{
public:
	WechatManageUserMsgLYC(UserLYC*);
	~WechatManageUserMsgLYC();
	void registerOtherUser();
	void manageBind();						//管理绑定账号
};