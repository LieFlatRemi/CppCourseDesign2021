#include"ManageUserMsg.h"
#include"Tools.h"
ManageUserMsgLYC::ManageUserMsgLYC(UserLYC* user) {
	this->user = user;
}

ManageUserMsgLYC::~ManageUserMsgLYC() {}

void ManageUserMsgLYC::showDetailedData() {
	cout << "用户详细信息：" << endl;
	user->printDetailInfo();
}

void ManageUserMsgLYC::changeUserData() {
	cout << endl;
	cout << "== 选择你想修改的内容：==" << endl;
	cout << endl;
	cout << "======== 1.昵称 ========" << endl;
	cout << endl;
	cout << "====== 2.出生日期 ======" << endl;
	cout << endl;
	cout << "======= 3.所在地 =======" << endl;
	cout << endl;
	cout << "====== 0.返回上级 ======" << endl;
	cout << endl;
	cout << "请输入您的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		cout << "请输入修改后的昵称：" << endl;
		getline(cin, key);
		if (key.compare("") == 0) {
			cout << endl;
			cout << "昵称不可为空！" << endl;
			return;
		}
		else user->setNickName(key);
		break;
	case 2:
		cout << "请输入修改后的生日(基本格式:xxxx.xx.xx)：" << endl;
		getline(cin, key);
		//检查输入合法
		if (!Tools::isBirthFormat(key)) {
			cout << "输入不符合格式，修改失败！" << endl;
			return;
		}
		user->setBirth(key);
		break;
	case 3:
		cout << "请输入修改后的地址：" << endl;
		getline(cin, key);
		user->setAddress(key);
		break;
	default:
		cout << "对不起，您的输入有误！" << endl;
		return;
	}
	cout << "修改成功！" << endl;
}

void ManageUserMsgLYC::changePasswd() {
	string oldPasswd;
	cout << "输入旧密码：";
	getline(cin, oldPasswd);
	cout << "输入新密码：";
	getline(cin, key);
	if (oldPasswd.compare(user->getPasswd()) != 0) {
		cout << "旧密码输入错误，修改失败！" << endl;
	}
	else if (Tools::isEmptyString(key)) {
		cout << "新密码不能为空，修改失败！" << endl;
	}
	else {
		user->setPasswd(key);
		cout << "密码修改成功！" << endl;
	}
}

//开通其他平台用户
void ManageUserMsgLYC::registerOtherUser() {
	string name;
	string pwd;
	WechatUserLYC* w_user = NULL;
	QQUserLYC* q_user = NULL;
	cout << endl;
	cout << "选择开通平台：" << endl;
	cout << endl;
	cout << "1.QQ\t2.微信\t3.微博\t0.返回" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	cout << endl;
	switch (Tools::getStringChoice(key)) {
	case 0:
		return;
	case 1:
		//该id已经开通
		if (QQUserCollections::getUser(user->getUserId()) != NULL) {
			cout << "该id已开通QQ账号！" << endl;
		}
		else {
			cout << "开通QQ用户" << endl;
			cout << "输入QQ账号的用户名：";
			getline(cin, name);
			cout << "输入QQ账号的密码：";
			getline(cin, pwd);
			cout << endl;
			//判断合法性，与注册部分相同
			if (name.compare("") == 0) {
				cout << "用户名不能为空！" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "密码不能为空！" << endl;
				return;
			}
			QQUserCollections::addUserFromFile(name, pwd, user->getUserId());
			cout << "开通QQ账号成功！" << endl;
		}
		break;
	case 2:
		//优先开通当前id的QQ账号，之后才能开通微信账号
		//判断当前id是否绑定了微信，如果有则视为已经开通了微信账号
		q_user = (QQUserLYC*)QQUserCollections::getUser(user->getUserId());
		if (q_user == NULL) {								//qq账号不存在
			cout << "请先开通该id的QQ账号！" << endl;
		}
		else if (q_user->getIsBind()) {						//qq账号已经绑定微信号
			cout << "当前id已经绑定了微信账号！" << endl;
		}
		else {
			cout << "开通微信用户" << endl;
			cout << "输入微信账号的用户名：";
			getline(cin, name);
			cout << "输入微信账号的密码：";
			getline(cin, pwd);
			cout << endl;
			//判断合法性，与注册部分相同
			if (name.compare("") == 0) {
				cout << "用户名不能为空！" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "密码不能为空！" << endl;
				return;
			}
			WechatUserCollections::addUser(name, pwd);
			//设置绑定情况
			string wid = to_string(WechatUserCollections::nextWcId - 1);
			w_user = (WechatUserLYC*)WechatUserCollections::getUser(wid);
			w_user->bindWithQQ(q_user->getUserId());
			cout << "开通微信账号成功！" << endl;
			cout << "微信id：" << wid << endl;
		}
		break;
	case 3:
		if (WeiboUserCollections::getUser(user->getUserId()) != NULL) {
			cout << "该id已开通微博账号！" << endl;
		}
		else {
			cout << "开通微博用户" << endl;
			cout << "输入微博账号的用户名：";
			getline(cin, name);
			cout << "输入微博账号的密码：";
			getline(cin, pwd);
			cout << endl;
			//判断合法性，与注册部分相同
			if (name.compare("") == 0) {
				cout << "用户名不能为空！" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "密码不能为空！" << endl;
				return;
			}
			WeiboUserCollections::addUserFromFile(name, pwd, user->getUserId());
			cout << "开通微博账号成功！" << endl;
		}
		break;
	default:
		cout << "您的输入有错误，请重新输入！" << endl;
		break;
	}
}

