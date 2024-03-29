#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "./City.h"
#include "GraphIncList.h"
#include "Node.h"
#include "TreePosVector.h"
#include "TreePtrList.h"
#include "DHeap.h"
#include "GraphEdgeList.h"
#include "BasicGraph.h"
#include "Testing.h"


inline void Dijkstra(){
	/* 
    algorimo Dijkstra(grafo G,vertice s)->albero
    for(each)(vertice u in G) do Dsu <- +inf
     T = albero formato dal solo vertice s
     Dheap S
     Dss = 0
     S.insert(s,0)

     while( not S.isEmpty())do
       u = s.popValue()
       for each(arco(u,v)in G)do
            if(Dsv == inf)then
                s.insert(v,Dsu + w(u,v))
                Dsv = Dsu + w(u,w)
                rendi u padre di v in T
            else if(Dsu + w(u,v)<Dsv)then
                s.decreaseKey(v,Dsv-(Dsu-w(u,v)))
                rendi u nuovo padre di v in T
    
    return T
    */
    

	// Open the input file that contains graph data
    std::fstream input;
    input.open( "../../input_test/city_graph.txt",std::ios::in);

	// Create a graph instance for cityGraph
    GraphIncList<City> cityGraph;
	
    if(input.is_open()){
		// Read edges from the input file and add them to the graph
        while(!input.eof()){
            Edge<City> edge;
            input>>edge;
            double weight = calculateDistance(edge.getSourceValue(),edge.getDestinationValue());
            edge.setWeight(weight);
            cityGraph.addEdge(edge);
        }

		// Create a DOT file for cityGraph visualization
        std::ofstream cytyGraphdotFile("../output_test/cityGraph.dot",std::ios::out);
        cityGraph.outputDotFile(cytyGraphdotFile);
        cytyGraphdotFile.close();

		// Create a DHeap for processing nodes with the minimum distance
        DHeap<double,City> S(2,cityGraph.getNumNode(),true);

		// Initialize the minimum spanning tree
        TreePtrList<City> tree;

		// Set the source city and add it to the root of the tree
        City startValue = cityGraph.getValue({"Roma"});
        startValue.setDistance(0);
        cityGraph.setValue({"Roma"},startValue);
        tree.addRoot(startValue);
        S.insert(std::pair<double,City>(0,startValue));

		// Process vertices to find the minimum spanning tree
        while(!S.isEmpty()){
            City u = S.popValue().second;

            //get all outgoing edges from city u
            std::list<Edge<City>> edges;
            cityGraph.getOutgoingEdges(u,edges);

			// macro for  reading optimization
            #define dest e.getDestinationValue()
            #define src e.getSourceValue()

			// Process outgoing edges from the current city
            for(auto& e: edges){
                double Dsv = dest.getDistance();
                double Dsu = src.getDistance();
                double weight = e.getWeight();

                if(Dsv >= 10000){
                    Dsv = Dsu + weight;
                    S.insert(std::pair<double,City>(Dsv,dest));
                    tree.addNode(dest, src);
                    
                    //update the distance of dest
                    City newDistance = dest; 
                    newDistance.setDistance(Dsv);
                    cityGraph.setValue(dest,newDistance); 

                }else if(Dsu + weight < Dsv){
                    Dsv = Dsu + weight;
                    S.changeKey(Dsv, dest);
                    
                    //update the distance of dest
                    City newDistance = dest; 
                    newDistance.setDistance(Dsv);
                    cityGraph.setValue(dest,newDistance); 
                    tree.updateParent(dest, src);
                }
            }
        }

        // std::cout<<"spanning tree edge list: "<<tree<<std::endl;

		// Output the resulting minimum spanning tree to a DOT file
        std::ofstream dotFile("../output_test/minimum_spanning_tree.dot",std::ios::out);
        
        tree.outputDotFile(dotFile);
        dotFile.close();
        
		// Generate an image of the minimum spanning tree using graphImage function
        // uncomment the below code for generate an image of the Tree ( GraphViz needed )
        // graphImage("minimum_spanning_tree.dot","minimum_spanning_tree.png");

    }
    else
        std::cout<<"file non aperto\n";

	
	return;
}