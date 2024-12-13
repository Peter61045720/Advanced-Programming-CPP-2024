#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>

// Hasznalj kommenteket a #define-ok elott kodblokkok inaktivalasahoz!

// #define MANIPULATOR
// #define EFFECTOR
// #define FUNCTION_TEMPLATE
// #define CLASS_TEMPLATE
// #define TRAITS

// #define METAPROGRAMMING
// #define FUNCTION_OBJECT
// #define STL
// #define ITERATOR

#define TESTS

#ifdef MANIPULATOR

std::ostream& write_roman_numbers(std::ostream& os) {
    const std::string ROMAN_NUMBERS[10] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X" };
    static int idx = 0;
    if (idx == 10) {
        idx = 0;
    }
    return os << ROMAN_NUMBERS[idx++];
}

std::ostream& write_roman_numbers_flipped(std::ostream& os) {
    const std::string ROMAN_NUMBERS[10] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X" };
    static int idx = 0;
    static bool flipped = false;
    if (idx == 0) {
        flipped = false;
    }
    if (idx == 9) {
        flipped = true;
    }
    return os << ROMAN_NUMBERS[!flipped ? idx++ : idx--];
}

#endif

#ifdef EFFECTOR

class negation {
private:
    int n;
public:
    negation(int n) : n(n) {}

    friend std::ostream& operator<<(std::ostream& os, const negation& neg) {
        // Nem jo: return os << -this->n;
        return os << -neg.n;
    }
};

class bool_string {
private:
    bool value;
public:
    bool_string(bool value) : value(value) {}

    friend std::ostream& operator<<(std::ostream& os, const bool_string& b_str) {
        return os << (b_str.value ? "true" : "false");
    }
};

#endif

#ifdef FUNCTION_TEMPLATE

template<typename T>
T add_elements(const T& elem1, const T& elem2) {
    return elem1 + elem2;
}

template<>
char add_elements<char>(const char& elem1, const char& elem2) {
    return elem1 < elem2 ? elem2 : elem1;
}

template<typename T>
T invert(T& t) {
    return -t;
}

template<>
unsigned invert<unsigned>(unsigned& t) {
    return t;
}

template<>
bool invert<bool>(bool& t) {
    return !t;
}

template<>
char invert<char>(char& t) {
    return isupper(t) ? tolower(t) : toupper(t);
}

template<>
std::string invert<std::string>(std::string& t) {
    std::reverse(t.begin(), t.end());
    return t;
}

template<typename IT>
std::string join(const IT& begin, const IT& end, char separator = '\0') {
    std::ostringstream oss;
    auto it = begin;
    if (it != end) {
        oss << *it++;
    }
    for (; it != end; it++) {
        oss << separator << *it;
    }
    return oss.str();
}

template<>
std::string join<std::vector<char>::iterator>(const std::vector<char>::iterator& begin, const std::vector<char>::iterator& end, char separator) {
    return std::string(begin, end);
}

#endif

#ifdef CLASS_TEMPLATE

template<typename T, size_t N>
class my_vector {
private:
    std::vector<T> vec;
    size_t n;
public:
    my_vector(T* t, size_t n) : n(n) {
        for (size_t i = 0; i < n; i++) {
            vec.push_back(t[i]);
        }
    }

    my_vector& operator+=(const T& t) {
        if (n >= N) {
            throw std::out_of_range("Index out of range");
        }
        vec.push_back(t);
        n++;
        return *this;
    }

    T& operator[](size_t idx) {
        if (idx >= n) {
            throw std::out_of_range("Index out of range");
        }
        return vec[idx];
    }

    const T& operator[](size_t idx) const {
        if (idx >= n) {
            throw std::out_of_range("Index out of range");
        }
        return vec[idx];
    }

    friend std::ostream& operator<<(std::ostream& os, const my_vector& m_vec) {
        for (size_t i = 0; i < m_vec.n; i++) {
            os << m_vec[i] << std::endl;
        }
        return os;
    }
};

#endif

#ifdef TRAITS

// Energia tipusok
struct Solar {
    double output = 150.0;
};

