#include <iostream>

using namespace std;

void print_tree(int *xs, int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("node %d: ", (i+1));
        printf("key = %d, ", xs[i]);
        if(i)
        {
            int p = (i-1)/2;
            printf("parent key = %d, ", xs[p]);
        }
        int left = i*2 + 1;
        int right = i*2 + 2;
        if(left < n)
        {
            printf("left key = %d, ", xs[left]);
        }
        if(right < n)
        {
            printf("right key = %d, ", xs[right]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    cin >> n;
    int xs[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> xs[i];
    }
    print_tree(xs, n);
}
