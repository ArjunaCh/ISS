#include<iostream>
#include<stdio.h>
using namespace std;

void display(int[3][3]);
void accept(int[3][3]);
void mul(int[3][3], int[3], int[3]);

int main()
{
    int key[3][3],t_res[3],res[3], pl[3],det, inv[3][3], adj[3][3]={0,0,0,0,0,0,0,0,0};
    char p[4],c[4], d[4];
    int i, j;

    cout<<" Enter key :-"<<endl;
    accept(key);

    cout<<"\n Enter three char string. :- ";
    cin>>p;

    for(i=0;i<3;i++)
        pl[i]=p[i]-'a';

    mul(key, pl,res);

    for(i=0;i<3;i++)
        c[i]=res[i]+'a';

    c[i]='\0';

    cout<<"\n Encrypted text :- "<<c;

    /**------------- Decryption ----------------**/

    det=(key[0][0]*(key[1][1]*key[2][2]-key[1][2]*key[2][1]))-(key[0][1]*(key[1][0]*key[2][2]-key[1][2]*key[2][0]))+(key[0][2]*(key[1][0]*key[2][1]-key[1][1]*key[2][0]));

    adj[0][0]=key[1][1]*key[2][2]-key[2][1]*key[1][2];
    adj[0][1]=(-1)*(key[2][2]*key[1][0]-key[2][0]*key[1][2]);
    adj[0][2]=key[1][0]*key[2][1]-key[2][0]*key[1][1];

    adj[1][0]=(-1)*(key[0][1]*key[2][2]-key[2][1]*key[0][2]);
    adj[1][1]=key[0][0]*key[2][2]-key[2][0]*key[0][2];
    adj[1][2]=(-1)*(key[0][0]*key[2][1]-key[2][0]*key[0][1]);

    adj[2][0]=key[0][1]*key[1][2]-key[1][1]*key[0][2];
    adj[2][1]=(-1)*(key[0][0]*key[1][2]-key[1][0]*key[0][2]);
    adj[2][2]=key[0][0]*key[1][1]-key[1][0]*key[0][1];

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            inv[i][j]=adj[j][i]/det;
        }
    }

    mul(inv,res,t_res);
    for(i=0;i<3;i++)
        d[i]=t_res[i]+'a';

    d[i]='\0';

    cout<<"\n Decrypted text :- "<<d;

    return 0;
}
void accept(int n[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cin>>n[i][j];
        }
    }
}
void display(int n[3][3])
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            cout<<n[i][j]<<" ";
        }
        cout<<endl;
    }
}
void mul(int key[3][3], int n2[3], int res[3])
{
    int sum, i, j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<1;j++)
        {
            sum=0;
            for(int k=0;k<3;k++)
            {
                sum+=key[i][k]*n2[k];
            }
            res[i]=(26+sum)%26;
        }
    }
}
