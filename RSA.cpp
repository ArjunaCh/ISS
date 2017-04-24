#include <stdio.h>
int isprime(int);
int isRalativePrime(int, int);

int main()
{
    int p, q, n, totient_n, e, d=1;
    while(1)
    {
        printf("\n Enter prime Numbers 'p' and 'q' :- ");
        scanf("%d%d", &p,&q);
        if(isprime(p) && isprime(q))
            break;
    }

    n=p*q;
    printf("Calculated value of 'n' is :- %d",n);

    totient_n=(p-1)*(q-1);
    printf("\nTotient of 'n' is :- %d",totient_n);

    while(1)
    {
        printf("\nEnter value of 'e' relatively prime to %d :- ",totient_n);
        scanf("%d",&e);
        if(isRalativePrime(totient_n,e))
            break;
    }

    while(1)
    {
        if((((e%totient_n)*(d%totient_n))%totient_n)==1)
            break;
        d++;
    }
    printf("Calculated value of 'd' is :- %d",d);
    printf("\n Private Key:-(%d,%d) \n Public key:-(%d,%d)",d,n,e,n);
    return 0;
}

int isprime(int num)
{
    for (int i = 2; i <= num/2 ; ++i) {
        if(num%i==0)
            return 0;
    }
    return 1;
}
int isRalativePrime(int a, int b)
{
    if(a%b == 1)
        return 1;
    else if(a%b == 0)
        return 0;
    else
        isRalativePrime(b,a%b);
}
