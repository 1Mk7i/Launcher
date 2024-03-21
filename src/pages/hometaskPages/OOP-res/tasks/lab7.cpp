#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Matrix {
private:
    vector<vector<double>> data;
    int rows, cols;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(rows, vector<double>(cols, 0));
    }

    ~Matrix() {}
    vector<vector<double>> getMatrix() const {
        return data;
    }

    friend vector<double> multiply(const Matrix& m, const vector<double>& v);
    friend vector<double> multiply(const vector<double>& v, const Matrix& m);
    friend vector<double> multiply(const vector<double>& v, double num);
    friend vector<double> multiply(double num, const vector<double>& v);
    friend Matrix multiply(const Matrix& m, double num);
    friend Matrix multiply(double num, const Matrix& m);
    friend Matrix multiply(const Matrix& m1, const Matrix& m2);
};

class Vector {
private:
    vector<double> data;
    int size;

public:
    Vector(int s) : size(s) {
        data.resize(size, 0);
    }

    ~Vector() {}

    friend vector<double> multiply(const Matrix& m, const vector<double>& v);
    friend vector<double> multiply(const vector<double>& v, const Matrix& m);
    friend vector<double> multiply(const vector<double>& v1, const vector<double>& v2);
};

vector<double> multiply(const Matrix& m, const vector<double>& v) {
    if (m.cols != v.size()) {
        cout << "Неможливо перемножити матрицю та вектор" << endl;
        return {};
    }

    vector<double> result(m.rows, 0);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result[i] += m.data[i][j] * v[j];
        }
    }
    return result;
}

vector<double> multiply(const vector<double>& v, const Matrix& m) {
    if (v.size() != m.rows) {
        cout << "Неможливо перемножити вектор та матрицю" << endl;
        return {};
    }

    vector<double> result(m.cols, 0);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result[j] += v[i] * m.data[i][j];
        }
    }
    return result;
}

vector<double> multiply(const vector<double>& v, double num) {
    vector<double> result(v.size());
    for (int i = 0; i < v.size(); i++) {
        result[i] = v[i] * num;
    }
    return result;
}

vector<double> multiply(double num, const vector<double>& v) {
    return multiply(v, num);
}

Matrix multiply(const Matrix& m, double num) {
    Matrix result(m.rows, m.cols);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[i][j] = m.data[i][j] * num;
        }
    }
    return result;
}

Matrix multiply(double num, const Matrix& m) {
    return multiply(m, num);
}

Matrix multiply(const Matrix& m1, const Matrix& m2) {
    if (m1.cols != m2.rows) {
        cout << "Неможливо перемножити матриці" << endl;
        return Matrix(0, 0);
    }

    Matrix result(m1.rows, m2.cols);
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m2.cols; j++) {
            for (int k = 0; k < m1.cols; k++) {
                result.data[i][j] += m1.data[i][k] * m2.data[k][j];
            }
        }
    }
    return result;
}

vector<double> multiply(const vector<double>& v1, const vector<double>& v2) {
    if (v1.size() != v2.size()) {
        cout << "Неможливо перемножити вектори" << endl;
        return {};
    }

    vector<double> result(v1.size(), 0);
    for (int i = 0; i < v1.size(); i++) {
        result[i] = v1[i] * v2[i];
    }
    return result;
}

// Функція для множення вектора на число зі значенням за замовчуванням 1
vector<double> vectornumMultiply(const vector<double>& v, double num = 1) {
    vector<double> result(v.size());
    for (int i = 0; i < v.size(); i++) {
        result[i] = v[i] * num;
    }
    return result;
}

// Функція для виведення вектора
void printVector(const vector<double>& v) {
    cout << "[ ";
    for (double x : v) {
        cout << x << " ";
    }
    cout << "]" << endl;
}

// Функція для виведення матриці
void printMatrix(const Matrix& m) {
    const vector<vector<double>>& matrix = m.getMatrix();
    for (const auto& row : matrix) {
        cout << "[ ";
        for (double x : row) {
            cout << setw(6) << x << " ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

int main() {
    Matrix m(3, 2);
    vector<double> v1 = {1, 2};
    vector<double> v2 = {3, 4, 5};
    double num = 2.5;

    vector<double> result1 = multiply(m, v1);
    vector<double> result2 = multiply(v2, m);
    vector<double> result3 = vectornumMultiply(v1, num);
    vector<double> result4 = vectornumMultiply(v1);
    Matrix result5 = multiply(m, num);
    Matrix result6 = multiply(num, m);

    cout << "Результат множення матриці на вектор:" << endl;
    printVector(result1);

    cout << "Результат множення вектора на матрицю:" << endl;
    printVector(result2);

    cout << "Результат множення вектора на число:" << endl;
    printVector(result3);

    cout << "Результат множення вектора на 1 (за замовчуванням):" << endl;
    printVector(result4);

    cout << "Результат множення матриці на число:" << endl;
    printMatrix(result5);

    cout << "Результат множення числа на матрицю:" << endl;
    printMatrix(result6);

    return 0;
}