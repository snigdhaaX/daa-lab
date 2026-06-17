#include<iostream>
using namespace std;
int main(){
    int n;
    cout<<"Enter the number of elements in the array: ";
    cin>>n;
    int arr[n];
    cout<<"Enter the elements of the array: ";
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    int key;
    cout<<"Enter the element to be searched: ";
    cin>>key;
    bool found = false;
    for(int i=0; i<n; i++){
        if(arr[i] == key){
            found = true;
            cout<<"Element found at index: "<<i<<endl;
            break;
        }
    }
    if(!found){
        cout<<"Element not found in the array."<<endl;
    }

}