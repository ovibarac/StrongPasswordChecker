#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int strongPasswordChecker(string s) {
    int missingTypes=0, missingDigit=1, missingUpper=1, missingLower=1;
    for(const char& c : s){
        if(c >= '0' && c <='9')
            missingDigit=0;
        if(c >='a' && c <= 'z')
            missingLower=0;
        if(c >= 'A' && c <= 'Z')
            missingUpper=0;
    }
    //count missing character types
    missingTypes+=missingDigit+missingUpper+missingLower;

    //if there are less than 6 characters, the answer is the max of the number of missing character types and the number of missing characters
    if(s.length()<6)
        return max((int)(6-s.length()), missingTypes);

    vector<pair<int, int>> groups;//(len%3, len)
    int i=0;
    for(int j=0; j < s.length(); j++){
        //check if there is a group in the interval [i,j)
        if(s[j]!=s[i]){
            if(j-i >= 3){
                //add new group of at least 3 repeating characters
                groups.push_back(pair<int,int>((j-i)%3, j-i));
            }
            i=j;
        }
        //if j points to last character
        if(j==s.length()-1){
            if(j-i+1 >= 3){
                //add new group of at least 3 repeating characters
                groups.push_back(pair<int,int>((j-i+1)%3, j-i+1));
            }
        }
    }

    if(s.length() > 20){
        //order groups by len%3 ascending
        make_heap(groups.begin(), groups.end(), greater<>{});

        //while there are too many characters, remove from the groups ordered by len%3,
        //because always removing from the group closest to len%3=0 ensures that the sum of the lengths/3 calculated in the next step will be minimal
        for(int i = 0; i < s.length()-20 && !groups.empty(); i++){
            auto group = groups.front();
            pop_heap(groups.begin(), groups.end(), std::greater<>{});
            groups.pop_back();

            //if group len is 3, after removing one it will be 2 so it doesn't need to be added back in
            if(group.second > 3){
                //remove element from group
                groups.push_back(pair<int,int>((group.second-1)%3, group.second-1));
                push_heap(groups.begin(), groups.end(), std::greater<>{});
            }
        }
    }

    //for each group g we need g/3 replaces
    int sum=0;
    for(const auto& g : groups){
        sum+=g.second/3;
    }

    //answer is max between missing types and the number to replace from the groups + the number of extra characters
    return max(missingTypes, sum) + max(0, (int)s.length()-20);
}

int main() {
    string password="abbabcaaaaaaaaaaacccccc";
    cout<<strongPasswordChecker(password);
}
