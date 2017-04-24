#include<iostream>
#include<cstdlib>
#include<fstream>
#define DEBUG 1
using namespace std;
int main()
{
    ifstream file;
    string line;
    string input;
    char ci[100], di[100];
    char char_set[]="abcdefghijklmnopqrstuvwwxyz!@#$%^&*";
    int c;
    int i,j, index;
    int size;
    int k;

    // Generating key from system date,
    system("date > date.txt");
    file.open("date.txt");

    if(DEBUG)
        while(getline(file,line))
        {
            cout<<line<<endl;
        }
    k=((int)line[17]-48)*10;
    k+=(int)line[18]-48;
    k=k%33;

    cout<<" Key :- "<<k<<endl;
    cout<<" Plain text :- ";
    getline(cin,input);


    for(i=0; input[i]!='\0'; i++)
    {
        for(j=0; char_set[j]!=input[i]; j++);
        ci[i]=char_set[(j+k)%33];
    }
    ci[i]='\0';
    size=i;
    cout<<" Ciphered text :- ";
    cout<<ci;
    cout<<endl;

    cout<<"\n Brute-Force Attack :- ";
    for(index=0; index<33; index++)
    {
        cout<<"\n Key "<<index<<" :- ";
        for(i=0; ci[i]!='\0'; i++)
        {
            for(j=0; char_set[j]!=ci[i]; j++);
                di[i]=char_set[(j+33-index)%33];     //Complement logic to add instead of subtracting.
        }
        di[i]='\0';
        cout<<di;
    }
    file.close();
    return 0;
}
