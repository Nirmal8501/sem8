// #include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
using namespace chrono;

void parBFS(vector<vector<int>> &graph, int node){
    vector<int> visited(graph.size(), 0);
    queue<int> q;
    q.push(node);
    visited[node]=1;

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        cout<<curr<<" --> ";

        #pragma omp parallel for shared(graph, q)
        for(int i=0; i<graph[curr].size(); i++){
            int neigh = graph[curr][i];
            if(visited[neigh]==0){
                visited[neigh] = 1;
                q.push(neigh);
            }
        }
    }
}


void BFS(vector<vector<int>> &graph, int node){
    vector<int> visited(graph.size(), 0);
    queue<int> q;
    q.push(node);
    visited[node]=1;

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        cout<<curr<<" --> ";

        // #pragma omp parallel for shared(graph, q)
        for(int i=0; i<graph[curr].size(); i++){
            int neigh = graph[curr][i];
            if(visited[neigh]==0){
                visited[neigh] = 1;
                q.push(neigh);
            }
        }
    }
}


void parDFS(vector<vector<int>> &graph, int node){
    vector<int> visited(graph.size(), 0);
    stack<int> s;
    s.push(node);
    visited[node]=1;

    while(!s.empty()){
        int curr = s.top();
        s.pop();
        cout<<curr<<" --> ";

        #pragma omp parallel for shared(graph, s)
        for(int i=0; i<graph[curr].size(); i++){
            int neigh = graph[curr][i];
            if(visited[neigh]==0){
                visited[neigh] = 1;
                s.push(neigh);
            }
        }
    }
}

void DFS(vector<vector<int>> &graph, int node){
    vector<int> visited(graph.size(), 0);
    stack<int> s;
    s.push(node);
    visited[node]=1;

    while(!s.empty()){
        int curr = s.top();
        s.pop();
        cout<<curr<<" --> ";

        // #pragma omp parallel for shared(graph, q)
        for(int i=0; i<graph[curr].size(); i++){
            int neigh = graph[curr][i];
            if(visited[neigh]==0){
                visited[neigh] = 1;
                s.push(neigh);
            }
        }
    }
}


void addEdge(int par, int chl ){

}

int main(){
    int nodes = 6;
    vector<vector<int>> graph(6);
    graph[0] = {1,2};
    graph[1] = {0,3};
    graph[2] = {0,4,5};
    graph[3] = {1};
    graph[4] = {2};
    graph[5] = {2};

    cout<<"Parellel BFS : ";
    auto start = high_resolution_clock::now();
    parBFS(graph, 0);
    auto end = high_resolution_clock::now();
    auto tim = duration_cast<milliseconds>(end-start);

    cout<<endl;

    cout<<"Normal BFS : ";
    start = high_resolution_clock::now();
    BFS(graph, 0);
     end = high_resolution_clock::now();
     tim = duration_cast<milliseconds>(end-start);

    cout<<endl;

     cout<<"Parellel DFS : ";
    start = high_resolution_clock::now();
    parDFS(graph, 0);
     end = high_resolution_clock::now();
     tim = duration_cast<milliseconds>(end-start);

    cout<<endl;

     cout<<"Norm DFS : ";
    start = high_resolution_clock::now();
    DFS(graph, 0);
     end = high_resolution_clock::now();
     tim = duration_cast<milliseconds>(end-start);

    cout<<endl;

    return 0;
}