#include <iostream>
#include <stdexcept>

using namespace std;
enum class Pict
{
    heart = 'h', diamond = 'd', club = 'c', spade = 's'
};
struct Card
{
    Pict p;
    int value;

    Card() : p {Pict::heart}, value {} {}
    Card(char ch, int v) : p {static_cast<Pict>(ch)} , value {v} {};
    Card(string str)
    {
        if(str.size() != 2)
        {
            throw invalid_argument("String length must be 2.");
        }
        p = static_cast<Pict>(str.at(0));
        value = str.at(1)-'0';
    };
};
ostream& operator<<(ostream& out, const Card& card)
{
    return out << static_cast<char>(card.p) << card.value;
};
const bool operator>(const Card& x, const Card& y)
{
    return x.value > y.value;
}

const bool operator<(const Card& x, const Card& y)
{
    return x.value < y.value;
}

const bool operator==(const Card& x, const Card& y)
{
    return x.p == y.p && x.value == y.value;
}

const bool operator!=(const Card& x, const Card& y)
{
    return !(x == y);
}

template<class T>
int selection_sort(T xs[], int n)
{
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        int mini = i;
        for(int j = i; j < n; ++j)
        {
            if(xs[j] < xs[mini])
            {
                mini = j;
            }
        }
        if(mini != i)
        {
            ++cnt;
            swap(xs[mini], xs[i]);
        }
    }
    return cnt;
}

template <class T>
int bubble_sort(T xs[], int n)
{
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = n-1; j > i; --j)
        {
            if(xs[j] < xs[j-1])
            {
                ++cnt;
                swap(xs[j], xs[j-1]);
            }
        }
    }
    return cnt;
}

template <class T>
void print_array(T xs[], int n)
{
    for(int i = 0; i < n-1; ++i)
    {
        cout << xs[i] << ' ';
    }
    cout << xs[n-1] << '\n';
}

template<class T>
bool eq_array(T xs[], T ys[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        if(xs[i] != ys[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n;
    cin >> n;
    Card xs[n];
    Card ys[n];
    string temp;
    for(int i = 0; i < n; ++i)
    {
        cin >> temp;
        xs[i] = Card(temp);
        ys[i] = xs[i];
    }
    bubble_sort(xs, n);
    print_array(xs, n);
    cout << "Stable\n";
    selection_sort(ys, n);
    print_array(ys, n);
    if(!eq_array(xs, ys, n))
    {
        cout << "Not stable\n";
    }
    else
    {
        cout << "Stable\n";
    }
}
