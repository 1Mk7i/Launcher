#include <iostream>
#include <vector>
#include <string>

using namespace std;

string red = "\033[1;31m";
string green = "\033[1;32m";
string yellow = "\033[1;33m";
string blue = "\033[1;34m";
string magenta = "\033[1;35m";
string cyan = "\033[1;36m";
string reset = "\033[0m";


class Product {
private:
    static int nextID;
    int id;
    string name;
    double price;
    vector<string> keywords;

public:
    Product() {
        id = generateID();
    }

    Product(const Product& obj) {
        id = generateID();
        name = obj.name;
        price = obj.price;
        keywords = obj.keywords;
    }

    Product(const string& name, double price, const vector<string>& keywords) : 
        name(name), price(price), keywords(keywords) {
        id = generateID();
    }

    ~Product() {}

    static void showNextID() {
        cout << magenta << "Наступний ID: " << yellow << nextID << reset << endl;
    }

    int getID() const {
        return id;
    }

    void getInfo() const {
        cout << blue << "ID: " << yellow << id << reset << endl;
        cout << blue << "Назва: " << yellow << name << reset << endl;
        cout << blue << "Ціна: " << yellow << price << reset << endl;
        cout << blue << "Ключові слова: " << yellow;
        for (const auto& keyword : keywords) {
            cout << keyword << " " << reset;
        }
        cout << endl;
    }

    void findKeyword(const string& keyword) const {
        for (const auto& key : keywords) {
            if (key == keyword) {
                getInfo();
                break;
            }
        }
    }

    // Сеттери та геттери
    void setName(const string& newName) {
        name = newName;
    }

    string getName() const {
        return name;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    double getPrice() const {
        return price;
    }

    // Додавання ключового слова
    void addKeyword(const string& keyword) {
        keywords.push_back(keyword);
    }

    // Видалення ключового слова
    void removeKeyword(const string& keyword) {
        for (auto it = keywords.begin(); it != keywords.end(); ++it) {
            if (*it == keyword) {
                keywords.erase(it);
                break;
            }
        }
    }

// Статичне поле класу
private:
    static int generateID() {
        return nextID++;
    }
};

int Product::nextID = 100000;

int main() {
    cout << green << "Початок роботи" << reset << endl;
    vector<Product> products;

    // Додавання товарів
    products.emplace_back("Книга1", 100, vector<string>{"Книга"});
    products.emplace_back("Lenovo", 1000, vector<string>{"Комп'ютер"});
    products.emplace_back("Яблуко", 5, vector<string>{"Їжа"});

    // Перегляд інформації про товари
    for (const auto& product : products) {
        product.getInfo();
    }

    // Пошук за ключовим словом
    cout << cyan << "Пошук за ключовим словом 'Комп'ютер':" << reset << endl;
    for (const auto& product : products) {
        product.findKeyword("Комп'ютер");
    }

    // Зміна назви та ціни товару
    products[0].setName("Книга2");
    products[0].setPrice(200);

    // Додавання та видалення ключових слів
    products[0].addKeyword("Художня");
    products[0].removeKeyword("Книга");

    // Вивід оновленої інформації про перший товар
    products[0].getInfo();

    Product::showNextID();

    cout << red << "Кінець роботи" << reset << endl;
    return 0;
}
