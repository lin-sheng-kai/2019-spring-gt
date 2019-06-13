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


void SSS(int ADJ_Matrix[10][10],int n, int Start_point, int End_point, int path[]); 
int MinPath(int* dist, int* Done,int n) ; 
 void PrintPath(int* Last, int End_point ,int path[],int l); 


int main(int argc, char** argv){

    /* start your program */
    


    string node[10];
    int edge[10];


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
    int adj_matrix[10][10];

    for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
			{
				adj_matrix[i][j] = 0;
			}
	}


     for(int i=0;i<edge_count;i=i+2)
     {
		adj_matrix[edge[i]][edge[i+1]] += 1;
		adj_matrix[edge[i+1]][edge[i]] += 1;
     }
     

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "==========Adjacency Matrix==========" << std::endl;

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
    
    int node_order[10];
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

    int node_ODD[10];
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

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "==========Odd Node Path==========" << std::endl;

	int path[10];
	int path_length[10];

	int node_path_route[10][10];


	
	for(int i=0;i<ODD_count;i++)
	{
		for(int j=i+1;j<ODD_count;j++)
			{	

				for(int m=0;m<10;m++)
					path[m] = 999;
				for(int n=0;n<10;n++)
					path_length[n] = 0;


				std::cout << "Node ["<<node[node_ODD[i]]<<"] to "<< "Node ["<<node[node_ODD[j]]<<"] :" ;
				SSS(adj_matrix,node_count, node_ODD[i], node_ODD[j],path);

					int LEN =0;
				//std::cout <<node_ODD[i]<<"---";
					for (int p = 0; p < 10; p++)
					{
   	   					 if (path[p] != 999)
	   					LEN++;
					}
					path[LEN] = node_ODD[i];
				
				for(int k=9;k>-1;k--)
				{
					if(path[k] == 999)
					{
						//std::cout << std::endl;
						//break;
					}
					else if (path[k] == node_ODD[j])
					{
						std::cout <<path[k];
						std::cout << std::endl;

						path_length[j] += 1;

						std::cout << "path_length ["<<node[node_ODD[i]]<<"_to_"<<node[node_ODD[j]]<<"] :" ;
						std::cout <<path_length[i];
						std::cout << std::endl;	
						std::cout << std::endl;			

					}

					else 
					{
						std::cout <<path[k]<<"---";
						path_length[i] += 1;
					}

				}

			}

	}



	if(ODD_count == 0)
	{
		
	}
	else if(ODD_count == 2)
	{
		for (int i =  0; i < 1 ;i++)  // update adj matrix
    	{
			adj_matrix[path[i]][path[i+1]]++;
			adj_matrix[path[i+1]][path[i]]++;

			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "==========Adjacency Matrix==========" << std::endl;

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
			}

	}
	else if(ODD_count == 4)
	{

	}
	else if(ODD_count == 6)
	{

	}
	else if(ODD_count == 8)
	{

	}
	else if(ODD_count == 10)
	{
	
	}








    return 0;
}


void SSS(int ADJ_Matrix[10][10],int n, int Start_point, int End_point, int path[]) 
{ 
  
    int i, u, j, count; 
	int l = -1;
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
        PrintPath(Last, End_point,path,l); 
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


 void PrintPath(int* Last, int End_point ,int path[],int l) 
{ 
    if (Last[End_point] == -1) { 
        //cout << End_point; 
		path[l] = End_point;
        return; 
    } 
	l++;
    PrintPath(Last, Last[End_point],path,l); 
    //cout << "---" << End_point; 
	path[l] = End_point;
} 

