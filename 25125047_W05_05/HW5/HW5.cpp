#include <iostream> 
using namespace std;



    
    int mySqrt(int x) {
        
        if (x == 0) {
            return 0;
        }

       
        long long left = 1;
        long long right = x;
        int ans = 0; 

        while (left <= right) {
           
            long long mid = (left + right) / 2;

          
            long long square = mid * mid;

            if (square == x) {
                
                return (int)mid;
            }
            else if (square < x) {
              
                ans = (int)mid;
                left = mid + 1;
            }
            else { 
                right = mid - 1;
            }
        }
        return ans;
    }



int main() {
    int n = 1; 
    while (n != 0) {
        cout << "input an interger: "; cin >> n;
        cout << mySqrt(n) << endl;
    }
    return 0;
}