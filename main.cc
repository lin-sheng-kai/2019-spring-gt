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
#include <vector>
#include <stdlib.h>
#include <string.h>
using namespace std;

vector<string> outpath;
int ok;



// create NetworkManager first
NetworkManager *nm = new NetworkManager();


void SSS(int ADJ_Matrix[10][10],int n, int Start_point, int End_point, int path[]); 
int MinPath(int* dist, int* Done,int n) ; 
void PrintPath(int* Last, int End_point ,int path[],int l); 
void DFS (int s, int len, int visit[], int adj[][10], string names[], int size);
void SPPC(int NPR[][10],int node_ODD[],int ODD_count,int &V1,int &V2,int &V3,int &V4,int &V5,int &V6,int &V7,int &V8,int &V9,int &V10);


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
	int node_path_walk[100][10];

	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
			{	
				node_path_route[i][j] = 99;
			}
	}
					
	for(int i=0;i<100;i++)
	{
		for(int j=0;j<10;j++)
			{	

						node_path_walk[i][j] = -1;

			}
	}




	
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
					int L_start = 0;

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

						}
						else if (path[k] == node_ODD[j])
						{
							std::cout <<path[k];
							std::cout << std::endl;
							node_path_walk[node_ODD[i]*10+node_ODD[j]][L_start] = path[k];
							
				
							L_start ++;
						

							std::cout << "path_length ["<<node[node_ODD[i]]<<"_to_"<<node[node_ODD[j]]<<"] :" ;
							std::cout <<path_length[i];
							std::cout << std::endl;	
							std::cout << std::endl;	
							node_path_route[node_ODD[i]][node_ODD[j]] = path_length[i];	
							node_path_route[node_ODD[j]][node_ODD[i]] = path_length[i];		

						}

						else 
						{

							std::cout <<path[k]<<"---";
							path_length[i] += 1;
							node_path_walk[node_ODD[i]*10+node_ODD[j]][L_start] = path[k];
							
			
							L_start ++;
						}

				}

			}

	}








			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "==========node_path_route==========" << std::endl;

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
						std::cout << node_path_route[i][j]<<"|" ;
					}
					std::cout << std::endl;
				}











