#include<iostream>
#include<string.h>
using namespace std;
int main()
{
    char key[100], p[100], c[100], size, de[100];
    char char_set[]="abcdefghijklmnopqrstuvwxyz0123456789";
    int i,k, p_loc, k_loc;
    cout<<"\n Enter key :- ";
    cin>>key;
    cout<<"\n Enter plain text :- ";
    cin>>p;
    size=strlen(key);
    for(i=0,k=0;i<strlen(p);i++)
    {
        for(p_loc=0;p[i]!=char_set[p_loc];p_loc++);
        for(k_loc=0;key[k]!=char_set[k_loc];k_loc++);
        k=(k+1)%size;
        c[i]=char_set[(p_loc+k_loc)%36];
    }
    c[i]='\0';
    cout<<"\n Ciphered text is :- "<<c;
    for(i=0,k=0;i<strlen(p);i++)
    {
        for(p_loc=0;c[i]!=char_set[p_loc];p_loc++);
        for(k_loc=0;key[k]!=char_set[k_loc];k_loc++);
        k=(k+1)%size;
        de[i]=char_set[(p_loc+36-k_loc)%36];
    }
    de[i]='\0';
    cout<<"\n Decrypted text is :- "<<de;
    return 0;
}
