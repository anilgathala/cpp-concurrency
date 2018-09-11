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
            //std::cout << " movign a node from a_list to c_list " << std::endl;
            move_node(a_list, c_list);
        } else {
            //std::cout << " movign a node from b_list to c_list " << std::endl;
            move_node(b_list, c_list);
        }
    }

    while (!a_list.empty()) {
        move_node(a_list, c_list);
    }

    while (!b_list.empty()) {
        move_node(b_list, c_list);
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



void front_back_split(
    std::forward_list<std::unique_ptr<Payload> > & a_list,
    std::forward_list<std::unique_ptr<Payload> > & front,
    std::forward_list<std::unique_ptr<Payload> > & back
    )
{
    if (a_list.empty()) {
        return;
    }
    size_t sz = size(a_list);

    if (sz == 1) {
        front.push_front(std::move(a_list.front()));
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
    //std::cout << " start = " << start << " front_end = " << front_end << std::endl;
    while (!a_list.empty()) {
        if (start > front_end) {
            break;
        }
        front.push_front(std::move(a_list.front()));
        a_list.pop_front();
        start++;
    }

    while (!a_list.empty()) {
        back.push_front(std::move(a_list.front()));
        a_list.pop_front();
    }

    front.reverse();
    back.reverse();
}

void do_merge_sort(
    std::forward_list<std::unique_ptr<Payload> >& a_list,
    std::forward_list<std::unique_ptr<Payload> >& result
    )
{
    if (a_list.empty()) {
        return;
    }
    if (size(a_list)==1) {
        result.push_front(std::move(a_list.front()));
        a_list.pop_front();
        return;
    }

    // divide into two halves
    std::forward_list<std::unique_ptr<Payload> > front, back, front_result, back_result;
    front_back_split(a_list, front, back);

    do_merge_sort(front, front_result);
    do_merge_sort(back, back_result);

    sorted_merge(front_result, back_result, result);
    return;

}

int main()
{
    // sorted list 
    // wish, std::make_unique() worked in this compiler
    //auto alist_ptr = (std::unique_ptr<std::forward_list<Payload>>) new std::forward_list<Payload>();
    std::forward_list<std::unique_ptr<Payload>> a_list;

    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((5))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((8))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((2))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((3))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((7))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((6))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((4))));
    a_list.push_front(std::move((std::unique_ptr<Payload>) new Payload((9))));

    std::cout << " a_list (unsorted input) contents: ";
    print_fwd_list_unique_ptr(a_list);

    std::forward_list<std::unique_ptr<Payload> > sorted_a_list;
    do_merge_sort(a_list, sorted_a_list);

    std::cout << " sorted_a_list (unsorted input) contents: ";
    print_fwd_list_unique_ptr(sorted_a_list);
 
    return 0;
}