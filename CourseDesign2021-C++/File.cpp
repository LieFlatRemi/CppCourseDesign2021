#include"File.h"

//���캯���������ļ�
FileLYC::FileLYC() {
}

//����������д���ļ�
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
	ifs.open("./DataFile/QQUser.txt", ios::in);			//Ϊ���ļ������ļ�
	//�ȶ���һ��
	getline(ifs, key);
	QQUserCollections::nextRegisterId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//����һ��
		//�ո�ָ��ַ���
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
		//��ȡ���ѣ��ָ���֮ǰ
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0) {			//�ָ�
				break;
			}
			int split = key.find(" ");
			string friId = key.substr(0, split);
			string remark = key.substr(split + 1, key.length());
			if (remark.compare("δ����") == 0) {
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
	//�ȶ���һ��nextGroupId
	getline(ifs, key);
	QQGroupCollections::nextGroupId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//����һ�У��ո�ָ��ַ���
		strs = Tools::splitString(key, ' ');
		//Ⱥid�� Ⱥ��id�� Ⱥ��
		QQGroupCollections::addGroupFromFile(new QQGroupLYC(strs.at(0), strs.at(1), strs.at(2)));
		QQGroupLYC* group = (QQGroupLYC*)QQGroupCollections::getGroup(strs.at(0));
		group->setChildId(atoi(strs.at(3).c_str()));					//��Ⱥid��
		//���ڶ���Ⱥ��Ա
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addMember(*sit);
		}
		//�������й���Ա
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addManager(*sit);
		}
		//�������м�Ⱥ����
		getline(ifs, key);
		strs = Tools::splitString(key, ' ');
		for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
			group->addRequest(*sit);
		}
		//����������Ⱥ����
		getline(ifs, key);
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0)	break;
			//����һ�У��ո�ָ��ַ���
			strs = Tools::splitString(key, ' ');
			//Ⱥid�� Ⱥ��id�� Ⱥ������Ⱥָ��
			group->addChildsFromFile(new QQChildGroupLYC(strs.at(0), strs.at(1), strs.at(2), group));
			QQChildGroupLYC* child = group->searchChilds(strs.at(0));
			//�ڶ��У���Ⱥ��Ա
			getline(ifs, key);
			strs = Tools::splitString(key, ' ');
			for (vector<string>::iterator sit = strs.begin(); sit != strs.end(); sit++) {
				child->addMember(*sit);
			}
			//��ȡ�ָ���
			getline(ifs, key);
		}
	}
	ifs.close();
}

void QQFile::writeUser() {
	ofs.open("./DataFile/QQUser.txt", ios::trunc);		//����ļ�������ɾ�����ٴ���
	//��д��id
	ofs << QQUserCollections::nextRegisterId << endl;
	//����User����
	map<string, UserLYC*>& users = QQUserCollections::getMap();
	for (map<string, UserLYC*>::iterator it = users.begin(); it != users.end(); it++) {
		QQUserLYC* user = (QQUserLYC*)it->second;		//��ȡUserָ��
		//д����Ϣ
		ofs << user->getUserId() << " ";
		ofs << user->getPasswd() << " ";
		ofs << user->getNickName() << " ";
		ofs << user->getBirth() << " ";
		ofs << user->getCreateYear() << " ";
		ofs << user->getAddress() << " ";
		if (user->getIsBind())	ofs << "1" ;
		else ofs << "0" ;
		ofs << endl;
		//д����ѵ�id���ǳ�,����map
		map<string, string>& fris = user->getFriendList();
		for (map<string, string>::iterator fit = fris.begin(); fit != fris.end(); fit++) {
			ofs << fit->first << " ";
			//�����ޱ�ע���������
			if (fit->second.compare("") == 0) {
				ofs << "δ����";
			}
			else ofs << fit->second;
			ofs << endl;
		}
		//�ָ�20���Ⱥţ���ʾ����
		ofs << "====================" << endl;
	}
	ofs.close();
}

