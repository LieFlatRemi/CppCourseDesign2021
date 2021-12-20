#include"File.h"

//构造函数：读入文件
FileLYC::FileLYC() {
}

//析构函数：写入文件
FileLYC::~FileLYC() {
}

QQFile::QQFile() {
	readUser();
	readGroup();
}

QQFile::~QQFile() {
	writeUser();
	writeGroup();
}

void QQFile::readUser() {
	string key;
	ifs.open("./DataFile/QQUser.txt", ios::in);			//为读文件而打开文件
	//先读第一行
	getline(ifs, key);
	QQUserCollections::nextRegisterId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//读第一行
		//空格分割字符串
		vector<string> strs = Tools::splitString(key, ' ');
		string id = strs.at(0);
		string pwd = strs.at(1);
		string nickName = strs.at(2);
		QQUserCollections::addUserFromFile(nickName, pwd, id);
		QQUserLYC* user = (QQUserLYC*)QQUserCollections::getUser(id);
		user->setBirth(strs.at(3));
		user->setCreateYear(atoi(strs.at(4).c_str()));
		user->setAddress(strs.at(5));
		if (strs.at(6).compare("1") == 0)	user->setIsBind(true);
		else user->setIsBind(false);
		//读取好友：分隔行之前
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0) {			//分隔
				break;
			}
			int split = key.find(" ");
			string friId = key.substr(0, split);
			string remark = key.substr(split + 1, key.length());
			if (remark.compare("未设置") == 0) {
				user->addFriend(friId, "");
			}
			else user->addFriend(friId, remark);
		}
	}
	ifs.close();
}

void QQFile::readGroup() {
	string key;
	vector<string> strs;
	ifs.open("./DataFile/QQGroup.txt", ios::in);
	//先读第一行nextGroupId
	getline(ifs, key);
	QQGroupCollections::nextGroupId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//读第一行，空格分割字符串
		strs = Tools::splitString(key, ' ');
		//群id， 群主id， 群名
		QQGroupCollections::addGroupFromFile(new QQGroupLYC(strs.at(0), strs.at(1), strs.at(2)));
		QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(strs.at(0));
		group->setChildId(atoi(strs.at(3).c_str()));					//子群id号
		//读第二行群成员
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addMember(*sit);
		}
		//读第三行管理员
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addManager(*sit);
		}
		//读第四行加群请求
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addRequest(*sit);
		}
		//接下来读子群部分
		getline(ifs, key);
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0)	break;
			//读第一行，空格分割字符串
			strs = Tools::splitString(key, ' ');
			//群id， 群主id， 群名，父群指针
			group->addChildsFromFile(new QQChildGroupLYC(strs.at(0), strs.at(1), strs.at(2), group));
			QQChildGroupLYC* child = group->searchChilds(strs.at(0));
			//第二行：子群成员
			getline(ifs, key);
			strs = Tools::splitString(key, ' ');
			for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
				child->addMember(*sit);
			}
			//读取分隔行
			getline(ifs, key);
		}
	}
	ifs.close();
}

void QQFile::writeUser() {
	ofs.open("./DataFile/QQUser.txt", ios::trunc);		//如果文件存在先删除，再创建
	//先写入id
	ofs << QQUserCollections::nextRegisterId << endl;
	//遍历User集合
	map<string, UserLYC*>& users = QQUserCollections::getMap();
	for (map<string, UserLYC*>::iterator it = users.begin(); it != users.end(); it++) {
		QQUserLYC* user = (QQUserLYC*)it->second;		//获取User指针
		//写入信息
		ofs << user->getUserId() << " ";
		ofs << user->getPasswd() << " ";
		ofs << user->getNickName() << " ";
		ofs << user->getBirth() << " ";
		ofs << user->getCreateYear() << " ";
		ofs << user->getAddress() << " ";
		if (user->getIsBind())	ofs << "1" ;
		else ofs << "0" ;
		ofs << endl;
		//写入好友的id和昵称,遍历map
		map<string, string>& fris = user->getFriendList();
		for (map<string, string>::iterator fit = fris.begin(); fit != fris.end(); fit++) {
			ofs << fit->first << " ";
			//考虑无备注的特殊情况
			if (fit->second.compare("") == 0) {
				ofs << "未设置";
			}
			else ofs << fit->second;
			ofs << endl;
		}
		//分隔20个等号，表示结束
		ofs << "====================" << endl;
	}
	ofs.close();
}

