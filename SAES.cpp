#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;


int SBOX[16]={0x9,0x4,0xA,0xB,0xD,0x1,0x8,0x5,0x6,0x2,0x0,0x3,0xC,0xE,0xF,0x7};
int IBOX[16]={0xA,0x5,0x9,0xB,0x1,0x7,0x8,0xF,0x6,0x0,0x2,0x3,0xC,0x4,0xD,0xE};
int key[16]={0,1,0,0,1,0,1,0,1,1,1,1,0,1,0,1};
int key1[16], key2[16];


void generate_key(int[], int[], int[]);
int binToDec(int []);
void decTobin(int i, int pInt[4]);
void encryption(int[]);
void decryption(int[]);
void MixColumn(int matrix[2][2],int MultiplicationMatrix[2][2],int output[16]);
int multiply_binary(int a,int b);
int divide_binary(int a,int b);

int main() {
    int pt[16]={1,1,0,1,0,1,1,1,0,0,1,0,1,0,0,0};
    int ct[16];
    printf("\n Entered plain text :- ");
    for (int i = 0; i < 16; ++i) {
        printf("%d",pt[i]);
    }
    printf("\n Entered Key0  :- ");
    for (int i = 0; i < 16; ++i) {
        printf("%d",key[i]);
    }
    printf("\n\n **----------------Key Generation------------------------**");

    printf("\n Key1  :- ");
    {
        int temp[16] = {1, 0, 0, 0, 0, 0, 0, 0};
        generate_key(key, key1, temp);
    }
    printf("\n\n Key2  :- ");
    {
        int temp[16] = {0, 0, 1, 1, 0, 0, 0, 0};
        generate_key(key1, key2, temp);
    }

    printf("\n\n **----------------Encryption------------------------**");
    encryption(pt);

    printf("\n\n **----------------Decryption------------------------**");
    decryption(pt);
    return 0;
}

void generate_key(int key[16], int key1[], int temp[8])
{
    int w0[8], w1[8], w2[8], t;
    for (int i = 0; i <8 ; ++i) {
        w0[i]=key[i];
        w1[i]=key[i+8];
    }

    printf("\n W0 :- ");
    for (int i = 0; i < 8; ++i) {
        printf("%d",w0[i]);
    }
    printf("\n W1 :- ");
    for (int i = 0; i < 8; ++i) {
        printf("%d",w1[i]);
    }
    // Rotate Nibble
    for (int k = 0; k <4 ; ++k) {
        t=w1[k];
        w1[k]=w1[k+4];
        w1[k+4]=t;
    }
    printf("\n W1 after rotation :- ");
    for (int i = 0; i < 8; ++i) {
        printf("%d",w1[i]);
    }
    // Subsitute Nibble

    int i=binToDec(w1);
    t=SBOX[i];
    decTobin(t,&w1[0]);

    i=binToDec(&w1[4]);
    t=SBOX[i];
    decTobin(t,&w1[4]);

    printf("\n W1 after Substitution :- ");
    for (int i = 0; i < 8; ++i) {
        printf("%d",w1[i]);
    }

    for (int j = 0; j <8 ; ++j)
        w2[j]=w0[j]^temp[j]^w1[j];

    int l;
    for (l = 0; l <8 ; ++l) {
        key1[l+8]=w2[l]^key[l+8];
    }
    for (int k=0;  k<8 ; k++) {
        key1[k]=w2[k];
    }

    printf("\n Generated Key :- ");
    for (int i = 0; i < 16; ++i) {
        printf("%d",key1[i]);
    }
}

void decTobin(int i, int pInt[4])
{
    int j;
    for (j = 0; i>0 ; ++j) {
        pInt[3-j]=i%2;
        i=i/2;
    }
    for (; j < 4 ; ++j) {
        pInt[3-j]=0;
    }
}

int binToDec(int bin[4])
{
    int dec=0;
    int temp;
    for (int i = 0; i <4 ; ++i) {
        dec+=bin[i]*pow(2,(3-i));
    }
    return  dec;
}

