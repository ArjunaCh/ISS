#include<iostream>
#include<string.h>
using namespace std;
int table[5][5];

int init()
{
    int i,j;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            table[i][j]=-1;
        }
    }
}
int isPresent(int c)
{
    int i, j;
    if(c==9)
        c=8;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
             if(c==table[i][j])
                return 1;
        }
    }
    return 0;
}
int search(int c)
{
    int i,j;
    if(c==9)
        c=8;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
             if(c==table[i][j])
                return ((i+1)*10+j);
        }
    }
}

int main()
{
    //cout<<"Hello"<<endl;
    char key[100];
    char ptxt[100], p[100], dec[100];
    int i,j,k, flag, cur_i, cur_j,a, a_i, a_j, b_i,b_j;
    int loc_a, loc_b;
    cout<<" Enter key ;- ";
    cin>>key;

    //Table Generation for key
    init();
    k=0;
    flag=0;
    a=0;

    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(key[k]=='\0')
                flag=1;

            if(flag)
            {
                while(1)
                {
                    if(!isPresent(a))
                    {
                        table[i][j]=a++;
                        break;
                    }
                    a++;
                }
            }
            else
            {
                while(1)
                {
                    int temp=(int)key[k]-97;
                    if(isPresent(temp)==0)
                    {
                        table[i][j]=temp;
                        k++;
                        break;
                    }
                    k++;
                    if(key[k]=='\0')
                    {
                        j--;
                        break;
                    }

                }
           }
        }
    }

    // Debugging:- Printing table
    cout<<"\n Table :- "<<endl;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            cout<<" "<<(char)(table[i][j]+97);
        }
        cout<<endl;
    }

    // Encryption
    cout<<"\n Enter the plain text :- ";
    cin>>ptxt;
    k=0;
    for(i=1;i<strlen(ptxt);)
    {
        p[k++]=ptxt[i-1];
        if(ptxt[i]==ptxt[i-1])
        {
            p[k++]='x';
            i++;
        }
        else
        {
            p[k++]=ptxt[i];
            i+=2;
        }
    }
    p[k]='\0';
    cout<<"\n Encryption Process :- "<<endl<<endl;
    cout<<"1. Step 1 :- "<<p<<endl;


    //step 2
    for(i=0;i<strlen(p)-1;)
    {
        loc_a=search((int)p[i]-97);
        loc_b=search((int)p[i+1]-97);
        a_i=(loc_a/10)-1;
        a_j=(loc_a%10);
        b_i=(loc_b/10)-1;
        b_j=(loc_b%10);
       // cout<<"\n Locations are :- "<<a_i<<a_j<<" "<<b_i<<b_j;
        if(a_i==b_i)
        {
            p[i]=(char)(table[a_i][(a_j+1)%5]+97);
            p[i+1]=(char)(table[b_i][(b_j+1)%5]+97);

        }
        else if(a_j==b_j)
        {
            p[i]=(char)(table[(a_i+1)%5][a_j]+97);
            p[i+1]=(char)(table[(b_i+1)%5][b_j]+97);

        }
        else
        {
            p[i]=(char)(table[a_i][b_j]+97);
            p[i+1]=(char)(table[b_i][a_j]+97);
        }
        i+=2;
    }
    cout<<"\n2. Step 2 :- "<<p<<endl;
    cout<<"\n Cipher Text :- "<<p<<endl;



   /***-------------------Decryption---------------------------------**/

    for(i=0;i<strlen(p)-1;)
    {
        loc_a=search((int)p[i]-97);
        loc_b=search((int)p[i+1]-97);
        a_i=(loc_a/10)-1;
        a_j=(loc_a%10);
        b_i=(loc_b/10)-1;
        b_j=(loc_b%10);
       // cout<<"\n Locations are :- "<<a_i<<a_j<<" "<<b_i<<b_j;
        if(a_i==b_i)
        {
            p[i]=(char)(table[a_i][(a_j+4)%5]+97);           //complement logic -1=5-1=4
            p[i+1]=(char)(table[b_i][(b_j+4)%5]+97);

        }
        else if(a_j==b_j)
        {
            p[i]=(char)(table[(a_i+4)%5][a_j]+97);
            p[i+1]=(char)(table[(b_i+4)%5][b_j]+97);

        }
        else
        {
            p[i]=(char)(table[a_i][b_j]+97);
            p[i+1]=(char)(table[b_i][a_j]+97);
        }
        i+=2;
    }
    p[i]='\0';

    for(k=0,i=0;i<strlen(p)-1;i++)
    {
        if((p[i]-'x')==0 && i>0)
        {
            if(p[i-1]-p[i+1]==0)
                continue;
        }
        dec[k++]=p[i];
    }
    dec[k++]=p[i];
    dec[k]='\0';
    cout<<"\n Decrypted text is :-"<<dec;
    return 0;
}
