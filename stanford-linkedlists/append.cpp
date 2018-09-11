#include <forward_list>
#include <iostream>
#include <memory>


void append_list(std::forward_list<int> & a_list, std::forward_list<int> & b_list)
{
    // go to the end of the list
    b_list.reverse();

    while(!b_list.empty()) {
        a_list.push_front(b_list.front());
        b_list.pop_front();
    }
}

size_t  size(std::forward_list<int> &a_list)
{
    int cnt = 0;
    for (auto itr = a_list.begin(); itr !=  a_list.end(); itr++) {
        cnt++;
    }
    return cnt;

}

void print_fwd_list(std::forward_list<int> & a_list)
{
    // for(auto &x: a_list) {
    //     std::cout << x << " --> ";
    // }
    for (auto itr = a_list.begin(); itr !=  a_list.end(); itr++) {
        std::cout << *itr << " -->";
    }
    std::cout << "END" << std::endl;
}


int main()
{
    std::forward_list<int> a_list { 9, 11, 13, 15 };
    std::cout << " a_list contents: ";
    print_fwd_list(a_list);

    std::forward_list<int> b_list { 1, 3, 5, 7 };
    std::cout << " b_list contents: ";
    print_fwd_list(b_list);

    append_list(a_list, b_list);
    std::cout << " a_list (after append) contents: ";
    print_fwd_list(a_list);

    std::cout << " b_list (after append) contents: ";
    print_fwd_list(b_list);

    return 0;
}