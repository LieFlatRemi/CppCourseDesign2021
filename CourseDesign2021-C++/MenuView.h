#pragma once
#include<iostream>
#include<string>
#include"Tools.h"
#include"Data.h"
#include"ManageUserMsg.h"
#include"ManageGroup.h"
#include"ManageFriend.h"
using namespace std;

//΢X�˵������࣬ʵ�ָ����˵����������û����������ҵ����
class MenuViewLYC 
{
protected:
	string key;										//��ȡ�û�������
	UserLYC* user;
	ManageUserMsgLYC* manageUserMsg;				//�������Ϲ���
	ManageFriendLYC* manageFriend;					//���ѹ���
	ManageGroupLYC* manageGroup;					//Ⱥ����
public:
	MenuViewLYC();
	~MenuViewLYC();
	void showFriendMenu();							//���ѹ���
	virtual void showGroupMenu() = 0;				//Ⱥ����
	virtual void registerMenu() = 0;				//�û���ͨ����
	virtual bool loginMenu() = 0;					//�û���¼����
	virtual bool userMenu(UserLYC*) = 0;			//�û�����
	virtual void showUserMsgMenu();					//�����û�������Ϣ(�޸����ϡ�����ƽ̨�˺ſ�ͨ)
	virtual bool changeApp() = 0;					//�л�Ӧ��
};

class QQViewLYC : public MenuViewLYC
{
public:
	QQViewLYC(string);
	~QQViewLYC();
	void showGroupMenu();					//Ⱥ����
	void registerMenu(); 					//�û���ͨ����
	bool loginMenu();						//�û���¼����
	bool userMenu(UserLYC*);				//�û�����
	bool changeApp();						//�л�Ӧ��
};

class WechatViewLYC : public MenuViewLYC
{
public:
	WechatViewLYC(string);
	~WechatViewLYC();
	void showGroupMenu();					//Ⱥ����
	void registerMenu(); 					//�û���ͨ����
	bool loginMenu();						//�û���¼����
	void showUserMsgMenu();
	bool userMenu(UserLYC*);				//�û�����
	bool changeApp();						//�л�Ӧ��
};

class WeiboViewLYC : public MenuViewLYC
{
public:
	WeiboViewLYC(string);
	~WeiboViewLYC();
	void showGroupMenu();					//Ⱥ����
	void registerMenu(); 					//�û���ͨ����
	bool loginMenu();						//�û���¼����
	bool userMenu(UserLYC*);				//�û�����
	bool changeApp();						//�л�Ӧ��
};

//�ܿͻ���
class Client {
private:
	string key;
	MenuViewLYC* menu;
public:
	Client();
	~Client();
};