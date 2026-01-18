#pragma once
#include "DataStructures.h"

// ======================= ALGORITHMS ============================== //
// The algorithms below can be related to ds/maths or different engineering fields




/*
* function to convert integer to binary
*/
std::string ToBinary(int N)
{
    std::string bin = "";

    while (N != 0)
    {
        if (N % 2 != 0)
            bin.push_back('1');
        else
            bin.push_back('0');
        N = N / 2;
    }
    return bin;
}

/*
* function to get the largest gap of zeros in a binary number
*/
int countBinaryGap(int N)
{
    // Implement your solution here
    std::string binN = ToBinary(N);
    int maxGap = 0;
    int currGap = 0;
    bool countZero = false;

    for (size_t i = 0; i < binN.size(); i++)
    {
        if (binN[i] == '1')
        {
            countZero = true;
            if (currGap > maxGap)
                maxGap = currGap;
            currGap = 0;
        }
        else if (countZero == true)
            currGap += 1;

    }
    return maxGap;
}

/**
 *  Deduce the parking fee 
 *  given time E for starting time and L which is the end time
 */
int parkingTicket(std::string& E, std::string& L)
{
    // Implement your solution here
    // parking entrance fee is 2 by default
    int fee = 2;
    int total_h = 0;
    int total_m = 0;
    std::vector<int> times;
    std::stringstream ss;
    ss << E << ':' << L;
    std::string s;

    while (std::getline(ss, s, ':'))
    {
        std::stringstream tempStream;
        int tempVal;
        tempStream << s;
        tempStream >> tempVal;
        times.push_back(tempVal);
    }


    if (times[0] < times[2])
    {
        total_h += (times[2] - times[0]);
    }
    if (times[1] > times[3])
    {
        times[3] += 60;
        total_h -= 1;
        total_m += (times[3] - times[1]);
    }
    else if (times[1] < times[3])
        total_m += (times[3] - times[1]);
    if (total_h >= 1 && total_m == 0)
    {
        total_h--;
        fee += 3;
    }
    if (total_h == 0 && total_m >= 1)
    {
        total_m = 0;
        fee += 3;
    }
    if (total_h >= 1 && total_m >= 1)
    {
        total_h--;
        fee += 3;
    }
    if (total_h >= 1)
    {
        fee += (total_h * 4);
        total_h = 0;
    }
    if (total_m >= 1)
        fee += 4;

    return fee;
}

/**
 *  Find the missing positive number from a vector where nums[i] >= 1
 *  ignoring duplicates and non-positive values
 */
int firstMissingPositive(std::vector<int>& nums)
{
    // Implement your solution here
    int s = 0;

    // cleaning up the vector
    std::sort(nums.begin(), nums.end());
    auto lastPositive = std::remove_if(nums.begin(), nums.end(), [](int i) {return i <= 0; });
    auto rmDup = std::unique(nums.begin(), lastPositive);
    nums.resize(std::distance(nums.begin(), rmDup));
    std::vector<int>::iterator min = std::min_element(nums.begin(), nums.end());

    if (nums.size() == 0)
        s = 1;
    else if (nums.size() == 1)
    {
        if (nums[nums.size() - 1] > 1)
            s = 1;
        else if (nums[nums.size() - 1] == 1)
            s = nums[nums.size() - 1] + 1;
    }
    else if (nums.size() > 1)
    {
        for (size_t i = 0; i < nums.size(); i++)
        {
            if (i == nums.size() - 1 && (nums[i] - nums[i - 1]) == 1)
            {
                s = nums[i] + 1;
                break;
            }
            // omit current element if it is the same as the next one
            if ((i != nums.size() - 1) && (*min == 1) && (nums[i] >= 1 && nums[i + 1] >= 1) && (nums[i] != nums[i + 1]))
            {
                if ((nums[i + 1] - nums[i]) == 1)
                    continue;
                else if ((nums[i + 1] - nums[i]) > 1)
                {
                    s = nums[i] + 1;
                    break;
                }
            }
            if (*min > 1)
            {
                s = 1;
                break;
            }
        }
    }
    return s;
}

/*
* utility function for swapping values of variables
*/
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/** hourglass problem #1
 * -given an array of 6X6 calculate the sum of the hourglasses
 * -and find the maximum
 */
