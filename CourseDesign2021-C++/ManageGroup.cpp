#include "ManageGroup.h"

ManageGroupLYC::ManageGroupLYC(UserLYC* user) {
	this->user = user;
}

ManageGroupLYC::~ManageGroupLYC() {}

/*===================================QQ群=====================================*/
ManageChildGroupLYC::ManageChildGroupLYC(UserLYC* user, QQGroupLYC* father) :ManageGroupLYC(user) {
	this->father = father;
	while (true) {
		system("cls");
		cout << "========== QQ子群管理 ==========" << endl;
		cout << endl;
		cout << "====== 1.邀请成员加入子群 =======" << endl;
		cout << endl;
		cout << "========= 2.退出子群 ==========" << endl;
		cout << endl;
		cout << "========= 3.管理子群 ==========" << endl;
		cout << endl;
		cout << "========= 4.创建子群 ==========" << endl;
		cout << endl;
		cout << "==========  0.返回 ============" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			return;
		case 1:				
			addGroup();
			break;
		case 2:				
			dropGroup();
			break;
		case 3:				
			administerGroup();
			break;
		case 4:
			createGroup();
			break;
		default:
			cout << "对不起，您的输入有错误！" << endl;
			break;
		}
		cout << endl;
		cout << "请按任意键继续。。" << endl;
		getline(cin, key);
	}
}

ManageChildGroupLYC::~ManageChildGroupLYC() {}

//QQ子群中，群主可以邀请群成员进入子群
void ManageChildGroupLYC::addGroup() {
	cout << "请输入子群群号：";
	getline(cin, key);
	cout << endl;
	QQChildGroupLYC* child = father->searchChilds(key);
	if (child == NULL) {
		return;
	}
	if (child->searchMember(user->getUserId()) == NULL) {
		cout << "你不在该子群中！" << endl;
		return;
	}
	if (child->getHostId().compare(user->getUserId()) != 0) {
		cout << "您没有该子群的管理权限" << endl;
		return;
	}
	else {
		cout << "查找结果：" << endl;
		child->printInfo();
		cout << "请输入邀请的群成员id：";
		getline(cin, key);
		UserLYC* res = father->searchMember(key);
		if (res == NULL) {				//添加的成员必须已经是父群的成员
			cout << "父群中无该成员！" << endl;
		}
		else if (child->searchMember(res->getUserId()) != NULL) {
			cout << "该用户已经是此子群成员了" << endl;
		}
		else {
			child->addMember(res->getUserId());
			cout << "已成功邀请id:" << res->getUserId() << "用户加入子群！" << endl;
		}
	}
}

void ManageChildGroupLYC::dropGroup() {
	cout << "输入你想退出子群的群号：" << endl;
	getline(cin, key);
	QQChildGroupLYC* child = father->searchChilds(key);
	if (child == NULL) {
		return;
	}
	if (child->searchMember(user->getUserId()) == NULL) {
		cout << "你不是该子群群成员" << endl;
		return;
	}
	cout << "确认退出子群：" << child->getName() << "?" << endl;
	cout << "1.退出" << endl;
	cout << "0.取消" << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		child->removeMember(user->getUserId());
		if (user->getUserId().compare(child->getHostId()) == 0) {
			cout << "由于你是子群群主，退出后子群将解散" << endl;
			father->deleteChilds(child->getId());
		}
		cout << "退群成功！" << endl;
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
		break;
	}
}

void ManageChildGroupLYC::createGroup() {
	cout << "请输入群名：" << endl;
	getline(cin, key);
	cout << endl;
	father->createChilds(user->getUserId(),key);
	cout << "建群成功！" << endl;
	cout << "子群id：" << father->getChildId() - 1;
}

