#include<iostream>
#include<stdlib.h>
#include<queue>
#include<bits/stdc++.h>
#include<vector>

using namespace std;

class Edge
{
    int start,stop,data;
public:
    Edge():start(0),stop(0),data(0){};
    Edge(int st,int en,int dat):start(st),stop(en),data(dat){};
    int get_start(void)
    {
        return start;
    }
    int get_stop(void)
    {
        return stop;
    }
    int get_data(void)
    {
        return data;
    }
};


class Node
{
    int data,pre;
public:
    Node():data(0),pre(-1){};
    Node(int x):data(x),pre(-1){};
    Node(Node &temp):data(temp.data),pre(temp.pre){};
    int get_data(void)
    {
        return data;
    }
    int get_pre(void)
    {
        return pre;
    }
    void set_pre(int prev)
    {
        pre = prev;
    }
};


class Graph
{
    int nodes,edges,**adj_mat,*visited;
    vector<Edge *> edges_arr;
    vector<Node *> nodes_arr;
    int DFS(Node *,int);
public:
    Graph(){};
    Graph(int node,int edge):nodes(node),edges(edge)
    {
        visited = new int[nodes]{0};
        adj_mat = new int * [nodes];
        for(int i=0;i<nodes;i++)
            adj_mat[i] = new int[nodes]{0};
    }
    void get_data(void);
    void display_tree(void);
    Graph * converter(void);
    int is_cycle(void);
};


void Graph::display_tree(void)
{
    cout<<endl;
    for(auto it = nodes_arr.begin();it<nodes_arr.end();it++)
        cout<<(*it)->get_data()<<" ";
    cout<<endl;
    for(int it = 0;it<edges_arr.size();it++)
        cout<<"Data: "<<edges_arr[it]->get_data()<<"\tStart: "<<edges_arr[it]->get_start()<<"\tEnd: "<<edges_arr[it]->get_stop()<<endl;
}


void Graph::get_data(void)
{
    cout<<"\nEnter number of nodes ";
    cin>>nodes;
    cout<<"\nEnter number of edges ";
    cin>>edges;
    visited = new int[nodes]{0};
    adj_mat = new int * [nodes];
    for(int i=0;i<nodes;i++)
    {
        adj_mat[i] = new int[nodes]{0};
        Node * temp = new Node(i);
        nodes_arr.push_back(temp);
    }
    for(int i=0;i<edges;i++)
    {
        cout<<"\nEnter edge "<<i+1<<": ";
        int st,en,dat;
        cin>>st>>en;
        if(st>=nodes||en>=nodes)
        {
            cout<<"\nInvalid input ";
            i--;
        }
        else
        {
            cout<<"Enter data ";
            cin>>dat;
            Edge *temp = new Edge(st,en,dat);
            edges_arr.push_back(temp);
            adj_mat[st][en] = adj_mat[en][st] = 1;
        }
    }
}


int Graph::is_cycle(void)
{
    int result(0);
    for(int i=0;i<nodes;i++)
        visited[i]=0;
    for(int j=0;j<nodes_arr.size();j++)
    if(!visited[j])
    {
        result = DFS(nodes_arr[j],-1);
        if(result)
            break;
    }
    return result;
}


int Graph::DFS(Node * start,int prev)
{
    static int result = 0;
    result=0;
    visited[start->get_data()]=1;
    Node * temp = new Node(*start);
    temp->set_pre(prev);
    for(int i=0;i<nodes;i++)
    {
        if(adj_mat[start->get_data()][i])
        {
            if(visited[i]==1&&i!=prev)
            {
                result = 1;
                return result;
            }
            if(!visited[i])
            DFS( nodes_arr[i],start->get_data());
        }
    }
    visited[start->get_data()]=2;
    return result;
}


Graph * Graph::converter(void)
{
    Graph * ptr = new Graph(nodes,nodes-1);
    for(auto it = nodes_arr.begin();it<nodes_arr.end();it++)
        ptr->nodes_arr.push_back(*it);
    for(int i=0;i<edges_arr.size();i++)
    for(int j=i+1;j<edges_arr.size();j++)
    if((edges_arr[i]->get_data())>(edges_arr[j]->get_data()))
        {
            Edge * temp = edges_arr[i];
            edges_arr[i] = edges_arr[j];
            edges_arr[j]=temp;
        }
    //for(int it = 0;it<edges_arr.size();it++)
    //cout<<"Data: "<<edges_arr[it]->get_data()<<"\tStart: "<<edges_arr[it]->get_start()<<"\tEnd: "<<edges_arr[it]->get_stop()<<endl;
    for(auto it = 0;it<edges_arr.size();it++)
    {
        Edge * temp = edges_arr[it];
        ptr->adj_mat[temp->get_start()][temp->get_stop()] = ptr->adj_mat[temp->get_stop()][temp->get_start()] = 1;
        //cout<<ptr->is_cycle();
        if(!(ptr->is_cycle()))
            ptr->edges_arr.push_back(temp);
        else
            ptr->adj_mat[temp->get_start()][temp->get_stop()] = ptr->adj_mat[temp->get_stop()][temp->get_start()] = 0;
    }
    return ptr;
}


main()
{
    Graph G;
    G.get_data();
    Graph *T = G.converter();
    T->display_tree();
}
