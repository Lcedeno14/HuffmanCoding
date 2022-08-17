#include "Helper.hpp"
#include "HCTree.hpp"
#include <sstream>
#include <iomanip>
int main(int argc, char* argv[])
{
     //check for valid arguments
    if(argc!=3)
    {
        error("Invalid number of arguments");
    }
    //Open the input file for reading
    FancyInputStream IN(argv[1]);
    vector<int> freqcount(256,0);
/*
    //read the file header at the beginning of the input file 
    for(auto i = 0; i < freqcount.size(); i++)
    {
        auto read = IN.read_int();
        freqcount[i] = read;
        
        if(freqcount[i]>0)
        {
        cout<<char(i)<<"::"<<freqcount[i]<<"\n";
        }
    }*/
    //new read from file
     // how many bytes to read
    for(auto i = 0; i < freqcount.size(); i++)
    {
        auto tee = IN.read_byte();
        char read (tee);
        //cout << "tee = " << tee << " : read = "<<read<< "\n";
        int x;
        
            //int l = (((count>>8) & 0xFF) << 8)+(((count>>0) & 0xFF) << 0);
            if(tee>0)
                {
                int a=0;
                int b =0;
                vector <int> fe;
                for(int j = 0; j< tee; j++)
                    { 
                        b = 8*(tee-1-j);
                        //cout<< "b = "<< b<< "\n"; 
                        //cout << "a = "<<a<< "\n";
                        auto t =IN.read_byte();
                        //cout << "t = "<< t << "\n";
                        a= a +(( t << b));
                    }
                
                freqcount[i] = a;
               }
            else
            {
            freqcount[i] = tee;
            }
       /* if(freqcount[i]>0)
        {
        cout<<char(i)<<"::"<<freqcount[i]<<"\n";
        }*/
    }
    //reconstruct the Huffman coding tree
    HCTree appleT; //creates tree object
    appleT.build(freqcount);//constructs tee
    //Open the output file for writing
    FancyOutputStream OUT(argv[2]);
    int lettercount = 0;
    for(auto i: freqcount)
    {
        lettercount += i;
    }
    cout<<"lettercount"<< lettercount <<"\n";
    //Using the Huffman coding tree, decode the bits from the 
    //input file into the appropriate sequence of bytes, writing them to the output file
    if(lettercount>1)
    {
        for (auto i = 0; i<lettercount; i++)
        {
            char ch = appleT.decode(IN);
            //cout<< ch <<"\n";
            OUT.write_byte(ch);
            //OUT.write_byte(appleT.decode(IN));
        }
    }
    return 0;
}
