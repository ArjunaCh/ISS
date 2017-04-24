#include <stdio.h>
#include <stdlib.h>
int p, a, b, n, s, h;
struct point
{
    int x, y;
};
int isPrime(int p)
{
    for (int i = 2; i <=(p/2) ; ++i) {
        if((p%i)==0)
            return 0;
    }
    return 1;
}

int slope(struct point g, struct point new_g)
{
    int s, pt, qt, i;
    if(g.x==new_g.x && g.y==new_g.y)
    {
        pt=(3*(g.x*g.x))+a;
        qt=2*g.y;
    }
    else
    {
        pt=new_g.y-g.y;
        qt=new_g.x-g.x;
    }

    // For numerator
    if(pt<0)
        pt=p-(abs(pt)%p);
    pt=pt%p;

    // For Denomerator
    if(qt<0)
        qt=p-(abs(qt)%p);


    for (i = 1; ((qt*i)%p)!=1 ; ++i);
    s=(pt*i)%p;
    return s;
}

struct point compute_nG(int n, struct point g)
{
    int s;
    struct point new_g=g;
    for (int i = 1; i < n; ++i) {
        s=slope(g,new_g);

        new_g.x=((s*s)-g.x-new_g.x);
        if(new_g.x<0)
            new_g.x=p-(abs(new_g.x)%p);
        new_g.x=new_g.x%p;

        new_g.y=((s*(g.x-new_g.x))-g.y);
        if(new_g.y<0)
            new_g.y=p-(abs(new_g.y)%p);
        new_g.y=new_g.y%p;
    }
    return new_g;
}
int find_n(struct point g, struct point t)
{
    int s, i;
    struct point new_g=g;
    i=1;
    while(!(new_g.x==t.x && new_g.y==t.y)) {
        s=slope(g,new_g);

        new_g.x=((s*s)-g.x-new_g.x);
        if(new_g.x<0)
            new_g.x=p-(abs(new_g.x)%p);
        new_g.x=new_g.x%p;

        new_g.y=((s*(g.x-new_g.x))-g.y);
        if(new_g.y<0)
            new_g.y=p-(abs(new_g.y)%p);
        new_g.y=new_g.y%p;
        i++;
    }
    return i;
}
int main()
{
    int alpha, beta;
    struct point g, new_g, A, B, Abeta, Balpha;
    h=1;                                     //Typically always considered as 1
    while(1)
    {
        printf("\n Enter field 'p' :-");
        scanf("%d", &p);

        if(isPrime(p))
            break;
    }

    printf("\n Enter Curve parameters 'a' and 'b' :- ");
    scanf("%d%d",&a,&b);

    printf("\n Enter Curve generator point 'G' :- ");
    scanf("%d%d",&g.x,&g.y);

    new_g=g;
    n=2;
    printf("\n Calculated point G1 :- %d %d",new_g.x,new_g.y);
    do
    {
        s=slope(g,new_g);

        new_g.x=((s*s)-g.x-new_g.x);
        if(new_g.x<0)
            new_g.x=p-(abs(new_g.x)%p);
        new_g.x=new_g.x%p;

        new_g.y=((s*(g.x-new_g.x))-g.y);
        if(new_g.y<0)
            new_g.y=p-(abs(new_g.y)%p);
        new_g.y=new_g.y%p;

        printf("\n Calculated point G%d :- %d %d",n,new_g.x,new_g.y);
        n++;
    }while(g.x!=new_g.x);
    printf("\n\n Calculated 'n' value is :- %d", n);
    printf("\n Enter private keys 'alpha' and 'beta' for the users :- ");
    scanf("%d%d",&alpha,&beta);

    A=compute_nG(alpha,g);
    B=compute_nG(beta,g);
    printf("\n Computed public of 'A'  is :- %d %d", A.x, A.y);
    printf("\n Computed publlic key of 'B' is :- %d %d", B.x, B.y);

    int temp=find_n(g,B);
    temp=((temp%n)*(alpha%n))%n;
    Balpha=compute_nG(temp,g);
    printf("\n Secrete key computed by 'A'  is :- %d %d", Balpha.x, Balpha.y);


    temp=find_n(g,A);
    temp=((temp%n)*(beta%n))%n;
    Abeta=compute_nG(temp,g);
    printf("\n Secrete key computed by 'B'  is :- %d %d", Abeta.x, Abeta.y);

    return 0;
}