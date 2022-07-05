#include <vector>
#include <iostream>
#include <algorithm>
#include<functional>
#include "..\headers\dnd_template_functions.h"
using namespace std;
int main(){
    vector<int> test1 = {0,0,-1};
    vector<int> test2 = {1,2,4};
    vector<int> test3 = test1 + test2;
    //std::transform(test1.begin(), test1.end(), test2.begin(), std::back_inserter(test3), std::plus<int>());
;
    for(int x : test3){
        cout << x << " ";
    }
    cout << endl;
    system("pause");
}