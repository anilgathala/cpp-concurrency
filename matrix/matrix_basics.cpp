#include <iostream>
#include <vector>

void different_ways_to_init()
{
    // initialization style #1
    int n = 4;
    int m = 10;
    std::vector<std::vector<int> > A;
    A.resize(n);
    for (int i = 0; i < n; i++) {
        A[i].resize(m, 0);
    }

    // initialization style #2
    std::vector<std::vector<int> > B ( n, std::vector<int>(m, 0));

    // initialization style #2
    std::vector<std::vector<int> > C ( n, std::vector<int>(m));

    std::vector<std::vector<int> > D {
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    };

     std::vector<std::vector<int> > E = {
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 },
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
    };

}

void print_matrix(std::vector<std::vector<int> > & A)
{
    if (A.empty()) {
        return;
    }

    int n = A.size();
    int m = A[0].size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; i++)
        {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;

    }
}

void diagonal_sum()
{
    std::vector<std::vector<int> > A   = {
        { 5, 4, 3, 2 },
        { 2, 3, 4, 5 },
        { 5, 4, 3, 2 },
        { 2, 3, 4, 5 }
    };
    
    // print diagonals
    int i = 0, j = 0;
    int r = 0, c = 0;
    int m = 4, n = 4;
    
    std::vector<int> diagonals(2*n, 0);
    
    j = 0;
    for ( i = 0; i < n; i++) {
        r = i; c = j;
        int sum = 0;
        while (r >= 0 && r < n && c >= 0 && c < m) {
            sum += A[r][c];
            r++;
            c++;
        }
        diagonals[n + i - j] = sum;
    }
    
    i = 0;
    for ( j = 1; j < n; j++) {
        r = i; c = j;
        int sum = 0;
        while (r >= 0 && r < n && c >= 0 && c < m) {
            sum += A[r][c];
            r++;
            c++;
        }
        diagonals[n + i - j] = sum;
    }
    
    std::vector<int> anti_diagonals(2*n, 0);
    // print antidiagonals
    j = n - 1;
    for ( i = 0; i < n; i++) {
        r = i; c = j;
        int sum = 0;
        while (r >= 0 && r < n && c >= 0 && c < m) {
            sum += A[r][c];
            r++;
            c--;
        }
        anti_diagonals[2*n - (i + j + 1)] = sum;
    }
    
    
    i = 0 ;
    for ( j = n - 2; j >= 0; j--) {
        r = i; c = j;
        int sum = 0;
        while (r >= 0 && r < n && c >= 0 && c < m) {
            sum += A[r][c];
            r++;
            c--;
        }
        anti_diagonals[2*n - (i + j + 1)] = sum;
    }

    std::cout << " diagonals: " << std::endl;
    for (auto d: diagonals) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
    
    std::cout << " anti-diagonals: " << std::endl;
    for (auto d: anti_diagonals) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
    
    
    
}

int main()
{
    diagonal_sum();
    return 0;
}

