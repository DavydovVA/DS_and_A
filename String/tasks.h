#ifndef STRINGTASKS_H
#define STRINGTASKS_H

#define LEETCODE

#include <string>
#include <algorithm>


bool isAnagram(std::string str1, std::string str2) {
    // O(N log(n))
    str1.erase(std::remove_if(
            std::begin(str1),
            std::end(str1),
            ::isspace),
        std::end(str1));

    str2.erase(std::remove_if(
            std::begin(str2),
            std::end(str2),
            ::isspace),
        std::end(str2));

    if (str1.size() != str2.size()) {
        return false;
    }

    std::transform(std::begin(str1), std::end(str1),
        std::begin(str1), ::toupper);
    std::transform(std::begin(str2), std::end(str2),
        std::begin(str2), ::toupper);

#ifndef LEETCODE
    // First way: sort and compare
    std::sort(std::begin(str1), std::end(str1));
    std::sort(std::begin(str2), std::end(str2));

    return str1 == str2;
#else
    // Second path: use array representing alphabet
    int alphabMap [26] {};

    for(size_t i = 0; i < str1.size(); i++) {
        alphabMap[str1[i] - 'A']++;
        alphabMap[str2[i] - 'A']--;
    }

    for (int i = 0; i < sizeof(alphabMap) / sizeof(alphabMap[0]); i++) {
        if (alphabMap[i] != 0) {
            return false;
        }
    }

    return true;
#endif
}


bool isPalindrome(std::string str) {
    // O(n/2) = O(n)
    str.erase(
        std::remove_if(std::begin(str),
                    std::end(str),
                    ::isspace),
                std::end(str)
            );

    std::transform(std::begin(str), std::end(str),
        std::begin(str), ::toupper);

#ifndef LEETCODE
    int left = 0, right = str.size() - 1;
    while (left < right) {
        if (str[left++] != str[right--]) {
            return false;
        }
    }

    return true;
#else
    return std::equal(
                std::begin(str),
                std::begin(str) + str.size() / 2,
                std::rbegin(str)
                );
#endif
}


#undef LEETCODE

#endif