#include <forward_list>
#include <iostream>
#include <memory>


void remove_duplicates(std::forward_list<int> & a_list)
{
    for(auto itr = a_list.begin(), prev_itr = a_list.begin(); itr != a_list.end();) {
        if (itr != a_list.begin()) {
            if (*prev_itr == *itr) {
                itr = a_list.erase_after(prev_itr);
            } else {
                prev_itr = itr;
                itr++;
            }
        } else {
            prev_itr = itr;
            itr++;
        }
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
    // sorted list 
    std::forward_list<int> a_list { 9, 9, 9, 10, 11, 13, 13, 15, 15 };
    std::cout << " a_list contents: ";
    print_fwd_list(a_list);

    remove_duplicates(a_list);
    std::cout << " a_list contents (after remove duplicates): ";
    print_fwd_list(a_list);

    std::forward_list<int> b_list { 9, 9, 9 };
    std::cout << " b_list contents: ";
    print_fwd_list(b_list);

    remove_duplicates(b_list);
    std::cout << " b_list contents (after remove duplicates): ";
    print_fwd_list(b_list);

    std::forward_list<int> c_list { 9 };
    std::cout << " c_list contents: ";
    print_fwd_list(c_list);

    remove_duplicates(c_list);
    std::cout << " c_list contents (after remove duplicates): ";
    print_fwd_list(c_list);

    std::forward_list<int> d_list;
    std::cout << " d_list contents: ";
    print_fwd_list(d_list);

    remove_duplicates(d_list);
    std::cout << " d_list contents (after remove duplicates): ";
    print_fwd_list(d_list);



    return 0;
}