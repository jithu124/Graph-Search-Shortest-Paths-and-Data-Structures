#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long Long;

class Graph{
    public:
        Graph(){}
        map<Long,vector<Long>> graph,reverse,first;
        Long total_nodes;
        vector<bool> visited;
        vector<Long> finished,scc;
        Long t,scc_size;

        void Getdata(string filename)
        {
            ifstream myfile(filename);
            string s;
            while(getline(myfile,s))
            {
                stringstream line(s);
                Long n1,n2;
                while(line>>n1>>n2)
                {
                    if(n1 != n2)
                    {
                        graph[n1].push_back(n2);
                        reverse[n2].push_back(n1);
                        //cout<<n1<<" "<<n2<<endl;
                        
                    }
                }
            }

            total_nodes = Totalnodes();//graph.size();
            for(auto i = 0; i<graph.size();i++)
            {

            }

            //cout<<total_nodes<<endl;
            visited = vector<bool>(total_nodes,false);
            finished = vector<Long>(total_nodes,0);
            t = 0;
        }

        void DFS_loop1()
        {
            for(auto i = total_nodes; i>0;i--)
            {
                if(visited[i]==false)
                {
                    DFS1(i);
                }
            }
        }

        void DFS1(Long i)
        {
            visited[i] = true;
            for(auto i:reverse[i])
            {
                if(visited[i] == false)
                {
                    DFS1(i);
                }
            }
            finished[t] = i;
            t++;
        }

        void DFS2(Long i)
        {
            visited[i] = true;
            for (auto edge:graph[i])
                {
                    if (visited[edge] == false)
                   {
                       DFS2(edge);
                   }
                }
            
            scc_size += 1;
        }
    
      


    void DFS_loop2()
        {
        
            visited = vector<bool>(total_nodes,false);
            
            for (auto i = total_nodes;i>0;i--)
                {
                    //cout<<"Node is"<<i<<endl;
                    if (visited[finished[i]]==false)
                    {
                        scc_size = 0 ;
                        DFS2(finished[i]);
                        scc.push_back(scc_size);
                    }
                }
        
        }

    void Process()
    {
         DFS_loop1();
         DFS_loop2();
         sort(scc.begin(),scc.end(),greater<int>());
         for(auto i = 0; i<5;i++)
         {
             cout<<scc[i]<<" ";
         }
    }

    Long Totalnodes()//finding the maximum value of nodes. it is assumed as the total number of nodes
    {
        map<Long,vector<Long>>::iterator it = graph.begin();
        Long max = 0;
        while(it !=graph.end())
        {
            auto node = it->first;
            if(node>max)
            {
                max = node;
            }
            for(auto a:graph[node])
            {
                if(a>max)
                {
                    max = a;
                }

            }
           it++; 
        }
        return max;
    }


};

int main(){

    Graph a;
    a.Getdata("SCC.txt");
    a.Process();

    return 0;
}