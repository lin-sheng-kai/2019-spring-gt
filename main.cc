/* 
    Your main program goes here
*/
#include <algorithm>
#include <iostream> 
#include <unistd.h>
#include <queue>
#include <map>
#include "network_manager.h"
#include "gplot.h"
#include "path.h"




using namespace std;


// create NetworkManager first
NetworkManager *nm = new NetworkManager();


void SSS(int ADJ_Matrix[100][100],int n, int Start_point, int End_point) ; 
int MinPath(int* dist, int* Done,int n) ; 
void PrintPath(int* Last, int End_point) ; 


int main(int argc, char** argv){

    /* start your program */
    


    string node[100];
    int edge[100];


    // read from file
    nm->interpret("./topo.txt");


    // get all nodes
    Vertex *node_list = nm->get_all_nodes();

    int node_count=0;

    while(node_list!=NULL){

	node[node_count] = node_list->name;
	node_count ++;	
	
        node_list=node_list->next;
    }


    //print all nodes
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "==========Node==========" << std::endl;


    for(int i=0;i<node_count;i++)
	{
	
	    std::cout << "Node["<<i<<"] = " <<node[i]<< std::endl;

	}

     
    // get all edges
	std::cout << std::endl;
	std::cout << std::endl; 
	std::cout << "==========Edge==========" << std::endl;


        int edge_count=0;	

    Edge *edge_list = nm->elist;
    while(edge_list!=NULL) {
        std::cout << edge_list->head->name <<"---"<<  edge_list->tail->name << std::endl;
	
	for(int i=0;i<node_count;i++)
	{
		if(node[i] == edge_list->head->name)        	
			edge[edge_count] = i;
	}
        edge_count ++;

	for(int i=0;i<node_count;i++)
	{
		if(node[i] == edge_list->tail->name)        	
			edge[edge_count] = i;
	}
        edge_count ++; 
       
        edge_list=edge_list->next;
    }


    //print all edges
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "==========Endpoint List==========" << std::endl;
    for(int i=0;i<edge_count;i++)
	{
	
	    std::cout << "Point["<<i<<"] = " <<edge[i]<< std::endl;

	}

    

    //Adjacenry Matrix
    int adj_matrix[100][100];

    for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
			{
				adj_matrix[i][j] = 0;
			}
	}


     for(int i=0;i<edge_count;i=i+2)
     {
	adj_matrix[edge[i]][edge[i+1]] = 1;
	adj_matrix[edge[i+1]][edge[i]] = 1;
     }
     

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "==========Adjacenry Matrix==========" << std::endl;

    std::cout << "X|";
    for(int i=0;i<node_count;i++)
	{
	
	    std::cout <<node[i]<<"|";

	}
    std::cout << std::endl;
	

    for(int i=0;i<node_count;i++)
	{
		std::cout <<node[i]<<"|";
		for(int j=0;j<node_count;j++)
			{
				std::cout << adj_matrix[i][j]<<"|" ;
			}
		std::cout << std::endl;
	}



    //VETOR ORDER
    
    int node_order[100];
    for(int i=0;i<node_count;i++)
	{
		node_order[i] = 0;
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "==========Node Order==========" << std::endl;

    for(int i=0;i<node_count;i++)
	{
		for(int j=0;j<node_count;j++)
			{
				node_order[i] += adj_matrix[i][j];
			}
		std::cout << "Node " <<node[i]<<" Order = " <<node_order[i]<< std::endl;
	}

    int node_ODD[100];
	int ODD_count = 0;
    for(int i=0;i<node_count;i++)
	{
		if(node_order[i]%2 == 1)
			{
				node_ODD[ODD_count] = i;
				ODD_count += 1;
			}
			
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "==========Odd Node==========" << std::endl;


    for(int i=0;i<ODD_count;i++)
	{

		std::cout << "Node  " <<node[node_ODD[i]]<< std::endl;

	}
	std::cout << "ODD count = " <<ODD_count<< std::endl;



	//SSS(adj_matrix,node_count, node_ODD[0], node_ODD[1]);
	SSS(adj_matrix,node_count, 0, 3);









    return 0;
}


void SSS(int ADJ_Matrix[100][100],int n, int Start_point, int End_point) 
{ 
  
    int i, u, j, count; 
    int dist[n]; 
    int Done[n] = { 0 }; 
    int pathlength[n] = { 0 }; 
    int Last[n]; 
  
    Last[Start_point] = -1; 
  
    for (i = 0; i < n; i++) 
        dist[i] = 999; 
  
    dist[Start_point] = 0; 
    for (count = 0; count < n - 1; count++) { 
        u = MinPath(dist, Done,n); 
  
        if (u == 999) 
            break; 
        else { 
  
         
            Done[u] = 1; 
            for (j = 0; j < n; j++) { 
                if (!Done[j] && ADJ_Matrix[u][j] 
                    && dist[u] + ADJ_Matrix[u][j] < dist[j]) { 
                    Last[j] = u; 
                    pathlength[j] = pathlength[Last[j]] + 1; 
                    dist[j] = dist[u] + ADJ_Matrix[u][j]; 
                } 
                else if (!Done[j] && ADJ_Matrix[u][j] 
                         && dist[u] + ADJ_Matrix[u][j] == dist[j] 
                         && pathlength[u] + 1 < pathlength[j]) { 
                    Last[j] = u; 
                    pathlength[j] = pathlength[u] + 1; 
                } 
            } 
        } 
    } 
  
    if (dist[End_point] != 999) 
        PrintPath(Last, End_point); 
    else
        cout << "There is no path between vertex "
             << Start_point << "to vertex " << End_point; 
}


int MinPath(int* dist, int* Done,int n) 
{ 
    int min = 999, min_index, j; 
    for (j = 0; j < n; j++) 
        if (!Done[j] && dist[j] < min) { 
            min = dist[j]; 
            min_index = j; 
        } 
    return (min == 999) ? 999 : min_index; 
} 


 void PrintPath(int* Last, int End_point) 
{ 
    if (Last[End_point] == -1) { 
        cout << End_point; 
        return; 
    } 
    PrintPath(Last, Last[End_point]); 
    cout << "->" << End_point; 
} 
