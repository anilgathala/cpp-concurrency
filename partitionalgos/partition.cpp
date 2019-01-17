/// hoare's parition algo
/// link: https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/

#include <iostream>
#include <vector>


/// TODO: also look into median of medians
int get_pivot(std::vector<int> &A, int lo, int hi)
{
    return lo + std::rand() % (hi - lo + 1);
}

int hoare_partition(std::vector<int> &A, int lo, int hi)
{
    int num_swaps = 0;
    if (lo > hi) {
        return -1;
    }

    int pivot = A[lo];

    int i = lo - 1;
    int j = hi + 1;
    
    while (true) {
        do {
            i++;
        } while(A[i] < pivot);

        do {
            j--;
        } while(A[j] > pivot);

        if (i >= j) {
            std::cout << "[hoare] num_swaps = " << num_swaps << std::endl;
            return j;
        }

        std::swap(A[i], A[j]);
        num_swaps++;
    }

    return -1;
}

int lomuto_partition(std::vector<int> &A, int lo, int hi)
{
    int num_swaps = 0;
    if (lo > hi) {
        return -1;
    }
    
    int i = lo - 1;
    int pivot = A[hi];
    for (int j = i + 1; j <= hi - 1; j++) {
        if (A[j] <= pivot) {
            i++;
            std::swap(A[i], A[j]);
            num_swaps++;
        }
    }

    std::swap(A[i+1], A[hi]);
    num_swaps++;
    std::cout << "[lomuto] total_num of swaps: " << num_swaps << std::endl;
    return (i+1);
}

void dutch_flag(std::vector<int>&A)
{
    int i = 0;
    int j = 0;
    int k = A.size() - 1;

    int low = 0;
    int mid = 1;
    int hi = 2;
    // [ (<= low...) ...(..mid..)... (... >= hi) ]

    while (j <= k) {
        if (A[j] <= low) {
            std::swap(A[i], A[j]);
            i++;
            j++;
        } else if (A[j] >= hi) {
            std::swap(A[k], A[j]);
            k--;
        } else {
            j++;
        }
    }

}

void three_way_partition(std::vector<int>&A, int lo, int hi)
{
    int i = 0;
    int j = 0;
    int k = A.size() - 1;

    // [ (<= low...) ...(..mid..)... (... >= hi) ]

    while (j <= k) {
        if (A[j] < lo) {
            std::swap(A[i], A[j]);
            i++;
            j++;
        } else if (A[j] > hi) {
            std::swap(A[k], A[j]);
            k--;
        } else {
            j++;
        }
    }
}



void print_vec(std::vector<int>& A)
{
    for (auto x: A) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}

void test_three_way_partition()
{
    std::vector<int> A = {40, 15, 45, 20, 60, 50, 25, 72, 50, 30, 37, 35, 19, 50 };
    
    

    std::cout << " orig A: ";
    print_vec(A);
    int pivot = 42;
    three_way_partition(A, pivot, pivot);
    std::cout << " after threeway partition around " << pivot << " A: ";
    print_vec(A);
}

int quick_select(std::vector<int>& A, int rank)
{
    int lo = 0;
    int hi = A.size() - 1;
    std::cout << "orig A:";
    print_vec(A);
    while (lo <= hi) {
        if (rank > hi || rank < lo) {
            std::cout << "rank is out of bounds" << std::endl;
            return -1;
        }
        int p = lomuto_partition(A, lo, hi);
        std::cout << "after lumato at p = " << p << std::endl;
        print_vec(A);
        if (p == -1) {
            return p;
        }
        if (p == rank) {
            return A[p];
        }

        if (p < rank) {
            lo = p + 1;
        } else {
            hi = p - 1;
        }
    }
    return -1;
}

void partition_0s_and_1s_hoares(std::vector<int> & A)
{
    // lomuto method
    int i = 0;
    int j = A.size() - 1;

    while (true) {
        while (i < A.size() && A[i] == 0) { i++; }
        while (j >= 0 && j < A.size() && A[j] == 1) { j--; }
        if (i >= j) {
            return;
        }
        std::swap(A[i], A[j]);
    }
}

void partition_0s_and_1s_lomuto(std::vector<int> & A)
{
    // lomuto method
    int i = 0;
    int j = 0;

    while (j < A.size()) {
        if (A[j] == 0) {
            std::swap(A[i], A[j]);
            i++;
            j++;
        } else {
            j++;
        }
    }
}


void test_partition_0s_and_1s_hoares()
{
    std::vector<int> A = { 0, 1, 0, 1, 1, 1, 0, 0, 1, 0};
    std::cout << " orig A: ";
    print_vec(A);
    partition_0s_and_1s_hoares(A);
    std::cout << " after partition_0s_and1s_hoares A: ";
    print_vec(A);
}

void test_partition_0s_and_1s_lomuto()
{
    std::vector<int> A = { 0, 1, 0, 1, 1, 1, 0, 0, 1, 0};
    std::cout << " orig A: ";
    print_vec(A);
    partition_0s_and_1s_lomuto(A);
    std::cout << " after partition_0s_and1s_lomuto A: ";
    print_vec(A);
}

void test_quickselect()
{
    std::vector<int> A = {30, 10, 40, 50, 20, 15, 75 };
    int rank = 7;//A.size() - 1;
    int element = quick_select(A, rank);
    std::cout << " element with rank " << rank << " is " << element << std::endl;
}

void test_dutch_flag()
{
    std::vector<int> A = {0, 0}; //{0,1, 2, 2, 1, 0, 1, 2, 2, 1, 1, 1, 2, 2 };
    std::cout << " orig A: ";
    print_vec(A);
    dutch_flag(A);
    std::cout << " after dutchflag A: ";
    print_vec(A);

}

void test_lomuto()
{

    std::vector<int> A = {1, 1, 1, 1, 1, 1, 1 }; //{ 16 , 10, 6, 12, 2, 15, 8 };
    std::cout << "Original A: ";
    for (auto x: A) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    int p = lomuto_partition(A, 0, A.size() - 1);
    std::cout << "After lumuto's partitioning A, at index: " << p << " : ";
    for (auto x: A) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;

}

void test_hoares()
{
    std::vector<int> B = {1, 1, 1, 1, 1, 1, 1 }; // { 8 , 16, 10, 6, 12, 2, 15 }; // keeping the same pivot 8
    std::cout << "Original B: ";
    for (auto x: B) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    int p = hoare_partition(B, 0, B.size() - 1);
    std::cout << "After hoare's partitioning B, at index: " << p << " : ";
    for (auto x: B) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
}


int main()
{
    test_three_way_partition();
    // test_partition_0s_and_1s_hoares();
    // test_partition_0s_and_1s_lomuto();
    // test_quickselect();
    // test_dutch_flag();
    // test_lomuto();
    // test_hoares();
    
    return 0;
}