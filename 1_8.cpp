#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

void ISSQuicksort(vector<int>& A, int p, int r, int M);
void InsertionSort(vector<int>& A, int p, int r);
int Medium3_Partition(vector<int>& A, int p, int r);
int Partition(vector<int>& A, int p, int r);
void sort3(int& A, int& B, int& C);
void swap(int& A, int& B);

int main()
{
    srand(time(NULL));
    fstream fs;
    fs.open(".\\result.csv", ios::out);
    fs << "M,aveRuntime" << endl;

    //generate data
    vector<int> Array;
    for(int i=0; i<100000; i++)
    {
        Array.push_back( rand()%2147483647 );
    }

    //find best M
    for(int M=1; M<=100; M++)
    {
        double aveRuntime = 0;
        const int TESTTIME = 10;
        for(int t=0; t<TESTTIME; t++)
        {
            double t_start = clock();

            ISSQuicksort(Array, 0, Array.size()-1, M);

            double t_end = clock();
            aveRuntime += t_end - t_start;
        }
        aveRuntime /= TESTTIME;
        cout << "M: " << M << ", average runtime: " << aveRuntime << "(ms)" << endl;
        fs << M << "," << aveRuntime << endl;
    }

    fs.close();
    system("pause");
}

void ISSQuicksort(vector<int>& A, int p, int r, int M)
{
    if(r-p+1 >= M)
    {
        int q = Medium3_Partition(A, p, r);
        ISSQuicksort(A, p, q-1, M);
        ISSQuicksort(A, q+1, r, M);
    }
    else if(p < r)
    {
        InsertionSort(A, p, r);
    }
}
void InsertionSort(vector<int>& A, int p, int r)
{
    for(int i=p; i<=(r-1); i++)
    {
        int min = i;
        for(int j=i+1; j<=r; j++)
        {
            if(A[j] < A[min])
            {
                min = j;
            }
        }
        swap(A[i], A[min]);
    }
}
int Medium3_Partition(vector<int>& A, int p, int r)
{
    if(r-p+1 >= 3)
    {
        int q=(p+r)/2;
        sort3(A[p], A[q], A[r]);
        swap(A[q], A[r]);
    }
    return Partition(A, p, r);
}
int Partition(vector<int>& A, int p, int r)
{
    int pivot = A[r];
    int i= p-1;
    for(int j=p; j<=r-1; j++)
    {
        if(A[j] <= pivot)
        {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i+1;
}
void sort3(int& A, int& B, int& C)
{
    if(A > B)
    {
        swap(A, B);
    }
    if(B > C)
    {
        swap(B, C);
    }
    if(A > B)
    {
        swap(A, B);
    }
}
void swap(int& A, int& B)
{
    int x = A;
    A = B;
    B = x;
}