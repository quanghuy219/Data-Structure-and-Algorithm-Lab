/*
Watson gives Sherlock an array A1,A2...AN. 
He asks him to find an integer M between P and Q(both inclusive), such that, min {|Ai-M|, 1 ≤ i ≤ N} is maximised. 
If there are multiple solutions, print the smallest one.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int min(int c[], int k, int n, int pos){
    int min;
    if (pos == 0) min = c[1] - k;
    
    else if (pos == n) min = k - c[n-1];
    
    else {
        min = fabs(c[pos] - c[pos-1]);
        if( fabs(c[pos+1]-c[pos]) < min ) min = fabs(c[pos+1]-c[pos]);
    }        
    return min;
}


int binarySearch(int k, int a[], int l, int r){
    
    if(l > r) return -1;
    int mid = (l+r)/2;
    if(a[mid] == k ) return mid;
    else if ( k < a[mid] ) return binarySearch(k,a,l,mid-1);
    else return binarySearch(k,a,mid+1,r);    
}


int sort(int a[], int c[], int n, int k){
    int i,j,tmp;
    for (i = 0; i < n; i++)
    {
        c[i] = a[i];
    }

    for(i=0; i<n;i++){
        for(j=i+1;j<n;j++){
            if(c[i] > c[j]){
               tmp = c[i];
                c[i] = c[j];
                c[j] = tmp;
            }
        }
    }
    return binarySearch(k,c,0,n);    
}



int main() {

    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1],c[n+1];
    int k,i,j,tmp;
    for(i=0;i<n;i++) scanf("%d",&a[i]);

    
    int p,q;
    scanf("%d",&p);
    scanf("%d",&q);
    int minimax = 0;
    int pos;
    int result;
        //sort a[]
        for (int i = 0; i < n; i++)
        {
            for (int j = i+1; j < n; j++)
            {
                if (a[i] > a[j])
                {
                    tmp = a[i];
                    a[i] = a[j];
                    a[j] = tmp;
                }
            }
        }


        a[n] = p;
        pos = sort(a,b,n+1,p);       
        minimax = min(b,p,n,pos);
        result = p;

        b[0] = p;
        b[n] = q;

        for (int i = 1; i < n; ++i)
        {
            b[i] = (a[i-1] + a[i]) / 2; //array b[] represent inteval p-q
        }

        for (int i = 0; i <= n; ++i) //c[]: sorted array with value b[i]
        {
            a[n] = b[i];
            pos = sort(a,c,n+1,b[i]);
            tmp = min(c,b[i],n,pos);

            if (tmp > minimax && (b[i] >= p && b[i] <= q) )
            {
                minimax = tmp;
                result = b[i];
            }
        }
    printf("%d\n",result);
    
    return 0;
}