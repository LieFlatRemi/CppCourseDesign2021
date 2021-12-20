#include"ManageFriend.h"

ManageFriendLYC::ManageFriendLYC(UserLYC* user) {
	this->user = user;
}

ManageFriendLYC::~ManageFriendLYC() {}

void ManageFriendLYC::setFriendRemark() {
	cout << "请输入好友id：";
	getline(cin, key);
	//查询
	if (user->searchFriend(key) == NULL) {
		cout << "这个用户不是你的好友！" << endl;
		return;
	}
	cout << endl;
	cout << "请输入修改后的备注名:(不输入表示无备注)";
	string remark; 
	getline(cin, remark);
	user->setFriendRemark(key, remark);
	cout << endl;
	cout << "修改成功！" << endl;
}

void ManageFriendLYC::deleteFriend() {
	cout << "请输入好友id：";
	getline(cin, key);
	if (user->deleteFriend(key)) {
		cout << "删除好友成功！" << endl;
	}
	else cout << "删除好友失败！" << endl;
}

/*----------------------------------QQ------------------------------------------*/

QQManageFriendLYC::QQManageFriendLYC(UserLYC* user) :ManageFriendLYC(user) {
}

QQManageFriendLYC::~QQManageFriendLYC() {}

void QQManageFriendLYC::addFriend() {
	cout << "请输入你想添加的好友id：";
	getline(cin, key);
	//不能添加自己为好友
	if (key.compare(user->getUserId()) == 0) {
		cout << "你不能添加自己为好友！" << endl;
		return;
	}
	if (QQUserCollections::getUser(key) == NULL) {
		cout << "未查找到此用户！" << endl;
		return;
	}
	else if (user->searchFriend(key) != NULL) {
		cout << "该用户已经是你的好友了" << endl;
	}
	else {
		string remark;
		cout << "输入好友的备注名（你也可以不输入，即无备注）：";
		getline(cin, remark);
		user->addFriend(key, remark);
		cout << "添加好友成功！" << endl;
	}
}

void QQManageFriendLYC::searchFriend() {
	cout << "请输入好友id：";
	getline(cin, key);
	if (user->searchFriend(key) == NULL) {
		cout << "这个用户不是你的好友！" << endl;
		return;
	}
	string friId = key;
	cout << endl;
	cout << "请输入你希望执行的操作：" << endl;
	cout << endl;
	cout << "====1.查询详细信息====" << endl;
	cout << endl;
	cout << "=====2.修改备注名=====" << endl;
	cout << endl;
	cout << "=====3.删除该好友=====" << endl;
	cout << endl;
	cout << "======= 0.返回 =======" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << endl;
		cout << "好友详细信息：" << endl;
		fri = QQUserCollections::getUser(friId);
		fri->printDetailInfo();
		break;
	case 2:
		cout << "输入新备注名：";
		getline(cin, key);
		user->setFriendRemark(friId, key);
		cout << "修改成功！" << endl;
		break;
	case 3:
		cout << "确认要删除该好友吗？" << endl;
		cout << "1.删除\t0.再考虑一下。。" << endl;
		cout << "请输入你的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			break;
		case 1:
			if (user->deleteFriend(friId)) {
				cout << "删除好友成功！" << endl;
			}
			break;
		default:
			cout << "对不起，您的输入有错误！" << endl;
		}
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
	}
}

void QQManageFriendLYC::getAllFriends() {
	map<string, string>& fris = user->getFriendList();
	if (fris.size() == 0) {
		cout << "您暂未添加任何好友" << endl;
		return;
	}
	cout << "========好友列表：========" << endl;
	cout << endl;
	cout << "\tid\t昵称" << endl;
	//遍历map
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		fri = QQUserCollections::getUser(it->first);
		cout << "\t" << fri->getUserId() << "\t" << fri->getNickName() << " ";
		if (it->second.compare("") == 0) {
			cout << "(无备注名)" << endl;
		}
		else cout <<"(备注名："<< it->second << ")" << endl;
		cout << endl;
	}
}

/*----------------------------------Wechat------------------------------------------*/

WechatManageFriendLYC::WechatManageFriendLYC(UserLYC* user) :ManageFriendLYC(user) {
}

WechatManageFriendLYC::~WechatManageFriendLYC() {}

void WechatManageFriendLYC::addFriend() {
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	cout << "请输入你想添加的好友微信id：";
	getline(cin, key);
	//不能添加自己为好友
	if (key.compare(w_user->getWechatId()) == 0) {
		cout << "你不能添加自己为好友！" << endl;
		return;
	}
	if (WechatUserCollections::getUser(key) == NULL) {
		cout << "未查找到此用户！" << endl;
		return;
	}
	else if (user->searchFriend(key) != NULL) {
		cout << "该用户已经是你的好友了" << endl;
	}
	else {
		string remark;
		cout << "输入好友的备注名（你也可以不输入，即无备注）：";
		getline(cin, remark);
		user->addFriend(key, remark);
		cout << "添加好友成功！" << endl;
	}
}