struct Nuclear {
    double output = 320.0;
};

// Sebesseg tipusok
struct LowSpeed {
    double velocity = 12.0;
};

struct HighSpeed {
    double velocity = 50.0;
};

// Resztvevok
class Astronaut {
    std::string name;
public:
    Astronaut(const std::string& name) : name(name) {}
    std::string get_name() const {
        return name;
    }
};

class Robot {
    std::string name;
public:
    Robot(const std::string& name) : name(name) {}
    std::string get_name() const {
        return name;
    }
};

template<typename Occupant>
class SpaceTraits;

template<>
class SpaceTraits<Astronaut> {
public:
    typedef Solar energy_source;
    typedef LowSpeed speed;
};

template<>
class SpaceTraits<Robot> {
public:
    typedef Nuclear energy_source;
    typedef HighSpeed speed;
};

template<typename Occupant, typename Traits = SpaceTraits<Occupant>>
class Spacecraft {
public:
    Occupant occupant;
    typedef typename Traits::energy_source energy_source;
    typedef typename Traits::speed speed;
    energy_source energy;
    speed spd;

    Spacecraft(Occupant oc) : occupant(oc) {}

    double energy_consumption() const {
        return energy.output * spd.velocity;
    }

    friend std::ostream& operator<<(std::ostream &os, const Spacecraft &sc) {
        return os << sc.occupant.get_name();
    }
};

#endif

#ifdef METAPROGRAMMING

// futasi- es forditasi idoben
constexpr unsigned factorial_crt(unsigned n) {
    if (n <= 0) {
        return 1;
    }
    return n * factorial_crt(n-1);
}

// forditasi idoben
template<unsigned N>
struct factorial_ct {
    static const unsigned value = N * factorial_ct<N-1>::value;
};

template<>
struct factorial_ct<0> {
    static const unsigned value = 1;
};

// futasi- es forditasi idoben
constexpr unsigned count_digits_crt(unsigned n) {
    if (n < 10) {
        return 1;
    }
    return 1 + count_digits_crt(n/10);
}

// forditasi idoben
template<unsigned N, bool FIRST = true>
struct count_digits_ct {
    static const unsigned value = 1 + count_digits_ct<N/10, false>::value;
};

template<>
struct count_digits_ct<0, true> {
    static const unsigned value = 1;
};

template<>
struct count_digits_ct<0, false> {
    static const unsigned value = 0;
};

// Zart keplet
// S_n = (n * (n+1)) / 2

// futasi- es forditasi idoben
constexpr unsigned nth_sum_closed_crt(unsigned n) {
    return n * (n + 1) / 2;
}

// forditasi idoben
template<unsigned N>
struct nth_sum_closed_ct {
    static const unsigned value = N * (N + 1) / 2;
};

// Rekurziv keplet
// S_1 = 1
// ...
// S_n = n + S_(n-1)

// futasi- es forditasi idoben
constexpr unsigned nth_sum_crt(unsigned n) {
    if (n == 0) {
        return 0;
    }
    return n + nth_sum_crt(n-1);
}

// forditasi idoben
template<unsigned N>
struct nth_sum_ct {
    static const unsigned value = N + nth_sum_ct<N-1>::value;
};

template<>
struct nth_sum_ct<0> {
    static const unsigned value = 0;
};

#endif

#ifdef FUNCTION_OBJECT

struct count_number {
private:
    int n;
public:
    count_number(int n) : n(n) {}
    bool operator()(int input_number){
        return input_number == n;
    }
};

#endif

#ifdef STL

std::map<unsigned, unsigned> count_grades(const std::vector<unsigned>& grades) {
    std::map<unsigned, unsigned> result;
    for (const auto grade : grades) {
        result[grade]++;
    }
    return result;
}

std::map<unsigned, unsigned> count_grades_in_set(const std::set<unsigned>& grades) {
    std::map<unsigned, unsigned> result;
    for (const auto grade : grades) {
        result[grade]++;
    }
    return result;
}

