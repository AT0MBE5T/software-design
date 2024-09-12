#include <iostream> //1
#include <vector>
#include <algorithm>

class Book {
public:
    static std::vector<Book> library;
    Book(std::string title, std::string author, int year) : title(title), author(author), year(year) {}
    void SetTitle(std::string _title) {
        title = _title;
    }
    void SetAuthor(std::string _author) {
        author = _author;
    }
    void SetYear(int _year) {
        year = _year;
    }
    std::string GetTitle() {
        return title;
    }
    std::string GetAuthor() {
        return author;
    }
    int GetYear() {
        return year;
    }
    void displayInfo() const {
        std::cout << "Title: " << title << ", Author: " << author << ", Year: " << year << std::endl;
    }

    bool operator<(const Book& other) const {
        return title < other.title;
    }

private:
    std::string title;
    std::string author;
    int year;
};

std::vector<Book> Book::library;

void Menu() {
    std::cout << "1. Add a book" << std::endl;
    std::cout << "2. Print the books" << std::endl;
    std::cout << "3. Remove a book" << std::endl;
    std::cout << "4. Edit a book" << std::endl;
    std::cout << "5. Sort the books" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

void AddBook(std::vector<Book>& vec) {
    std::string title, author;
    int year;
    std::cout << "Type a title: ";
    std::cin >> title;
    std::cout << "Type a author: ";
    std::cin >> author;
    std::cout << "Type a year: ";
    std::cin >> year;
    vec.push_back(Book(title, author, year));
}

void PrintBooks(std::vector<Book>& vec) {
    for (const auto& i : vec) i.displayInfo();
}

void RemoveBook(std::vector<Book>& vec) {
    int choice;
    PrintBooks(vec);
    do {
        std::cout << "Select a book(1-" << vec.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 && choice > vec.size());
    choice--;
    std::vector<Book>::iterator it = begin(vec);
    std::advance(it, choice);
    vec.erase(it);
}

void EditBook(std::vector<Book>& vec) {
    int choice, year;
    std::string title, author;
    PrintBooks(vec);
    do {
        std::cout << "Select a book(1-" << vec.size() << "): ";
        std::cin >> choice;
    } while (choice < 1 && choice > vec.size());
    choice--;
    std::cout << "Type a title: ";
    std::cin >> title;
    std::cout << "Type a author: ";
    std::cin >> author;
    std::cout << "Type a year: ";
    std::cin >> year;
    vec[choice].SetTitle(title);
    vec[choice].SetAuthor(author);
    vec[choice].SetYear(year);
}

void Sort(std::vector<Book>& vec) {
    std::sort(begin(vec), end(vec));
    std::cout << "Sorted!" << std::endl;
}

int main() {
    char c{};
    while (c != 54) {
        Menu();
        do {
            std::cout << "Select item: ";
            std::cin >> c;
        } while (c != 49 && c != 50 && c != 51 && c != 52 && c != 53 && c != 54);
        system("cls");
        switch (c) {
        case 49:
            AddBook(Book::library);
            system("cls");
            break;
        case 50:
            PrintBooks(Book::library);
            system("pause");
            system("cls");
            break;
        case 51:
            RemoveBook(Book::library);
            system("cls");
            break;
        case 52:
            EditBook(Book::library);
            system("cls");
            break;

        case 53:
            Sort(Book::library);
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    }
    return 0;
}




#include <iostream> //2
#include <vector>
#include <algorithm>
#include <windows.h>

void Menu() {
    std::cout << "1. Додати фрукт" << std::endl;
    std::cout << "2. Відсортувати фрукти за зростанням" << std::endl;
    std::cout << "3. Відсортувати фрукти за спаданням" << std::endl;
    std::cout << "4. Вивести фрукти" << std::endl;
    std::cout << "5. Вихід" << std::endl;
}

void AddFruit(std::vector<std::string>& vec) {
    std::string fruit;
    std::cout << "Введіть свої улюблені фрукти (введіть 'кінець', щоб завершити введення):" << std::endl;
    while (true) {
        std::cout << "Фрукт: ";
        std::cin >> fruit;
        if (fruit == "кінець")break;
        vec.push_back(fruit);
    }
}

void SortByDesc(std::vector<std::string>& vec) {
    std::sort(vec.rbegin(), vec.rend());
    std::cout << "Успіх!" << std::endl;
}

void SortByAsc(std::vector<std::string>& vec) {
    std::sort(vec.begin(), vec.end());
    std::cout << "Успіх!" << std::endl;
}

void PrintFruits(std::vector<std::string>& vec) {
    for (const auto& i : vec) std::cout << i << std::endl;
}

int main() {
    std::vector<std::string> favoriteFruits;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Ласкаво просимо до гри 'Сортування фруктів'!" << std::endl;
    char c{};
    while (c != 53) {
        Menu();
        do {
            std::cout << "Оберіть пункт: ";
            std::cin >> c;
        } while (c != 49 && c != 50 && c != 51 && c != 52 && c != 53);
        system("cls");
        switch (c) {
        case 49:
            AddFruit(favoriteFruits);
            system("cls");
            break;
        case 50:
            SortByAsc(favoriteFruits);
            system("pause");
            system("cls");
            break;
        case 51:
            SortByDesc(favoriteFruits);
            system("pause");
            system("cls");
            break;
        case 52:
            PrintFruits(favoriteFruits);
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    }
    return 0;
}




#include <iostream> //3
#include <list>
#include <unordered_set>
#include <string>
#include <iomanip>
#include <windows.h>

class Joke {
public:
    Joke(std::string text) : text(text), votes(0), totalRating(0) {}

    void tellJoke() const {
        std::cout << "Жарт: " << text << std::endl;
        std::cout << "Оцінка: " << std::fixed << std::setprecision(2) << getAverageRating() << " (Голосів: " << votes << ")" << std::endl;
    }

    bool rateJoke(int rating) {
        if (rating >= 1 && rating <= 5) {
            votes++;
            totalRating += rating;
            return true;
        }
        else {
            std::cout << "Оцінка повинна бути від 1 до 5!" << std::endl;
            return false;
        }
    }
    std::string getText() {
        return text;
    }
    double getAverageRating() const {
        return (votes > 0) ? static_cast<double>(totalRating) / votes : 0.0;
    }

private:
    std::string text;
    int votes;
    int totalRating;
};

void Menu() {
    std::cout << "1. Додати жарти" << std::endl;
    std::cout << "2. Оцінити жарти" << std::endl;
    std::cout << "3. Вивести жарти за рейтингом" << std::endl;
    std::cout << "4. Наступний гравець" << std::endl;
    std::cout << "5. Вихід" << std::endl;
}

void AddJokes(std::list<Joke>& vec) {
    std::string joke;
    std::cout << "Для повернення у меню введіть 'кінець'" << std::endl;
    while (true) {
        std::cout << "Жарт №" << vec.size() + 1 << ": ";
        std::cin >> joke;
        if (joke == "кінець")break;
        vec.push_back(joke);
    }
}

void EstimateJokes(std::list<Joke>& vec, std::unordered_set<unsigned short>& chosed) {
    unsigned short userRating{};
    unsigned short dec{};
    do {
        for (auto& i : vec) std::cout << i.getText() << std::endl;
        do {
            if (chosed.size() == vec.size())return;
            std::cout << "Оберіть жарт для оцінки(1-" << vec.size() << "): ";
            std::cin >> dec;
            if (chosed.find(dec - 1) != chosed.end())std::cout << "Ви вже оцінили цей жарт" << std::endl;
        } while (dec < 1 || dec > vec.size() || chosed.find(dec - 1) != chosed.end());
        dec--;
        chosed.insert(dec);
        system("cls");
        auto it = vec.begin();
        std::advance(it, dec);
        it->getText();
        do {
            std::cout << "Ваша оцінка (1-5): ";
            std::cin >> userRating;
        } while (!it->rateJoke(userRating));
        do {
            std::cout << "Введіть 0 для продовження або 1 для виходу у меню: ";
            std::cin >> dec;
        } while (dec < 0 || dec > 1);
        system("cls");
    } while (!dec);
}

void PrintJokesByRating(std::list<Joke>& vec) {
    double decision;
    do {
        std::cout << "Введіть від якого рейтингу будуть виводитися елементи: ";
        std::cin >> decision;
    } while (decision < 0 && decision > 5);
    system("cls");
    for (const auto& joke : vec) {
        if (joke.getAverageRating() >= decision) {
            joke.tellJoke();
        }
    }
}

int main() {
    std::list<Joke> jokeList;
    std::unordered_set<unsigned short> chosed;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char c{};
    int people;
    int currentPlayer{};
    std::cout << "Введіть кількість гравців: ";
    std::cin >> people;
    while (c != 53 && currentPlayer != people) {
        std::cout << "Гравець №" << currentPlayer + 1 << std::endl;
        Menu();
        do {
            std::cout << "Оберіть пункт: ";
            std::cin >> c;
        } while (c != 49 && c != 50 && c != 51 && c != 52 && c != 53);
        system("cls");
        switch (c) {
        case 49:
            AddJokes(jokeList);
            system("cls");
            break;
        case 50:
            EstimateJokes(jokeList, chosed);
            system("cls");
            break;
        case 51:
            PrintJokesByRating(jokeList);
            system("pause");
            system("cls");
            break;
        case 52:
            currentPlayer++;
            chosed.clear();
            break;
        default:
            break;
        }
    }
    return 0;
}



#include <iostream> //4
#include <list>
#include <map>
#include <string>
#include <windows.h>

void Log(std::list<std::pair<std::string, std::map<std::string, double>>>& log) {
    for (const auto& i : log) {
        std::cout << "Запит: " << i.first << ". Результат: ";
        for (const auto& j : i.second) {
            std::cout << j.first << " - " << j.second << " ; ";
        }
        std::cout << std::endl;
    }
}
void AddStudents(std::map<std::string, double>& m, std::list<std::pair<std::string, std::map<std::string, double>>>& log) {
    std::string name;
    double grade;
    std::cout << "Введіть ім'я студента: ";
    std::cin >> name;
    std::cout << "Введіть бал студента: ";
    std::cin >> grade;
    m.insert(m.end(), std::make_pair(name, grade));
    std::map<std::string, double> mt{ {name,grade} };
    log.push_back(std::make_pair("Додавання студента", mt));
}
void PrintStudents(std::map<std::string, double>& m, std::list<std::pair<std::string, std::map<std::string, double>>>& log) {
    std::map<std::string, double> mt;
    for (const auto& i : m) {
        std::cout << i.first << " : " << i.second << std::endl;
        mt.emplace(std::make_pair(i.first, i.second));
    }
    log.push_back(std::make_pair("Виведення даних", mt));
}

void SearchStudent(std::map<std::string, double>& m, std::list<std::pair<std::string, std::map<std::string, double>>>& log) {
    std::string searchStudent;
    std::cout << "Введіть ім'я студента для пошуку середнього балу: ";
    std::cin >> searchStudent;
    auto it = m.find(searchStudent);
    if (it != m.end()) {
        std::cout << "Середній бал студента " << searchStudent << ": " << it->second << std::endl;
        std::map<std::string, double> mt{ {searchStudent, it->second} };
        log.push_back(std::make_pair("Пошук студента", mt));
    }
    else {
        std::cout << "Студент з іменем " << searchStudent << " не знайдений." << std::endl;
        std::map<std::string, double> mt{ {searchStudent, -1} };
        log.push_back(std::make_pair("Невдалий пошук студента", mt));
    }
}

void Menu() {
    std::cout << "1. Додати студентів" << std::endl;
    std::cout << "2. Вивести студентів" << std::endl;
    std::cout << "3. Пошук студента" << std::endl;
    std::cout << "4. Журнал запитів" << std::endl;
    std::cout << "5. Вихід" << std::endl;
}

int main() {
    std::map<std::string, double> studentGrades;
    std::list<std::pair<std::string, std::map<std::string, double>>> log;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char c{};
    while (c != 53) {
        Menu();
        do {
            std::cout << "Оберіть пункт: ";
            std::cin >> c;
        } while (c != 49 && c != 50 && c != 51 && c != 52 && c != 53);
        system("cls");
        switch (c) {
        case 49:
            AddStudents(studentGrades, log);
            system("cls");
            break;
        case 50:
            PrintStudents(studentGrades, log);
            system("pause");
            system("cls");
            break;
        case 51:
            SearchStudent(studentGrades, log);
            system("pause");
            system("cls");
            break;
        case 52:
            Log(log);
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    }
    return 0;
}
