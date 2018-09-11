#include <forward_list>
#include <iostream>

bool insert_nth(std::forward_list<int> &a_list, int n, int val)
{
    if (n == 0) {
        a_list.push_front(val);
        return true;
    }
    int idx = 0;
    //std::forward_list<int>::iterator itr;
    for (auto itr = a_list.begin(); itr != a_list.end(); itr++) {
        if (n == idx+1) {
            a_list.insert_after(itr, val);
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


int main()
{
    std::forward_list<int> a_list { 10, 20, 30, 40, 50 };
    std::cout << " list contents: ";
    print_fwd_list(a_list);


    insert_nth(a_list, 0, 9);
    std::cout << " list contents (after insert 9): ";
    print_fwd_list(a_list);
    insert_nth(a_list, 2, 11);
    std::cout << " list contents (after insert 11): ";
    insert_nth(a_list, 7, 51);
    std::cout << " list contents (after insert 51): ";
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;



    return 0;
}