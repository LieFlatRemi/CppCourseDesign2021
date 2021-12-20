#pragma once
#include"Data.h"
using namespace std;

//�����û�������Ϣ��

class ManageUserMsgLYC
{
protected:
	UserLYC* user;
	string key;								//��ȡ�û�����
public:
	ManageUserMsgLYC(UserLYC* );
	~ManageUserMsgLYC(); 
	void showDetailedData();				//������ϸ����
	void changeUserData();					//�޸Ļ�������
	void changePasswd();					//�޸�����
	virtual void registerOtherUser();		//��ͨ����ƽ̨�˺�
};

class WechatManageUserMsgLYC : public ManageUserMsgLYC
{
public:
	WechatManageUserMsgLYC(UserLYC*);
	~WechatManageUserMsgLYC();
	void registerOtherUser();
	void manageBind();						//������˺�
};