#include <iostream>
#include <string>

using namespace std;

void print_cl_arguments(int argc, char* argv[]) {
    std::cout << "argc: " << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
    }
}

void test_std_io() {
    int a, b;
    std::cout << "a=";
    std::cin >> a;
    std::cout << "b=";
    std::cin >> b;

    std::cout << "a+b=" << a + b << std::endl;

    std::cout << "(a b)=";
    std::cin >> a >> b;

    std::cout << "a*b=" << a * b << std::endl;

    cout << "With std namespace" << endl;
}

void test_pointers() {
    int a = 10;
    int* p = &a;

    std::cout << "a\t= " << a << std::endl;
    std::cout << "&a\t= " << &a << std::endl;
    std::cout << "p\t= " << p << std::endl;
    std::cout << "*p\t= " << *p << std::endl;

    a = 15;
    std::cout << "------" << std::endl;

    std::cout << "a\t= " << a << std::endl;
    std::cout << "&a\t= " << &a << std::endl;
    std::cout << "p\t= " << p << std::endl;
    std::cout << "*p\t= " << *p << std::endl;

    *p += 23;
    std::cout << "------" << std::endl;

    std::cout << "a\t= " << a << std::endl;
    std::cout << "&a\t= " << &a << std::endl;
    std::cout << "p\t= " << p << std::endl;
    std::cout << "*p\t= " << *p << std::endl;

    int* d_ptr = new int[10];
    for (int i = 0; i < 10; i++) {
        *(d_ptr + i) = i;
    }
    int* n_ptr = nullptr;

    std::cout << "d_ptr=" << d_ptr << std::endl;
    std::cout << "d_ptr[i]=" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "  " << d_ptr[i] << std::endl;
    }
    std::cout << "n_ptr=" << n_ptr << std::endl;
}

void test_references(int& a) {
    a = 32;

    int b = 100;
    int& ref_b = b;

    std::cout << "b\t= " << b << std::endl;
    std::cout << "&b\t= " << &b << std::endl;
    std::cout << "ref_b\t= " << ref_b << std::endl;
    std::cout << "&ref_b\t= " << &ref_b << std::endl;

    b = 120;
    std::cout << "------" << std::endl;

    std::cout << "b\t= " << b << std::endl;
    std::cout << "&b\t= " << &b << std::endl;
    std::cout << "ref_b\t= " << ref_b << std::endl;
    std::cout << "&ref_b\t= " << &ref_b << std::endl;

    ref_b += 170;
    std::cout << "------" << std::endl;

    std::cout << "b\t= " << b << std::endl;
    std::cout << "&b\t= " << &b << std::endl;
    std::cout << "ref_b\t= " << ref_b << std::endl;
    std::cout << "&ref_b\t= " << &ref_b << std::endl;
}

void v_swap(int a, int b) {
    std::swap(a, b);
}

void p_swap(int* a, int* b) {
    std::swap(*a, *b);
}

void r_swap(int& a, int& b) {
    std::swap(a, b);
}

void print_a_b(const int& a, const int& b) {
    std::cout << "(a, b) = " << a << " " << b << std::endl;
}

void test_string() {
    std::string s1 = "S1_";
    std::string s2("R2_");
    std::string s3{"L3"};

    std::string s4 = s1 + s2 + s3;
    std::cout << "s4\t\t= " << s4 << std::endl;
    std::cout << "size()\t\t= " << s4.size() << std::endl;
    std::cout << "empty()\t\t= " << s4.empty() << std::endl;
    std::cout << "c_str()\t\t= " << s4.c_str() << std::endl;
    std::cout << "substr(0,3)\t= " << s4.substr(0, 3) << std::endl;
    std::cout << "substr(2,6)\t= " << s4.substr(2, 6) << std::endl;
    std::cout << "s4[4]\t\t= " << s4[4] << std::endl;
    std::cout << "('A') npos\t= " << (s4.find_first_of('A') == string::npos) << std::endl;
    std::cout << "('R') npos\t= " << (s4.find_first_of('S') == string::npos) << std::endl;
    s4.clear();
    std::cout << "clear()\t\t= " << s4 << std::endl;

    std::string si = std::to_string((int)12);
    std::string su = std::to_string((unsigned)97);

    std::cout << "si = " << si << std::endl;
    std::cout << "su = " << su << std::endl;

    int i10 = std::stoi("79523");
    size_t pos = 0;
    int i16 = std::stoi("+0xF2 foo 99", &pos, 16);
    std::cout << "i10 = " << i10 << std::endl;
    std::cout << "i16 = " << i16 << ", pos =" << pos << std::endl;
}

