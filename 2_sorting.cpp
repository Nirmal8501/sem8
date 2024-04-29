#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
using namespace chrono;

void bSort(vector<int> &arr){
    int n = arr.size();

    for(int i =0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void pbSort(vector<int> &arr){
    int n = arr.size();
    #pragma omp parallel for
    for(int i =0; i<n-1; i++){
        for(int j=0; j<n-i-1; j++){
            if(arr[j]>arr[j+1]){
                // #pragma omp critical
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void merge(vector<int> &arr, int lo, int mid, int hi){
    vector<int> temp;
    int left = lo;
    int right = mid+1;

    while(left<=mid && right<=hi){
        if(arr[left]<=arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
             temp.push_back(arr[right]);
             right++;
        }
    }

    while(left<=mid){
        temp.push_back(arr[left]);
        left++;
    }

    while(right<=hi){
        temp.push_back(arr[right]);
        right++;
    }

    for(int i=lo; i<=hi; i++){
        arr[i] = temp[i-lo];
    }
}



void mergeSort(vector<int> &arr, int lo, int hi){
    if(lo<hi){
        int mid=(lo+hi)/2;
        mergeSort(arr, lo, mid);
        mergeSort(arr, mid+1, hi);
        merge(arr, lo, mid, hi);
    }
}

// void pmergeSort(vector<int> &arr, int lo, int hi){
//     if(lo<hi){

//         int mid=(lo+hi)/2;

//         #pragma omp parallel sections{
//             #pragma omp section
//             mergeSort(arr, lo, mid);
//             #pragma omp section
//             mergeSort(arr, mid+1, hi);
//         }
        
//         merge(arr, lo, mid, hi);
//     }
// }

void print(vector<int> arr){
    cout<<endl;
    for(int i=0; i<arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


int main(){

    vector<int> val;
    for(int i=25; i>=0; i--){
        val.push_back(i);
    }

    vector<int> arr1 = val;
    vector<int> arr2 = val;
    vector<int> arr3 = val;
    vector<int> arr4 = val;
    
    auto start = high_resolution_clock::now();
    bSort(arr1);
    auto end = high_resolution_clock::now();
    auto tim = duration_cast<milliseconds>(end-start);
    print(arr1);

    start = high_resolution_clock::now();
    pbSort(arr2);
    end = high_resolution_clock::now();
    tim = duration_cast<milliseconds>(end-start);
    // print(arr2);
    print(arr2);

    start = high_resolution_clock::now();
    mergeSort(arr3, 0, 25);
    end = high_resolution_clock::now();
    tim = duration_cast<milliseconds>(end-start);
    // print(arr2);
    print(arr3);

    
    

    return 0;

}