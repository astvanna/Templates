#include <iostream>
#include <string>
#include <vector>

void unpack(std::vector<std::string>& Args) { }

template <typename T, typename ...Types>
void unpack(std::vector<std::string>& Args, const T& first, const Types&... args) {
    Args.push_back(std::to_string(first));
    unpack(Args, args...);
}

template <typename... Types>
void unpack(std::vector<std::string>& Args, const std::string& first,  const Types&... args) {
    Args.push_back(first);
    unpack(Args, args...);
}

template <typename... Types>
void unpack(std::vector<std::string>& Args, const char* first, const Types&... args) {
    Args.push_back(std::string(first));
    unpack(Args, args...);
}

template <typename... Types>
void unpack(std::vector<std::string>& Args, char first, const Types&... args) {
    Args.push_back(std::string(1, first));
    unpack(Args, args...);
}

template <typename ...Types>
std::string format(const std::string& format, const Types&... args) {
    std::string s;
    std::vector<std::string> Args;
    unpack(Args, args...);
    int k = 0;
    for (int i = 0; i < format.size(); ++i) {
        if (i < format.size() && format[i] == '{' && format[i + 1] == '}') {
            s += Args[k++];
            ++i;
            continue;
        } 
        s += format[i];
    }
    return s;
}

int main() {
    std::cout << format("Hello, {}! You have {} messages.", "Alice", 3) << std::endl;
}