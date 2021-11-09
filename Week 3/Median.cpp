#include<iostream>
#include<fstream>
using namespace std;
typedef long long int64;
#define SIZE 10000
class Maxheap;

class Minheap{
    protected:
        int64 max;
        int64 * arr;
        int64 len;
    public:
        Minheap(int64 s):max(s),len(-1),arr(new int64[s]){cout<<"Heap initialized"<<endl;}

        int64 parent(int64 i){return (i-1)/2;}

        int64 left(int64 i){return 2*i+1;}

        int64 right(int64 i){return 2*i+2;}

        int64 getlen(){return len;}

        void add(int64 a){

            arr[++len] = a;
            int64 i = len;
            while((i!=0)&&(arr[parent(i)] > arr[i]))
            {
                swap(arr[parent(i)],arr[i]);
                i = parent(i);
            }

        }

        void heapify(int64 i)
        {
            int64 l = left(i), r = right(i);
            int64 min = i;
            if((l<=len) && (arr[i]>arr[l]))
            {
                min = l;
            }

            if((r<=len) && arr[min]>arr[r])
            {
                min = r;
            }

            if(i != min)
            {
                swap(arr[i],arr[min]);
                heapify(min);
            }
        }

        int64 extractmin(){
            if(len >= 0)
            {
                int64 res = arr[0];
                arr[0] = arr[len--];
                heapify(0);
                return res;
            }
            else
            {
                return 0;
            }

        }
        int64 first(){
            return len>=0 ? arr[0]:0 ;
        }

        void printit()
        {
            for(int i = 0;i<=len;i++)
            {
                cout<<arr[i]<<" ";
            }
            cout<<"\n";
        }

        //friend Maxheap;

};

class Maxheap:public Minheap{

            public:
            Maxheap(int64 s):Minheap(s){}      

        void add(int64 a){

            arr[++len] = a;
            int64 i = len;
            while((i!=0)&&(arr[parent(i)] < arr[i]))
            {
                swap(arr[parent(i)],arr[i]);
                i = parent(i);
            }

        }

        void heapify(int64 i)
        {
            int64 l = left(i), r = right(i);
            int64 min = i;
            if((l<=len) && (arr[i]<arr[l]))
            {
                min = l;
            }

            if((r<=len) && arr[min]<arr[r])
            {
                min = r;
            }

            if(i != min)
            {
                swap(arr[i],arr[min]);
                heapify(min);
            }
        }

        int64 extractmax(){
            if(len >= 0)
            {
                int64 res = arr[0];
                arr[0] = arr[len--];
                heapify(0);
                return res;
            }
            else
            {
                return 0;
            }

        }

};

class Median
{
    Maxheap a;
    Minheap b;
    int64 count ;
    int64 sum;
    public:
        Median():a(SIZE),b(SIZE),count(0),sum(0){}
        void addelement(int64 e)
        {
            if((a.getlen()==-1)&&(b.getlen()==-1))
            {   count++;
                b.add(e);
                //cout<<"Added :"<<e;
            }
            else{
                count++;
                if(e < a.first())
                {
                    a.add(e);
                    //cout<<"Added :"<<e;
                    
                }
                else if(e > b.first())
                {
                    b.add(e);
                     //cout<<"Added :"<<e;
                }
                else
                {
                    a.add(e);
                    //cout<<"Added :"<<e;
                }
               
            }
             balance();
             updatesum();
             //cout<<"A";a.printit();
             //cout<<"B";b.printit();

        }

        void balance(){
            if(a.getlen()== b.getlen())
            {
                return;
            }
            else if(a.getlen() - b.getlen()>1)
            {
               auto temp = a.extractmax(); 
               b.add(temp);
            }
            else if(b.getlen() - a.getlen()>1)
            {
               auto temp = b.extractmin(); 
               a.add(temp);
            }
            else
            {
                //do nothing
            }
        }

        void updatesum(){
            auto mode = a.first();;
            if(b.getlen()>a.getlen())
            {
                mode = b.first();
            }
            //cout<<" Median "<<mode<<endl;
            sum +=mode;
        }

        int64 medianmod()
        {
            return sum%10000;
        }
};

int main(){
    Median a;
    ifstream myfile("assignment3.txt");
    int64 element;
    while(myfile>>element)
    {
        //cout<<"Element:"<<element<<" ";
        a.addelement(element);
        
    }
    
    cout<<"\n"<<a.medianmod()<<endl; //Output = 1213
   
    return 0;
}