WechatManageUserMsgLYC::WechatManageUserMsgLYC(UserLYC* user) : ManageUserMsgLYC(user) {}

WechatManageUserMsgLYC::~WechatManageUserMsgLYC() {}

void WechatManageUserMsgLYC::registerOtherUser() {
	string name;
	string pwd;
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	cout << endl;
	cout << "选择开通平台：" << endl;
	cout << endl;
	cout << "1.QQ\t2.微博\t0.返回" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	cout << endl;
	//有绑定账号的情况，直接用绑定id去注册，此时可以开通微博
	//无绑定账号的情况，相当于注册新账号，此时只能先开通QQ
	string id = user->getUserId();
	if (id.compare("") != 0) {			//已经绑定了qq账号
		switch (Tools::getStringChoice(key))
		{
		case 0:
			return;
		case 1:
			//绑定了账号的情况下，必定已经开通QQ账号
			cout << "该微信账号已绑定对应QQ账号！" << endl;
			break;
		case 2:
			if (WeiboUserCollections::getUser(id) != NULL) {
				cout << "对应绑定id已经开通微博账号！" << endl;
			}
			else {
				//开通微博账号
				cout << "开通微博用户" << endl;
				cout << "输入微博账号的用户名：";
				getline(cin, name);
				cout << "输入微博账号的密码：";
				getline(cin, pwd);
				cout << endl;
				//判断合法性，与注册部分相同
				if (name.compare("") == 0) {
					cout << "用户名不能为空！" << endl;
					return;
				}
				if (pwd.compare("") == 0) {
					cout << "密码不能为空！" << endl;
					return;
				}
				WeiboUserCollections::addUserFromFile(name, pwd, id);
				cout << "开通微博账号成功！" << endl;
			}
			break;
		default:
			cout << "您的输入有错误，请重新输入！" << endl;
			break;
		}
	}
	else {								//没有绑定qq账号
		switch (Tools::getStringChoice(key))
		{
		case 0:
			return;
		case 1:
			cout << "开通QQ用户" << endl;
			cout << "输入QQ账号的用户名：";
			getline(cin, name);
			cout << "输入QQ账号的密码：";
			getline(cin, pwd);
			cout << endl;
			//判断合法性，与注册部分相同
			if (name.compare("") == 0) {
				cout << "用户名不能为空！" << endl;
				return;
			}
			if (pwd.compare("") == 0) {
				cout << "密码不能为空！" << endl;
				return;
			}
			QQUserCollections::addUser(name, pwd);
			//绑定
			w_user->bindWithQQ(to_string(QQUserCollections::nextRegisterId - 1));
			cout << "开通QQ账号成功！" << endl;
			cout << "该微信号已经绑定新注册的QQ账号（" << w_user->getUserId() << "）！" << endl;
			break;
		case 2:
			//没有绑定账号的情况下，只能先开通QQ账号
			cout << "请先开通新QQ账号或绑定已注册的QQ账号！" << endl;
			break;
		default:
			cout << "您的输入有错误，请重新输入！" << endl;
			break;
		}
	}
	
}

void WechatManageUserMsgLYC::manageBind() {
	WechatUserLYC* w_user = (WechatUserLYC*)user;				//向下转型
	QQUserLYC* bindUser = NULL;
	cout << endl;
	cout << "==== 绑定账号管理 ====" << endl;
	cout << endl;
	cout << "目前绑定状态：" << endl;
	cout << endl;
	if (user->getUserId().compare("") == 0) {
		cout << "当前账号暂未与任何QQ账号绑定" << endl;
	}
	else cout << "当前账号绑定QQ ID：" << user->getUserId() << endl;
	cout << endl;
	cout << "1.绑定新QQ ID\t2.与当前QQ ID解绑\t0.返回";
	cout << endl;
	cout << "请输入你的选择：" << endl;
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return;
	case 1:
		cout << "请输入你想绑定的QQ ID：";
		getline(cin, key);
		cout << endl;
		bindUser = (QQUserLYC*)QQUserCollections::getUser(key);
		if (bindUser == NULL) {
			cout << "未查找到此用户！" << endl;
			return;
		}
		else if (bindUser->getIsBind()) {
			cout << "该QQ ID已与现有微信账号绑定！" << endl;
		}
		else {
			w_user->resetBind();
			w_user->bindWithQQ(key);
			cout << "绑定QQ成功！" << endl;
		}
		break;
	case 2:
		if (w_user->getUserId().compare("") == 0) {
			cout << "当前未与QQ ID绑定！" << endl;
		}
		else {
			cout << "与当前QQ ID解绑成功！" << endl;
			w_user->resetBind();
		}
		break;
	default:
		cout << "对不起，您的输入有错误！" << endl;
		break;
	}
}