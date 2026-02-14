#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace buildsystems {

class Calculator {
public:
    static int add(int a, int b);
    static int subtract(int a, int b);
    static int multiply(int a, int b);
    static double divide(int a, int b);
};

} // namespace buildsystems

#endif // CALCULATOR_H
