#ifndef STRINGTASKS_H
#define STRINGTASKS_H

#define LEETCODE

#include <string>
#include <vector>
#include <cmath>
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


std::string DecimalToBinary(int decimal) {
    // O(n log(n)), n = decimal
    std::string binaryStr {"0"};

    if (decimal > 0) {
        binaryStr = "";

        //variable for convenient division
        div_t d {};
        d.quot = decimal;

        do {
            d = std::div(d.quot, 2);

            binaryStr = std::to_string(d.rem) + binaryStr;
        }while(d.quot);
    }

    return binaryStr;
}


int StringToDecimal(const std::string str) {
    // O(n)
    int decimal = 0, n = 0;
    std::string::const_reverse_iterator it;

    for(it = std::rbegin(str), n; it != std::rend(str); it++, n++) {
        if (*it == '1') {
            decimal += pow(2, n);
        }
    }

    return decimal;
}


std::vector<std::string> GenerateSubsequences(std::string str) {
    // O(n 2^n)
    // To find out all subsequences of a string, we need to iterate through all characters of the
    // string. We also create a bit counter variable to mark which element position should be
    // considered to take as a subsequence, also known as a power set. The power set of S is the
    // set of all subsets of S. Suppose we have three characters in a string, which are xyz. The
    // power set of the string will be 2n elements, which is as follows:
    // BIT -> SUBSET
    // ===================
    // 000 -> Empty subset
    // 001 -> "x"
    // 010 -> "y"
    // 011 -> "xy"
    // 100 -> "z"
    // 101 -> "xz"
    // 110 -> "yz"
    // 111 -> "xyz"
    std::vector<std::string> vec;

    const int strLen = str.size();
    const int bitCounter = std::pow(2, strLen);
    for (int i = 1; i < bitCounter; i++) {
        std::string subseq = "";

        for(int j = 0; j < strLen; j++) {
            if (i & (1 << j)) {
                subseq += str[j];
            }
        }

        vec.push_back(subseq);
    }

    return vec;
}


// A subsequence is a sequence that can be derived from another sequence
// by deleting some elements without changing the order of the remaining elements
// We suppose str1 is subsequence of str2, x - str1's index, y - str2's
bool RisSubsequence(
    const std::string &str1,
    const std::string &str2,
    int x,
    int y)
{
    // O(n)
    if (x == 0) {
        return true;
    }
    if (y == 0) {
        return false;
    }

    if (str1[x - 1] == str2[y - 1]) {
        return RisSubsequence(str1, str2, x - 1, y - 1);
    }

    return RisSubsequence(str1, str2, x, y - 1);
}

// Returns true if str1 is subsequence of str2
bool IisSubsequence(const std::string &str1, const std::string &str2) {
    // O(n)
    int n = str1.size(), m = str2.size();

    int i = 0, j = 0;
    while (i < n && j < m) {
        if (str1[i] == str2[j]) {
            i++;
        }
        j++;
    }

    return i == n;
}


std::vector<int> SearchPattern(std::string str, std::string pattern) {
    // O(n * (m - n))
    std::vector<int> indexVec;

    int strLen = str.size(), patLen = pattern.size();
    if (patLen <= strLen) {
        for(int i = 0; i < strLen - patLen; i++) {
            int j;
            for (j = 0; j < patLen; j++) {
                if (str[i + j] != pattern[j]) {
                    break;
                } 
            }

            if (j == patLen) {
                indexVec.push_back(i);
            }
        }
    }

    return indexVec;
}


#undef LEETCODE

#endif