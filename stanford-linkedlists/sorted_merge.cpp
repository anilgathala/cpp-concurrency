#include <forward_list>
#include <iostream>
#include <memory>

class Payload {
    public:
    int val;
    
    Payload(int v): val(v) {};
    
    ~Payload() {};
    friend std::ostream& operator<<(std::ostream& os, const Payload& p); 
};

std::ostream& operator<<(std::ostream& os, const Payload& p)
{
    os << p.val;
    return os;
}


size_t  size(std::forward_list<int> &a_list)
{
    int cnt = 0;
    for (auto itr = a_list.begin(); itr !=  a_list.end(); itr++) {
        cnt++;
    }
    return cnt;

}

// move one front element from a_list to the front of b_list
void move_node(
    std::forward_list<std::unique_ptr<Payload>> & a_list,
    std::forward_list<std::unique_ptr<Payload>> & b_list
    )
{
    if (a_list.empty()) {
        return;
    }
    b_list.push_front(std::move(a_list.front()));
    a_list.pop_front();
}

void sorted_merge(
    std::forward_list< std::unique_ptr<Payload> > & a_list,
    std::forward_list< std::unique_ptr<Payload> > & b_list,
    std::forward_list< std::unique_ptr<Payload> > & c_list
    )
{
    while (!a_list.empty() && !b_list.empty()) {
        if (a_list.front()->val < b_list.front()->val) {
            std::cout << " movign a node from a_list to c_list " << std::endl;
            move_node(a_list, c_list);
        } else {
            std::cout << " movign a node from b_list to c_list " << std::endl;
            move_node(b_list, c_list);
        }
    }

    while (!a_list.empty()) {
        move_node(a_list, c_list);
    }

    while (!b_list.empty()) {
        move_node(b_list, c_list);
    }

    if (!c_list.empty()) {
        c_list.reverse();
    }
}

void print_fwd_list_unique_ptr(std::forward_list<std::unique_ptr<Payload>> & a_list)
{

    for (auto itr = a_list.begin(); itr !=  a_list.end(); itr++) {
        // *itr --> unique_ptr<Payload>
        // (*itr).get() --> gives a pointer to the object within (Payload*)
        // *( (*itr).get() ) --> access the object (Payload)
        std::cout << *((*itr).get());
        std::cout << " -->";
    }
    std::cout << "END" << std::endl;
}


int main()
{
    // sorted list 
    // wish, std::make_unique() worked in this compiler
    //auto alist_ptr = (std::unique_ptr<std::forward_list<Payload>>) new std::forward_list<Payload>();
    std::forward_list<std::unique_ptr<Payload>> a_list;

    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((9))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((7))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((5))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((3))));

    std::forward_list<std::unique_ptr<Payload>> b_list;

    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((8))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((6))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((4))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((2))));

    std::forward_list<std::unique_ptr<Payload>> c_list;

    std::cout << " a_list contents: ";
    print_fwd_list_unique_ptr(a_list);

    std::cout << " b_list contents: ";
    print_fwd_list_unique_ptr(b_list);

    std::cout << " c_list contents: ";
    print_fwd_list_unique_ptr(c_list);

    // move one front element from a_list
    // to the front of b_list
    sorted_merge(a_list, b_list, c_list);

    std::cout << " a_list (after move) contents: ";
    print_fwd_list_unique_ptr(a_list);

    std::cout << " b_list (after move) contents: ";
    print_fwd_list_unique_ptr(b_list);

    std::cout << " c_list (after move) contents: ";
    print_fwd_list_unique_ptr(c_list);

    a_list.clear();
    b_list.clear();
    c_list.clear();

    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((8))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((6))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((4))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((2))));

    std::cout << "test #2: " << std::endl;

        std::cout << " a_list contents: ";
    print_fwd_list_unique_ptr(a_list);

    std::cout << " b_list contents: ";
    print_fwd_list_unique_ptr(b_list);

    std::cout << " c_list contents: ";
    print_fwd_list_unique_ptr(c_list);

    sorted_merge(a_list, b_list, c_list);

    std::cout << " a_list (after move) contents: ";
    print_fwd_list_unique_ptr(a_list);

    std::cout << " b_list (after move) contents: ";
    print_fwd_list_unique_ptr(b_list);

    std::cout << " c_list (after move) contents: ";
    print_fwd_list_unique_ptr(c_list);



    return 0;
}