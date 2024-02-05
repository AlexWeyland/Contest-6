#include <vector>
#include <iostream>
#include <iomanip>

using std::vector;

vector<vector<double>> matrix;

double Dynamics(int number, int height) {
    for (int index = 2; index <= number; ++index) {
        for (int level = 0; level < height; ++level) {
            double res = 0;
            for (int left = 0; left < index; ++left) {
                res += matrix[left][level] * matrix[index - left - 1][level];
                for (int right_level = 0; right_level < level; ++right_level) {
                    res += 2 * matrix[left][level] * matrix[index - left - 1][right_level];
                }
            }
            res = res / index;
            matrix[index][level + 1] = res;
        }
    }
    return matrix[number][height];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number, height;
    std::cin >> number >> height;

    if (height > number) {
        std::cout << 0;
    } else {
        matrix.resize(number + 2, vector<double>(height + 2, 0));
        matrix[0][0] = 1;
        matrix[1][0] = 1;

        double result = Dynamics(number, height);
        std::cout << std::setprecision(10) << result;
    }
    return 0;
}
