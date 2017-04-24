#include <stdio.h>
#include<math.h>

int main() {
    long int q, alpha, YA, YB, XA, XB, i, KA, KB;
    printf("\n Enter prime number 'q' and 'alpha' :- ");
    scanf("%ld%ld", &q, &alpha);

    printf("\n User 'A' select random number XA < %ld:- ", q);
    scanf("%ld", &XA);

    printf("\n User 'B' select random number XB < %ld:- ", q);
    scanf("%ld", &XB);

    YA = alpha;
    for (i = XA; i > 1; i--) {
        YA = ((YA % q) * (alpha % q)) % q;
    }
    printf("\n Calculated value of YA:- %d", YA);

    YB = alpha;
    for (i = XB; i > 1; i--) {
        YB = ((YB % q) * (alpha % q)) % q;
    }
    printf("\n Calculated value of YA:- %d", YB);

    YB = alpha;
    for (i = XB; i > 1; i--) {
        YB = ((YB % q) * (alpha % q)) % q;
    }

    KA = YB;
    for (i = XA; i > 1; i--) {
        KA = ((KA % q) * (YB % q)) % q;
    }
    printf("\n Key computed by user 'A':- %d", KA);


    KB = YA;
    for (i = XB; i > 1; i--) {
        KB = ((KB % q) * (YA % q)) % q;
    }
    printf("\n Key computed by user 'B':- %d", KB);

    return 0;
}
