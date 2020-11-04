#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>

const double a = -5.;
const double b = 2.;

void printZagolovok() {
    std::cout << std::left << std::string(47, '-') << '\n'
         << "| " << std::setw(4) << "N"
         << "| " << std::setw(10) << "T"
         << "| " << std::setw(11) << "x"
         << "| " << std::setw(13) << "f(x)" << "|\n"
         << std::string(47, '-') << '\n';
}

void printLine(const int iteration, const double T,
               const double value, const double functionValue) {
    std::cout << "| " << std::setw(4) << iteration
         << "| " << std::setw(10) << T
         << "| " << std::setw(11) << value
         << "| " << std::setw(13) << functionValue << "|\n";
}

double random(const double lower, const double upper) {
    return lower + rand() * 1./RAND_MAX * (upper - lower);
}

template<class Function>
auto Method(const double A, const double B,
            Function func) {
    printZagolovok();
    const double T_min = .01;
    double T_i = 10000.;
    double x_i = random(A, B);
    int i = 0;
    while (T_i > T_min) {
        ++i;
        double x_new = random(A, B);
        double delta_f = func(x_new) - func(x_i);
        if (delta_f <= 0) {
            x_i = x_new;
        } else {
            double rand_Prob = random(0, 1);
            double proba = exp(-delta_f / T_i);
            if (rand_Prob < proba){
                x_i = x_new;
            }
        }
        printLine(i, T_i, x_i, func(x_i));
        T_i *= .95;
    }

    std::cout << std::string(47, '-') << '\n';
    return std::pair{x_i, func(x_i)};
}

double MyFunction(const double x) {
    return (-0.5)*std::cos(0.5*x)-0.5;
}

double MyFunctionWithSin(const double x) {
    return MyFunction(x) * sin(5*x);
}


int main() {
    std::cout << "Variant 1\n\n (-0.5)*cos(0.5*x)-0.5, interval: ["
              << a << " " << b << "]\n";
    srand(time(nullptr));
    auto result_1 = Method(a, b, MyFunction);
    std::cout << "Result: Xmin = " << result_1.first
         << ", Fmin = " << result_1.second << '\n';

    std::cout << "\n\n (-0.5)*cos(0.5*x)-0.5)*sin(5x), interval: ["
              << a << " " << b << "]\n";
    auto result_2 = Method(a, b, MyFunctionWithSin);
    std::cout << "Result: Xmin = " << result_2.first
         << ", Fmin = " << result_2.second << '\n';

    return 0;
}