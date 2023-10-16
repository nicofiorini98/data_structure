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
#include "Testing.h"


#define DIJKSTRA 1


using namespace datalib;

// output stream to print std::pair
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << p.first ;
    return os;
}

int main(){

    testTreePtrList();
    // testTreePosVector();
    // testCopyCostructor();
    // testGraphCopyCostructor();
    // testGraphEdgeList();


#if DIJKSTRA 

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
    /* Come posso rappresentare le distanze tra i nodi?
     * posso usare std::pair<int,Node<T>>
     * Devo fare una struct per inserire nell'heap le distanze tra i nodi
     */
    

    std::fstream input;
    input.open( "/home/nico/project/data_structure/input_test/city_graph.txt",std::ios::in);

    GraphIncList<City> cityGraph;
    if(input.is_open()){
        // input all the edges in the graph
        while(!input.eof()){
            Edge<City> edge;
            input>>edge;
            double weight = calculateDistance(edge.getSourceValue(),edge.getDestinationValue());
            edge.setWeight(weight);
            cityGraph.addEdge(edge);
        }

        std::ofstream cytyGraphdotFile("/home/nico/project/data_structure/output_test/cityGraph.dot",std::ios::out);
        
        cityGraph.outputDotFile(cytyGraphdotFile);
        
        cytyGraphdotFile.close();

        DHeap<double,City> S(2,cityGraph.getNumNode(),true);

        //initialization spanning tree
        TreePtrList<City> tree;

        City startValue = cityGraph.getValue({"Bolzano"});
        startValue.setDistance(0);

        //aggiorno la start city with distance 0
        cityGraph.setValue({"Bolzano"},startValue);

        tree.addRoot(startValue);
        
        S.insert(std::pair<double,City>(0,startValue));
        //aggiornare distanza da Roma->Roma Dss=0

        while(!S.isEmpty()){
            City u = S.popValue().second;

            //get all outgoing edges from city u
            std::list<Edge<City>> edges;
            cityGraph.getOutgoingEdges(u,edges);

            #define dest e.getDestinationValue()
            #define src e.getSourceValue()

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

        std::cout<<"spanning tree edge list: "<<tree<<std::endl;

        std::ofstream dotFile("/home/nico/project/data_structure/output_test/minimum_spanning_tree.dot",std::ios::out);
        
        tree.outputDotFile(dotFile);
        dotFile<<std::endl;
        dotFile.close();
        
        graphImage("minimum_spanning_tree.dot","minimum_spanning_tree.png");

    }
    else
        std::cout<<"file non aperto\n";

#endif
    return 0;
}
