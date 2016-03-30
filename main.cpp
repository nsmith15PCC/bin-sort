#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

enum DIRECTION {ASCENDING, DESCENDING};

template<typename T>
struct printtypes
{
typedef void (*print_ptr)(const vector<T>&, char*);
};

template<typename T>
size_t maxOfList(const vector<T>& list);


template<typename T>
void initialize(vector<T> &list);


template<typename T>
void binSort(vector<T> &list);

template<typename T>
void printAscending(const vector<T>&list, char* title);

template<typename T>
void printDescending(const vector<T>&list, char* title);


int main()
{
   vector<size_t> list;
   string line;
   srand(time(NULL));
   printtypes<size_t>::print_ptr prints[2] = {printAscending, printDescending};
   initialize(list);
   cout<<"Generated numbers and starting to sort"<<endl;
   printAscending(list,"unsorted");
   binSort(list);
   cout<<"Sort finished"<<endl;
   cin.ignore(INT_MAX, '\n');
   cout<<"Display in [a]scending or [d]escending order? ";
   getline(cin, line);
   prints[tolower(line[0]) == 'd'](list, "sorted");
}


template<typename T>
void binSort(vector<T> &list)
{
    vector<T> bins[10];
    size_t digit = 1;
    while(list.size() != bins[0].size())
    {
        //Clear the bins!
        for(size_t
            i = 0; i < 10; ++i)
            bins[i].clear();
        for(size_t i = 0; i < list.size();++i)
        {
            size_t num = list[i]/digit, theBin = num - num/10*10;
            bins[theBin].push_back(list[i]);
        }
        list.clear();
        for(size_t i = 0; i < 10; ++i)
            list.insert(list.end(),bins[i].begin(),bins[i].end());
        digit*=10;
    }
}

template<typename T>
void initialize(vector<T> &list)
{
    size_t largest, qty;
    cout<<"How many random numbers do you want? ";
    cin>>qty;
    cout<<"What is the largest random number to see? ";
    cin>>largest;
    for(size_t i = 0; i < qty; ++i)
       list.push_back(rand()%largest + 1);
}


template<typename T>
size_t maxOfList(const vector<T>& list)
{
    size_t maximum = list[0];
    for(size_t i = 1; i < list.size(); ++i)
        maximum = max(maximum, list[i]);
    return maximum;
}

template<typename T>
void printAscending(const vector<T>&list, char* title)
{
    size_t digits = 2 + log10(maxOfList(list))+1,
           col = 65/digits;
    cout<<"Your "<<title<<" list is: "<<endl;
    for(size_t i = 0; i < list.size(); ++i)
    {
        if(!(i%col))
            cout<<endl;
        cout<<setw(digits)<<list[i];
    }
    cout<<endl<<endl;
}

template<typename T>
void printDescending(const vector<T>&list, char* title)
{
    size_t digits = 2 + log10(maxOfList(list))+1,
           col = 65/digits;
    cout<<"Your "<<title<<" list is: "<<endl;
    for(int i = list.size()-1; i >= 0; --i)
    {
        if(!((list.size()-i-1)%col))
            cout<<endl;
        cout<<setw(digits)<<list[i];
    }
    cout<<endl<<endl;
}
