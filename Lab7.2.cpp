// list_utils.h
#pragma once
#include <forward_list>

void create(std::forward_list<int>& lst, int n);
void print(const std::forward_list<int>& lst);
void remove_preceding(std::forward_list<int>& lst, int target);
// list_utils.cpp
#include "list_utils.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib> 
using namespace std;

int RandomNumber() {
    return rand() % 100 - 50;
}

void create(forward_list<int>& lst, int n) {
    for (int i = 0; i < n; ++i)
        lst.push_front(RandomNumber());
    lst.reverse(); 
}

void print(const forward_list<int>& lst) {
    for (int i : lst)
        cout << i << " ";
    cout << endl;
}

void remove_preceding(forward_list<int>& lst, int target) {
    if (lst.empty())
        return;

    auto before = lst.before_begin();     
    auto curr = lst.begin();              
    auto next = std::next(curr);          

    while (next != lst.end()) {
        if (*next == target) {
            lst.erase_after(before);      
            curr = before;
            next = std::next(curr);
        }
        else {
            ++before;
            ++curr;
            ++next;
        }
    }
}
// main.cpp
#include <iostream>
#include <forward_list>
#include <ctime>
#include "list_utils.h"

using namespace std;

int main() {
    srand((unsigned int)time(NULL));
    setlocale(LC_CTYPE, "ukr");

    int n;
    cout << "Введiть кiлькiсть елементiв списку: ";
    cin >> n;

    forward_list<int> lst;
    create(lst, n);

    cout << "Початковий список:\n";
    print(lst);

    int x;
    cout << "Введiть значення елемента, перед яким слiд видалити попереднiй: ";
    cin >> x;

    remove_preceding(lst, x);

    cout << "Список пiсля видалення:\n";
    print(lst);

    return 0;
}
