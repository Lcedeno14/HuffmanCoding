#include "Helper.hpp"
#include "HCTree.hpp"

void HCTree::build(const vector<int>& freqs)
{
    priority_queue<HCNode*, vector<HCNode*>,HCNodePtrComp> pq; //minheap
    for(unsigned int i = 0; i< freqs.size(); i++)
    {
        if(freqs[i]!=0) //>0
        {
            HCNode* letter = new HCNode(freqs[i], char(i));
            pq.push(letter);
            leaves[i] = letter;
        }
    }
    while(pq.size()>1) //create tree using pq 
    {
        HCNode* L = pq.top();
        pq.pop();
        HCNode* R = pq.top();
        pq.pop();
        int num = ((L->count) + (R->count));
        HCNode* dad = new HCNode(num , L->symbol);
        dad ->c0 = L;
        dad ->c1 = R;
        L ->p = dad;
        R ->p = dad;
        pq.push(dad);
    }
        if (pq.size()==1)
        {
            root = pq.top(); //maybe not use this->
            pq.pop();
        }

    
}
void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const
{
    
    vector<int> encode;
    HCNode* curr = leaves[int(symbol)];
    while(root!= curr){
        if(curr->p->c0 == curr)
        {
            encode.push_back(0);
        }
        else
        {
            encode.push_back(1);
        }
        curr = curr-> p;
    }
   
    for( auto reverse= encode.rbegin();reverse != encode.rend(); ++reverse)
    {
        out.write_bit(*reverse);
    }
}
unsigned char HCTree::decode(FancyInputStream & in) const
{
    int bit; //read a bit and set it to this
    HCNode* curr = root;
    while(curr->c0)
    {   
        bit = in.read_bit();
        if(bit == -1 )
        {
            break;
        }
        if (bit == 0)
        {
            curr = curr->c0;
        }
        else if(bit == 1)
        {
            curr = curr->c1;
        }
    }
    return curr->symbol;
}

HCTree::~HCTree()
{
    
    queue <HCNode*> q; 
    q.push(root);

    while(!q.empty())
    {   
        HCNode* curr = q.front();
        if(curr){
        if(curr->c0)
        {
        q.push(curr->c0);
        }
        if(curr->c1)
        {
        q.push(curr->c1);
        }
        
        delete curr;
        }
        q.pop();
    }
}
 
