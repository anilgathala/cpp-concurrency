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
void alt_split(
    std::forward_list< std::unique_ptr<Payload> > & a_list,
    std::forward_list< std::unique_ptr<Payload> > & b_list,
    std::forward_list< std::unique_ptr<Payload> > & c_list
    )
{
    if (a_list.empty()) {
        return;
    }

    bool b = true;
    while(!a_list.empty()) {
        if (b) {
            b_list.push_front(std::move(a_list.front()));
            b = false;
        } else {
            c_list.push_front(std::move(a_list.front()));
            b = true;
        }
        a_list.pop_front();
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
    std::forward_list< std::unique_ptr<Payload> > a_list;
    for (int i = 0; i < 10; i++) {
        auto ptr = (std::unique_ptr<Payload>) new Payload((i+1)*1000);
        a_list.push_front(std::move(ptr));
    }

    std::forward_list< std::unique_ptr<Payload> > b_list;
    std::forward_list< std::unique_ptr<Payload> > c_list;

    std::cout << " a_list (before split) contents: ";
    print_fwd_list_unique_ptr(a_list);
    
    alt_split(a_list, b_list, c_list);

    std::cout << " a_list (after split) contents: ";
    print_fwd_list_unique_ptr(a_list);

    std::cout << " b_list (after split) contents: ";
    print_fwd_list_unique_ptr(b_list);

    std::cout << " c_list (after split) contents: ";
    print_fwd_list_unique_ptr(c_list);

    return 0;
}