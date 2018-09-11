#include <forward_list>
#include <iostream>


bool get_nth(std::forward_list<int> &a_list, int n, int &val)
{
    int idx = 0;
    for (auto  itr = a_list.begin(); itr != a_list.end(); itr++) {
        if (n == idx) {
            val = *itr;
            return true;
        }
        idx++;
    }
    return false;
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

void find_nth(std::forward_list<int> & a_list, int n)
{
    int val;
    bool found = get_nth(a_list, n, val);
    if (found) {
        std::cout << " found: list[" << n << "] = " << val << std::endl; 
    } else {
        std::cout << " not found list[" << n << "]" << std::endl;
    }

}

int main()
{
    std::forward_list<int> mylist { 10, 20, 30, 40, 50 };
    std::cout << " list contents: ";
    print_fwd_list(mylist);

    find_nth(mylist, -1);
    find_nth(mylist, 0);
    find_nth(mylist, 1);
    find_nth(mylist, 2);
    find_nth(mylist, 3);
    find_nth(mylist, 4);
    find_nth(mylist, 5);

    std::cout << "----------" << std::endl;

    std::forward_list<int> b_list;
    find_nth(b_list, 0);
    find_nth(b_list, -1);
    find_nth(b_list, 10);

    return 0;
}