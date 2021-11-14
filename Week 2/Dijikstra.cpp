#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

class Edge{
    public:
        int tail_node;
        int edge_length;
        Edge(int t = -1,int l = 0):tail_node(t),edge_length(l){}
};

class Node{
    public:
        bool isvisited;
        vector<Edge> Adjacent_array;
        Node():isvisited(false){}
};

class Graph{
    public:
        vector<Node> graph;
        Graph(){ 
                graph.push_back(Node());
               }

        void Addedge(int pos = 0, int e = 0, int l = 0)
        {   
            Edge edge(e,l); 
            if(pos > graph.size()-1)
            {
                graph.push_back(Node());
            }
            graph[pos].Adjacent_array.push_back(edge);        
        }

        void takeinput(char * file)
        {
            ifstream myfile(file);
            string in;
            while(getline(myfile,in))
            {   
                std::stringstream s(in);
                int n,n1,n2;
                s>>n;
                char comma  = ',';
                
                int vertex = 0;
                graph.push_back(Node());
                while(s>>n1>>comma>>n2)
                {
                    //cout<<"|"<<n1<<":"<<n2<<"|"; 
                    Edge e(n1,n2);
                    graph.back().Adjacent_array.push_back(e);
                    
                }
                vertex++;
            }
        }
        
        void printit()
        {
            for(int i = 0;i<graph.size();i++)
            {   cout<<i<<"-";
                for(int j = 0;j<graph[i].Adjacent_array.size();j++)
                 {
                     cout<<graph[i].Adjacent_array[j].tail_node <<":"<<graph[i].Adjacent_array[j].edge_length<<" ";
                 }
                 cout<<"\n";
            }
        }


        
};

class Dij{
    public:
        vector<int> len;
        vector<int> V;
        Dij(int n):len(vector<int>(n,0)){ }
        vector<int> Iterate(Graph &g){
            int node=1, next=1, edge=1;
            int min = INT32_MAX;
            for(int i=0;i<V.size();++i)
            {
                for(int j = 0; j < g.graph[V[i]].Adjacent_array.size();++j)
                {   
                    auto connected = g.graph[V[i]].Adjacent_array[j].tail_node;
                    if(g.graph[connected].isvisited == false)
                    {
                        int current = len[V[i]] + g.graph[V[i]].Adjacent_array[j].edge_length;
                        if(current<min)
                        {
                            min = current;
                            node = V[i];
                            next = connected;
                            edge = j;
                        }
                    }
                    
                    
                }
                
            }
            vector<int> a;
            a.push_back(node);
            a.push_back(next);
            a.push_back(edge);
            return  a;

        }

        void Findlen(Graph & g, int node)
        {
           
            g.graph[node].isvisited = true;
            V.push_back(node);
            while(V.size() < g.graph.size())
            {   
                vector<int> node_values = Iterate(g);//return the tail node, added node and edge value
                V.push_back(node_values[1]);
                g.graph[node_values[1]].isvisited = true;
                len[node_values[1]] = len[node_values[0]] + g.graph[node_values[0]].Adjacent_array[node_values[2]].edge_length;
            }
        }

        void printlengths(vector<int> v)
        {
            for(auto e:v)
            {
                cout<<len[e]<<",";
            }
            
        }


};


int main()
{   
    char filename[] = "assignment2.txt";
    Graph g;
    g.takeinput(filename);
    //g.printit();
    Dij d(g.graph.size());
    d.Findlen(g,1);
    vector<int> dist = {7,37,59,82,99,115,133,165,188,197 };
    d.printlengths(dist);
    return 0;
}