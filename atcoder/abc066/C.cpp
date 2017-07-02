#include <stdio.h>
#include <stdlib.h>

int main()

{
	int a[200005], i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	     scanf("%d", &a[i]);
	     
	for(i = n - 1; i > 0; i -= 2) 
	      printf("%d ", a[i]);
	      
	printf("%d ", a[0]);
	
	for(i = abs(i) + 1; i < n; i += 2)
	       printf("%d ", a[i]);
	       
	 return 0;
}