int hourGlassLargestSum(vect2d& arr)
{
    vect2d hourGlasses;
    vect hourGlass;
    vect hourGlassesSums;
    // a hourglass is a 3X3 subset and contains 16 in total if arr size is 6x6
    int hg = (int)pow(((pow(arr.size(), 2) / 3) / 3), 2);
    // indices to add to the iterators to start from a specific point
    int ibg, ilst, jbg, jlst;
    ibg = 0;
    ilst = 3;
    jbg = 0;
    jlst = 3;
    // main loop
    while (hg > 0)
    {
        // can use auto but prefer to use exact type at some points
        for (iter2d iti = arr.begin() + ibg; iti != arr.end() - ilst; iti = std::next(iti))
        {
            for (iter itj = iti->begin() + jbg; itj != iti->end() - jlst; itj = std::next(itj))
            {
                hourGlass.push_back(*itj);
            }
        }
        hourGlasses.push_back(hourGlass);
        hourGlass.clear();
        // inner vector iterator manipulation
        if ((jbg >= 0 && jbg <= 3) && (jlst >= 0 && jlst <= 3))
        {
            ++jbg;
            --jlst;
        }
        // outer vector iterator manipulation
        if (jbg > 3 && jlst < 0)
        {
            ++ibg;
            --ilst;
            jbg = 0;
            jlst = 3;
        }
        --hg;
    }
    // summing the hourglasses
    for (auto i = hourGlasses.begin(); i != hourGlasses.end(); i = std::next(i))
    {
        int sum = 0;
        for (auto j = i->begin(); j != i->end(); j = std::next(j))
        {
            // skip the moust outer left and right index (coresponding to a hourglass)
            if (std::distance(i->begin(), j) == 3 || std::distance(i->begin(), j) == 5) continue;
            sum += *j;
        }
        hourGlassesSums.push_back(sum);
    }
    // find the maximum;
    int max = INT_MIN;
    for (auto i : hourGlassesSums)
    {
        if (max < i)
            max = i;
    }
    return max;
}

/** duplicate numbers
 *  find the number pair numbers (2 same numbers)
 */
int sockMerchant(int n, vect& ar)
{
    vect colorsFound;
    int matchingPairs = 0;

    for (int i = 0; i < n; ++i)
    {
        int currentColor = ar.at(i);
        int inColor = 0;
        for (size_t f = 0; f < colorsFound.size(); ++f)
        {
            if (currentColor == colorsFound.at(f))
            {
                inColor = colorsFound.at(f);
                break;
            }
        }
        if (currentColor == inColor)
            continue;

        vect pairsFound;
        for (int j = 0; j < n; ++j)
        {
            if (currentColor == ar.at(j))
            {
                pairsFound.push_back(ar.at(j));
            }
        }
        colorsFound.push_back(currentColor);

        int socks = 0;
        for (size_t f = 0; f < pairsFound.size(); ++f)
        {
            socks += pairsFound.at(f);
        }
        socks = (int)(socks / (ar.at(i) * 2));
        matchingPairs += socks;
    }
    return matchingPairs;
}


// First Unique Character in a String
int firstUniqChar(std::string s)
{
    std::map<char, int> a;

    for (unsigned int i = 0; i < s.length(); ++i)
    {
        char curr = s[i];
        if (a.find(curr) == a.end())
        {
            a.insert(a.begin(), std::pair<char, int>(curr, 1));
        }
        else
        {
            a.at(s[i]) += 1;
        }
    }

    unsigned int i = 0;
    while (i < s.length())
    {
        for (auto it = a.begin(); it != a.end(); ++it)
        {
            if (s[i] == it->first && it->second == 1)
            {
                return i;
            }
        }
        ++i;
    }
    return -1;
}

/** Given 2 strings
 * return the number of deletions to make an anagram from both strings
 */
int makeAnagram(std::string a, std::string b)
{
    int deletions = 0;
    std::map<char, int> freqCharsA;
    std::map<char, int> freqCharsB;

    for (char i = 'a'; i <= 'z'; ++i)
    {
        freqCharsA.insert(std::pair<char, int>(i, 0));
        freqCharsB.insert(std::pair<char, int>(i, 0));
    }

    for (unsigned int i = 0; i < a.length(); ++i)
    {
        freqCharsA.at(a[i]) += 1;
    }
    for (unsigned int i = 0; i < b.length(); ++i)
    {
        freqCharsB.at(b[i]) += 1;
    }

    for (char i = 'a'; i <= 'z'; ++i)
    {
        deletions += abs(freqCharsA.at(i) - freqCharsB.at(i));
    }
    return deletions;
}

/** Given a vector of prices and a budget of k
 *  find all toys that you can buy with the budget k
 *  by finding the minimum
 */
int maximumToys(vect prices, int k)
{
    int items = 0;
    while (k > 0)
    {
        int lowestPrice = INT_MAX;
        int lowestAt = 0;
        for (size_t i = 0; i < prices.size(); ++i)
        {
            if (lowestPrice > prices.at(i))
            {
                lowestPrice = prices.at(i);
                lowestAt = i;
            }
        }
        if ((k - lowestPrice) >= 0)
        {
            items += 1;
            prices.erase(prices.begin() + lowestAt);
        }
        k -= lowestPrice;
    }
    return items;
}


/** Given a vector of prices and a budget of k
 *  find all toys that you can buy with the budget k
 *  by sorting the sequence from the smallest to the largest
 */
int maximumToysTwo(vect prices, int k)
{
    for (unsigned int i = 0; i < prices.size(); ++i)
    {
        for (unsigned int j = 0; j < prices.size() - 1; ++j)
        {
            if (prices.at(j) > prices.at(j + 1))
            {
                int temp = 0;
                temp = prices.at(j);
                prices.at(j) = prices.at(j + 1);
                prices.at(j + 1) = temp;
            }
        }
    }
    int items = 0;
    for (unsigned int p = 0; p < prices.size(); ++p)
    {
        if ((k - prices.at(p)) >= 0)
        {
            items += 1;
            k -= prices.at(p);
        }
    }
    return items;
}

