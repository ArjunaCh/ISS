#include<iostream>
using namespace std;
int key[10], k1[8], k2[8], pt[8], temp[8], op[4];
int S0[4][4] = { {1,0,3,2} , {3,2,1,0} , {0,2,1,3} , {3,1,3,2} } ;
int S1[4][4]= { {0,1,2,3}, {2,0,1,3}, {3,0,1,0}, {2,1,0,3}} ;
void keyGeneration();
void IP(int[]);
void IPI(int[]);
void expansion(int p[4]);
void XOR(int temp[],int key[], int n);
void SBOX();
void P4(int[]);
void SWAP(int[], int[]);
int main()
{
    int i, p4[4];
    key={1,0,1,0,0,0,0,0,1,0};

    cout<<"\n\n Enter 8-bit plain text :- ";
    for(i=0;i<8;i++)
        cin>>pt[i];

    cout<<"\n\n Enter 10-bit Key :- ";
    for(i=0;i<10;i++)
        cin>>key[i];

    cout<<"\n\n Key Used :- ";
    for(i=0;i<10;i++)
        cout<<key[i];
    cout<<endl;

    cout<<" Entered plain text is :- ";
    for(i=0;i<8;i++)
        cout<<pt[i];
    cout<<endl;

    keyGeneration();

/**----------------------Encryption---------------------------------------**/

    cout<<"\n ----------------------Encryption------------------------------";
    IP(pt);
    cout<<"\n\n Plain text After initial permutation :- ";
    for(i=0;i<8;i++)
        cout<<pt[i];

    // Round 1
    cout<<" \n\n A.   Round 1 ";
    expansion(&pt[4]);
    cout<<"\n\n Exapansion result :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    cout<<"\n Key1:- ";
    for(i=0;i<8;i++)
        cout<<k1[i];

    XOR(temp,k1,8);
    cout<<"\n XOR with Key 1 :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    SBOX();
    cout<<"\n SBOX Result:- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    cout<<"\n Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<pt[i];

   //P4 permutation 2 4 3 1
    P4(op);
    cout<<"\n P4 Permutation :- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    XOR(op,pt,4);
    cout<<"\n XOR with Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<op[i];


    SWAP(pt,op);
    cout<<"\n Result swap :- ";
    for(i=0;i<8;i++)
        cout<<pt[i];


    // Round 2
    cout<<" \n\n B.   Round 2 ";
    expansion(&pt[4]);
    cout<<"\n\n Exapansion result :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    cout<<"\n Key2- ";
    for(i=0;i<8;i++)
        cout<<k2[i];

    XOR(temp,k2,8);
    cout<<"\n XOR with Key 2 :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    SBOX();
    cout<<"\n SBOX Result:- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    cout<<"\n Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<pt[i];

   //P4 permutation 2 4 3 1
    P4(op);
    cout<<"\n P4 Permutation :- ";
    for(i=0;i<4;i++)
        cout<<op[i];


    XOR(op,pt,4);
    cout<<"\n XOR with Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<op[i];
    for(i=0;i<4;i++)
        pt[i]=op[i];
    IPI(pt);
    cout<<"\n\n Final Encrypted text :- ";
    for(i=0;i<8;i++)
        cout<<pt[i];



/**----------------------Decryption---------------------------------------**/

    cout<<"\n ----------------------Decryption------------------------------";
    IP(pt);
    cout<<"\n\n Cipher text After initial permutation :- ";
    for(i=0;i<8;i++)
        cout<<pt[i];

    // Round 1
    cout<<" \n\n A.   Round 1 ";
    expansion(&pt[4]);
    cout<<"\n\n Exapansion result :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    cout<<"\n Key2:- ";
    for(i=0;i<8;i++)
        cout<<k2[i];

    XOR(temp,k2,8);
    cout<<"\n XOR with Key 2 :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    SBOX();
    cout<<"\n SBOX Result:- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    cout<<"\n Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<pt[i];

   //P4 permutation 2 4 3 1
    P4(op);
    cout<<"\n P4 Permutation :- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    XOR(op,pt,4);
    cout<<"\n XOR with Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<op[i];


    SWAP(pt,op);
    cout<<"\n Result swap :- ";
    for(i=0;i<8;i++)
        cout<<pt[i];


    // Round 2
    cout<<" \n\n B.   Round 2 ";
    expansion(&pt[4]);
    cout<<"\n\n Exapansion result :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    cout<<"\n Key1- ";
    for(i=0;i<8;i++)
        cout<<k1[i];

    XOR(temp,k1,8);
    cout<<"\n XOR with Key 1 :- ";
    for(i=0;i<8;i++)
        cout<<temp[i];

    SBOX();
    cout<<"\n SBOX Result:- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    cout<<"\n Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<pt[i];


   //P4 permutation 2 4 3 1
    P4(op);
    cout<<"\n P4 Permutation :- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    XOR(op,pt,4);
    cout<<"\n XOR with Left Nibble :- ";
    for(i=0;i<4;i++)
        cout<<op[i];

    for(i=0;i<4;i++)
        pt[i]=op[i];

    IPI(pt);
    cout<<"\n\n Final Decrypted text :- ";
    for(i=0;i<8;i++)
        cout<<pt[i];

    return 0;
}