void QQFile::writeGroup() {
	ofs.open("./DataFile/QQGroup.txt", ios::trunc);
	//第一行，写入nextGroupId
	ofs << QQGroupCollections::nextGroupId << endl;
	//遍历Group集合
	map<string, GroupLYC*>& groups = QQGroupCollections::getMap();
	for (map<string, GroupLYC*>::iterator it = groups.begin(); it != groups.end(); it++) {
		QQGroupLYC* group = (QQGroupLYC*)it->second;
		//第一行，群的基本信息
		ofs << group->getId() << " " << group->getHostId() << " " << group->getName() << " ";
		ofs << group->getChildId() << endl;			//qq群多一个子群id号
		//第二行，群成员id,遍历members
		set<string>& members = group->getMembersSet();
		for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
			if (mit != members.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//第三行，管理员id，QQ群独有
		set<string>& managers = group->getManagersSet();
		for (set<string>::iterator mit = managers.begin(); mit != managers.end(); mit++) {
			if (mit != managers.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//第四行，加群请求id，QQ群独有
		set<string>& requests = group->getRequestsSet();
		for (set<string>::iterator rit = requests.begin(); rit != requests.end(); rit++) {
			if (rit != requests.begin())	ofs << " ";
			ofs << *rit;
		}
		ofs << endl;
		//分隔10个等号，表示之后部分为子群
		ofs << "==========" << endl;
		map<string, QQChildGroupLYC*>& childs = group->getChildsMap();
		//子群部分，和群类似
		for (map<string, QQChildGroupLYC*>::iterator git = childs.begin(); git != childs.end(); git++) {
			QQChildGroupLYC* child = git->second;
			//第一行，群的基本信息（不需要父群id，因为文件会先读取父群）
			ofs << child->getId() << " " << child->getHostId() << " " << child->getName() << " " << endl;
			//第二行，群成员id,遍历members
			set<string>& members = child->getMembersSet();
			for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
				if (mit != members.begin())	ofs << " ";
				ofs << *mit;
			}
			ofs << endl;
			//分隔10个等号，表示一个子群写入结束
			ofs << "==========" << endl;
		}
		//分隔20个等号，表示一个群写入文件结束
		ofs << "====================" << endl;
	}
	ofs.close();
}

WechatFile::WechatFile() {
	readUser();
	readGroup();
}

WechatFile::~WechatFile() {
	writeUser();
	writeGroup();
}

void WechatFile::readUser() {
	string key;
	ifs.open("./DataFile/WechatUser.txt", ios::in);			//为读文件而打开文件
	getline(ifs, key);
	WechatUserCollections::nextWcId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//读第一行
		//空格分割字符串
		vector<string> strs = Tools::splitString(key, ' ');
		string id = strs.at(1);
		string pwd = strs.at(2);
		string nickName = strs.at(3);
		WechatUserCollections::addUserFromFile(nickName, pwd, id);
		WechatUserLYC* user = (WechatUserLYC*)WechatUserCollections::getUser(id);
		if (strs.at(0).compare("未绑定") == 0)	user->setUserId("");
		else user->setUserId(strs.at(0));
		user->setBirth(strs.at(4));
		user->setCreateYear(atoi(strs.at(5).c_str()));
		user->setAddress(strs.at(6));
		//读取好友：分隔行之前
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0) {			//分隔
				break;
			}
			int split = key.find(" ");
			string friId = key.substr(0, split);
			string remark = key.substr(split + 1, key.length());
			if (remark.compare("未设置") == 0) {
				user->addFriend(friId, "");
			}
			else user->addFriend(friId, remark);
		}
	}
	ifs.close();
}

void WechatFile::readGroup() {
	string key;
	vector<string> strs;
	ifs.open("./DataFile/WechatGroup.txt", ios::in);
	//先读第一行nextGroupId
	getline(ifs, key);
	WechatGroupCollections::nextGroupId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//读第一行，空格分割字符串
		strs = Tools::splitString(key, ' ');
		//群id， 群主id， 群名
		WechatGroupCollections::addGroupFromFile(new WechatGroupLYC(strs.at(0), strs.at(1), strs.at(2)));
		GroupLYC* group = WechatGroupCollections::getGroup(strs.at(0));
		//读第二行群成员
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addMember(*sit);
		}
		getline(ifs, key);
	}
	ifs.close();
}

void WechatFile::writeUser() {
	ofs.open("./DataFile/WechatUser.txt", ios::trunc);		//如果文件存在先删除，再创建
	//先写入id
	ofs << WechatUserCollections::nextWcId << endl;
	//遍历User集合
	map<string, UserLYC*>& users = WechatUserCollections::getMap();
	for (map<string, UserLYC*>::iterator it = users.begin(); it != users.end(); it++) {
		WechatUserLYC* user = (WechatUserLYC*)it->second;		//获取User指针
		//写入信息
		//如果未绑定QQ，写入未绑定
		if (user->getUserId().compare("") == 0)	ofs << "未绑定" << " ";
		else ofs << user->getUserId() << " ";
		ofs << user->getWechatId() << " ";
		ofs << user->getPasswd() << " ";
		ofs << user->getNickName() << " ";
		ofs << user->getBirth() << " ";
		ofs << user->getCreateYear() << " ";
		ofs << user->getAddress() << endl;
		//写入好友的id和昵称,遍历map
		map<string, string>& fris = user->getFriendList();
		for (map<string, string>::iterator fit = fris.begin(); fit != fris.end(); fit++) {
			ofs << fit->first << " ";
			//考虑无备注的特殊情况
			if (fit->second.compare("") == 0) {
				ofs << "未设置";
			}
			else ofs << fit->second;
			ofs << endl;
		}
		//分隔20个等号，表示结束
		ofs << "====================" << endl;
	}
	ofs.close();
}