std::map<unsigned, unsigned> unite_maps(const std::map<unsigned, unsigned>& m1, const std::map<unsigned, unsigned>& m2) {
    std::map<unsigned, unsigned> result;
    for (const auto [k, v] : m1) {
        result[k] += v;
    }
    for (const auto [k, v] : m2) {
        result[k] += v;
    }
    return result;
}

std::map<unsigned, unsigned> unite_maps_from_vector(const std::vector<std::map<unsigned, unsigned>>& vector_of_maps) {
    std::map<unsigned, unsigned> result;
    for (const auto& a_map : vector_of_maps) {
        for (const auto [k, v] : a_map) {
            result[k] += v;
        }
    }
    return result;
}

std::string vector_to_string(const std::vector<std::string>& strings) {
    std::ostringstream oss;
    for (const auto& str : strings) {
        oss << str;
    }
    return oss.str();
}

struct Task {
    unsigned priority;
    std::string name;
};

void store_tasks(const std::vector<Task>& tasks, std::map<unsigned, std::string>& result) {
    for (const auto& task : tasks) {
        unsigned idx = task.priority;
        // Addig no az idx erteke, amig nincs szabad hely a kulcs szamara
        while (result.find(idx) != result.end()) {
            idx++;
        }
        result[idx] = task.name;
    }
}

#endif

#ifdef ITERATOR

struct Entry {
    std::string id;
    unsigned mark;
    friend std::ostream& operator<<(std::ostream& os, const Entry& e) {
        return os << e.id << " - " << e.mark;
    }
};

template <size_t N>
class EntryBook {
private:
    Entry entries[N];
    size_t n = 0;
    unsigned selected_mark;
public:
    EntryBook(Entry* entrs, size_t n, unsigned s_m) : n(n), selected_mark(s_m) {
        if (n > N) {
            throw std::out_of_range("EntryBook(Entry*, size_t), " + std::to_string(n));
        }
        for (size_t i = 0; i < n; i++) {
            entries[i] = entrs[i];
        }
    }

    unsigned get_selected_mark() const {
        return selected_mark;
    }

    void set_selected_mark(unsigned n) {
        selected_mark = n;
    }

    EntryBook& operator+=(const Entry& entry) {
        if (n >= N) {
            throw std::out_of_range("operator+=, " + std::to_string(n));
        }
        entries[n++] = entry;
        return *this;
    }

    Entry& operator[](size_t idx) {
        if (idx >= n) {
            throw std::out_of_range("operator[], " + std::to_string(n));
        }
        return entries[idx];
    }

    friend std::ostream& operator<<(std::ostream& os, const EntryBook& eb) {
        for (size_t i = 0; i < eb.n; i++) {
            os << " " << eb.entries[i] << std::endl;
        }
        return os;
    }

    class iterator {
    private:
        Entry* e_ptr;
        Entry* end;
        unsigned selected_mark;

        iterator(Entry* e_ptr, Entry* end, unsigned s_m) : e_ptr(e_ptr), end(end), selected_mark(s_m) {}

        friend class EntryBook;

    public:
        iterator() = default;

        iterator(const iterator& it) : e_ptr(it.e_ptr), end(it.end), selected_mark(it.selected_mark) {}

        bool operator==(const iterator& it) const {
            return e_ptr == it.e_ptr;
        }

        bool operator!=(const iterator& it) const {
            return !operator==(it);
        }

        Entry& operator*() {
            return *e_ptr;
        }

        Entry* operator->() {
            return e_ptr;
        }

        iterator& operator++() {
            e_ptr++;
            while (e_ptr->mark != selected_mark && e_ptr != end) {
                e_ptr++;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp(*this);
            operator++();
            return temp;
        }
    };

    iterator begin() {
        Entry* start = entries;
        Entry* end = entries + n;
        while (start != end && start->mark != selected_mark) {
            start++;
        }
        return iterator(start, end, selected_mark);
    }

    iterator end() {
        return iterator(entries + n, entries + n, selected_mark);
    }
};

template<size_t N>
class numbers {
private:
    int n_arr[N];
    size_t n;

public:
    numbers(int* nums = nullptr, size_t n = 0) : n(n) {
        if (n > N) {
            throw std::out_of_range("numbers(int*, size_t), " + std::to_string(n));
        }
        if (nums) {
            for (size_t i = 0; i < n; i++) {
                n_arr[i] = nums[i];
            }
        }
    }

