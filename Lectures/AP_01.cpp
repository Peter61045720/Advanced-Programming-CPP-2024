#include <iostream>

// Object Oriented Programming:
// - Encapsulation
// - Abstraction
// - Inheritance
// - Polymorphism

class Engine {
public:
    unsigned power = 100;
};

class Trailer {
public:
    unsigned capacity = 300;
};

// Abstraction: Abstract Class
class AbstractClass {
public:
    void basic_method() {}

    virtual void pure_virtual_method() = 0;
};

// Abstraction: Interface
class Vehicle {
public:
    virtual int get_speed() = 0;
};

// The Car is a Vehicle (Inheritance) 
class Car : public Vehicle {
// Encapsulation: Access modifiers
private:
    const std::string ID = "ABC123";

protected:
    unsigned fuel_capacity;

public:
    Trailer trailer; // Aggregation (weak)
    Engine engine; // Composition (strong)

    // Implementation 
    // Late Binding | Dynamic Polymorphism: Overriding
    int get_speed() override {
        return 90;
    }

    // Association
    void replace_engine(const Engine& engine) {
        this->engine = engine;
    }

    void travel() {
        std::cout << "The car is going without a trailer" << std::endl;
    }

    // Early Binding | Static Polymorphism: Overloading
    void travel(Trailer trailer) {
        std::cout << "The car is going with a trailer" << std::endl;
    }
};

class Boat : public Vehicle {
public:
    int get_speed() final {
        return 50;
    }
};

// Late binding usage
void print_speed(Vehicle& vehicle) {
    std::cout << "The speed of this vehicle is: " << vehicle.get_speed() << std::endl; 
}

// Diamond Problem
class Parent {
public:
    Parent() { std::cout << "Parent" << std::endl; }

    unsigned get_id() { return 4; }
};

// Solution: virtual inheritance
class ChildA : virtual public Parent {
public:
    ChildA() { std::cout << "ChildA" << std::endl; }

    unsigned get_id() { return Parent::get_id() - 1; }
};

// Solution: virtual inheritance
class ChildB : virtual public Parent {
public:
    ChildB() { std::cout << "ChildB" << std::endl; }

    unsigned get_id() { return Parent::get_id() - 2; }
};

class GrandChild : public ChildA, public ChildB {
public:
    GrandChild() { std::cout << "GrandChild" << std::endl; }

    unsigned get_id() { return ChildA::get_id() * ChildB::get_id(); }
};

// Custom Exception
class division_by_zero : public std::exception {
private:
    std::string message;

public:
    division_by_zero(const std::string& message) : message(message) {}

    const char* what() const noexcept override {
        return this->message.c_str();
    }
};

class A {
public:
    int value;

    A() : value(0) {} // Default Constructor
    A(int v) : value(v) {} // Parameterized Constructor
    ~A() { std::cout << "~Destructor called" << std::endl; } // Destructor

    bool operator==(const A& other) const { return this->value == other.value; }
};

int main() {
    // Object:
    // - State
    // - Behavior
    // - Identity

    Car car; // Local Object - Stack
    static Boat boat; // Data Segment - Static Object
    Vehicle* car2 = new Car(); // Dynamic Object - Heap
    std::cout << car.engine.power << std::endl;
    std::cout << car.get_speed() << std::endl;
    std::cout << boat.get_speed() << std::endl;
    print_speed(car);
    print_speed(boat);
    print_speed(*car2);

    GrandChild gc;
    std::cout << gc.get_id() << std::endl;

    try {
        int a = 0;
        if (a == 0) {
            // throw division_by_zero("Division By Zero!");
        } else {
            std::cout << 10 / a << std::endl;
        }
        // throw 404;
    } catch (const division_by_zero& ex) {
        std::cout << ex.what() << std::endl;
    } catch (int error_code) {
        std::cout << "Error code: " << error_code << std::endl;
    }

    A a1(20);
    A a2(20);
    A a3(10);

    std::cout << (a1 == a2 ? "Equals" : "Not Equals") << std::endl;
    std::cout << (a1 == a3 ? "Equals" : "Not Equals") << std::endl;

    return 0;
}