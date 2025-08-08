#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>


int main() {
    print_with_separator(", ", "apple", "banana", "cherry");  // → apple, banana, cherry
    print_upper(", ", "hello", "world");  // → HELLO, WORLD
    print_compressed("  this   is    compressed  ");  // → thisiscompressed
    return 0;
}
