#include <iostream>
#include "IGraph.h"
#include "CMatrixGraph.h"
#include "CListGraph.h"
#include "CArcGraph.h"
#include "CSetGraph.h"

int main()
{

    CListGraph *Listgraph = new CListGraph(5);
    Listgraph->AddEdge(0, 5);
    Listgraph->AddEdge(1, 6);
    Listgraph->AddEdge(2, 7);
    Listgraph->AddEdge(3, 8);
    Listgraph->AddEdge(4, 9);

    std::cout<< "\n------------------------LIST------------------\n";
    CListGraph secondListgraph(Listgraph);

    for( int i = 0; i < Listgraph->VerticesCount(); ++i){
    	for (int v : Listgraph->GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }

    std::cout << "\nCopy: ";
    for( int i = 0; i < secondListgraph.VerticesCount(); ++i){
    	for (int v : secondListgraph.GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }


    CArcGraph *Arcgraph = new CArcGraph(5);
    Arcgraph->AddEdge(0, 5);
    Arcgraph->AddEdge(1, 6);
    Arcgraph->AddEdge(2, 7);
    Arcgraph->AddEdge(3, 8);
    Arcgraph->AddEdge(4, 9);

    std::cout<< "\n------------------------ARC------------------\n";
    CArcGraph secondArcgraph(Arcgraph);
 
    for( int i = 0; i < Arcgraph->VerticesCount(); ++i){
    	for (int v : Arcgraph->GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }

    std::cout << "\nCopy: ";
    for( int i = 0; i < secondArcgraph.VerticesCount(); ++i){
    	for (int v : secondArcgraph.GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }

    CMatrixGraph *Matrixgraph = new CMatrixGraph(5);
    Matrixgraph->AddEdge(0, 4);
   	Matrixgraph->AddEdge(1, 3);
   	Matrixgraph->AddEdge(2, 2);
    Matrixgraph->AddEdge(3, 1);
    Matrixgraph->AddEdge(4, 0);
    std::cout << "\n";

    std::cout<< "\n------------------------MATRIX------------------\n";
    CMatrixGraph secondMatrixgraph(Matrixgraph);
 
    for( int i = 0; i < Matrixgraph->VerticesCount(); ++i){
    	for (int v : Matrixgraph->GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }

    std::cout << "\nCopy: ";
    for( int i = 0; i < secondMatrixgraph.VerticesCount(); ++i){
    	for (int v : secondMatrixgraph.GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }



    CSetGraph *Setgraph = new CSetGraph(5);
    Setgraph->AddEdge(0, 4);
   	Setgraph->AddEdge(1, 3);
   	Setgraph->AddEdge(2, 2);
    Setgraph->AddEdge(3, 1);
    Setgraph->AddEdge(4, 0);


    std::cout<< "\n------------------------SET------------------\n";
    CSetGraph secondSetgraph(Setgraph);
 
    for( int i = 0; i < Setgraph->VerticesCount(); ++i){
    	for (int v : Setgraph->GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }

    std::cout << "\nCopy: ";
    for( int i = 0; i < secondSetgraph.VerticesCount(); ++i){
    	for (int v : secondSetgraph.GetNextVertices(i)) {
        	std::cout << v << " ";
    	}	
    }



	return 0;
}