void foo() {
    std::cout << "::foo()" << std::endl;
}

namespace A {
    void foo() {
        std::cout << "A::foo()" << std::endl;
    }

    void foo(int) {
        std::cout << "A::foo(int)" << std::endl;
    }

    namespace B {
        void foo() {
            std::cout << "A::B::foo()" << std::endl;
        }

        void foo(int) {
            std::cout << "A::B::foo(int)" << std::endl;
        }
    }
}

int divide(int a, int b) {
    return a / b;
}

double divide(double a, double b) {
    return a / b;
}

size_t divide(size_t a, size_t b, ...) {
    return a / b;
}

void bar(double a) {
    std::cout << "bar(double) = " << a << std::endl;
}

void bar(int a, int b) {
    std::cout << "bar(int, int) = " << a << ", " << b << std::endl;
}

void bar(double a, int b) {
    std::cout << "bar(double, int) = " << a << ", " << b << std::endl;
}

void bar(int a, double b) {
    std::cout << "bar(int, double) = " << a << ", " << b << std::endl;
}

void goo(unsigned a) {
    std::cout << "goo(unsigned) = " << a << std::endl;
}

void goo(unsigned long a) {
    std::cout << "goo(unsigned long) = " << a << std::endl;
}

void goo(size_t a) {
    std::cout << "goo(size_t) = " << a << std::endl;
}

struct Pair {
    int a, b;
    Pair() : a(0), b(0) {}
    Pair(int a, int b) : a(a), b(b) {}
    ~Pair() { std::cout << "  Destructor called" << std::endl; }
};

Pair operator+(const Pair& p1, const Pair& p2) {
    return Pair(p1.a + p2.a, p1.b + p2.b);
}

Pair operator*(const Pair& p1, const Pair& p2) {
    return Pair(p1.a * p2.a, p1.b * p2.b);
}

Pair operator*(const Pair& p1, int c) {
    return Pair(p1.a * c, p1.b * c);
}

Pair operator*(int c, const Pair& p1) {
    return Pair(p1.a * c, p1.b * c);
}

void test_din_mem() {
    int* n = new int;
    int* m = new int[10];
    *n = 117;
    *m = 118;
    *(m+1) = 119;
    m[2] = 120;

    Pair* p = new (nothrow) Pair[2];
    *p = Pair(33, 45);
    *(p+1) = Pair(54, 87);

    std::cout << *n << ", " << m[0] << ", " << m[1] << ", " << m[2] << endl;
    std::cout << p->a << ", " << p->b << endl;
    std::cout << p[1].a << ", " << p[1].b << endl;

    delete n;
    n = nullptr;

    delete[] m;
    delete[] p;
}

int main(int argc, char* argv[]) {
    print_cl_arguments(argc, argv);
    test_std_io();
    test_pointers();
    {
        int a = 17;
        test_references(a);
        std::cout << "a=" << a << std::endl;
    }
    {
        int a = 16;
        int b = 32;

        v_swap(a, b);
        print_a_b(a, b);

        p_swap(&a, &b);
        print_a_b(a, b);

        r_swap(a, b);
        print_a_b(a, b);
    }
    test_string();
    {
        foo();
        ::foo();
        A::foo();
        A::foo(20);
        A::B::foo();
        A::B::foo(123);

        std::cout << divide(11, 3) << std::endl;
        std::cout << divide(11.0, 3.0) << std::endl;
        std::cout << divide(11, 3, 199, "asd", 'z', false, nullptr) << std::endl;

        bar(3);
        bar(1.2, 3);
        bar(1, 3.7);
        bar(1, 3);
        // bar(1.7, 3.7); error: ambiguous call --> "bar(int, double) == bar(double, int)"

        // goo(5); error: ambiguous call --> goo(unsigned) == goo(unsigned long) == goo(size_t)
    }
    {
        Pair p1(3, 5);
        Pair p2(12, 57);
        Pair p3 = p1 + p2;
        std::cout << "(" << p3.a << "," << p3.b << ")" << std::endl;

        p3 = p1 * p2;
        std::cout << "(" << p3.a << "," << p3.b << ")" << std::endl;

        p3 = p1 * 3;
        std::cout << "(" << p3.a << "," << p3.b << ")" << std::endl;

        p3 = 3 * p1;
        std::cout << "(" << p3.a << "," << p3.b << ")" << std::endl;
    }
    test_din_mem();
    return 0;
}