#include"MenuView.h"

Client::Client() {
	menu = NULL;
	while (true) {
		system("cls");
		cout << "=========== 1.QQ ============" << endl;
		cout << endl;
		cout << "========= 2.Wechat ==========" << endl;
		cout << endl;
		cout << "========== 3.Weibo ==========" << endl;
		cout << endl;
		cout << "========== 0.退出 ===========" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << endl;
			cout << "欢迎下次使用！" << endl;
			return;
		case 1:
			menu = new QQViewLYC("");
			break;
		case 2:
			menu = new WechatViewLYC("");
			break;
		case 3:
			menu = new WeiboViewLYC("");
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

Client::~Client() {}

MenuViewLYC::MenuViewLYC() {
	user = NULL;
	manageFriend = NULL;
	manageGroup = NULL;
	manageUserMsg = NULL;
}

MenuViewLYC::~MenuViewLYC() {}

void MenuViewLYC::showUserMsgMenu() {				//管理个人信息
	while (true) {
		system("cls");
		cout << "======== 个人信息管理 =========" << endl;
		cout << endl;
		cout << "======= 1.查看个人资料 ========" << endl;
		cout << endl;
		cout << "======= 2.修改个人资料 ========" << endl;
		cout << endl;
		cout << "======== 3.修改密码 ==========" << endl;
		cout << endl;
		cout << "===== 4.开通其他平台账号 ======" << endl;
		cout << endl;
		cout << "========== 0.退出 ============" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "退出个人管理界面" << endl;
			return;
		case 1:
			cout << endl;
			manageUserMsg->showDetailedData();
			break;
		case 2:
			manageUserMsg->changeUserData();
			break;
		case 3:
			manageUserMsg->changePasswd();
			break;
		case 4:
			manageUserMsg->registerOtherUser();
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

//好友管理界面
void MenuViewLYC::showFriendMenu() {
	while (true) {
		system("cls");
		cout << "========== 好友管理 ==========" << endl;
		cout << endl;
		cout << "======== 1.添加好友 ==========" << endl;
		cout << endl;
		cout << "======== 2.修改备注 ==========" << endl;
		cout << endl;
		cout << "======= 3.查看好友列表 =======" << endl;
		cout << endl;
		cout << "======== 4.查询好友 ==========" << endl;
		cout << endl;
		cout << "======== 5.删除好友 ==========" << endl;
		cout << endl;
		cout << "======= 6.获取推荐好友 ========" << endl;
		cout << endl;
		cout << "========== 0.返回 ============" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "退出好友管理界面。。" << endl;
			return;
		case 1:				//添加好友
			manageFriend->addFriend();
			break;
		case 2:				//修改备注
			manageFriend->setFriendRemark();
			break;
		case 3:				//查询所有好友
			manageFriend->getAllFriends();
			break;
		case 4:				//查询好友
			manageFriend->searchFriend();
			break;
		case 5:				//删除好友
			manageFriend->deleteFriend();
			break;
		case 6:
			user->getRecoFriend();
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

/*--------------------------------QQ---------------------------------*/

QQViewLYC::QQViewLYC(string id) :MenuViewLYC() {
	//通过其他应用认证登录
	if (id.compare("") != 0) {
		user = QQUserCollections::getUser(id);
		userMenu(user);
		return;
	}
	//账号密码登录
	while (true) {
		system("cls");
		cout << "============ QQ =============" << endl;
		cout << endl;
		cout << "======== 1.用户登录 ==========" << endl;
		cout << endl;
		cout << "======== 2.用户注册 ==========" << endl;
		cout << endl;
		cout << "======== 0.切换应用 ==========" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "======== 退出QQ应用。。 ========" << endl;
			return;
		case 1:
			if (!loginMenu())	return;
			break;
		case 2:
			registerMenu();
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

QQViewLYC::~QQViewLYC() {}

//用户注册
void QQViewLYC::registerMenu() {
	string name, pwd;
	cout << "请输入用户名：";
	getline(cin, name);
	cout << endl;
	cout << "请输入密码：";
	getline(cin, pwd);
	if (name.compare("") == 0) {
		cout << "用户名不能为空！" << endl;
		return;
	}
	if (pwd.compare("") == 0) {
		cout << "密码不能为空！" << endl;
		return;
	}
	QQUserCollections::addUser(name, pwd);
	cout << "用户注册成功！" << endl;
	cout << "用户id：" << QQUserCollections::nextRegisterId - 1 << endl;
}

//用户登录
bool QQViewLYC::loginMenu() {
	string id;
	string pwd;
	cout << "请输入用户id：" ;
	getline(cin, id);
	cout << "请输入密码：" ;
	getline(cin, pwd);
	bool isCorrent = true;
	user = QQUserCollections::getUser(id);
	if (user == NULL) {
		cout << "未查找到此用户！" << endl;
		return true;
	}
	if (user->getPasswd().compare(pwd) != 0) {
		cout << "密码错误！" << endl;
		isCorrent = false;
	}
	//登录成功
	if (isCorrent) {	
		return userMenu(user);
	}
	return true;
}

bool QQViewLYC::userMenu(UserLYC* user) {
	cout << endl;
	cout << "登录成功！" << endl;
	cout << "欢迎用户:" << user->getNickName() <<
		"(id:" << user->getUserId() << ")登录QQ" << endl;
	cout << endl;
	cout << "请按任意键继续。。" << endl;
	getline(cin, key);
	//初始化下级菜单指针
	manageUserMsg = new ManageUserMsgLYC(user);
	manageFriend = new QQManageFriendLYC(user);
	manageGroup = new QQManageGroupLYC(user);
	while (true) {
		system("cls");
		cout << "============== QQ ===============" << endl;
		cout << endl;
		cout << "========== 用户id:" + user->getUserId() + "==========" << endl;
		cout << endl;
		cout << "========== 1.管理好友 ===========" << endl;
		cout << endl;
		cout << "========== 2.管理群聊 ===========" << endl;
		cout << endl;
		cout << "========= 3.个人信息管理 ========" << endl;
		cout << endl;
		cout << "========== 4.切换应用 ===========" << endl;
		cout << endl;
		cout << "========== 0.退出登录 ===========" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:				//退出登录
			cout << "=======用户 : " << user->getUserId() << "已退出登录！=====" << endl;
			return true;
		case 1:				//进入好友管理菜单
			showFriendMenu();
			break;
		case 2:				//进入群聊管理菜单
			showGroupMenu();
			break;
		case 3:				//进入用户个人信息管理菜单
			showUserMsgMenu();
			break;
		case 4:				//切换应用
			if (changeApp())	return false;
			break;
		default:
			cout << "对不起，您的输入有错误！" << endl;
			break;
		}
		cout << endl;
		cout << "请按任意键继续。。" << endl;
		getline(cin, key);
	}
	return true;
}

//群管理
void QQViewLYC::showGroupMenu() {
	while (true) {
		system("cls");
		cout << "========== QQ群管理 ===========" << endl;
		cout << endl;
		cout << "========= 1.添加群聊 ==========" << endl;
		cout << endl;
		cout << "========= 2.退出群聊 ==========" << endl;
		cout << endl;
		cout << "========= 3.管理群聊 ==========" << endl;
		cout << endl;
		cout << "========= 4.创建群聊 ==========" << endl;
		cout << endl;
		cout << "==========  0.返回 ============" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "退出群聊管理界面。。" << endl;
			return;
		case 1:				//加入群聊
			manageGroup->addGroup();
			break;
		case 2:				//退出群聊
			manageGroup->dropGroup();
			break;
		case 3:				//管理群聊
			manageGroup->administerGroup();
			break;
		case 4:				//创建群聊
			manageGroup->createGroup();
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

//切换应用：其他应用简单确认后视为自动登录
bool QQViewLYC::changeApp() {
	QQUserLYC* q_user = (QQUserLYC*)user;
	WechatUserLYC* w_user = NULL;
	cout << endl;
	cout << "选择并切换至其他应用：" << endl;
	cout << "1.微信\t2.微博\t0.返回" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return false;
	case 1:
		cout << endl;
		//没有绑定微信
		if (!q_user->getIsBind()) {
			cout << "当前QQ账号并未绑定微信！" << endl;
		}
		else {
			w_user = (WechatUserLYC*)WechatUserCollections::getBindUser(q_user->getUserId());
			cout << "将登录微信id：" << w_user->getWechatId() << "账号并切换至微信界面" << endl;
			cout << endl;
			cout << "\t1.确认\t0.取消" << endl;
			cout << endl;
			cout << "请输入你的选择：";
			getline(cin, key);
			switch(Tools::getStringChoice(key))
			{
			case 0:
				cout << endl;
				cout << "已取消应用切换" << endl;
				return false;
			case 1:
				new WechatViewLYC(w_user->getWechatId());
				return true;
			default:
				cout << endl;
				cout << "您的输入有错误，请重新输入！" << endl;
				break;
			}
		}
		break;
	case 2:
		cout << endl;
		//没有开通微博
		if (WeiboUserCollections::getUser(q_user->getUserId()) == NULL) {
			cout << "该id未开通微博用户！" << endl;
		}
		else {
			cout << "将登录微博id：" << q_user->getUserId() << "账号并切换至微博界面" << endl;
			cout << "\t1.确认\t0.取消" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				cout << "已取消应用切换" << endl;
				return false;
			case 1:
				new WeiboViewLYC(q_user->getUserId());
				return true;
			default:
				cout << "您的输入有错误，请重新输入！" << endl;
				break;
			}
		}
		break;
	default:
		cout << "您的输入有错误，请重新输入！" << endl;
		break;
	}
	return false;
}

/*--------------------------------Wechat---------------------------------*/

WechatViewLYC::WechatViewLYC(string id) :MenuViewLYC() {
	//通过其他应用认证登录
	if (id.compare("") != 0) {
		user = WechatUserCollections::getUser(id);
		userMenu(user);
		return;
	}
	while (true) {
		system("cls");
		cout << "========== Wechat ===========" << endl;
		cout << endl;
		cout << "======== 1.用户登录 ==========" << endl;
		cout << endl;
		cout << "======== 2.用户注册 ==========" << endl;
		cout << endl;
		cout << "======== 0.切换应用 ==========" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "======== 退出Wechat应用。。 ========" << endl;
			return;
		case 1:
			if (!loginMenu())	return;
			break;
		case 2:
			registerMenu();
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

WechatViewLYC::~WechatViewLYC() {}

//用户注册
void WechatViewLYC::registerMenu() {
	string name, pwd;
	cout << "请输入用户名：";
	getline(cin, name);
	cout << endl;
	cout << "请输入密码：";
	getline(cin, pwd);
	if (name.compare("") == 0) {
		cout << "用户名不能为空！" << endl;
		return;
	}
	if (pwd.compare("") == 0) {
		cout << "密码不能为空！" << endl;
		return;
	}
	WechatUserCollections::addUser(name, pwd);
	cout << "用户注册成功！" << endl;
	cout << "用户id：" << WechatUserCollections::nextWcId - 1 << endl;
}

//用户登录
bool WechatViewLYC::loginMenu() {
	string id;
	string pwd;
	cout << "请输入用户id：";
	getline(cin, id);
	cout << "请输入密码：";
	getline(cin, pwd);
	bool isCorrent = true;
	user = WechatUserCollections::getUser(id);
	if (user == NULL) {
		cout << "未查找到此用户！" << endl;
		return true;
	}
	if (user->getPasswd().compare(pwd) != 0) {
		cout << "密码错误！" << endl;
		isCorrent = false;
	}
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	//登录成功
	if (isCorrent) {
		return userMenu(user);
	}
	return true;
}

bool WechatViewLYC::userMenu(UserLYC* user) {
	WechatUserLYC* w_user = (WechatUserLYC*)user;			//向下转型
	cout << endl;
	cout << "登录成功！" << endl;
	cout << "欢迎用户:" << user->getNickName() <<
		"(id:" << w_user->getWechatId() << ")登录微信" << endl;
	cout << endl;
	cout << "请按任意键继续。。" << endl;
	getline(cin, key);
	//初始化下级菜单指针
	manageUserMsg = new WechatManageUserMsgLYC(user);
	manageFriend = new WechatManageFriendLYC(user);
	manageGroup = new WechatManageGroupLYC(user);
	while (true) {
		system("cls");
		cout << "============= Wechat =============" << endl;
		cout << endl;
		cout << "========== 用户id:" + w_user->getWechatId() + "===========" << endl;
		cout << endl;
		cout << "========== 1.管理好友 ===========" << endl;
		cout << endl;
		cout << "========== 2.管理群聊 ===========" << endl;
		cout << endl;
		cout << "======== 3.个人信息管理 =========" << endl;
		cout << endl;
		cout << "========== 4.切换应用 ===========" << endl;
		cout << endl;
		cout << "========== 0.退出登录 ===========" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:				//退出登录
			cout << "=======用户 : " << w_user->getWechatId() << "已退出登录！=====" << endl;
			return true;
		case 1:				//进入好友管理菜单
			showFriendMenu();
			break;
		case 2:				//进入群聊管理菜单
			showGroupMenu();
			break;
		case 3:				//进入用户个人信息管理菜单
			showUserMsgMenu();
			break;
		case 4:				//切换应用
			if (changeApp())		return false;
			break;
		default:
			cout << "对不起，您的输入有错误！" << endl;
			break;
		}
		cout << endl;
		cout << "请按任意键继续。。" << endl;
		getline(cin, key);
	}
	return true;
}

//群管理
void WechatViewLYC::showGroupMenu() {
	while (true) {
		system("cls");
		cout << "======== Wechat群管理 =========" << endl;
		cout << endl;
		cout << "====== 1.邀请用户进入群聊 ======" << endl;
		cout << endl;
		cout << "========= 2.退出群聊 ==========" << endl;
		cout << endl;
		cout << "========= 3.管理群聊 ==========" << endl;
		cout << endl;
		cout << "========= 4.创建群聊 ==========" << endl;
		cout << endl;
		cout << "==========  0.返回 ============" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "退出群聊管理界面。。" << endl;
			return;
		case 1:				//加入群聊
			manageGroup->addGroup();
			break;
		case 2:				//退出群聊
			manageGroup->dropGroup();
			break;
		case 3:				//管理群聊
			manageGroup->administerGroup();
			break;
		case 4:				//创建群聊
			manageGroup->createGroup();
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

void WechatViewLYC::showUserMsgMenu() {				//管理个人信息
	WechatManageUserMsgLYC* w_manageUserMsg = (WechatManageUserMsgLYC*)manageUserMsg;
	while (true) {
		system("cls");
		cout << "======== 个人信息管理 =========" << endl;
		cout << endl;
		cout << "======= 1.查看个人资料 ========" << endl;
		cout << endl;
		cout << "======= 2.修改个人资料 ========" << endl;
		cout << endl;
		cout << "======== 3.修改密码 ==========" << endl;
		cout << endl;
		cout << "===== 4.开通其他平台账号 ======" << endl;
		cout << endl;
		cout << "===== 5.绑定QQ账号管理 ========" << endl;
		cout << endl;
		cout << "========== 0.退出 ============" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "退出个人管理界面" << endl;
			return;
		case 1:
			cout << endl;
			manageUserMsg->showDetailedData();
			break;
		case 2:
			manageUserMsg->changeUserData();
			break;
		case 3:
			manageUserMsg->changePasswd();
			break;
		case 4:
			manageUserMsg->registerOtherUser();
			break;
		case 5:				//绑定qq账号管理
			w_manageUserMsg->manageBind();
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

bool WechatViewLYC::changeApp() {
	WechatUserLYC* w_user = (WechatUserLYC*)user;
	cout << endl;
	//没有绑定QQ不能登录其他应用
	if (w_user->getUserId().compare("") == 0) {
		cout << "该账号暂未与QQ绑定，无法切换应用！" << endl;
		return false;
	}
	cout << "选择并切换至其他应用：" << endl;
	cout << "1.QQ\t2.微博\t0.返回" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return false;
	case 1:
		cout << endl;
		cout << "将登录QQ id：" << w_user->getUserId() << "账号并切换至QQ界面" << endl;
		cout << endl;
		cout << "\t1.确认\t0.取消" << endl;
		cout << endl;
		cout << "请输入你的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key))
		{
		case 0:
			cout << endl;
			cout << "已取消应用切换" << endl;
			return false;
		case 1:
			new QQViewLYC(w_user->getUserId());
			return true;
		default:
			cout << endl;
			cout << "您的输入有错误，请重新输入！" << endl;
			break;
		}
		break;
	case 2:
		cout << endl;
		//没有开通微博
		if (WeiboUserCollections::getUser(w_user->getUserId()) == NULL) {
			cout << "该id未开通微博用户！" << endl;
		}
		else {
			cout << "将登录微博id：" << w_user->getUserId() << "账号并切换至微博界面" << endl;
			cout << "\t1.确认\t0.取消" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				cout << "已取消应用切换" << endl;
				return false;
			case 1:
				new WeiboViewLYC(w_user->getUserId());
				return true;
			default:
				cout << "您的输入有错误，请重新输入！" << endl;
				break;
			}
		}
		break;
	default:
		cout << "您的输入有错误，请重新输入！" << endl;
		break;
	}
	return false;
}

/*--------------------------------Weibo---------------------------------*/

WeiboViewLYC::WeiboViewLYC(string id) :MenuViewLYC() {
	//通过其他应用认证登录
	if (id.compare("") != 0) {
		user = WeiboUserCollections::getUser(id);
		userMenu(user);
		return;
	}
	while (true) {
		system("cls");
		cout << "=========== Weibo ===========" << endl;
		cout << endl;
		cout << "======== 1.用户登录 ==========" << endl;
		cout << endl;
		cout << "======== 2.用户注册 ==========" << endl;
		cout << endl;
		cout << "======== 0.切换应用 ==========" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "======== 退出微博应用。。 ========" << endl;
			return;
		case 1:
			if (!loginMenu())	return;
			break;
		case 2:
			registerMenu();
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

WeiboViewLYC::~WeiboViewLYC() {}

//用户注册
void WeiboViewLYC::registerMenu() {
	string name, pwd;
	cout << "请输入用户名：";
	getline(cin, name);
	cout << endl;
	cout << "请输入密码：";
	getline(cin, pwd);
	if (name.compare("") == 0) {
		cout << "用户名不能为空！" << endl;
		return;
	}
	if (pwd.compare("") == 0) {
		cout << "密码不能为空！" << endl;
		return;
	}
	WeiboUserCollections::addUser(name, pwd);
	cout << "用户注册成功！" << endl;
	cout << "用户id：" << QQUserCollections::nextRegisterId - 1 << endl;
}

//用户登录
bool WeiboViewLYC::loginMenu() {
	string id;
	string pwd;
	cout << "请输入用户id：";
	getline(cin, id);
	cout << "请输入密码：";
	getline(cin, pwd);
	bool isCorrent = true;
	user = WeiboUserCollections::getUser(id);
	if (user == NULL) {
		cout << "未查找到此用户！" << endl;
		return true;
	}
	if (user->getPasswd().compare(pwd) != 0) {
		cout << "密码错误！" << endl;
		isCorrent = false;
	}
	//登录成功
	if (isCorrent) {
		return userMenu(user);
	}
	return true;
}

bool WeiboViewLYC::userMenu(UserLYC* user) {
	cout << endl;
	cout << "登录成功！" << endl;
	cout << "欢迎用户:" << user->getNickName() <<
		"(id:" << user->getUserId() << ")登录Weibo" << endl;
	cout << endl;
	cout << "请按任意键继续。。" << endl;
	getline(cin, key);
	//初始化下级菜单指针
	manageUserMsg = new ManageUserMsgLYC(user);
	manageFriend = new WeiboManageFriendLYC(user);
	manageGroup = new WeiboManageGroupLYC(user);
	while (true) {
		system("cls");
		cout << "============= Weibo =============" << endl;
		cout << endl;
		cout << "========== 用户id:" + user->getUserId() + "==========" << endl;
		cout << endl;
		cout << "========== 1.管理好友 ===========" << endl;
		cout << endl;
		cout << "========== 2.管理群聊 ===========" << endl;
		cout << endl;
		cout << "========= 3.个人信息管理 ========" << endl;
		cout << endl;
		cout << "========== 4.切换应用 ===========" << endl;
		cout << endl;
		cout << "========== 0.退出登录 ===========" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:				//退出登录
			cout << "=======用户 : " << user->getUserId() << "已退出登录！=====" << endl;
			return true;
		case 1:				//进入好友管理菜单
			showFriendMenu();
			break;
		case 2:				//进入群聊管理菜单
			showGroupMenu();
			break;
		case 3:				//进入用户个人信息管理菜单
			showUserMsgMenu();
			break;
		case 4:				//切换应用
			if (changeApp())		return false;
			break;
		default:
			cout << "对不起，您的输入有错误！" << endl;
			break;
		}
		cout << endl;
		cout << "请按任意键继续。。" << endl;
		getline(cin, key);
	}
	return true;
}

//群管理
void WeiboViewLYC::showGroupMenu() {
	while (true) {
		system("cls");
		cout << "========== 微博群管理 ==========" << endl;
		cout << endl;
		cout << "====== 1.邀请用户进入群聊 ======" << endl;
		cout << endl;
		cout << "========= 2.退出群聊 ==========" << endl;
		cout << endl;
		cout << "========= 3.管理群聊 ==========" << endl;
		cout << endl;
		cout << "========= 4.创建群聊 ==========" << endl;
		cout << endl;
		cout << "==========  0.返回 ============" << endl;
		cout << endl;
		cout << "请输入您的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key)) {
		case 0:
			cout << "退出群聊管理界面。。" << endl;
			return;
		case 1:				//加入群聊
			manageGroup->addGroup();
			break;
		case 2:				//退出群聊
			manageGroup->dropGroup();
			break;
		case 3:				//管理群聊
			manageGroup->administerGroup();
			break;
		case 4:				//创建群聊
			manageGroup->createGroup();
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

bool WeiboViewLYC::changeApp() {
	cout << endl;
	//未开通QQ不能切换
	if (QQUserCollections::getUser(user->getUserId()) == NULL) {
		cout << "该微博ID暂未开通QQ，无法进行用户切换！" << endl;
		return false;
	}
	WechatUserLYC* w_user = NULL;
	cout << "选择并切换至其他应用：" << endl;
	cout << "1.QQ\t2.微信\t0.返回" << endl;
	cout << endl;
	cout << "请输入你的选择：";
	getline(cin, key);
	switch (Tools::getStringChoice(key))
	{
	case 0:
		return false;
	case 1:
		cout << endl;
		cout << "将登录QQ id：" << user->getUserId() << "账号并切换至QQ界面" << endl;
		cout << endl;
		cout << "\t1.确认\t0.取消" << endl;
		cout << endl;
		cout << "请输入你的选择：";
		getline(cin, key);
		switch (Tools::getStringChoice(key))
		{
		case 0:
			cout << endl;
			cout << "已取消应用切换" << endl;
			return false;
		case 1:
			new QQViewLYC(user->getUserId());
			return true;
		default:
			cout << endl;
			cout << "您的输入有错误，请重新输入！" << endl;
			break;
		}
		break;
	case 2:
		cout << endl;
		w_user = (WechatUserLYC*)WechatUserCollections::getBindUser(user->getUserId());
		//没有绑定微信
		if (w_user == NULL) {
			cout << "该id未绑定微信账号！" << endl;
		}
		else { 
			cout << "将登录微信id：" << w_user->getWechatId() << "账号并切换至微信界面" << endl;
			cout << "\t1.确认\t0.取消" << endl;
			cout << endl;
			cout << "请输入你的选择：" << endl;
			getline(cin, key);
			switch (Tools::getStringChoice(key))
			{
			case 0:
				cout << "已取消应用切换" << endl;
				return false;
			case 1:
				new WechatViewLYC(w_user->getWechatId());
				return true;
			default:
				cout << "您的输入有错误，请重新输入！" << endl;
				break;
			}
		}
		break;
	default:
		cout << "您的输入有错误，请重新输入！" << endl;
		break;
	}
	return false;
}