#include <forward_list>
#include <iostream>


int count(std::forward_list<int> &a_list, int element)
{
    int cnt = 0;
    for (auto itr = a_list.begin(); itr != a_list.end(); itr++)
    {
        if (*itr == element) {
            cnt++;
        }   
    }
    return cnt;
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
    std::forward_list<int> mylist { 10, 20, 30, 40, 50, 10, 20, 30, 10 };
    std::cout << " size = " << size(mylist) << std::endl;
    std::cout << " contents: ";
    print_fwd_list(mylist);
    std::cout << " number of 10's in the list: " << count(mylist, 10) << std::endl;
    std::cout << " number of 30's in the list: " << count(mylist, 30) << std::endl;
    return 0;
}