void WechatFile::writeGroup() {
	ofs.open("./DataFile/WechatGroup.txt", ios::trunc);
	//第一行，写入nextGroupId
	ofs << WechatGroupCollections::nextGroupId << endl;
	//遍历Group集合
	map<string, GroupLYC*>& groups = WechatGroupCollections::getMap();
	for (map<string, GroupLYC*>::iterator it = groups.begin(); it != groups.end(); it++) {
		GroupLYC* group = it->second;
		//第一行，群的基本信息
		ofs << group->getId() << " " << group->getHostId() << " " << group->getName() << " " << endl;
		//第二行，群成员id,遍历members
		set<string>& members = group->getMembersSet();
		for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
			if (mit != members.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//分隔20个等号，表示一个群写入文件结束
		ofs << "====================" << endl;
	}
	ofs.close();
}

WeiboFile::WeiboFile() {
	readUser();
	readGroup();
}

WeiboFile::~WeiboFile() {
	writeUser();
	writeGroup();
}

void WeiboFile::readUser() {
	string key;
	ifs.open("./DataFile/WeiboUser.txt", ios::in);			//为读文件而打开文件
	while (getline(ifs, key)) {
		//读第一行
		//空格分割字符串
		vector<string> strs = Tools::splitString(key, ' ');
		string id = strs.at(0);
		string pwd = strs.at(1);
		string nickName = strs.at(2);
		WeiboUserCollections::addUserFromFile(nickName, pwd, id);
		WeiboUserLYC* user = (WeiboUserLYC*)WeiboUserCollections::getUser(id);
		user->setBirth(strs.at(3));
		user->setCreateYear(atoi(strs.at(4).c_str()));
		user->setAddress(strs.at(5));
		//读取好友：分隔行之前
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0) {			//分隔
				break;
			}
			int split = key.find(" ");
			string friId = key.substr(0, split);
			string remark = key.substr(split + 1, key.length());
			if (remark.compare("未设置") == 0) {
				user->addFriend(friId, "");
			}
			else user->addFriend(friId, remark);
		}
	}
	ifs.close();
}

void WeiboFile::readGroup() {
	string key;
	vector<string> strs;
	ifs.open("./DataFile/WeiboGroup.txt", ios::in);
	//先读第一行nextGroupId
	getline(ifs, key);
	WeiboGroupCollections::nextGroupId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//读第一行，空格分割字符串
		strs = Tools::splitString(key, ' ');
		//群id， 群主id， 群名
		WeiboGroupCollections::addGroupFromFile(new WeiboGroupLYC(strs.at(0), strs.at(1), strs.at(2)));
		GroupLYC* group = WeiboGroupCollections::getGroup(strs.at(0));
		//读第二行群成员
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addMember(*sit);
		}
		getline(ifs, key);
	}
	ifs.close();
}

void WeiboFile::writeUser() {
	ofs.open("./DataFile/WeiboUser.txt", ios::trunc);		//如果文件存在先删除，再创建
	//遍历User集合
	map<string, UserLYC*>& users = WeiboUserCollections::getMap();
	for (map<string, UserLYC*>::iterator it = users.begin(); it != users.end(); it++) {
		WeiboUserLYC* user = (WeiboUserLYC*)it->second;		//获取User指针
		//写入信息
		ofs << user->getUserId() << " ";
		ofs << user->getPasswd() << " ";
		ofs << user->getNickName() << " ";
		ofs << user->getBirth() << " ";
		ofs << user->getCreateYear() << " ";
		ofs << user->getAddress() << endl;
		//写入好友的id和昵称,遍历map
		map<string, string>& fris = user->getFriendList();
		for (map<string, string>::iterator fit = fris.begin(); fit != fris.end(); fit++) {
			ofs << fit->first << " ";
			//考虑无备注的特殊情况
			if (fit->second.compare("") == 0) {
				ofs << "未设置";
			}
			else ofs << fit->second;
			ofs << endl;
		}
		//分隔20个等号，表示结束
		ofs << "====================" << endl;
	}
	ofs.close();
}

void WeiboFile::writeGroup() {
	ofs.open("./DataFile/WeiboGroup.txt", ios::trunc);
	//第一行，写入nextGroupId
	ofs << WeiboGroupCollections::nextGroupId << endl;
	//遍历Group集合
	map<string, GroupLYC*>& groups = WeiboGroupCollections::getMap();
	for (map<string, GroupLYC*>::iterator it = groups.begin(); it != groups.end(); it++) {
		GroupLYC* group = it->second;
		//第一行，群的基本信息
		ofs << group->getId() << " " << group->getHostId() << " " << group->getName() << " " << endl;
		//第二行，群成员id,遍历members
		set<string>& members = group->getMembersSet();
		for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
			if (mit != members.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//分隔20个等号，表示一个群写入文件结束
		ofs << "====================" << endl;
	}
	ofs.close();
}