/** Given a string of only A B chars
 *  if there are duplicates adjents e.g. : AA , BB
 *  find the number of deletions to eliminate the duplicates
 */
int alternatingCharacters(std::string s)
{
    int deletions = 0;
    for (unsigned int i = 0; i < s.size(); ++i)
    {
        if ((s[i] == 'A' || s[i] == 'B') && (s[i + 1] == 'A' || s[i + 1] == 'B'))
        {
            if (s[i] == s[i + 1])
            {
                deletions += 1;
            }
        }
    }
    return deletions;
}

/** Recursive super digit
 *  Given a string n and a number k
 *  Repeat the string k times
 *  Do the sums of the repeated string numbers till the size reacheas 1
 */
int superDigit(std::string n, int k)
{
    if (n.length() > 1)
    {
        long int sum = 0;
        for (unsigned int i = 0; i < n.size(); ++i)
        {
            std::stringstream s;
            int num = 0;
            s << n[i];
            s >> num;
            sum += num;
        }
        return superDigit(std::to_string(sum * k), 1);
    }
    return stoi(n);
}

// Given 2 strings find the common characters
std::string twoStrings(std::string s1, std::string s2)
{
    int commonSubStrings = 0;
    std::map<char, int> strMap1;
    std::map<char, int> strMap2;

    for (char i = 'a'; i <= 'z'; ++i)
    {
        strMap1.insert(std::pair<char, int>(i, 0));
    }
    for (unsigned int i = 0; i < s1.length(); ++i)
    {
        strMap1.at(s1[i]) += 1;
    }
    for (unsigned int i = 0; i < s2.length(); ++i)
    {
        if (strMap1.at(s2[i]) > 0)
        {
            strMap1.at(s2[i])--;
            commonSubStrings++;
        }
    }
    if (commonSubStrings > 0)
    {
        return "YES";
    }
    return "NO";
}

// simple conversion from string to integer using hashmaps;
int convertToInt(std::string a)
{
    if (a.length() == 1)
        return stoi(a);
    std::map<int, char> ints;
    int n = 0;
    for (char i = '\0'; i <= '\t'; i++)
    {
        ints.insert(std::pair<int, char>(n, i));
        n++;
    }

    int sum = 0;
    for (unsigned int s = 0; s < a.length(); ++s)
    {
        std::map<int, char>::iterator f = ints.find((int)a[s]);
        int num = f->first;
        sum += num;
    }
    return convertToInt(std::to_string(sum));
}

long repeatedString(std::string s, long n)
{
    std::string newStr = "";
    int aFreq = 0;
    unsigned int i = 0;
    if (s == "a")
    {
        return s.length() * n;
    }
    while (newStr.length() != n && i < s.length())
    {
        std::stringstream stream;
        std::string ch = "";
        stream << s[i];
        stream >> ch;
        newStr += ch;
        ++i;
        if (i == s.length())
            i = 0;
    }
    std::cout << newStr;
    for (auto i : newStr)
    {
        if (i == 'a') aFreq++;
    }
    return aFreq;
}

/** Inserting nodes in a doubly-linked list in a sorted way
 *  Given node to the head of the list and a data
 *  Insert the node according to its order
 */
Lists::nodePtrD sortedInsert(Lists::nodePtrD& head, int data)
{
    Lists::nodePtrD n = new Lists::nodeDll;
    n->data = data;
    n->prev = NULL;
    n->next = NULL;

    if (head == NULL)
    {
        head = n;
        return head;
    }

    Lists::nodePtrD curr = head;

    while (curr != NULL)
    {
        if (data <= curr->data && curr->prev == NULL)
        {
            curr->prev = n;
            n->next = curr;
            return n;
        }
        if (data > curr->data&& curr->next == NULL)
        {
            curr->next = n;
            n->prev = curr;
            break;
        }
        if (data > curr->data&& data <= curr->next->data)
        {
            n->prev = curr;
            n->next = curr->next;
            curr->next = n;
            curr->next->prev = n;
            break;
        }
        curr = curr->next;
    }
    return head;
}

// Reversing a linked list
Lists::nodePtr ReverseLL(Lists::nodePtr head)
{
    if (head == NULL || head->next == NULL) return head;
    Lists::nodePtr prevPtr = NULL;
    Lists::nodePtr nextPtr = NULL;
    Lists::nodePtr curr = head;

    while (curr != NULL)
    {
        nextPtr = curr->next;
        curr->next = prevPtr;
        prevPtr = curr;
        curr = nextPtr;
    }
    head = prevPtr;
    return head;
}

Lists::nodePtrD ReverseDLL(Lists::nodePtrD& head)
{
    if (head == NULL || head->next == NULL) return head;
    // find the last el

    Lists::nodePtrD prevPtr = NULL;
    Lists::nodePtrD nextPtr = NULL;
    Lists::nodePtrD curr = head;

    while (curr != NULL)
    {
        nextPtr = curr->next;
        curr->next = prevPtr;
        prevPtr = curr;
        curr = nextPtr;
    }
    head = prevPtr;
    return head;
}