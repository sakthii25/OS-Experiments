#include <bits/stdc++.h>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
using namespace std;

class PCB{
public:
    int id;
    string state;
    vector<pair<int,int>> pagetable;
    PCB(int id){
        this->id = id;
        state = "new";
    }
    int getid(){
        return id;
    }
    string getstate(){
        return state;
    }
    void setstate(string&& state){
        this->state = state;
    }
    vector<pair<int,int>> getPageTable(){
        return pagetable;
    }
};
class Os{
public:
    int* MemFrame;
    int n;
    map<int,int> mpids;
    map<int,PCB*> ProcessTable;
    Os(int n){
        this->n = n;
        MemFrame = new int[n];
        for(int i=0;i<n;++i){
            *(MemFrame+i) = 0;
        }
    }
    ~Os(){
        delete[] MemFrame;
    }
    int CreateProcess(int sz){
        //sz size of the program
        int pages = sz;
        int id = rand() % 100 + 1;
        while(mpids[id]){
            id = rand() % 100 + 1;
        }
        PCB* obj = new PCB(id);
        
        int ind = 0;
        for(int i=0;i<n and ind < sz;++i){
            if(!MemFrame[i]){
                MemFrame[i]  = 1;
                obj->pagetable.push_back({ind,i});
                ++ind;
            }
        }
        
        if(ind < sz){
            cout << "Insufficient Memory" << endl;
            for(auto i:obj->pagetable){
                MemFrame[i.second] = 0;
            }
            delete obj;
            return -1;
        }
        
        mpids[id] = 1;
        ProcessTable[id] = obj;
        return id;
    }
    void DeleteProcess(int id){
        if(!mpids[id]){
            cout << "There is no such process with this id" << endl;
            return;
        }
        
        mpids[id] = 0;
        PCB* obj = ProcessTable[id];
        
        for(auto i:obj->pagetable){
            MemFrame[i.second] = 0;
        }
        
        ProcessTable.erase(id);
        delete obj;
        
        return;
    }
};
int main(){
     srand(time(nullptr));
     Os obj(100);
     int id = obj.CreateProcess(20);
     cout <<  id << endl;
     id = obj.CreateProcess(320);
     cout << id << endl;
}
