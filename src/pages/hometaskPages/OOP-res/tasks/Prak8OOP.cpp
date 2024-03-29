#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class KvadratnaMatrix {
private:
    vector<vector<double>> matrix;
    int size;
public:
    KvadratnaMatrix(int s) : size(s) {
        matrix.resize(size, vector<double>(size, 0));
    }

    ~KvadratnaMatrix() {}

    void print() {
        for (int i = 0; i < size; i++) {
            cout << "| ";
            for (int j = 0; j < size; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << "|" << endl;
        }
    }

    void setMatrix(vector<vector<double>> data) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = data[i][j];
            }
        }
    }

    friend KvadratnaMatrix operator+(const KvadratnaMatrix& m1, const KvadratnaMatrix& m2);
    friend KvadratnaMatrix operator-(const KvadratnaMatrix& m1, const KvadratnaMatrix& m2);
    friend KvadratnaMatrix operator-(const KvadratnaMatrix& m1);
};

KvadratnaMatrix operator+(const KvadratnaMatrix& m1, const KvadratnaMatrix& m2) {
    KvadratnaMatrix result(m1.size);
    // Додаємо відповідні елементи матриць
    for (int i = 0; i < m1.size; i++) {
        for (int j = 0; j < m1.size; j++) {
            result.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
        }
    }
    return result;
}

KvadratnaMatrix operator-(const KvadratnaMatrix& m1, const KvadratnaMatrix& m2) {
    KvadratnaMatrix result(m1.size);
    // Віднімаємо відповідні елементи матриць
    for (int i = 0; i < m1.size; i++) {
        for (int j = 0; j < m1.size; j++) {
            result.matrix[i][j] = m1.matrix[i][j] - m2.matrix[i][j];
        }
    }
    return result;
}

KvadratnaMatrix operator-(const KvadratnaMatrix& m1) {
    KvadratnaMatrix result(m1.size);

    int n = m1.size;
    std::vector<std::vector<double>> identity(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; ++i)
        identity[i][i] = 1;

    std::vector<std::vector<double>> tempMatrix(m1.matrix);

    for (int i = 0; i < n; ++i) {
        double divisor = tempMatrix[i][i];

        if (divisor == 0) {
            bool found = false;
            for (int k = i + 1; k < n; ++k) {
                if (tempMatrix[k][i] != 0) {
                    std::swap(tempMatrix[i], tempMatrix[k]);
                    std::swap(identity[i], identity[k]);
                    divisor = tempMatrix[i][i];
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Error: matrix is singular" << endl;
                return result;
            }
        }

        for (int j = 0; j < n; ++j) {
            tempMatrix[i][j] /= divisor;
            identity[i][j] /= divisor;
        }

        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double multiplier = tempMatrix[k][i];
                for (int j = 0; j < n; ++j) {
                    tempMatrix[k][j] -= multiplier * tempMatrix[i][j];
                    identity[k][j] -= multiplier * identity[i][j];
                }
            }
        }
    }

    result.matrix = identity;
    return result;
}

class mnozhyna {
private:
    vector<double> data;
public:
    mnozhyna() {}
    mnozhyna(const vector<double>& data) : data(data) {}
    ~mnozhyna() {}

    void print() {
        cout << "{ ";
        for (const auto& el : data) {
            cout << el << " ";
        }
        cout << "}" << endl;
    }

    friend mnozhyna operator>(const mnozhyna& m1, const mnozhyna& m2);
    friend mnozhyna operator<(const mnozhyna& m1, const mnozhyna& m2);
    friend bool operator==(const mnozhyna& m1, const mnozhyna& m2);
    friend bool operator!=(const mnozhyna& m1, const mnozhyna& m2);
};
// Порівняння розмірів множин
mnozhyna operator>(const mnozhyna& m1, const mnozhyna& m2) {
    mnozhyna result;

    if (m1.data.size() > m2.data.size()) {
        result.data = m1.data;
    } else {
        result.data = m2.data;
    }
    return result;
}
mnozhyna operator<(const mnozhyna& m1, const mnozhyna& m2) {
    mnozhyna result;
    if (m1.data.size() < m2.data.size()) {
        result.data = m1.data;
    } else {
        result.data = m2.data;
    }
    return result;
}
bool operator==(const mnozhyna& m1, const mnozhyna& m2) {
    // Перевіряємо, чи розміри множин однакові
    if (m1.data.size() != m2.data.size()) {
        return false;
    }

    // Сортуємо копії векторів
    vector<double> sorted_m1 = m1.data;
    vector<double> sorted_m2 = m2.data;
    sort(sorted_m1.begin(), sorted_m1.end());
    sort(sorted_m2.begin(), sorted_m2.end());

    // Порівнюємо відсортовані вектори
    return sorted_m1 == sorted_m2;
}

bool operator!=(const mnozhyna& m1, const mnozhyna& m2) {
    return !(m1 == m2);
}

int main() {
    cout << "\033[1;35m" << "Task №1" << "\033[0m" << endl;
    cout << "\033[1;33m" << "Matrix 1:" << "\033[0m" << endl;
    KvadratnaMatrix m1(2);
    vector<vector<double>> data1 = {{1, 2}, {3, 4}};
    m1.setMatrix(data1);
    m1.print();
    
    cout << "\033[1;33m" << "Matrix 2:" << "\033[0m" << endl;
    KvadratnaMatrix m2(2);
    vector<vector<double>> data2 = {{5, 6}, {7, 8}};
    m2.setMatrix(data2);
    m2.print();

    cout << "\033[1;33m" << "Matrix 1 + Matrix 2:" << "\033[0m" << endl;
    KvadratnaMatrix m3 = m1 + m2;
    m3.print();
    cout << "\033[1;33m" << "Matrix 1 - Matrix 2:" << "\033[0m" << endl;
    KvadratnaMatrix m4 = m1 - m2;
    m4.print();

    cout << "\033[1;35m" << "Task №2" << "\033[0m" << endl;
    cout << "\033[1;34m" << "Select the matrix (1 or 2):" << "\033[0m" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "\033[1;33m" << "-Matrix 1:" << "\033[0m" << endl;
        KvadratnaMatrix m5 = -m1;
        m5.print();
    } else if (choice == 2) {
        cout << "\033[1;33m" << "-Matrix 2:" << "\033[0m" << endl;
        KvadratnaMatrix m6 = -m2;
        m6.print();
    } else {
        cout << "\033[1;31m" << "Error: invalid choice" << "\033[0m" << endl;
    }

    cout << "\033[1;35m" << "Task №3" << "\033[0m" << endl;
    cout << "\033[1;33m" << "Set 1:" << "\033[0m" << endl;
    mnozhyna s1({1, 2, 3});
    s1.print();
    cout << "\033[1;33m" << "Set 2:" << "\033[0m" << endl;
    mnozhyna s2({4, 5, 6, 7});
    s2.print();
    cout << "\033[1;33m" << ">Set:" << "\033[0m" << endl;
    mnozhyna s3 = s1 > s2;
    s3.print();
    cout << "\033[1;33m" << "<Set:" << "\033[0m" << endl;
    mnozhyna s4 = s1 < s2;
    s4.print();
    if (s1 == s2) {
        cout << "\033[1;32m" << "Set 1 == Set 2" << "\033[0m" << endl;
    } else {
        cout << "\033[1;31m" << "Set 1 != Set 2" << "\033[0m" << endl;
    }

    return 0;
}