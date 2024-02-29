#include <iostream>
#include <vector>

using namespace std;

class Product {
private:
    static int ID;
    string name;
    double price;
    int idProduct;
    string kay;
    vector<string> Keywords;
public:
    Product() {
        cout << "Початок роботи" << endl;
    }

    Product(const Product& obj) {
        ID = obj.ID;
        name = obj.name;
        price = obj.price;
        Keywords = obj.Keywords;
    }

    Product(vector<vector<string>> arr) {
        for (int i = 0; i < arr.size(); i++) {
            idProduct = ID;
            name = arr[i][0];
            price = stod(arr[i][2]);
            kay = arr[i][1];
            Keywords.push_back(kay);
        }
        ID++;
    }

    ~Product() {
        cout << "Кінець роботи" << endl;
    }

    static void showID() {
        cout << "ID: " << ID << endl;
    }

    void get() {
        cout << "ID: " << idProduct << endl;
        cout << "Name: " << name << endl;
        cout << "Price: " << price << endl;
        cout << "Keywords: ";
        for (int i = 0; i < Keywords.size(); i++) {
            cout << Keywords[i] << " ";
        }
        cout << endl;
    }

    void find(string keyword) {
        
    }
};

int Product::ID = 100000;

int main() {
    vector<vector<string>> array1 = {
        {"Книга1", "Книга", "100"},
        {"Lenovo", "Комп'ютер", "1000"},
        {"Яблуко", "Їжа", "5"}
    };
    Product product1(array1);
    Product product2(array1);
    product1.get();
    Product::showID();
    product2.get();
    Product::showID();
    product1.find("Книга");
    product2.find("Телефон");
    return 0;
}
