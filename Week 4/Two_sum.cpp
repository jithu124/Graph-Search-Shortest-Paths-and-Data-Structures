#include<iostream>
#include<fstream>//header for infile
#include<algorithm>//header for sort
#include<map>
#include<vector>
#include<string>

using namespace std;

class Twosum{
    private:
        vector<long long> arr;
        long long len;
        string filename;
    public:
        Twosum(string file=""):filename(file),len(0){cout<<"initialized the class with file: "<<filename<<endl;}

        void getelements()
        {
            ifstream myfile(filename);
            long long element;
            while(myfile>>element)
            {
                arr.push_back(element);
                len++;
            }
        }

        long long GetTwosum()
        {
            getelements();
            sort(arr.begin(),arr.end());
            long long low, high, sum, i,j,total = 0;
            map<long long,bool> m;
            for(i=0; i<len ; i++)
            {   
                low = -10000-arr[i];
                high = 10000-arr[i];
                for(j = lower_bound(arr.begin(),arr.end(),low)-arr.begin();(j>0)&&(j<len)&&(arr[j]<=high);j++)
                {
                    sum = arr[i]+arr[j];
                    if(m[sum]==0)
                    {
                        m[sum]=1;
                        total++;

                    }
                }
            }

            return total;

        }

};

int main()
{   
    Twosum a("assignment4.txt");
    cout<<a.GetTwosum()<<endl;

    return 0;
}

