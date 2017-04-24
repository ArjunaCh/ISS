#include<iostream>
#include<string.h>
using namespace std;

int key_len;
unsigned char key[16];
unsigned char S[256];
unsigned char plain[20];
unsigned char cipher[20];

void KSA()
{
    int i,j=0;
    int bit, k_index;
    unsigned char temp;

    for(i=0; i<256; i++)
    {
        j = ( j + S[i] + key[ i % key_len] ) % 256;
        temp=S[i];
        S[i]=S[j];
        S[j]=temp;
    }
}

void PRGA()
{
    int i,j,m;
    unsigned char temp, keystream;
    i = j = m = 0;
    while(plain[m]!='\0')
    {
        i = ( i + 1) % 256;
        j = ( j + S[i] ) % 256;

        temp=S[i];
        S[j]=S[i];
        S[i]=temp;

        keystream = S[ ( S[i] + S[j] ) % 256 ];
        cipher[m]=plain[m] ^ keystream;
        m++;
    }
}

void PRGAd()
{
    int i,j,m;
    unsigned char temp, keystream;
    i = j = m = 0;
    while(cipher[m]!='\0')
    {
        i = ( i + 1) % 256;
        j = ( j + S[i] ) % 256;

        temp=S[i];
        S[j]=S[i];
        S[i]=temp;

        keystream = S[ ( S[i] + S[j] ) % 256 ];
        cipher[m]=cipher[m] ^ keystream;
        m++;
    }
}

int main()
{
    int i;

    cout<<"\n Enter the key :- ";
    cin>>key;
    key_len=strlen((char *)key);

    cout<<"\n Enter Plain text :- ";
    cin>>plain;

    for(i=0; i<256; i++)
        S[i]=i;

    KSA();
    PRGA();

    cout<<"\n Ciphered text is :- "<<cipher<<endl;

    for(i=0; i<256; i++)
        S[i]=i;

    KSA();
    PRGAd();
    cout<<"\n Plain text is :- "<<cipher<<endl;

    return 0;
}