void encryption(int pt[16])
{
    int t, i;
    int m[2][2]={1,4,4,1};
    int s[2][2];
    for (i = 0; i <16 ; ++i) {
        pt[i]^=key[i];
    }
    printf("\n\n Add round 0 Key:- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Round 1
    printf("\n\n Round 1:- ");
    for (int j = 0; j <=12 ; ) {
        i=binToDec(&pt[j]);
        t=SBOX[i];
        decTobin(t,&pt[j]);
        j+=4;
    }
    printf("\n Substitution :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //swap 2nd and 4th nibble
    for (int k = 4; k <8 ; ++k) {
        t=pt[k];
        pt[k]=pt[k+8];
        pt[k+8]=t;
    }
    printf("\n Shift rows :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Mix Column
    t=0;
    for (i = 0; i <2 ; ++i) {
        for (int j = 0; j <2 ; ++j) {
            s[i][j]=binToDec(&pt[t]);
            t=t+4;
        }
    }
    MixColumn(s,m,pt);
    t=0;

    printf("\n Column mix :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Add round key 1
    for (i = 0; i <16 ; ++i) {
        pt[i]^=key1[i];
    }
    printf("\n Add round 1 Key:- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Round 2
    printf("\n\n Round 2:- ");
    for (int j = 0; j <=12 ; ) {
        i=binToDec(&pt[j]);
        t=SBOX[i];
        decTobin(t,&pt[j]);
        j+=4;
    }
    printf("\n Substitution :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //swap 2nd and 4th nibble
    for (int k = 4; k <8 ; ++k) {
        t=pt[k];
        pt[k]=pt[k+8];
        pt[k+8]=t;
    }
    printf("\n Shift rows :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }
    //Add round key 2
    for (i = 0; i <16 ; ++i) {
        pt[i]^=key2[i];
    }
    printf("\n Add round 2 Key:- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    printf("\n");
}

void decryption(int pt[16])
{
    int t, i;
    int m[2][2]={9,2,2,9};
    int s[2][2];
    for (i = 0; i <16 ; ++i) {
        pt[i]^=key2[i];
    }
    printf("\n\n Add round Key 2:- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Round 1
    printf("\n\n Round 1:- ");

    //swap 2nd and 4th nibble
    for (int k = 4; k <8 ; ++k) {
        t=pt[k];
        pt[k]=pt[k+8];
        pt[k+8]=t;
    }
    printf("\n Inverse Shift rows :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Inverse substitution
    for (int j = 0; j <=12 ; ) {
        i = binToDec(&pt[j]);
        t = IBOX[i];
        decTobin(t, &pt[j]);
        j += 4;
    }
    printf("\n Substitution :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Add round key 1
    for (i = 0; i <16 ; ++i) {
        pt[i]^=key1[i];
    }
    printf("\n Add round 1 Key:- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Mix Column
    t=0;
    for (i = 0; i <2 ; ++i) {
        for (int j = 0; j <2 ; ++j) {
            s[j][i]=binToDec(&pt[t]);
            t=t+4;
        }
    }
    MixColumn(s,m,pt);
    t=0;

    printf("\n Column mix :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }


    //Round 2
    printf("\n\n Round 2:- ");

    //swap 2nd and 4th nibble
    for (int k = 4; k <8 ; ++k) {
        t=pt[k];
        pt[k]=pt[k+8];
        pt[k+8]=t;
    }
    printf("\n Shift rows :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Inverse substitution
    for (int j = 0; j <=12 ; ) {
        i=binToDec(&pt[j]);
        t=IBOX[i];
        decTobin(t,&pt[j]);
        j+=4;
    }
    printf("\n Substitution :- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }

    //Add round key 2
    for (i = 0; i <16 ; ++i) {
        pt[i]^=key[i];
    }
    printf("\n Add round  Key 0:- ");
    for (i = 0; i <16 ; ++i) {
        printf("%d",pt[i]);
    }
    printf("\n");
}


void MixColumn(int matrix[2][2],int MultiplicationMatrix[2][2],int output[16])
{
    //multiplication matrix is {{1,4},{4,1}}

    int a,b,c,d;

    a = divide_binary(multiply_binary(MultiplicationMatrix[0][0],matrix[0][0]),19) ^ divide_binary(multiply_binary(MultiplicationMatrix[0][1],matrix[1][0]),19);
    c = divide_binary(multiply_binary(MultiplicationMatrix[0][0],matrix[0][1]),19) ^ divide_binary(multiply_binary(MultiplicationMatrix[0][1],matrix[1][1]),19);
    b = divide_binary(multiply_binary(MultiplicationMatrix[1][0],matrix[0][0]),19) ^ divide_binary(multiply_binary(MultiplicationMatrix[1][1],matrix[1][0]),19);
    d = divide_binary(multiply_binary(MultiplicationMatrix[1][0],matrix[0][1]),19) ^ divide_binary(multiply_binary(MultiplicationMatrix[1][1],matrix[1][1]),19);

    output[0] = a>>3 & 1;
    output[1] = a>>2 & 1;
    output[2] = a>>1 & 1;
    output[3] = a    & 1;

    output[4] = b>>3 & 1;
    output[5] = b>>2 & 1;
    output[6] = b>>1 & 1;
    output[7] = b    & 1;

    output[8]  = c>>3 & 1;
    output[9]  = c>>2 & 1;
    output[10] = c>>1 & 1;
    output[11] = c    & 1;

    output[12] = d>>3 & 1;
    output[13] = d>>2 & 1;
    output[14] = d>>1 & 1;
    output[15] = d    & 1;
}


int multiply_binary(int a,int b)
{
    int i,multiplication=0;
    for(i=7;i>=0;i--)
    {
        if(b & 1<<i)
        {
            multiplication ^= (a << i);
        }
    }
    return multiplication;
}



int divide_binary(int a,int b)
{
    int i,remainder=a;
    double integral1,integral2;

    modf(log(remainder)/log(2),&integral1);
    modf(log(b)/log(2),&integral2);
    i = (int)integral1 - (int)integral2;
    while(i >= 0)
    {
        remainder ^= (b << (int)i);
        modf(log(remainder)/log(2),&integral1);
        modf(log(b)/log(2),&integral2);
        i = (int)integral1 - (int)integral2;
    }
    return remainder;
}
