#pragma once
#include"Group.h"

//保存各平台数据，包括用户数据、群聊数据等

class QQUserCollections {
private:
	static map<string, UserLYC*> users;
public:
	static map<string, UserLYC*>& getMap();									//获取用户集合的哈希表
	static UserLYC* getUser(string id);										//根据id返回所指的用户对象
	static int nextRegisterId;												//表示下一个注册用户的id号，顺位
	static void addUser(string name, string pwd);							//用户注册
	static void addUserFromFile(string name, string pwd, string id);		//从文件读入
};

class QQGroupCollections{
private:
	static map<string, GroupLYC*> groups;
public:
	static int nextGroupId;													//表示下一个新建群的群号，顺位
	static void deleteGroup(string id);										//解散群
	static GroupLYC* getGroup(string id);									//根据id查询群
	static map<string, GroupLYC*>& getMap();								//获取群集合的哈希表
	static void addNewGroup(string id, string name);						//新建群
	static void addGroupFromFile(QQGroupLYC*);								//从文件读入群
};

class WechatUserCollections {
private:
	static map<string, UserLYC*> users;										//key为微信独立id
public:
	static int nextWcId;													//下一个注册用户的微信独立id
	static map<string, UserLYC*>& getMap();									//获取用户集合的哈希表
	static UserLYC* getUser(string id);										//根据id返回所指的用户对象
	static UserLYC* getBindUser(string id);									//根据绑定id查询用户
	static void addUser(string name, string pwd);							//用户注册
	static void addUserFromFile(string name, string pwd, string id);		//从文件读入
};

class WechatGroupCollections{
private:
	static map<string, GroupLYC*> groups;
public:
	static int nextGroupId;													//表示下一个新建群的群号，顺位
	static void deleteGroup(string id);										//解散群
	static GroupLYC* getGroup(string id);									//根据id查询群
	static map<string, GroupLYC*>& getMap();								//获取群集合的哈希表
	static void addNewGroup(string id, string name);						//新建群
	static void addGroupFromFile(WechatGroupLYC*);							//从文件读入群
};

class WeiboUserCollections {
private:
	static map<string, UserLYC*> users;
public:
	static map<string, UserLYC*>& getMap();									//获取用户集合的哈希表
	static UserLYC* getUser(string id);										//根据id返回所指的用户对象
	static void addUser(string name, string pwd);							//用户注册
	static void addUserFromFile(string name, string pwd, string id);		//从文件读入
};

class WeiboGroupCollections {
private:
	static map<string, GroupLYC*> groups;
public:
	static void deleteGroup(string id);										//解散群
	static GroupLYC* getGroup(string id);									//根据id查询群
	static map<string, GroupLYC*>& getMap();								//获取群集合的哈希表
	static int nextGroupId;													//表示下一个新建群的群号，顺位
	static void addNewGroup(string id, string name);						//新建群
	static void addGroupFromFile(WeiboGroupLYC*);							//从文件读入群
};