int x1=11;
int x2=11;
int x3=11;
int x4=11;
int x5=11;
int x6=11;
int x7=11;
int x8=11;
int x9=11;
int x10=11;
int LL=999;


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
		
		SPPC( node_path_route, node_ODD, ODD_count, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10);


		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x1*10+x2][m+1] == -1)
				break;

			std::cout << node_path_walk[x1*10+x2][m]<< std::endl;
			std::cout << node_path_walk[x1*10+x2][m+1]<< std::endl;

			adj_matrix[node_path_walk[x1*10+x2][m]][node_path_walk[x1*10+x2][m+1]]++;
			adj_matrix[node_path_walk[x1*10+x2][m+1]][node_path_walk[x1*10+x2][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x3*10+x4][m+1] == -1)
				break;

			std::cout << node_path_walk[x3*10+x4][m]<< std::endl;
			std::cout << node_path_walk[x3*10+x4][m+1]<< std::endl;

			adj_matrix[node_path_walk[x3*10+x4][m]][node_path_walk[x3*10+x4][m+1]]++;
			adj_matrix[node_path_walk[x3*10+x4][m+1]][node_path_walk[x3*10+x4][m]]++;

		}



	}
	else if(ODD_count == 6)
	{
		SPPC( node_path_route, node_ODD, ODD_count, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10);


		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x1*10+x2][m+1] == -1)
				break;

			std::cout << node_path_walk[x1*10+x2][m]<< std::endl;
			std::cout << node_path_walk[x1*10+x2][m+1]<< std::endl;

			adj_matrix[node_path_walk[x1*10+x2][m]][node_path_walk[x1*10+x2][m+1]]++;
			adj_matrix[node_path_walk[x1*10+x2][m+1]][node_path_walk[x1*10+x2][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x3*10+x4][m+1] == -1)
				break;

			std::cout << node_path_walk[x3*10+x4][m]<< std::endl;
			std::cout << node_path_walk[x3*10+x4][m+1]<< std::endl;

			adj_matrix[node_path_walk[x3*10+x4][m]][node_path_walk[x3*10+x4][m+1]]++;
			adj_matrix[node_path_walk[x3*10+x4][m+1]][node_path_walk[x3*10+x4][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x5*10+x6][m+1] == -1)
				break;

			std::cout << node_path_walk[x5*10+x6][m]<< std::endl;
			std::cout << node_path_walk[x5*10+x6][m+1]<< std::endl;

			adj_matrix[node_path_walk[x5*10+x6][m]][node_path_walk[x5*10+x6][m+1]]++;
			adj_matrix[node_path_walk[x5*10+x6][m+1]][node_path_walk[x5*10+x6][m]]++;

		}

	}
	else if(ODD_count == 8)
	{

		SPPC( node_path_route, node_ODD, ODD_count, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10);


		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x1*10+x2][m+1] == -1)
				break;

			std::cout << node_path_walk[x1*10+x2][m]<< std::endl;
			std::cout << node_path_walk[x1*10+x2][m+1]<< std::endl;

			adj_matrix[node_path_walk[x1*10+x2][m]][node_path_walk[x1*10+x2][m+1]]++;
			adj_matrix[node_path_walk[x1*10+x2][m+1]][node_path_walk[x1*10+x2][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x3*10+x4][m+1] == -1)
				break;

			std::cout << node_path_walk[x3*10+x4][m]<< std::endl;
			std::cout << node_path_walk[x3*10+x4][m+1]<< std::endl;

			adj_matrix[node_path_walk[x3*10+x4][m]][node_path_walk[x3*10+x4][m+1]]++;
			adj_matrix[node_path_walk[x3*10+x4][m+1]][node_path_walk[x3*10+x4][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x5*10+x6][m+1] == -1)
				break;

			std::cout << node_path_walk[x5*10+x6][m]<< std::endl;
			std::cout << node_path_walk[x5*10+x6][m+1]<< std::endl;

			adj_matrix[node_path_walk[x5*10+x6][m]][node_path_walk[x5*10+x6][m+1]]++;
			adj_matrix[node_path_walk[x5*10+x6][m+1]][node_path_walk[x5*10+x6][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x7*10+x8][m+1] == -1)
				break;

			std::cout << node_path_walk[x7*10+x8][m]<< std::endl;
			std::cout << node_path_walk[x7*10+x8][m+1]<< std::endl;

			adj_matrix[node_path_walk[x7*10+x8][m]][node_path_walk[x7*10+x8][m+1]]++;
			adj_matrix[node_path_walk[x7*10+x8][m+1]][node_path_walk[x7*10+x8][m]]++;

		}

	}
	else if(ODD_count == 10)
	{

		SPPC( node_path_route, node_ODD, ODD_count, x1, x2, x3, x4, x5, x6, x7, x8, x9, x10);


		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x1*10+x2][m+1] == -1)
				break;

			std::cout << node_path_walk[x1*10+x2][m]<< std::endl;
			std::cout << node_path_walk[x1*10+x2][m+1]<< std::endl;

			adj_matrix[node_path_walk[x1*10+x2][m]][node_path_walk[x1*10+x2][m+1]]++;
			adj_matrix[node_path_walk[x1*10+x2][m+1]][node_path_walk[x1*10+x2][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x3*10+x4][m+1] == -1)
				break;

			std::cout << node_path_walk[x3*10+x4][m]<< std::endl;
			std::cout << node_path_walk[x3*10+x4][m+1]<< std::endl;

			adj_matrix[node_path_walk[x3*10+x4][m]][node_path_walk[x3*10+x4][m+1]]++;
			adj_matrix[node_path_walk[x3*10+x4][m+1]][node_path_walk[x3*10+x4][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x5*10+x6][m+1] == -1)
				break;

			std::cout << node_path_walk[x5*10+x6][m]<< std::endl;
			std::cout << node_path_walk[x5*10+x6][m+1]<< std::endl;

			adj_matrix[node_path_walk[x5*10+x6][m]][node_path_walk[x5*10+x6][m+1]]++;
			adj_matrix[node_path_walk[x5*10+x6][m+1]][node_path_walk[x5*10+x6][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x7*10+x8][m+1] == -1)
				break;

			std::cout << node_path_walk[x7*10+x8][m]<< std::endl;
			std::cout << node_path_walk[x7*10+x8][m+1]<< std::endl;

			adj_matrix[node_path_walk[x7*10+x8][m]][node_path_walk[x7*10+x8][m+1]]++;
			adj_matrix[node_path_walk[x7*10+x8][m+1]][node_path_walk[x7*10+x8][m]]++;

		}

		for(int m=0;m<10;m++)
		{

			if (node_path_walk[x7*10+x8][m+1] == -1)
				break;

			std::cout << node_path_walk[x9*10+x10][m]<< std::endl;
			std::cout << node_path_walk[x9*10+x10][m+1]<< std::endl;

			adj_matrix[node_path_walk[x9*10+x10][m]][node_path_walk[x9*10+x10][m+1]]++;
			adj_matrix[node_path_walk[x9*10+x10][m+1]][node_path_walk[x9*10+x10][m]]++;

		}


	}























			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << "==========NEW Adjacency Matrix==========" << std::endl;

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








    int array_dfs[10];
	int names_vector[10];