void keyGeneration()
{
    int p[10], temp, i, temp1;

    /** P10 Permutation **/
    p[0]=key[2];
    p[1]=key[4];
    p[2]=key[1];
    p[3]=key[6];
    p[4]=key[3];
    p[5]=key[9];
    p[6]=key[0];
    p[7]=key[8];
    p[8]=key[7];
    p[9]=key[5];

    /** Circular Right shift **/
    temp=p[0];
    for(i=0;i<4;i++)
        p[i]=p[i+1];
    p[i]=temp;

    temp=p[5];
    for(i=5;i<9;i++)
        p[i]=p[i+1];
    p[i]=temp;


    k1[0]=p[5];
    k1[1]=p[2];
    k1[2]=p[6];
    k1[3]=p[3];
    k1[4]=p[7];
    k1[5]=p[4];
    k1[6]=p[9];
    k1[7]=p[8];

    /** Circular Right shift **/

    //shift 1
    temp=p[0];
    for(i=0;i<4;i++)
        p[i]=p[i+1];
    p[i]=temp;

    temp=p[5];
    for(i=5;i<9;i++)
        p[i]=p[i+1];
    p[i]=temp;

    //shift 2
    temp=p[0];
    for(i=0;i<4;i++)
        p[i]=p[i+1];
    p[i]=temp;

    temp=p[5];
    for(i=5;i<9;i++)
        p[i]=p[i+1];
    p[i]=temp;

    k2[0]=p[5];
    k2[1]=p[2];
    k2[2]=p[6];
    k2[3]=p[3];
    k2[4]=p[7];
    k2[5]=p[4];
    k2[6]=p[9];
    k2[7]=p[8];

}

void IP(int t[8])
{
    int ip[8];
    ip[0]=t[1];
    ip[1]=t[5];
    ip[2]=t[2];
    ip[3]=t[0];
    ip[4]=t[3];
    ip[5]=t[7];
    ip[6]=t[4];
    ip[7]=t[6];

    for(int i=0;i<8;i++)
        t[i]=ip[i];

}

void IPI(int t[8])
{
    int ipi[8], i;
    ipi[0]=t[3];
    ipi[1]=t[0];
    ipi[2]=t[2];
    ipi[3]=t[4];
    ipi[4]=t[6];
    ipi[5]=t[1];
    ipi[6]=t[7];
    ipi[7]=t[5];
    for(int i=0;i<8;i++)
        t[i]=ipi[i];

}
void expansion(int p[4])
{
    temp[0]=p[3];
    temp[1]=p[0];
    temp[2]=p[1];
    temp[3]=p[2];
    temp[4]=p[1];
    temp[5]=p[2];
    temp[6]=p[3];
    temp[7]=p[0];
}
void XOR(int temp[],int key[], int n)
{
    for(int i=0;i<n;i++)
    {
        temp[i]=(temp[i]==key[i])?0:1;
    }
}
void SBOX()
{
    int row=temp[0]*2+temp[3];
    int col=temp[1]*2+temp[2];
    int o=S0[row][col];
    op[0]=o%2;
    op[1]=(o/2)%2;

    row=temp[4]*2+temp[7];
    col=temp[5]*2+temp[6];
    o=S1[row][col];
    op[2]=o%2;
    op[3]=(o/2)%2;

}
void P4(int op[])
{
    int p4[4];
    p4[0]=op[1];
    p4[1]=op[3];
    p4[2]=op[2];
    p4[3]=op[0];
    for(int i=0;i<4;i++)
        op[i]=p4[i];
}
void SWAP(int pt[], int op[])
{
    for(int i=0;i<4;i++)
        pt[i]=pt[i+4];
    for(int i=0;i<4;i++)
        pt[i+4]=op[i];
}