void WechatManageFriendLYC::searchFriend() {
	cout << "请输入好友微信id：";
	getline(cin, key);
	if (user->searchFriend(key) == NULL) {
		cout << "这个用户不是你的好友！" << endl;
		return;
	}
	string friId = key;
	cout << endl;
	cout << "请输入你希望执行的操作：" << endl;
	cout << endl;
	cout << "====1.查询详细信息====" << endl;
	cout << endl;
	cout << "=====2.修改备注名=====" << endl;
	cout << endl;
	cout << "=====3.删除该好友=====" << endl;
	cout << endl;
	cout << "======= 0.返回 =======" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << endl;
		cout << "好友详细信息：" << endl;
		fri = (WechatUserLYC*)WechatUserCollections::getUser(friId);
		fri->printDetailInfo();
		break;
	case 2:
		cout << "输入新备注名：";
		getline(cin, key);
		user->setFriendRemark(friId, key);
		cout << "修改成功！" << endl;
		break;
	case 3:
		cout << "确认要删除该好友吗？" << endl;
		cout << "1.删除\t0.再考虑一下。。" << endl;
		cout << "请输入你的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			break;
		case 1:
			if (user->deleteFriend(friId)) {
				cout << "删除好友成功！" << endl;
			}
			break;
		default:
			cout << "对不起，您的输入有错误！" << endl;
		}
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
	}
}

void WechatManageFriendLYC::getAllFriends() {
	map<string, string>& fris = user->getFriendList();
	if (fris.size() == 0) {
		cout << "您暂未添加任何好友" << endl;
		return;
	}
	cout << "========好友列表：========" << endl;
	cout << endl;
	cout << "\tid\t昵称" << endl;
	//遍历map
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		fri = (WechatUserLYC*)WechatUserCollections::getUser(it->first);
		cout << "\t" << fri->getWechatId() << "\t" << fri->getNickName() << " ";
		if (it->second.compare("") == 0) {
			cout << "(无备注名)" << endl;
		}
		else cout << "(备注名：" << it->second << ")" << endl;
		cout << endl;
	}
}

/*----------------------------------Weibo-----------------------------------------*/

WeiboManageFriendLYC::WeiboManageFriendLYC(UserLYC* user) :ManageFriendLYC(user) {
}

WeiboManageFriendLYC::~WeiboManageFriendLYC() {}

void WeiboManageFriendLYC::addFriend() {
	cout << "请输入你想添加的好友id：";
	getline(cin, key);
	//不能添加自己为好友
	if (key.compare(user->getUserId()) == 0) {
		cout << "你不能添加自己为好友！" << endl;
		return;
	}
	if (WeiboUserCollections::getUser(key) == NULL) {
		cout << "未查找到此用户！" << endl;
		return;
	}
	else if (user->searchFriend(key) != NULL) {
		cout << "该用户已经是你的好友了" << endl;
	}
	else {
		string remark;
		cout << "输入好友的备注名（你也可以不输入，即无备注）：";
		getline(cin, remark);
		user->addFriend(key, remark);
		cout << "添加好友成功！" << endl;
	}
}

void WeiboManageFriendLYC::searchFriend() {
	cout << "请输入好友id：";
	getline(cin, key);
	if (user->searchFriend(key) == NULL) {
		cout << "这个用户不是你的好友！" << endl;
		return;
	}
	string friId = key;
	cout << endl;
	cout << "请输入你希望执行的操作：" << endl;
	cout << endl;
	cout << "====1.查询详细信息====" << endl;
	cout << endl;
	cout << "=====2.修改备注名=====" << endl;
	cout << endl;
	cout << "=====3.删除该好友=====" << endl;
	cout << endl;
	cout << "======= 0.返回 =======" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << endl;
		cout << "好友详细信息：" << endl;
		fri = WeiboUserCollections::getUser(friId);
		fri->printDetailInfo();
		break;
	case 2:
		cout << "输入新备注名：";
		getline(cin, key);
		user->setFriendRemark(friId, key);
		cout << "修改成功！" << endl;
		break;
	case 3:
		cout << "确认要删除该好友吗？" << endl;
		cout << "1.删除\t0.再考虑一下。。" << endl;
		cout << "请输入你的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			break;
		case 1:
			if (user->deleteFriend(friId)) {
				cout << "删除好友成功！" << endl;
			}
			break;
		default:
			cout << "对不起，您的输入有错误！" << endl;
		}
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
	}
}

void WeiboManageFriendLYC::getAllFriends() {
	map<string, string>& fris = user->getFriendList();
	if (fris.size() == 0) {
		cout << "您暂未添加任何好友" << endl;
		return;
	}
	cout << "========好友列表：========" << endl;
	cout << endl;
	cout << "\tid\t昵称" << endl;
	//遍历map
	for (map<string, string>::iterator it = fris.begin(); it != fris.end(); it++) {
		fri = WeiboUserCollections::getUser(it->first);
		cout << "\t" << fri->getUserId() << "\t" << fri->getNickName() << " ";
		if (it->second.compare("") == 0) {
			cout << "(无备注名)" << endl;
		}
		else cout << "(备注名：" << it->second << ")" << endl;
		cout << endl;
	}
}