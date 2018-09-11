#include <forward_list>
#include <iostream>

bool sorted_insert(std::forward_list<int> &a_list, int val)
{
    //if (val <= a_list.front()) {
    if (a_list.empty() || (!a_list.empty() && val <= a_list.front())) {
        a_list.push_front(val);
        return true;
    }

    std::forward_list<int>::iterator prev_itr;
    for (auto itr = a_list.begin();; itr++) {
        //if ((itr == a_list.end()) || (itr!= a_list.end() && val <= *itr)) {
        //prev_itr = itr;
        if ((itr!= a_list.end() && val <= *itr) || (itr == a_list.end())) {
            a_list.insert_after(prev_itr, val);
            return true;
        }
        prev_itr = itr;
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

    sorted_insert(a_list, 9);
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;

    sorted_insert(a_list, 11);
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;

    sorted_insert(a_list, 21);
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;

    sorted_insert(a_list, 31);
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;

    sorted_insert(a_list, 41);
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;

    sorted_insert(a_list, 51);
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;

    sorted_insert(a_list, 68);
    print_fwd_list(a_list);
    std::cout << "----------" << std::endl;

    return 0;
}