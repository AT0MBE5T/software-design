#include <iostream>
#include <vector>
using namespace std;

class Character {
protected:
    string name;
    int health;
    int power;
public:
    Character(string, int, int);
    string getName();
    int getHealth();
    bool isAlive();
    void takeDamage(int);
    void Print();

    virtual void attack(Character&, int) = 0;
};
class Hero : public Character {
private:
    static vector<Hero>heroes;
public:
    Hero(string, int, int);
    static vector<Hero>& getVector();
    void attack(Character&, int) override;
};

class Monster : public Character {
private:
    static vector<Monster> monsters;
public:
    Monster(string, int, int);
    static vector<Monster>& getVector();
    void attack(Character&, int) override;
};

vector<Hero> Hero::heroes;
vector<Monster> Monster::monsters;

void Fill();

void AttackLogic(int, int);

void Round();

void Start();

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    Fill();
    Start();
    return 0;
}

Character::Character(string _name, int _health, int _power) : name(_name), health(_health), power(_power) {}
string Character::getName() {
    return name;
}
int Character::getHealth() {
    return health;
}
bool Character::isAlive() {
    return health > 0;
}
void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

void Character::Print() {
    cout << " name: " << name << " health: " << health << " power: " << power << endl;
}

Hero::Hero(string _name, int _health, int _power) : Character(_name, _health, _power) {}
vector<Hero>& Hero::getVector() {
    return heroes;
}
void Hero::attack(Character& target, int id) {
    int damage = rand() % power + 1;
    target.takeDamage(damage);
    cout << name << " attacks " << target.getName() << " for " << damage << " damage " << endl;
    cout << name << " shouts a heroic battle cry!" << endl;
    if (!target.isAlive()) {
        cout << target.getName() << " is defeated!" << endl;
        Monster::getVector().erase(Monster::getVector().begin() + id);
    }
}
Monster::Monster(string _name, int _health, int _power) : Character(_name, _health, _power) {}
vector<Monster>& Monster::getVector() {
    return monsters;
}
void Monster::attack(Character& target, int id) {
    int damage = rand() % power + 1;
    target.takeDamage(damage);
    cout << name << " attacks " << target.getName() << " for " << damage << " damage " << endl;
    cout << name << " growls menacingly!" << endl;
    if (!target.isAlive()) {
        cout << target.getName() << " is defeated!" << endl;
        Hero::getVector().erase(Hero::getVector().begin() + id);
    }
}
void Start() {
    while (!Hero::getVector().empty() && !Monster::getVector().empty()) Round();
    if (Hero::getVector().empty()) cout << "Monsters won!";
    else cout << "Heroes won!";
}
void Fill() {
    int h, m, health, power;
    string name;
    cout << "Enter amount of heroes: ";
    cin >> h;
    cout << "Enter amount of monsters: ";
    cin >> m;
    for (int i = 0; i < h; ++i) {
        cout << "Name of hero: ";
        cin >> name;
        cout << "Health of hero: ";
        cin >> health;
        cout << "Power of hero: ";
        cin >> power;
        Hero::getVector().push_back(Hero(name, health, power));
    }
    for (int i = 0; i < m; ++i) {
        cout << "Name of monster: ";
        cin >> name;
        cout << "Health of monster: ";
        cin >> health;
        cout << "Power of monster: ";
        cin >> power;
        Monster::getVector().push_back(Monster(name, health, power));
    }
}

void AttackLogic(int isRandom, int isHeroFirst) {
    int iUnder;
    int iAttack;
    if (isHeroFirst == 1) {
        if (isRandom == 1) {
            iUnder = rand() % Monster::getVector().size();
            iAttack = rand() % Hero::getVector().size();
        }
        else {
            for (auto& i : Hero::getVector()) i.Print();
            do {
                cout << "Choose the character(id 1-" << Hero::getVector().size() << "): ";
                cin >> iAttack;
            } while (iAttack < 1 || iAttack > Hero::getVector().size());
            iAttack--;
            for (auto& i : Monster::getVector()) i.Print();
            do {
                cout << "Choose the character(id 1-" << Monster::getVector().size() << "): ";
                cin >> iUnder;
            } while (iUnder < 1 || iUnder > Monster::getVector().size());
            iUnder--;
        }
        if (!Monster::getVector().empty())Hero::getVector()[iAttack].attack(Monster::getVector()[iUnder], iUnder);
    }
    else {
        if (isRandom == 1) {
            iUnder = rand() % Monster::getVector().size();
            iAttack = rand() % Hero::getVector().size();
        }
        else {
            for (auto& i : Monster::getVector()) i.Print();
            do {
                cout << "Choose the character(id 1-" << Monster::getVector().size() << "): ";
                cin >> iAttack;
            } while (iAttack < 1 || iAttack > Monster::getVector().size());
            iAttack--;
            for (auto& i : Hero::getVector()) i.Print();
            do {
                cout << "Choose the character(id 1-" << Hero::getVector().size() << "): ";
                cin >> iUnder;
            } while (iUnder < 1 || iUnder > Hero::getVector().size());
            iUnder--;
        }
        if (!Hero::getVector().empty())Monster::getVector()[iAttack].attack(Hero::getVector()[iUnder], iUnder);
    }
}

void Round() {
    int dec, who;
    do {
        cout << "1 Random" << endl;
        cout << "2 Input" << endl;
        cin >> dec;
    } while (dec < 1 || dec > 2);
    do {
        cout << "Who attacks?(1-Heroes, 2-Monsters): ";
        cin >> who;
    } while (who < 1 || who > 2);
    AttackLogic(dec, who);
}
