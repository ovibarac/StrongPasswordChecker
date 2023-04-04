# StrongPasswordChecker

A password is considered strong if below conditions are all met: 

1. It has at least 6 characters and at most 20 characters. 

2. It must contain at least one lowercase letter, at least one uppercase letter, and at least one 
digit. 

3. It must NOT contain three repeating characters in a row ("...aaa..." is weak, but "...aa...a..." 
is strong, assuming other conditions are met). 

Write an algorithm that takes a string s as input, and return the MINIMUM change required to 
make s a strong password. If s is already strong, return 0. 

Insertion, deletion or replace of any one character are all considered as one change

## Algorithm:

The algorithm starts by counting the missing types of characters, which can be a value from 0 to 3 because of condition number 2.

If there are less than 6 characters in the password, the minimum number of changes is the max between the number of missing types and (6 - the password length), which is the number of missing characters.


For example, if the password is "1A" the needed number of changes is 4 because we need to add 4 characters, which encapsulates the missing lowercase letter, and if the password is "ababa" the needed number of changes is 2, because it is missing an uppercase letter and a digit, and only needs one more character added.
 
If the length is >=6, the algorithm continues by storing the length of each group of 3 or more repeating characters, together with the length % 3 which will be used for sorting.
If there are more than 20 characters, we can remove (password length - 20) characters from the groups, in order of their lengths % 3 ascending. This is because removing at each step from the group closest to len%3==0 ensures that we are minimizing the number of replacements needed, because in a group we can always remove every third character.


For example, the group of length 13 "aaaaaaaaaaaaa" can have a minimum of 13/3=4 changes if every third character is replaced: "aaBaa1aabaaba". So if the password is "bbaaaaaaaaaaaaaaacccccc", with group 'a' of size 15 and group 'c' of size 6, we can first remove a character from 'a' so the length will be 14 and 14%3=2, so next we will remove from group 'c' so the length will be 5 and 5%3=2, and then we can remove from 'a' again and the password length will now be 20.

The sorting of the groups is achieved by using a min heap which stores a pair of (len%3, len), and if a character is removed from a group the group is either shortened or removed if it's length is less than 3.

The number of changes required for each group is it's length/3 as stated earlier, so the total number of changes for groups is the sum of each length/3.

The output is the maximum between the number of changes required by the character types condition and the groups condition + the number of removed characters if the length is greater than 20.