    numbers(const std::vector<int>& nums, size_t n = 0) : n(n) {
        if (n > N) {
            throw std::out_of_range("numbers(const std::vector<int>&, size_t), " + std::to_string(n));
        }
        if (!nums.empty()) {
            for (auto it = nums.begin(); it != nums.end(); it++) {
                operator+=(*it);
            }
        }
    }

    size_t get_count() const {
        return n;
    }

    numbers& operator+=(const int number) {
        if (n >= N) {
            std::cout << n << std::endl;
            throw std::out_of_range("operator+=, " + std::to_string(number));
        }
        n_arr[n++] = number;
        return *this;
    }

    const int operator[](size_t idx) const {
        if (idx >= n) {
            throw std::out_of_range("operator[], " + std::to_string(idx));
        }
        return n_arr[idx];
    }

    friend std::ostream& operator<<(std::ostream& os, const numbers& ns) {
        for (size_t i = 0; i < ns.n; i++) {
            os << " " << ns.n_arr[i] << std::endl;
        }
        return os;
    }

    class iterator {
    private:
        int* n_ptr;
        int* end;

        iterator(int* ptr, int* e) : n_ptr(ptr), end(e) {}

        friend class numbers;

    public:
        iterator() = default;

        iterator(const iterator& it) : n_ptr(it.n_ptr), end(it.end) {}

        bool operator==(const iterator& it) const {
            return n_ptr == it.n_ptr && end == it.end;
        }

        bool operator!=(const iterator& it) const {
            return !operator==(it);
        }

        int operator*() {
            return *n_ptr;
        }

        // int* operator->() {
        //     return n_ptr;
        // }

        iterator& operator++() {
            n_ptr++;
            while (*n_ptr % 2 != 0 && n_ptr != end) {
                n_ptr++;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp(*this);
            operator++();
            return temp;
        }
    };

    iterator begin() {
        int* start = n_arr;
        int* end = n_arr + n;
        while (*start % 2 != 0 && start != end) {
            start++;
        }
        return iterator(start, end);
    }

