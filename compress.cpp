#include "Helper.hpp"
#include "HCTree.hpp"
#include <stdio.h>
#include <limits.h>
#include <sstream>
#include <iomanip>
int main(int argc, char* argv[])
{
    //check for valid arguments
    if(argc!=3)
    {
        error("Invalid number of arguments");
    }
    
    //open a input file
    FancyInputStream IN(argv[1]);
    vector<int> freqcount(256,0);
    
    while(true)//loop to read file and update freqcount
    {
        int read = IN.read_byte();
        if(read == -1)
        {
            break;
        }
        freqcount[read]++;
    }
    
    for(auto i = 0; i < freqcount.size(); i++)
    {
        if(freqcount[i]>0){
        cout<<char(i)<<"::"<<freqcount[i]<<"\n";
        }
    }
   IN.reset();
   
    //main tree
    
    HCTree appleT; //creates tree object
    
    appleT.build(freqcount);//constructs tree


    //basic header
    
        FancyOutputStream OUT(argv[2]);
       /* for(auto count : freqcount)
        {
            OUT.write_int(count);
        }*/
 //new header
        
        //unsigned char bytes1[4];
        //vector<int>  bytes2[8];
        //unsigned char bytes3[8];
        //int bit_count = 0;
        int i=0;
        for(auto & count  : freqcount)
        {   //if (bit_count < 0){bit_count = 0;}
            //for (int i = 0; i<=7; i++){}
            if(freqcount[i]>0){
            cout<<char(i)<<"::"<<freqcount[i]<<"\n";
            }
                if(count==0)
                {
                    
                    OUT.write_byte((0>>0) & 0xFF);
                    //cout << "byte char is:" << ((0>>0) & 0xFF);
                }
                else if(count<255)
                {
                    OUT.write_byte((1>>0) & 0xFF);
                    OUT.write_byte((count>>0)& 0xFF);
                    cout << "byte unit is:" << ((1>>0) & 0xFF)<<"\n";
                    cout << "byte char 1 is:" << ((count>>0) & 0xFF)<<"\n";
                }
                else if(count< 65535)
                {
                    OUT.write_byte((2>>0) & 0xFF);
                    OUT.write_byte((count>>8)& 0xFF);
                    OUT.write_byte((count>>0)& 0xFF);
                    //cout << "byte unit is:" << ((2>>0) & 0xFF)<<"\n";
                    //cout << "byte char 1 is:" << ((count>>0) & 0xFF)<<"\n";
                    //cout << "byte char 2 is:" << ((count>>8) & 0xFF)<<"\n";
                    int x;
                    string a="";
                    a = a+char(((count>>8) & 0xFF));
                    a = a+char(((count>>0) & 0xFF));
                    int l = (((count>>8) & 0xFF) << 8)+(((count>>0) & 0xFF) << 0);
                    //cout<< "hex string: "<< a <<"\n";
                    //cout<< "hex string converted is :" << l <<" and the righ one is " << freqcount[i]<<"\n";

                    //stream << x;
                    //stream >> std::hex >> y;
                }
                else
                {
                    OUT.write_byte((3>>0) & 0xFF);
                    OUT.write_byte((count>>16) & 0xFF);
                    OUT.write_byte((count>>8)& 0xFF);
                    OUT.write_byte((count>>0)& 0xFF);
                }
                i++;
                
        }

    //Using the Huffman coding tree, translate each byte from the input file into its code, 
    //and append these codes as a sequence of bits to the output file, after the header
    
    while(true)
    {
        int read = IN.read_byte();
        if(read == -1)
        {
            break;
        } 
        appleT.encode(char(read),OUT);
    }
    //compress finished
    return 0; 
}

