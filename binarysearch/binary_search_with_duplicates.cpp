///
/// Different varaitions
///

#include <iostream>
#include <vector>

// same code without dup
int binsearch_dup(std::vector<int> A, int key) {
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


void test_binary_search_dup()
{
    std::vector<int> A = { 20, 22, 22, 26, 30, 34, 38, 40, 40 };
    std::sort(A.begin(), A.end());
    int key = 22;
    int idx = binsearch_dup(A, key);
    if (idx < 0) {
        std::cout << " key: " << key << " not found!" << std::endl;
    } else {
        std::cout << " key: " << key << " found at idx = " << idx << std::endl;
    }
}


int bin_floor_dup(std::vector<int> A, int key, int& index) {
    int idx = -1;
    int idx2 = -1;
    int lo = 0;
    int hi = A.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == key) { 
            idx = mid;
            hi = mid - 1;
        }
        else if (key < A[mid]) {
            hi = mid - 1;
        } else {

           idx2 = mid;
            //std::cout << "idx = " << idx << std::endl;
            lo = mid + 1;
        }
    }

    index = (idx != -1) ? idx : idx2;
    if (index == idx2) {
        std::cout << "idx2 used!" << std::endl;
    }
    return (index == -1) ? -1 : A[index];
}

// assumption: key is guaranteed to be present
int bin_first(std::vector<int> A, int key, int& index) {
    int idx = -1;

    int lo = 0;
    int hi = A.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == key) { 
            idx = mid;
            hi = mid - 1;
        }
        else if (key < A[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    index = idx;
    return (idx == -1) ? -1 : A[idx];
}


int bin_ceil_dup(std::vector<int> A, int key, int &index) {
    int idx = -1;
    int idx2 = -1;
    int lo = 0;
    int hi = A.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == key) {
            idx = mid;
            lo =  mid + 1;
            // return A[mid]; 
        }
        else if (key < A[mid]) {
            idx2 = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }


    index = (idx != -1) ? idx : idx2;
    if (index == idx2) {
        std::cout << "idx2 used!" << std::endl;
    }
    return (index == -1) ? -1 : A[index];
}

// key is guaranteed to be present
int bin_last(std::vector<int> A, int key, int &index) {
    int idx = -1;
    int lo = 0;
    int hi = A.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (A[mid] == key) {
            idx = mid;
            lo =  mid + 1;
            // return A[mid]; 
        }
        else if (key < A[mid]) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }


    index = idx;
    return (index == -1) ? -1 : A[index];
}


void test_first()
{
    // std::vector<int> A = { 20, 22, 26, 30, 34, 38, 38, 38, 38, 40 };
    std::vector<int> A = { 19, 19, 19, 19, 19, 19, 19 };
    int key = 19;
    int index = -1;
    int res = bin_first(A, key, index);
    if (res < 0) {
        std::cout << " first(key): " << key << " not found!" << std::endl;
    } else {
        std::cout << " first(key): " << key << " is  " << res
                << " found at index = " << index << std::endl;
    }
}

void test_last()
{
    // std::vector<int> A = { 20, 22, 26, 30, 34, 38, 38, 38, 38, 40 };
    std::vector<int> A = { 19, 19, 19, 19, 19, 19, 19 };
    int key = 19;
    int index = -1;
    int res = bin_last(A, key, index);
    if (res < 0) {
        std::cout << " first(key): " << key << " not found!" << std::endl;
    } else {
        std::cout << " first(key): " << key << " is  " << res
                << " found at index = " << index << std::endl;
    }
}


void test_ceil_dup()
{
    std::vector<int> A = { 20, 22, 26, 30, 34, 38, 38, 38, 38, 40 };
    int key = 19;
    int index = -1;
    int res = bin_ceil_dup(A, key, index);
    if (res < 0) {
        std::cout << " ceil(key): " << key << " not found!" << std::endl;
    } else {
        std::cout << " ceil(key): " << key << " is  " << res
                << " found at index = " << index << std::endl;
    }
}

void test_floor_dup()
{
   //  std::vector<int> A = { 20, 21, 22, 23, 24, 25, 26, 30, 34, 34, 34, 38, 40 };
    std::vector<int> A = { 12, 12, 12, 12, 12 };
    int key = 10; //34; // 27; // 21
    // also try removing all occurences of 21 and 34 from ip array, the code still works
    int index = -1;
    int res = bin_floor_dup(A, key, index);
    if (res < 0) {
        std::cout << " floor(key): " << key << " not found!" << std::endl;
    } else {
        std::cout << " floor(key): " << key << " is  " << res
                << " found at index " << index << std::endl;
    }
}


int main()
{ 
    // test_last();
    // test_first();
    // test_ceil_dup();
    test_floor_dup();
    //test_binary_search_dup();
    return 0;
}