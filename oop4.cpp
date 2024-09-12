#include <iostream>
#include <windows.h>
using namespace std;

class User {
public:
	User(const string& _login, unsigned short _lvl) : login(_login), lvl(_lvl) {}
	void Look() const {
		cout << "Перегляд доступної інформації рівня " << lvl << endl;
	}
	void SetLvl(unsigned short _lvl) {
		lvl = _lvl;
	}
	unsigned short GetLvl() {
		return lvl;
	}
private:
	string login;
	unsigned short lvl;
};

class UserWithRights : protected User {
public:
	UserWithRights(const string& _login, unsigned short _lvl) : User(_login, _lvl) {}
	void LookAll() {
		cout << "Доступ до всієї доступної інформації рівня " << GetLvl() << endl;
	}
	void LookVIP() const {
		cout << "Перегляд інформації для VIP-користувачів" << endl;
	}
};

class Admin : protected UserWithRights {
public:
	Admin(const string& _login, unsigned short _lvl, unsigned short _adminLvl) : UserWithRights(_login, _lvl), adminLvl(_adminLvl) {}
	void AdminCommands() const {
		if (adminLvl >= 1) {
			cout << "/admins - Список адміністрації онлайн" << endl;
			cout << "/ans [player] [answer] - Відповісти користувачу" << endl;
		}
		if (adminLvl >= 2) {
			cout << "/warn [player] [reason] - Видати попередження" << endl;
			cout << "/unwarn [player] - Зняти попередження" << endl;
			cout << "/kick [player] [reason] - Заглушити користувача" << endl;
		}
		if (adminLvl >= 3) {
			cout << "/msg [message] - Вивести повідомлення всім користувачам" << endl;
			cout << "/ban [player] [days] - Заборонити доступ користувачу" << endl;
			cout << "/unban [player] - Повернути доступ користувачу" << endl;
			cout << "/setlvl [player] [lvl] - Видати рівень доступу" << endl;
		}
	}
	void CheckAdminLvl() const {
		cout << "Доступ до адмінки рівня " << adminLvl << endl;
	}
private:
	unsigned short adminLvl;
};

class SuperAdmin : protected Admin {
public:
	SuperAdmin(const string& _login, unsigned short _lvl, unsigned short _adminLvl) : Admin(_login, _lvl, _adminLvl) {}
	void ServerCommands() const {
		cout << "SERVER COMMANDS:" << endl;
		cout << "/restart - Перезавантаження сайту" << endl;
		cout << "/changeName [name] - Змінити назву сайту" << endl;
		cout << "/stop - Вимкнути сайт" << endl;
		cout << "/setadmin [player] [adminLvl] - Видати/змінити адмін-рівень користувачу" << endl;
	}
	void CallLook() {
		Look();
	}
	void CallSetLvl(unsigned short _lvl) {
		SetLvl(_lvl);
	}
	void CallAdminCommands() {
		AdminCommands();
	}
	void CallCheckAdminLvl() {
		CheckAdminLvl();
	}
	unsigned short CallGetLvl() {
		return GetLvl();
	}
	void CallLookAll() {
		LookAll();
	}
	void CallLookVIP() {
		LookVIP();
	}
};

class UserWithLimits : protected User {
public:
	UserWithLimits(const string& _login, unsigned short _lvl) : User(_login, _lvl) {}
	void LookLimit() {
		cout << "Доступ до обмеженої інформації рівня " << GetLvl() << endl;
	}
};

class Guest : protected UserWithLimits {
public:
	Guest(const string& _login, unsigned short _lvl) : UserWithLimits(_login, _lvl) {}
	void CallLook() {
		Look();
	}
	void CallSetLvl(unsigned short _lvl) {
		SetLvl(_lvl);
	}
	unsigned short CallGetLvl() {
		return GetLvl();
	}
	void Guesting() const {
		cout << "Гістюємо" << endl;
	}
	void CallLookLimit() {
		LookLimit();
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Guest g("Weird Newbie", 1);
	g.CallSetLvl(2);
	cout << g.CallGetLvl() << endl;
	g.CallLook();
	cout << endl;
	g.CallLookLimit();
	cout << endl;
	g.Guesting();
	cout << endl;
	SuperAdmin sa("WhoAmI", 5, 4);
	sa.CallSetLvl(6);
	cout << sa.CallGetLvl() << endl;
	sa.CallLook();
	cout << endl;
	sa.CallLookAll();
	cout << endl;
	sa.CallLookVIP();
	cout << endl;
	sa.CallAdminCommands();
	cout << endl;
	sa.CallCheckAdminLvl();
	cout << endl;
	sa.ServerCommands();
	cout << endl;
	return 0;
}