    iterator end() {
        return iterator(n_arr + n, n_arr + n);
    }
};

#endif

#ifdef TESTS

#ifdef MANIPULATOR
void test_manipulator() {
    std::cout << "TEST MANIPULATOR" << std::endl;
    for (size_t i = 0; i < 20; i++) {
        std::cout << write_roman_numbers << std::endl;
    }
    std::cout << "--------------------" << std::endl;

    for (size_t i = 0; i < 30; i++) {
        std::cout << write_roman_numbers_flipped << std::endl;
    }

    std::cout << "--------------------" << std::endl;
}
#endif

#ifdef EFFECTOR
void test_effector() {
    std::cout << "TEST EFFECTOR" << std::endl;

    std::cout << negation(-5) << std::endl;
    std::cout << negation(17) << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << bool_string(true) << std::endl;
    std::cout << bool_string(false) << std::endl;

    std::cout << "--------------------" << std::endl;
}
#endif

#ifdef FUNCTION_TEMPLATE
void test_function_template() {
    std::cout << "TEST FUNCTION TEMPLATE" << std::endl;
    // Altalanos eset
    std::cout << add_elements<int>(3, 4) << std::endl;
    std::cout << add_elements<std::string>("3n", "-4m") << std::endl;
    std::cout << add_elements<bool>(true, false) << std::endl;

    // Specializacio
    std::cout << add_elements<char>('A', 'B') << std::endl;
    std::cout << add_elements<char>('Z', 'A') << std::endl;

    std::cout << "--------------------" << std::endl;

    // Altalanos eset
    int num1 = 15;
    int num2 = -9;
    std::cout << invert<int>(num1) << std::endl;
    std::cout << invert(num2) << std::endl;

    long long l_num1 = 23462138946;
    long long l_num2 = -12462241298;
    std::cout << invert<long long>(l_num1) << std::endl;
    std::cout << invert(l_num2) << std::endl;

    // Specializacio
    unsigned p_num1 = 87;
    unsigned p_num2 = 3;
    std::cout << invert(p_num1) << std::endl;
    std::cout << invert(p_num2) << std::endl;
    std::cout << invert((int&)p_num2) << std::endl;

    bool isVisible = false;
    bool isEnabled = true;
    #ifdef EFFECTOR
    std::cout << bool_string(invert(isVisible)) << std::endl;
    std::cout << bool_string(invert(isEnabled)) << std::endl;
    #else
    std::cout << invert(isVisible) << std::endl;
    std::cout << invert(isEnabled) << std::endl;
    #endif

    char ch1 = 'k';
    char ch2 = 'R';
    std::cout << invert(ch1) << std::endl;
    std::cout << invert(ch2) << std::endl;

    std::string str1 = "AlmA";
    std::string str2 = "Indul a gorog aludnI";
    std::cout << invert(str1) << std::endl;
    std::cout << invert(str2) << std::endl;

    std::cout << "--------------------" << std::endl;

    // Altalanos eset
    std::vector<std::string> str_vec = { "Al", "ma", " es ", "ko", "rte" };
    std::vector<int> int_vec = { 5, 713, 643, 913 };
    std::cout << join<std::vector<std::string>::iterator>(str_vec.begin(), str_vec.end()) << std::endl;
    std::cout << join(str_vec.begin(), str_vec.end(), ':') << std::endl;
    std::cout << join(str_vec.begin(), str_vec.end(), 35) << std::endl;
    std::cout << join(int_vec.begin(), int_vec.end(), '.') << std::endl;
    std::cout << join(int_vec.begin(), int_vec.end(), ' ') << std::endl;

    // Specializacio
    std::vector<char> char_vec = { 'K', 'o', 'r', 't', 'e', ' ', 'e', 's', ' ', 'a', 'l', 'm','a' };
    std::cout << join<std::vector<char>::iterator>(char_vec.begin(), char_vec.end()) << std::endl;
    std::cout << join(char_vec.begin(), char_vec.end()) << std::endl;

    std::cout << "--------------------" << std::endl;
}
#endif

#ifdef CLASS_TEMPLATE
void test_class_template() {
    std::cout << "TEST CLASS TEMPLATE" << std::endl;

    int numbers[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    my_vector<int, 20> vec(numbers, 9);
    std::cout << vec << std::endl;

    vec += 10;
    vec += 123;
    vec += 7531;
    std::cout << vec << std::endl;

    std::string strs[5] = { "Alma", "Korte", "Barack", "Szilva", "Banan" };
    my_vector<std::string, 7> vec_str(strs, 5);
    std::cout << vec_str << std::endl;

    vec_str += "Mango";
    vec_str += "Kiwi";
    // vec_str += "Meggy";
    std::cout << vec_str << std::endl;

    std::cout << "--------------------" << std::endl;
}
#endif

#ifdef TRAITS
void test_traits() {
    std::cout << "TEST TRAITS" << std::endl;

    Astronaut astronaut("John");
    Spacecraft<Astronaut> spacecraft_astronaut(astronaut);
    std::cout << spacecraft_astronaut.energy_consumption() << std::endl;

    Robot robot("R2D2");
    Spacecraft<Robot> spacecraft_robot(robot);
    std::cout << spacecraft_robot.energy_consumption() << std::endl;

    std::cout << "--------------------" << std::endl;
}
#endif

#ifdef METAPROGRAMMING

void test_metaprogramming() {
    std::cout << "TEST METAPROGRAMMING" << std::endl;

    std::cout << factorial_ct<0>::value << std::endl;
    std::cout << factorial_ct<1>::value << std::endl;
    std::cout << factorial_ct<2>::value << std::endl;
    std::cout << factorial_ct<4>::value << std::endl;
    std::cout << factorial_ct<5>::value << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << factorial_crt(0) << std::endl;
    std::cout << factorial_crt(1) << std::endl;
    std::cout << factorial_crt(2) << std::endl;
    std::cout << factorial_crt(4) << std::endl;
    std::cout << factorial_crt(5) << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << count_digits_ct<0>::value << std::endl;
    std::cout << count_digits_ct<1>::value << std::endl;
    std::cout << count_digits_ct<19>::value << std::endl;
    std::cout << count_digits_ct<740>::value << std::endl;
    std::cout << count_digits_ct<123456789>::value << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << count_digits_crt(0) << std::endl;
    std::cout << count_digits_crt(1) << std::endl;
    std::cout << count_digits_crt(19) << std::endl;
    std::cout << count_digits_crt(740) << std::endl;
    std::cout << count_digits_crt(123456789) << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << nth_sum_closed_crt(9) << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << nth_sum_closed_ct<10>::value << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << nth_sum_crt(11) << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << nth_sum_closed_ct<12>::value << std::endl;

    std::cout << "--------------------" << std::endl;
}

#endif

#ifdef FUNCTION_OBJECT
void test_function_object() {
    std::cout << "TEST FUNCTION OBJECT" << std::endl;

    std::vector<int> nums = { 1, -1, 1, 2, 10, 1};
    std::cout << count_if(nums.begin(), nums.end(), count_number(1)) << std::endl;
    std::cout << count_if(nums.begin(), nums.end(), count_number(2)) << std::endl;
    nums.push_back(2);
    std::cout << count_if(nums.begin(), nums.end(), count_number(2)) << std::endl;
    nums.push_back(-1);
    std::cout << count_if(nums.begin(), nums.end(), count_number(-1)) << std::endl;

    std::cout << "--------------------" << std::endl;
}
#endif

#ifdef STL
void test_stl() {
    std::cout << "TEST STL" << std::endl;

    std::cout << "In vector:" << std::endl;
    std::vector<unsigned> grades = { 5, 3, 4, 2, 1, 5, 2, 3, 4, 2, 3, 1 };
    std::map<unsigned, unsigned> grades_map = count_grades(grades);

    for (const auto [k, v] : grades_map) {
        std::cout << "  " << k << ": " << v << "db" << std::endl;
    }

    std::cout << "--------------------" << std::endl;

    std::cout << "In set:" << std::endl;
    std::set<unsigned> grades_set = { 5, 3, 4, 2, 5, 2, 3, 4, 2, 3, 6 };
    auto grades_map_from_set = count_grades_in_set(grades_set);

    for (const auto [k, v] : grades_map_from_set) {
        std::cout << "  " << k << ": " << v << "db" << std::endl;
    }

    std::cout << "--------------------" << std::endl;

    std::cout << "Maps united:" << std::endl;
    for (const auto [k, v] : unite_maps(grades_map, grades_map_from_set)) {
        std::cout << "  " << k << ": " << v << "db" << std::endl;
    }

    std::cout << "--------------------" << std::endl;

    std::cout << "(n) Maps united:" << std::endl;
    std::map<unsigned, unsigned> number_counts = { 
        { 104, 4 },
        { 1, 10 },
        { 40, 7 }
    };
    number_counts[17] = 54;

    std::vector<std::map<unsigned, unsigned>> map_container = { 
        grades_map, 
        grades_map_from_set, 
        unite_maps(grades_map, grades_map_from_set),
        number_counts
    };
    for (const auto [k, v] : unite_maps_from_vector(map_container)) {
        std::cout << "  " << k << ": " << v << "db" << std::endl;
    }

    std::cout << "--------------------" << std::endl;

    std::vector<std::string> strings = { "This ", "is ", "a ", "sentence" };
    std::cout << vector_to_string(strings) << std::endl;

    std::cout << "--------------------" << std::endl;

    std::cout << "Tasks listed:" << std::endl;
    std::vector<Task> tasks = { 
        { 1, "A1" },
        { 1, "A2" },
        { 2, "B1" },
        { 2, "B2" },
        { 3, "C1" },
        { 5, "D1" },
        { 10, "E1" }
    };
    std::map<unsigned, std::string> task_map;
    store_tasks(tasks, task_map);
    for (const auto& [k, v] : task_map) {
        std::cout << k << ": " << v << std::endl;
    }

    std::cout << "--------------------" << std::endl;
}
#endif

#ifdef ITERATOR
void test_iterator() {
    std::cout << "TEST ITERATOR" << std::endl;
    Entry entries[9] = {
        { "ABC123", 5 },
        { "DEF456", 3 },
        { "GHI789", 1 },
        { "JKL012", 2 },
        { "MNO345", 1 },
        { "PQR678", 5 },
        { "STU901", 3 },
        { "VWX234", 4 },
        { "YZA567", 2 },
    };
    EntryBook<10> entrybook = EntryBook<10>(entries, 9, 1);
    entrybook += { "BCD890", 1 };

    std::cout << "All entries:" << std::endl;
    std::cout << entrybook << std::endl;

    std::cout << "Entries with " << entrybook.get_selected_mark() << " mark:" << std::endl;
    for (const auto& etrs : entrybook) {
        std::cout << " " << etrs << std::endl;
    }

    entrybook.set_selected_mark(5);

    std::cout << "Entries with " << entrybook.get_selected_mark() << " mark:" << std::endl;
    for (auto it = entrybook.begin(); it != entrybook.end(); ++it) {
        std::cout << " " << it->id << " - " << it->mark << std::endl;
    }

    entrybook.set_selected_mark(2);

    std::cout << "Entries with " << entrybook.get_selected_mark() << " mark:" << std::endl;
    for (auto it = entrybook.begin(); it != entrybook.end(); it++) {
        std::cout << " " << *it << std::endl;
    }

    std::cout << "--------------------" << std::endl;

    int input_numbers[10] = { 1, 5, 6, 12, 7, 20, 9, 11, 30, 55 };

    numbers<20> m_numbers(input_numbers, 10);
    m_numbers += 40;
    m_numbers += 43;

    std::cout << "All numbers:" << std::endl;
    std::cout << m_numbers;

    std::cout << "Count:" << std::endl;
    std::cout << " " << m_numbers.get_count() << std::endl;

    std::cout << "Without iterator:" << std::endl;
    for (size_t i = 0; i < m_numbers.get_count(); i++) {
        std::cout << " " << m_numbers[i] << std::endl;
    }

    std::cout << "With iterator:" << std::endl;
    for (const auto number : m_numbers) {
        std::cout << " " << number << std::endl;
    }

    std::cout << "With iterator (another loop):" << std::endl;
    for (auto it = m_numbers.begin(); it != m_numbers.end(); it++) {
        std::cout << " " << *it << std::endl;
    }

    std::cout << "--------------------" << std::endl;

    std::vector<int> number_vector = { 1, 3, 5, 7, 9, 11 };
    numbers<7> m_numbers_vec(number_vector);

    std::cout << "All numbers:" << std::endl;
    std::cout << m_numbers_vec;

    std::cout << "Count:" << std::endl;
    std::cout << " " << m_numbers_vec.get_count() << std::endl;

    std::cout << "With iterator:" << std::endl;
    for (const auto number : m_numbers_vec) {
        std::cout << " " << number << std::endl;
    }

    m_numbers_vec += 20;

    std::cout << "With iterator (after adding 20):" << std::endl;
    for (auto it = m_numbers_vec.begin(); it != m_numbers_vec.end(); it++) {
        std::cout << " " << *it << std::endl;
    }
}
#endif

#endif

int main() {
#ifdef TESTS

#ifdef MANIPULATOR
    test_manipulator();
#endif

#ifdef EFFECTOR
    test_effector();
#endif

#ifdef FUNCTION_TEMPLATE
    test_function_template();
#endif

#ifdef CLASS_TEMPLATE
    test_class_template();
#endif

#ifdef TRAITS
    test_traits();
#endif

#ifdef METAPROGRAMMING
    test_metaprogramming();
#endif

#ifdef FUNCTION_OBJECT
    test_function_object();
#endif

#ifdef STL
    test_stl();
#endif

#ifdef ITERATOR
    test_iterator();
#endif

#endif
    return 0;
}