for (int i = 0; i < 10; i++)
    {
	array_dfs[i] = 0;
    for (int j = 0; j < 10; j++)
    {
	
	array_dfs[i] = array_dfs[i] + adj_matrix[i][j];
	
}

}
//----------------------------------DFS-----------------------------//
	
int visit[10];
//vector<string> outpath;
int l = 0;
   

    for(int i=0;i<10;i++)
	{
	    names_vector[i]=0;
	    visit[i] = (array_dfs[i]/2);
	    names_vector[i]=i;
        //visited[i]=degree;

	} 

    for(int i=0;i<10;i++)
	{
    		visit[0]++;
    
	}

    for(int i = 0; i < 10; i++)    
   	{
		for(int j = 0; j < 10; j++)
		{
			l = l + adj_matrix[i][j];

		}
	}

	int length_line = 0;
	length_line = l/2;


    cout << "Total Path Length : " << length_line << endl;
	cout <<  endl;
	cout <<  endl;

	cout << "THE ANSWER IS : ";
    DFS(0, length_line, visit, adj_matrix, node,  10);

	cout <<  endl;







	stdout = fopen("RESULT.txt", "w");  // write file

	cout << "a" << " ";
	fprintf(stdout,"a");
	fprintf(stdout," ");

	char result[100];

    for(int i = 0; i < outpath.size(); i++)
    {	

		cout << outpath[i] << " ";
		fprintf(stdout, outpath[i].c_str());
		fprintf(stdout," ");
	
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

void DFS (int s, int len, int visit[], int adj[][10], string names[], int size)
{
	ok = 0;
	visit[s] = visit[s] - 1 ;
	for(int i = 0; i < size; i++)
	{
		if ((adj[s][i] != 0) && (visit[i] != 0))
		{
			adj[s][i]--;
			adj[i][s]--;
			
			outpath.push_back(names[i]);

			len--;
			
			if (len > 0)
			{
				DFS(i, len, visit, adj, names, size);
				
			}
			else if (i == 0)
			{
				ok = 1;
				return;
			}
			
			if (ok == 1)  return;
			
			len++;
			visit[i]++;
			outpath.pop_back();
			adj[s][i]++;
			adj[i][s]++;
		}	
	}
}






void SPPC(int NPR[][10],int node_ODD[],int ODD_count,int &V1,int &V2,int &V3,int &V4,int &V5,int &V6,int &V7,int &V8,int &V9,int &V10)
{
	int L_re =999;

	int x1=11;
	int x2=11;
	int x3=11;
	int x4=11;
	int x5=11;
	int x6=11;
	int x7=11;
	int x8=11;
	int x9=11;
	int x10=11;

	for(int a=0;a<ODD_count;a++)
	{

		
	for(int b=0;b<ODD_count;b++)//2
	{	

		if ((b==a)) continue;
		
		if (ODD_count == 2)
		{
			

			x1=a;
			x2=b;
			
			L_re = NPR[node_ODD[a]][node_ODD[b]];

			break;
			
		}
		
	for(int c=0;c<ODD_count;c++)
	{

		if ((c==a)||(c==b)) continue;	
				
	for(int d=0;d<ODD_count;d++)//4
	{

		if ((d==a)||(d==b)||(d==c)) continue;	
					
		if (ODD_count == 4)
		{

			if ((NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]) < L_re)
			{

				x1=a;
				x2=b;
				x3=c;
				x4=d;
				
				L_re = (NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]);
			}
			
		break;
			
		}		
					
	for(int e=0;e<ODD_count;e++)
	{

		if ((e==a)||(e==b)||(e==c)||(e==d)) continue;	
					
	for(int f=0;f<ODD_count;f++)//6
	{

		if ((f==a)||(f==b)||(f==c)||(f==d)||(f==e)) continue;	
		
		if (ODD_count == 6)
		{
			
			if ((NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]+NPR[node_ODD[e]][node_ODD[f]]) < L_re)
			{
				
				x1=a;
				x2=b;
				x3=c;
				x4=d;
				x5=e;
				x6=f;
				
				L_re = (NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]+NPR[node_ODD[e]][node_ODD[f]]);
			}
			
		break;
			
		}
					
	for(int g=0;g<ODD_count;g++)
	{

		if ((g==a)||(g==b)||(g==c)||(g==d)||(g==e)||(g==f)) continue;	
					
	for(int h=0;h<ODD_count;h++)//8
	{

		if ((h==a)||(h==b)||(h==c)||(h==d)||(h==e)||(h==f)||(h==g)) continue;	
				
		if (ODD_count == 8)
		{
			
			if ((NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]+NPR[node_ODD[e]][node_ODD[f]]+NPR[node_ODD[g]][node_ODD[h]]) < L_re)
			{
				
				x1=a;
				x2=b;
				x3=c;
				x4=d;
				x5=e;
				x6=f;
				x7=g;
				x8=h;
				
				L_re = (NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]+NPR[node_ODD[e]][node_ODD[f]]+NPR[node_ODD[g]][node_ODD[h]]);
			}
			
		break;
			
		}
				
	for(int i=0;i<ODD_count;i++)
	{

		if ((i==a)||(i==b)||(i==c)||(i==d)||(i==e)||(i==f)||(i==g)||(i==h)) continue;	
				
	for(int j=0;j<ODD_count;j++)//10
	{

		if ((j==a)||(j==b)||(j==c)||(j==d)||(j==e)||(j==f)||(j==g)||(j==h)||(j==i)) continue;	
			
		if (ODD_count == 10)
		{
			
			if ((NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]+NPR[node_ODD[e]][node_ODD[f]]+NPR[node_ODD[g]][node_ODD[h]]+NPR[node_ODD[i]][node_ODD[j]]) < L_re)
			{
				
				x1=a;
				x2=b;
				x3=c;
				x4=d;
				x5=e;
				x6=f;
				x7=g;
				x8=h;
				x9=i;
				x10=j;
				
				L_re = (NPR[node_ODD[a]][node_ODD[b]]+NPR[node_ODD[c]][node_ODD[d]]+NPR[node_ODD[e]][node_ODD[f]]+NPR[node_ODD[g]][node_ODD[h]]+NPR[node_ODD[i]][node_ODD[j]]);
			}
			
		break;
			
		}
			
		
	}
		
	}
		
	}
		
	}
		
	}
		
	}
		
	}
		
	}	
		
	}
		
	}
	
	int temp = -1;

	if(x1>x2)
	{
		temp = x1;
		x1 =x2;
		x2 = temp;
		
	}

	temp = -1;

	if(x3>x4)
	{
		temp = x3;
		x3 =x4;
		x4 = temp;
		
	}

	temp = -1;

	if(x5>x6)
	{
		temp = x5;
		x5 =x6;
		x6 = temp;
		
	}

	temp = -1;

	if(x7>x8)
	{
		temp = x7;
		x7 =x8;
		x8 = temp;
		
	}

	temp = -1;

	if(x9>x10)
	{
		temp = x9;
		x9 =x10;
		x10 = temp;
		
	}





	V1 = node_ODD[x1 ];
	V2 = node_ODD[x2 ];
	V3 = node_ODD[x3 ];
	V4 = node_ODD[x4 ];
	V5 = node_ODD[x5 ];
	V6 = node_ODD[x6 ];
	V7 = node_ODD[x7 ];
	V8 = node_ODD[x8 ];
	V9 = node_ODD[x9 ];
	V10= node_ODD[x10];
	
	
	
	cout<< endl;	
	cout<< endl;
	cout << "==========Shotest Pair Path Comparator==========" << endl;	
	cout << "ODD_count = " << ODD_count << endl;
	cout << "Need " << ODD_count/2 << " path" << endl;	

	if (ODD_count >= 2)
		cout<<"Path1 : "<<V1<< "---" << V2 << endl;
	if (ODD_count >= 4)                 
		cout<<"Path2 : "<<V3<< "---" << V4 << endl;
	if (ODD_count >= 6)                 
		cout<<"Path3 : "<<V5<< "---" << V6 << endl;
	if (ODD_count >= 8)                 
		cout<<"Path4 : "<<V7<< "---" << V8 << endl;
	if (ODD_count >= 10)                
		cout<<"Path5 : "<<V9<< "---" << V10 << endl;

	cout<<"Total Length = "<<L_re << endl;

}
