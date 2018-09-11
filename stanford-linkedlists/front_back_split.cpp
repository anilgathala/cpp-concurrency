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

void front_back_split(
    std::forward_list<int> & a_list,
    std::forward_list<int> & front,
    std::forward_list<int> & back
    )
{
    if (a_list.empty()) {
        return;
    }
    size_t sz = size(a_list);

    if (sz == 1) {
        front.push_front(a_list.front());
        a_list.pop_front();
        return;
    }
    // if (sz == 2) {
    //     front.push_front(a_list.front());
    //     a_list.pop_front();
    //     back.push_front(a_list.front());
    //     a_list.pop_front();
    //     return;
    // }

    int front_end =  (sz%2 ==0) ? ((sz/2)-1) : (sz/2);
    int start = 0;
    std::cout << " start = " << start << " front_end = " << front_end << std::endl;
    while (!a_list.empty()) {
        if (start > front_end) {
            break;
        }
        front.push_front(a_list.front());
        a_list.pop_front();
        start++;
    }

    while (!a_list.empty()) {
        back.push_front(a_list.front());
        a_list.pop_front();
    }

    front.reverse();
    back.reverse();

}

int main()
{
    std::forward_list<int> a_list { 1, 2, 3, 4, 9, 11, 13, 15 };
    std::cout << " a_list contents: ";
    print_fwd_list(a_list);

    std::forward_list<int> b_list { 1 };
    std::cout << " b_list contents: ";
    print_fwd_list(b_list);

    std::forward_list<int> c_list { 1, 2 };
    std::cout << " c_list contents: ";
    print_fwd_list(c_list);

    std::forward_list<int> d_list;
    std::cout << " d_list contents: ";
    print_fwd_list(d_list);

    std::forward_list<int> e_list { 1, 2, 3 };
    std::cout << " e_list contents: ";
    print_fwd_list(e_list);


    std::forward_list<int> front, back;

    front_back_split(a_list, front, back);
    std::cout << " split a_list" << std::endl;
    std::cout << " front contents: ";
    print_fwd_list(front);
    std::cout << " back contents: ";
    print_fwd_list(back);

    front.clear();
    back.clear();

    front_back_split(b_list, front, back);
    std::cout << " split b_list" << std::endl;
    std::cout << " front contents: ";
    print_fwd_list(front);
    std::cout << " back contents: ";
    print_fwd_list(back);

    front.clear();
    back.clear();

    front_back_split(c_list, front, back);
    std::cout << " split c_list" << std::endl;
    std::cout << " front contents: ";
    print_fwd_list(front);
    std::cout << " back contents: ";
    print_fwd_list(back);

    front.clear();
    back.clear();

    front_back_split(d_list, front, back);
    std::cout << " split d_list" << std::endl;
    std::cout << " front contents: ";
    print_fwd_list(front);
    std::cout << " back contents: ";
    print_fwd_list(back);

    front.clear();
    back.clear();

    front_back_split(e_list, front, back);
    std::cout << " split e_list" << std::endl;
    std::cout << " front contents: ";
    print_fwd_list(front);
    std::cout << " back contents: ";
    print_fwd_list(back);


    return 0;
}