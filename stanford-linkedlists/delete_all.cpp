#include <forward_list>
#include <iostream>

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

void clear_all(std::forward_list<int> & a_list)
{
    a_list.clear();
}

void pop_all(std::forward_list<int> & a_list)
{
    while(!a_list.empty()) {
        a_list.pop_front();
    }
}

int main()
{
    std::forward_list<int> a_list { 10, 20, 30, 40, 50 };
    std::cout << " list contents: ";
    print_fwd_list(a_list);
    
    std::cout << "a_list size = " << size(a_list) << std::endl;
    clear_all(a_list);
    std::cout << "a_list size (after clear_all) = " << size(a_list) << std::endl;

    std::forward_list<int> b_list { 10, 20, 30, 40, 50 };
    std::cout << " list contents: ";
    print_fwd_list(b_list);

    std::cout << "b_list size = " << size(b_list) << std::endl;
    pop_all(b_list);
    std::cout << "b_list size (after pop_all) = " << size(b_list) << std::endl;

    return 0;
}