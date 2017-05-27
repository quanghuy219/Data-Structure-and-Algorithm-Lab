#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int min(int b[], int k, int n, int pos){
    int min;
    if (pos == 0) min = b[1] - k;
    
    else if (pos == n) min = k - b[n-1];
    
    else {
        min = fabs(b[pos] - b[pos-1]);
        if( fabs(b[pos+1]-b[pos]) < min ) min = fabs(b[pos+1]-b[pos]);
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


int sort(int a[], int b[], int n, int k){
    int i,j,tmp;
    for (i = 0; i < n; i++)
    {
        b[i] = a[i];
    }

    for(i=0; i<n;i++){
        for(j=i+1;j<n;j++){
            if(b[i] > b[j]){
               tmp = b[i];
                b[i] = b[j];
                b[j] = tmp;
            }
        }
    }
    return binarySearch(k,b,0,n);    
}



int main() {

    int n;
    scanf("%d",&n);
    int a[n+1],b[n+1];
    int k,i,j,tmp;
    for(i=0;i<n;i++) scanf("%d",&a[i]);

    
    int p,q;
    scanf("%d",&p);
    scanf("%d",&q);
    int minimax = 0;
    int pos;
    int result;

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

    
    for(k = p; k <= q; k++){
        if (k < a[0])
        {
            tmp = a[0] - p;
            k = a[0];
        }

        else if (k > a[n-1]){ 
            tmp = q - a[n-1];
            k = q;
        }

        else {
            a[n] = k;
            pos = sort(a,b,n+1,k);       
            tmp = min(b,k,n,pos);
        }
        
        if(tmp > minimax) {
            minimax = tmp;
            result = k;
        }
    }
    printf("%d\n",result);
    
    return 0;
}