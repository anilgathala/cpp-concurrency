///
/// Different varaitions, with no duplicates
///

#include <iostream>
#include <vector>

int binsearch(std::vector<int> A, int key) {
    int lo = 0;
    int hi = A.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == key) { return mid; }
        if (key < A[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return -1;
}

int bin_floor(std::vector<int> A, int key) {
    int idx = -1;
    int lo = 0;
    int hi = A.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == key) { return A[mid]; }
        if (key < A[mid]) {
            hi = mid - 1;
        } else {

            idx = mid;
            //std::cout << "idx = " << idx << std::endl;
            lo = mid + 1;
        }
    }

    return (idx == -1) ? -1 : A[idx];
}

int bin_ceil(std::vector<int> A, int key) {
    int idx = -1;
    int lo = 0;
    int hi = A.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == key) { return A[mid]; }
        if (key < A[mid]) {
            idx = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    return (idx == -1) ? -1 : A[idx];
}


void test_ceil()
{
    std::vector<int> A = { 20, 22, 26, 30, 34, 38, 40 };
    int key = 21;
    int res = bin_ceil(A, key);
    if (res < 0) {
        std::cout << " ceil(key): " << key << " not found!" << std::endl;
    } else {
        std::cout << " ceil(key): " << key << " is  " << res << std::endl;
    }
}

void test_floor()
{
    std::vector<int> A = { 20, 22, 26, 30, 34, 38, 40 };
    int key = 19;
    int res = bin_floor(A, key);
    if (res < 0) {
        std::cout << " floor(key): " << key << " not found!" << std::endl;
    } else {
        std::cout << " floor(key): " << key << " is  " << res << std::endl;
    }
}


void test_binary_search()
{
    std::vector<int> A = { 20, 22, 26, 30, 34, 38, 40 };
    int key = 38;
    int idx = binsearch(A, key);
    if (idx < 0) {
        std::cout << " key: " << key << " not found!" << std::endl;
    } else {
        std::cout << " key: " << key << " found at idx = " << idx << std::endl;
    }
}

int main()
{
    test_ceil();
    // test_floor();
   // test_binary_search();    
    return 0;
}