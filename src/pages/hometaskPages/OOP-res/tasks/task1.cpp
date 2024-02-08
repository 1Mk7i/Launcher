#include <iostream>
#include <cmath>

using namespace std;

struct Shape {
    string name;
    int points;
    int x[3];
    int y[3];
};

void print(const Shape& inf) {
    float perimetr = 0.0;
    cout << "Shape: " << inf.name << endl;
    for (int i = 0; i < inf.points; ++i) {
        cout << "Point " << i + 1 << ": (" << inf.x[i] << ", " << inf.y[i] << ")" << endl;
    }
    if (inf.points == 3) {
        perimetr = sqrt(pow((inf.x[1] - inf.x[0]), 2) + pow((inf.y[1] - inf.y[0]), 2)) + sqrt(pow((inf.x[2] - inf.x[1]), 2) + pow((inf.y[2] - inf.y[1]), 2)) + sqrt(pow((inf.x[2] - inf.x[0]), 2) + pow((inf.y[2] - inf.y[0]), 2));
    }
    // периметр
    cout << "P: " << perimetr << endl;
    // площа
    float S = 0.5 * abs((inf.x[0] - inf.x[2]) * (inf.y[1] - inf.y[2]) - (inf.x[1] - inf.x[2]) * (inf.y[0] - inf.y[2]));
    cout << "S: " << S << endl;
    // радіус вписаного кола
    float r = S / (perimetr / 2);
    cout << "r: " << r << endl;
    // радіус описаного кола
    float R = (sqrt(pow((inf.x[1] - inf.x[0]), 2) + pow((inf.y[1] - inf.y[0]), 2)) * sqrt(pow((inf.x[2] - inf.x[1]), 2) + pow((inf.y[2] - inf.y[1]), 2)) * sqrt(pow((inf.x[2] - inf.x[0]), 2) + pow((inf.y[2] - inf.y[0]), 2))) / (4 * S);

    cout << "R: " << R << endl;
}

int main() {
    int x[3];
    int y[3];
    
    int n = 3;

    cout << "Enter 3 points (x y)" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    Shape triangle = { "Triangle", 3, {x[0], x[1], x[2]}, {y[0], y[1], y[2]} };
    print(triangle);
    return 0;
}
