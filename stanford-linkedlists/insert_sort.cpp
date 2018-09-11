#include <forward_list>
#include <iostream>
#include <memory>

bool sorted_insert(std::unique_ptr<std::forward_list<int>>& a_list, int val)
{
    if (a_list->empty() || (!a_list->empty() && val <= a_list->front())) {
        a_list->push_front(val);
        return true;
    }

    std::forward_list<int>::iterator prev_itr;
    for (auto itr = a_list->begin();; itr++) {
        if ((itr!= a_list->end() && val <= *itr) || (itr == a_list->end())) {
            a_list->insert_after(prev_itr, val);
            return true;
        }
        prev_itr = itr;
    }

    return false;
}

std::unique_ptr<std::forward_list<int>> insertion_sort(std::forward_list<int> &a_list)
{
    auto b_list = (std::unique_ptr<std::forward_list<int>>) new std::forward_list<int>();
    while(!a_list.empty()) {
        sorted_insert(b_list, a_list.front());
        a_list.pop_front();
    }
    /// NOTE: this is how you return a unique ptr, created in a function via std::move()
    return std::move(b_list);
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

void print_fwd_list_unique_ptr(std::unique_ptr<std::forward_list<int>> & a_list)
{
    // for(auto &x: a_list) {
    //     std::cout << x << " --> ";
    // }
    for (auto itr = a_list->begin(); itr !=  a_list->end(); itr++) {
        std::cout << *itr << " -->";
    }
    std::cout << "END" << std::endl;
}

int main()
{
    std::forward_list<int> a_list { 60, 20, 10, 30, 50, 40 };
    std::cout << " list contents: ";
    print_fwd_list(a_list);


    std::unique_ptr<std::forward_list<int>>  s_list = insertion_sort(a_list);

    std::cout << " sorted list contents: ";
    print_fwd_list_unique_ptr(s_list);
    std::cout << "----------" << std::endl;

    return 0;
}