void QQFile::writeGroup() {
	ofs.open("./DataFile/QQGroup.txt", ios::trunc);
	//��һ�У�д��nextGroupId
	ofs << QQGroupCollections::nextGroupId << endl;
	//����Group����
	map<string, GroupLYC*>& groups = QQGroupCollections::getMap();
	for (map<string, GroupLYC*>::iterator it = groups.begin(); it != groups.end(); it++) {
		QQGroupLYC* group = (QQGroupLYC*)it->second;
		//��һ�У�Ⱥ�Ļ�����Ϣ
		ofs << group->getId() << " " << group->getHostId() << " " << group->getName() << " ";
		ofs << group->getChildId() << endl;			//qqȺ��һ����Ⱥid��
		//�ڶ��У�Ⱥ��Աid,����members
		set<string>& members = group->getMembersSet();
		for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
			if (mit != members.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//�����У�����Աid��QQȺ����
		set<string>& managers = group->getManagersSet();
		for (set<string>::iterator mit = managers.begin(); mit != managers.end(); mit++) {
			if (mit != managers.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//�����У���Ⱥ����id��QQȺ����
		set<string>& requests = group->getRequestsSet();
		for (set<string>::iterator rit = requests.begin(); rit != requests.end(); rit++) {
			if (rit != requests.begin())	ofs << " ";
			ofs << *rit;
		}
		ofs << endl;
		//�ָ�10���Ⱥţ���ʾ֮�󲿷�Ϊ��Ⱥ
		ofs << "==========" << endl;
		map<string, QQChildGroupLYC*>& childs = group->getChildsMap();
		//��Ⱥ���֣���Ⱥ����
		for (map<string, QQChildGroupLYC*>::iterator git = childs.begin(); git != childs.end(); git++) {
			QQChildGroupLYC* child = git->second;
			//��һ�У�Ⱥ�Ļ�����Ϣ������Ҫ��Ⱥid����Ϊ�ļ����ȶ�ȡ��Ⱥ��
			ofs << child->getId() << " " << child->getHostId() << " " << child->getName() << " " << endl;
			//�ڶ��У�Ⱥ��Աid,����members
			set<string>& members = child->getMembersSet();
			for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
				if (mit != members.begin())	ofs << " ";
				ofs << *mit;
			}
			ofs << endl;
			//�ָ�10���Ⱥţ���ʾһ����Ⱥд�����
			ofs << "==========" << endl;
		}
		//�ָ�20���Ⱥţ���ʾһ��Ⱥд���ļ�����
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
	ifs.open("./DataFile/WechatUser.txt", ios::in);			//Ϊ���ļ������ļ�
	getline(ifs, key);
	WechatUserCollections::nextWcId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//����һ��
		//�ո�ָ��ַ���
		vector<string> strs = Tools::splitString(key, ' ');
		string id = strs.at(1);
		string pwd = strs.at(2);
		string nickName = strs.at(3);
		WechatUserCollections::addUserFromFile(nickName, pwd, id);
		WechatUserLYC* user = (WechatUserLYC*)WechatUserCollections::getUser(id);
		if (strs.at(0).compare("δ��") == 0)	user->setUserId("");
		else user->setUserId(strs.at(0));
		user->setBirth(strs.at(4));
		user->setCreateYear(atoi(strs.at(5).c_str()));
		user->setAddress(strs.at(6));
		//��ȡ���ѣ��ָ���֮ǰ
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0) {			//�ָ�
				break;
			}
			int split = key.find(" ");
			string friId = key.substr(0, split);
			string remark = key.substr(split + 1, key.length());
			if (remark.compare("δ����") == 0) {
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
	//�ȶ���һ��nextGroupId
	getline(ifs, key);
	WechatGroupCollections::nextGroupId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//����һ�У��ո�ָ��ַ���
		strs = Tools::splitString(key, ' ');
		//Ⱥid�� Ⱥ��id�� Ⱥ��
		WechatGroupCollections::addGroupFromFile(new WechatGroupLYC(strs.at(0), strs.at(1), strs.at(2)));
		GroupLYC* group = WechatGroupCollections::getGroup(strs.at(0));
		//���ڶ���Ⱥ��Ա
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
	ofs.open("./DataFile/WechatUser.txt", ios::trunc);		//����ļ�������ɾ�����ٴ���
	//��д��id
	ofs << WechatUserCollections::nextWcId << endl;
	//����User����
	map<string, UserLYC*>& users = WechatUserCollections::getMap();
	for (map<string, UserLYC*>::iterator it = users.begin(); it != users.end(); it++) {
		WechatUserLYC* user = (WechatUserLYC*)it->second;		//��ȡUserָ��
		//д����Ϣ
		//���δ��QQ��д��δ��
		if (user->getUserId().compare("") == 0)	ofs << "δ��" << " ";
		else ofs << user->getUserId() << " ";
		ofs << user->getWechatId() << " ";
		ofs << user->getPasswd() << " ";
		ofs << user->getNickName() << " ";
		ofs << user->getBirth() << " ";
		ofs << user->getCreateYear() << " ";
		ofs << user->getAddress() << endl;
		//д����ѵ�id���ǳ�,����map
		map<string, string>& fris = user->getFriendList();
		for (map<string, string>::iterator fit = fris.begin(); fit != fris.end(); fit++) {
			ofs << fit->first << " ";
			//�����ޱ�ע���������
			if (fit->second.compare("") == 0) {
				ofs << "δ����";
			}
			else ofs << fit->second;
			ofs << endl;
		}
		//�ָ�20���Ⱥţ���ʾ����
		ofs << "====================" << endl;
	}
	ofs.close();
}

void WechatFile::writeGroup() {
	ofs.open("./DataFile/WechatGroup.txt", ios::trunc);
	//��һ�У�д��nextGroupId
	ofs << WechatGroupCollections::nextGroupId << endl;
	//����Group����
	map<string, GroupLYC*>& groups = WechatGroupCollections::getMap();
	for (map<string, GroupLYC*>::iterator it = groups.begin(); it != groups.end(); it++) {
		GroupLYC* group = it->second;
		//��һ�У�Ⱥ�Ļ�����Ϣ
		ofs << group->getId() << " " << group->getHostId() << " " << group->getName() << " " << endl;
		//�ڶ��У�Ⱥ��Աid,����members
		set<string>& members = group->getMembersSet();
		for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
			if (mit != members.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//�ָ�20���Ⱥţ���ʾһ��Ⱥд���ļ�����
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
	ifs.open("./DataFile/WeiboUser.txt", ios::in);			//Ϊ���ļ������ļ�
	while (getline(ifs, key)) {
		//����һ��
		//�ո�ָ��ַ���
		vector<string> strs = Tools::splitString(key, ' ');
		string id = strs.at(0);
		string pwd = strs.at(1);
		string nickName = strs.at(2);
		WeiboUserCollections::addUserFromFile(nickName, pwd, id);
		WeiboUserLYC* user = (WeiboUserLYC*)WeiboUserCollections::getUser(id);
		user->setBirth(strs.at(3));
		user->setCreateYear(atoi(strs.at(4).c_str()));
		user->setAddress(strs.at(5));
		//��ȡ���ѣ��ָ���֮ǰ
		while (getline(ifs, key)) {
			if (key.compare("====================") == 0) {			//�ָ�
				break;
			}
			int split = key.find(" ");
			string friId = key.substr(0, split);
			string remark = key.substr(split + 1, key.length());
			if (remark.compare("δ����") == 0) {
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
	//�ȶ���һ��nextGroupId
	getline(ifs, key);
	WeiboGroupCollections::nextGroupId = atoi(key.c_str());
	while (getline(ifs, key)) {
		//����һ�У��ո�ָ��ַ���
		strs = Tools::splitString(key, ' ');
		//Ⱥid�� Ⱥ��id�� Ⱥ��
		WeiboGroupCollections::addGroupFromFile(new WeiboGroupLYC(strs.at(0), strs.at(1), strs.at(2)));
		GroupLYC* group = WeiboGroupCollections::getGroup(strs.at(0));
		//���ڶ���Ⱥ��Ա
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
	ofs.open("./DataFile/WeiboUser.txt", ios::trunc);		//����ļ�������ɾ�����ٴ���
	//����User����
	map<string, UserLYC*>& users = WeiboUserCollections::getMap();
	for (map<string, UserLYC*>::iterator it = users.begin(); it != users.end(); it++) {
		WeiboUserLYC* user = (WeiboUserLYC*)it->second;		//��ȡUserָ��
		//д����Ϣ
		ofs << user->getUserId() << " ";
		ofs << user->getPasswd() << " ";
		ofs << user->getNickName() << " ";
		ofs << user->getBirth() << " ";
		ofs << user->getCreateYear() << " ";
		ofs << user->getAddress() << endl;
		//д����ѵ�id���ǳ�,����map
		map<string, string>& fris = user->getFriendList();
		for (map<string, string>::iterator fit = fris.begin(); fit != fris.end(); fit++) {
			ofs << fit->first << " ";
			//�����ޱ�ע���������
			if (fit->second.compare("") == 0) {
				ofs << "δ����";
			}
			else ofs << fit->second;
			ofs << endl;
		}
		//�ָ�20���Ⱥţ���ʾ����
		ofs << "====================" << endl;
	}
	ofs.close();
}

void WeiboFile::writeGroup() {
	ofs.open("./DataFile/WeiboGroup.txt", ios::trunc);
	//��һ�У�д��nextGroupId
	ofs << WeiboGroupCollections::nextGroupId << endl;
	//����Group����
	map<string, GroupLYC*>& groups = WeiboGroupCollections::getMap();
	for (map<string, GroupLYC*>::iterator it = groups.begin(); it != groups.end(); it++) {
		GroupLYC* group = it->second;
		//��һ�У�Ⱥ�Ļ�����Ϣ
		ofs << group->getId() << " " << group->getHostId() << " " << group->getName() << " " << endl;
		//�ڶ��У�Ⱥ��Աid,����members
		set<string>& members = group->getMembersSet();
		for (set<string>::iterator mit = members.begin(); mit != members.end(); mit++) {
			if (mit != members.begin())	ofs << " ";
			ofs << *mit;
		}
		ofs << endl;
		//�ָ�20���Ⱥţ���ʾһ��Ⱥд���ļ�����
		ofs << "====================" << endl;
	}
	ofs.close();
}