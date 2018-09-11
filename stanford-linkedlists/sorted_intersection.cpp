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

template <typename T>
size_t  size(std::forward_list<T> &a_list)
{
    int cnt = 0;
    for (auto itr = a_list.begin(); itr !=  a_list.end(); itr++) {
        cnt++;
    }
    return cnt;

}



void find_intersection(
    std::forward_list< std::unique_ptr<Payload> > & a_list,
    std::forward_list< std::unique_ptr<Payload> > & b_list,
    std::forward_list< std::unique_ptr<Payload> > & c_list
    )
{
    auto a_itr = a_list.begin();
    auto b_itr = b_list.begin();

    while (a_itr != a_list.end() && b_itr!= b_list.end()) {
        if ((*a_itr)->val == (*b_itr)->val) {
            c_list.push_front((std::unique_ptr<Payload>)new Payload((*a_itr)->val));
            a_itr++;
            b_itr++;
        } else if ((*a_itr)->val < (*b_itr)->val) {
            a_itr++;
        } else {
            b_itr++;
        }
    }

    // change it to increasing order
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
    std::forward_list<std::unique_ptr<Payload> > a_list, b_list, c_list;

    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((2))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((4))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((6))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((8))));
    a_list.reverse();

    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((3))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((4))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((5))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((6))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((7))));
    b_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((9))));
    b_list.reverse();

    // intersection should be { 4, 6 }

    std::cout << " a_list contents: ";
    print_fwd_list_unique_ptr(a_list);

    std::cout << " b_list contents: ";
    print_fwd_list_unique_ptr(b_list);

    find_intersection(a_list, b_list, c_list);

    std::cout << " c_list (intersection) contents: ";
    print_fwd_list_unique_ptr(c_list);

 
    return 0;
}