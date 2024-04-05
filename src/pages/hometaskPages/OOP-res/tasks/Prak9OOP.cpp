#include <iostream>

using namespace std;

class String {
    private:
    char str[256];
    public:

    String(){
        str[0] = '\0';
    }

    ~String(){}

    void enterText(){
        cout << "Enter text: ";
        cin >> str;
    }

    void print(){
        cout << str << endl;
    }

    int length(){
        int i = 0;
        while(str[i] != '\0'){
            i++;
        }
        return i;
    }

    String operator+(String s){
        String result;
        int i = 0;
        while(str[i] != '\0'){
            result.str[i] = str[i];
            i++;
        }
        int j = 0;
        while(s.str[j] != '\0'){
            result.str[i] = s.str[j];
            i++;
            j++;
        }
        result.str[i] = '\0';
        return result;
    }
    bool operator==(String s){ return length() == s.length(); }
    bool operator>(String s){ return length() > s.length(); }
    bool operator!() { return length() == 0; }
};

class LongNumber {
    private:
    char num[256];
    public:

    LongNumber(){
        num[0] = '\0';
    }

    ~LongNumber(){}

    void enterNumber(){
        cout << "Enter number: ";
        cin >> num;
    }

    void print(){
        cout << num << endl;
    }

    LongNumber operator+(LongNumber n){
        // Перетворення рядків в числа
        int num1 = atoi(num);
        int num2 = atoi(n.num);
        // Додавання чисел
        LongNumber result;
        int sum = num1 + num2;
        // Перетворення числа в рядок
        sprintf(result.num, "%d", sum);
        return result;
    }
    LongNumber operator-(LongNumber n){
        int num1 = atoi(num);
        int num2 = atoi(n.num);
        // Віднімання чисел
        LongNumber result;
        int sub = num1 - num2;
        sprintf(result.num, "%d", sub);
        return result;
    }
    bool operator>(LongNumber n){
        int num1 = atoi(num);
        int num2 = atoi(n.num);
        if(num1 > num2){
            return true;
        } else {
            return false;
        }
    }
    bool operator<=(LongNumber n){
        int num1 = atoi(num);
        int num2 = atoi(n.num);
        if(num1 <= num2){
            return true;
        } else {
            return false;
        }
    }
    
    LongNumber operator++(int){
        LongNumber temp = *this;
        int num1 = atoi(num);
        num1++;
        sprintf(num, "%d", num1);
        return temp;
    }
    LongNumber operator--(){
        int num1 = atoi(num);
        num1--;
        sprintf(num, "%d", num1);
        return *this;
    }
    LongNumber operator-(){
        int num1 = atoi(num);
        num1 = -num1;
        sprintf(num, "%d", num1);
        return *this;
    }
    bool operator!(){ return atoi(num) == 0; }
    // Оператор правого зсуву
    LongNumber operator>>=(int n){
        int num1 = atoi(num);
        num1 >>= n;
        sprintf(num, "%d", num1);
        return *this;
    }
    // Оператор лівого зсуву
    LongNumber operator<<=(int n){
        int num1 = atoi(num);
        num1 <<= n;
        sprintf(num, "%d", num1);
        return *this;
    }
};



int main(){
    String s1, s2;
    s1.enterText();
    s2.enterText();
    cout << "Додавання рядків:" << endl;
    String s3 = s1 + s2;
    s3.print();
    cout << "Перевірка на рівність:" << endl;
    if(s1 == s2){
        cout << "Рядки рівні" << endl;
    } else {
        cout << "Рядки не рівні" << endl;
    }
    cout << "Перевірка на більшу кількість символів (s1 > s2):" << endl;
    if(s1 > s2){
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    cout << "Перевірка на пустий рядок:" << endl;
    if(!s1){
        cout << "Перший рядок пустий" << endl;
    } else {
        cout << "Перший рядок не пустий" << endl;
    }

    LongNumber n1, n2;
    n1.enterNumber();
    n2.enterNumber();
    cout << "Додавання чисел:" << endl;
    LongNumber n3 = n1 + n2;
    n3.print();
    cout << "Віднімання чисел:" << endl;
    LongNumber n4 = n1 - n2;
    n4.print();
    cout << "Перевірка на більше число (n1 > n2):" << endl;
    if(n1 > n2){
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    cout << "Перевірка на менше або рівне число (n1 <= n2):" << endl;
    if(n1 <= n2){
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    cout << "Постфіксний ++:" << endl;
    n1++;
    n1.print();
    cout << "Префіксний --:" << endl;
    --n1;
    n1.print();
    cout << "Унарний -:" << endl;
    -n1;
    n1.print();
    cout << "Перевірка на нуль:" << endl;
    if(!n1){
        cout << "Число дорівнює нулю" << endl;
    } else {
        cout << "Число не дорівнює нулю" << endl;
    }
    cout << "Оператор правого зсуву:" << endl;
    n1 >>= 2;
    n1.print();
    cout << "Оператор лівого зсуву:" << endl;
    n1 <<= 2;
    n1.print();

    return 0;
}