void ManageChildGroupLYC::administerGroup() {
	cout << "请输入子群群号：";
	getline(cin, key);
	QQChildGroupLYC* child = father->searchChilds(key);
	if (child == NULL) {
		return;
	}
	if (child->searchMember(user->getUserId()) == NULL) {
		cout << "你不是该子群群成员" << endl;
		return;
	}
	if (child->getHostId().compare(user->getUserId()) == 0) {
		//查看成员、搜索成员、T人、修改子群名
		while (true) {
			system("cls");
			cout << "群主管理\t子群id：" << child->getId() << "\t子群名：" << child->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看子群成员" << endl;
			cout << endl;
			cout << "2.搜索子群成员" << endl;
			cout << endl;
			cout << "3.踢出子群成员" << endl;
			cout << endl;
			cout << "4.修改子群名" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				child->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = child->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id" << "\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//T人
				cout << "请输入你想T出的群成员id：";
				getline(cin, key);
				if (child->searchMember(key) == NULL) {
					cout << "该用户不在子群中" << endl;
				}
				else {
					//不能T自己
					if (child->getHostId().compare(key) == 0)	
						cout << "不能踢出自己（你是群主）！" << endl;
					else {
						child->removeMember(key);
						cout << "踢出子群成员成功！" << endl;
					}
				}
				break;
			case 4:						//修改群名
				cout << "输入新的子群名：";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "子群名不能为空！" << endl;
				}
				else {
					child->setName(key);
					cout << "修改子群名成功！" << endl;
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
	else {
		cout << "您是该子群的：普通成员" << endl;
		//查看成员、搜索成员
		while (true) {
			system("cls");
			cout << "普通成员访问\t子群id：" << child->getId() << "\t子群名：" << child->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				child->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = child->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
}

QQManageGroupLYC::QQManageGroupLYC(UserLYC* user) :ManageGroupLYC(user) {
	this->manageChildGroup = NULL;
}

QQManageGroupLYC::~QQManageGroupLYC() {}

void QQManageGroupLYC::addGroup() {			//QQ群：申请加入
	cout << "请输入群号：";
	getline(cin, key);
	QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	cout << "查找结果：" << endl;
	group->printInfo();
	cout << endl;
	cout << "1.申请加群" << endl;
	cout << endl;
	cout << "0.返回" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	cout << endl;
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		//先判断是否已经是群成员
		if (group->searchMember(user->getUserId()) != NULL) {
			cout << "您已经是群成员了" << endl;
			return;
		}
		group->addRequest(user->getUserId());
		cout << "申请加群成功！请等待管理员审核。。" << endl;
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
		break;
	}
}

void QQManageGroupLYC::dropGroup() {
	cout << "输入你想退出群的群号：" << endl;
	getline(cin, key);
	QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "你不是该群群成员" << endl;
		return;
	}
	map<string, QQChildGroupLYC*>& childMap = group->getChildsMap();
	cout << "确认退出群：" << group->getName() << "?" << endl;
	cout << "1.退出" << endl;
	cout << "0.取消" << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		user->exitGroup(group);
		if (group->searchManager(user->getUserId()) != NULL) {		//如果在退出的群里是管理员，撤职
			group->deleteManager(user->getUserId());
		}
		//从所有子群中移出该成员
		for (map<string, QQChildGroupLYC*>::iterator it = childMap.begin(); it != childMap.end();) {
			QQChildGroupLYC* child = it->second;
			child->removeMember(user->getUserId());
			//是子群群主的情况
			if (child->getHostId().compare(user->getUserId()) == 0)
				childMap.erase(it++);
			else it++;
		}
		cout << "退群成功！" << endl;
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
		break;
	}
}

void QQManageGroupLYC::createGroup() {
	cout << "请输入群名：" << endl;
	getline(cin, key);
	if (key.compare("") == 0) {
		cout << "群聊名不能为空！" << endl;
		return;
	}
	cout << endl;
	QQGroupCollections::addNewGroup(key, user->getUserId());
	cout << "建群成功！" << endl;
	cout << "新群聊id：" << QQGroupCollections::nextGroupId - 1 << endl;
}

void QQManageGroupLYC::administerGroup() {
	cout << "请输入群号：";
	getline(cin, key);
	cout << endl;
	QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(key);	//向下转型
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "你不是该群群成员" << endl;
		return;
	}
	map<string, QQChildGroupLYC*>& childMap = group->getChildsMap();	//子群map
	//群主
	if (group->getHostId().compare(user->getUserId()) == 0) {
		//查看成员、搜索成员、处理申请、T人（除了自己）、添加管理员、删除管理员、修改群名、管理子群
		while (true) {
			system("cls");
			cout << "群主管理\t群id：" << group->getId() << "\t群名："<< group->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "3.管理子群" << endl;
			cout << endl;
			cout << "4.处理加群申请" << endl;
			cout << endl;
			cout << "5.踢出群成员" << endl;
			cout << endl;
			cout << "6.添加管理员" << endl;
			cout << endl;
			cout << "7.撤除管理员" << endl;
			cout << endl;
			cout << "8.修改群名" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				group->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//管理子群
				manageChildGroup = new ManageChildGroupLYC(user, group);
				break;
			case 4:
				group->handleRequest();
				break;
			case 5:							//T人
				cout << "请输入你想T出的群成员id：";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "该用户不在群中" << endl;
				}
				else {
					//不能T自己
					if (group->getHostId().compare(key) == 0)	cout << "不能踢出自己（你是群主）！" << endl;
					else {
						if (group->searchManager(key) != NULL) {		//如果T出的人是管理员，撤职
							group->deleteManager(key);
						}
						//从所有子群中移出该成员
						for (map<string, QQChildGroupLYC*>::iterator it = childMap.begin(); it != childMap.end();) {
							QQChildGroupLYC* child = it->second;
							child->removeMember(key);
							//是子群群主的情况
							if (child->getHostId().compare(key) == 0)
								childMap.erase(it++);
							else it++;
						}
						group->removeMember(key);
						cout << "踢出该群成员成功！" << endl;
					}
				}
				break;
			case 6:						//添加管理员
				cout << "输入新管理员的用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else if (key.compare(user->getUserId()) == 0) {
					cout << "你是本群群主，不能成为群管理员！" << endl;
				}
				else if (group->searchManager(key) != NULL) {
					cout << "该用户已经是群管理员了" << endl;
				}
				else {
					group->addManager(key);
					cout << "已成功令id:" << key << "的用户成为管理员" << endl;
				}
				break;
			case 7:						//删除管理员
				cout << "请输入管理员用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (group->searchManager(key) == NULL) {
					cout << "该用户不是本群的管理员" << endl;
				}
				else {
					group->deleteManager(key);
					cout << "已成功撤除id:" << key << "用户的管理员资格！" << endl;
				}
				break;
			case 8:						//修改群名
				cout << "输入新的群名：";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "新群名不能为空！" << endl;
				}
				else {
					group->setName(key);
					cout << "修改群名成功！" << endl;
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
	//管理员
	else if (group->searchManager(user->getUserId())) {
		//查看成员、搜索成员、处理申请、T人（只能T普通成员）、管理子群
		while (true) {
			system("cls");
			cout << "管理员管理\t群id：" << group->getId() << "\t群名：" << group->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "3.管理子群" << endl;
			cout << endl;
			cout << "4.处理加群申请" << endl;
			cout << endl;
			cout << "5.踢出群成员" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				group->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//管理子群
				manageChildGroup = new ManageChildGroupLYC(user, group);
				break;
			case 4:							
				group->handleRequest();
				break;
			case 5:							//T人
				cout << "请输入你想T出的群成员id：";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "该用户不在群中" << endl;
				}
				else {
					//不能T群主和其他管理员
					if (group->getHostId().compare(key) == 0)	cout << "不能踢出群主！" << endl;
					else if (user->getUserId().compare(key) == 0)	cout << "不能踢出自己！" << endl;
					else if (group->searchManager(key))	cout << "不能踢出其他管理员！" << endl;
					else {
						group->removeMember(key);
						//从所有子群中移出该成员
						for (map<string, QQChildGroupLYC*>::iterator it = childMap.begin(); it != childMap.end();) {
							QQChildGroupLYC* child = it->second;
							child->removeMember(key);
							//是子群群主的情况
							if (child->getHostId().compare(key) == 0)
								childMap.erase(it++);
							else it++;
						}
						cout << "踢出该群成员成功！" << endl;
					}
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
	//普通成员
	else {
		while (true) {
			system("cls");
			cout << "普通成员访问\t群id：" << group->getId() << "\t群名：" << group->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "3.管理子群" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				group->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//管理子群
				manageChildGroup = new ManageChildGroupLYC(user, group);
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
}

/*-----------------------------Wechat-------------------------------------*/

WechatManageGroupLYC::WechatManageGroupLYC(UserLYC* user) :ManageGroupLYC(user) {
	w_user = (WechatUserLYC*)user;
}

WechatManageGroupLYC::~WechatManageGroupLYC() {}

//微信群：邀请加入,且任何群成员都可以邀请用户进群
void WechatManageGroupLYC::addGroup() {			
	cout << "请输入微信群群号：";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WechatGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	else {
		cout << "查找结果：" << endl;
		group->printInfo();
		if (group->searchMember(w_user->getWechatId()) == NULL) {
			cout << "你不在该微信群中" << endl;
			return;
		}
		cout << endl;
		cout << "请输入邀请的用户id：";
		getline(cin, key);
		WechatUserLYC* res = (WechatUserLYC*)WechatUserCollections::getUser(key);
		if (res == NULL) {
			cout << "未查找到此用户！" << endl;
			return;
		}
		else if (group->searchMember(res->getWechatId()) != NULL) {
			cout << "该用户已经是此微信群成员了" << endl;
		}
		else {
			group->addMember(res->getWechatId());
			cout << "已成功邀请id:" << res->getWechatId() << "用户加入微信群！" << endl;
		}
	}
}

void WechatManageGroupLYC::dropGroup() {
	cout << "输入你想退出群的群号：" << endl;
	getline(cin, key);
	GroupLYC* group = WechatGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(w_user->getWechatId()) == NULL) {
		cout << "你不是该群群成员" << endl;
		return;
	}
	cout << "确认退出群：" << group->getName() << "?" << endl;
	cout << "1.退出" << endl;
	cout << "0.取消" << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		user->exitGroup(group);
		cout << "退群成功！" << endl;
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
		break;
	}
}

void WechatManageGroupLYC::createGroup() {
	cout << "请输入群名：" << endl;
	getline(cin, key);
	if (key.compare("") == 0) {
		cout << "群聊名不能为空！" << endl;
		return;
	}
	cout << endl;
	WechatGroupCollections::addNewGroup(key, w_user->getWechatId());
	cout << "建群成功！" << endl;
	cout << "新群聊id：" << WechatGroupCollections::nextGroupId - 1 << endl;
}

void WechatManageGroupLYC::administerGroup() {
	cout << "请输入群号：";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WechatGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(w_user->getWechatId()) == NULL) {
		cout << "你不是该群群成员" << endl;
		return;
	}
	//群主
	if (group->getHostId().compare(w_user->getWechatId()) == 0) {
		//查看成员、搜索成员、T人（除了自己）、修改群名
		while (true) {
			system("cls");
			cout << "群主管理\t群id：" << group->getId() << "\t群名：" << group->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "3.踢出群成员" << endl;
			cout << endl;
			cout << "4.修改群名" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				group->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//T人
				cout << "请输入你想T出的群成员id：";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "该用户不在群中" << endl;
				}
				else {
					//不能T自己
					if (group->getHostId().compare(key) == 0)	cout << "不能踢出自己（你是群主）！" << endl;
					else {
						group->removeMember(key);
						cout << "踢出该群成员成功！" << endl;
					}
				}
				break;
			case 4:						//修改群名
				cout << "输入新的群名：";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "新群名不能为空！" << endl;
				}
				else {
					group->setName(key);
					cout << "修改群名成功！" << endl;
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
	//普通成员
	else {
		while (true) {
			system("cls");
			cout << "普通成员访问\t群id：" << group->getId() << "\t群名：" << group->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				group->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
}

/*-----------------------------Weibo-------------------------------------*/

WeiboManageGroupLYC::WeiboManageGroupLYC(UserLYC* user) :ManageGroupLYC(user) {
}

WeiboManageGroupLYC::~WeiboManageGroupLYC() {}

void WeiboManageGroupLYC::addGroup() {
	cout << "请输入微博群群号：";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WeiboGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	else {
		cout << "查找结果：" << endl;
		group->printInfo();
		if (group->searchMember(user->getUserId()) == NULL) {
			cout << "你不在该微博群中" << endl;
			return;
		}
		if (group->getHostId().compare(user->getUserId()) != 0){
			cout << "您不是该群群主，无邀请成员权限！" << endl;
			return;
		}
		cout << endl;
		cout << "请输入邀请的用户id：";
		getline(cin, key);
		UserLYC* res = WeiboUserCollections::getUser(key);
		if (res == NULL) {
			cout << "未查找到此用户！" << endl;
			return;
		}
		else if (group->searchMember(res->getUserId()) != NULL) {
			cout << "该用户已经是此微博群成员了" << endl;
		}
		else {
			group->addMember(res->getUserId());
			cout << "已成功邀请id:" << res->getUserId() << "用户加入微博群！" << endl;
		}
	}
}

void WeiboManageGroupLYC::dropGroup() {
	cout << "输入你想退出群的群号：" << endl;
	getline(cin, key);
	GroupLYC* group = WeiboGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "你不是该群群成员" << endl;
		return;
	}
	cout << "确认退出群：" << group->getName() << "?" << endl;
	cout << "1.退出" << endl;
	cout << "0.取消" << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		user->exitGroup(group);
		cout << "退群成功！" << endl;
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
		break;
	}
}

void WeiboManageGroupLYC::createGroup() {
	cout << "请输入群名：" << endl;
	getline(cin, key);
	if (key.compare("") == 0) {
		cout << "群聊名不能为空！" << endl;
		return;
	}
	cout << endl;
	WeiboGroupCollections::addNewGroup(key, user->getUserId());
	cout << "建群成功！" << endl;
	cout << "新群聊id：" << WeiboGroupCollections::nextGroupId - 1 << endl;
}

void WeiboManageGroupLYC::administerGroup() {
	cout << "请输入群号：";
	getline(cin, key);
	cout << endl;
	GroupLYC* group = WeiboGroupCollections::getGroup(key);
	if (group == NULL) {
		return;
	}
	if (group->searchMember(user->getUserId()) == NULL) {
		cout << "你不是该群群成员" << endl;
		return;
	}
	//群主
	if (group->getHostId().compare(user->getUserId()) == 0) {
		//查看成员、搜索成员、T人（除了自己）、修改群名
		while (true) {
			system("cls");
			cout << "群主管理\t群id：" << group->getId() << "\t群名：" << group->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "3.踢出群成员" << endl;
			cout << endl;
			cout << "4.修改群名" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				group->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			case 3:							//T人
				cout << "请输入你想T出的群成员id：";
				getline(cin, key);
				if (group->searchMember(key) == NULL) {
					cout << "该用户不在群中" << endl;
				}
				else {
					//不能T自己
					if (group->getHostId().compare(key) == 0)	cout << "不能踢出自己（你是群主）！" << endl;
					else {
						group->removeMember(key);
						cout << "踢出该群成员成功！" << endl;
					}
				}
				break;
			case 4:						//修改群名
				cout << "输入新的群名：";
				getline(cin, key);
				if (Tools::isEmptyString(key)) {
					cout << "新群名不能为空！" << endl;
				}
				else {
					group->setName(key);
					cout << "修改群名成功！" << endl;
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
	//普通成员
	else {
		while (true) {
			system("cls");
			cout << "普通成员访问\t群id：" << group->getId() << "\t群名：" << group->getName() << endl;
			//查看成员、搜索成员、建子群
			cout << endl;
			cout << "1.查看群成员" << endl;
			cout << endl;
			cout << "2.搜索群成员" << endl;
			cout << endl;
			cout << "0.返回" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				return;
			case 1:							//查看群成员
				group->getMembers();
				cout << endl;
				break;
			case 2:							//搜索群成员
				cout << "输入用户id：";
				getline(cin, key);
				cur = group->searchMember(key);
				if (cur == NULL) {
					cout << "群中无此用户" << endl;
				}
				else {
					cout << "查找结果：" << endl;
					cout << "id\t昵称" << endl;
					cur->printBriefInfo();
				}
				break;
			default:
				cout << "您的输入有误，请重新输入！" << endl;
				break;
			}
			cout << endl;
			cout << "请按任意键继续。。" << endl;
			getline(cin, key);
		}
	}
}