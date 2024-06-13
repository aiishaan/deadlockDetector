/// this is the ONLY file you should edit and submit to D2L
//CPSC 457 assignment 3 part 1, submitted by Aishan Irfan (30157743)

//header files and includes
#include "deadlock_detector.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <iostream>


/// ----------------------------------------------------------------
/// split(s) splits string s into vector of strings (words)
/// the delimiters are 1 or more whitespaces
static std::vector<std::string> split(const std::string & s)
{
    auto linec = s + " ";
    std::vector<std::string> res;
    bool in_str = false;
    std::string curr_word = "";
    for (auto c : linec) {
        if (isspace(c)) {
            if (in_str)
                res.push_back(curr_word);
            in_str = false;
            curr_word = "";
        } else {
            curr_word.push_back(c);
            in_str = true;
        }
    }
    return res; 
}

//declaring the graph
class Graph {
public:
    //unordered map for the adjecency list
    std::unordered_map<std::string, std::vector<std::string>> adj_list;
    //unordered map for the out counts
    std::unordered_map<std::string, int> out_counts;
};

/// this is the function you need to (re)implement
/// -------------------------------------------------------------------------
/// parameter edges[] contains a list of request- and assignment- edges
///   example of a request edge, process "p1" resource "r1"
///     "p1 -> r1"
///   example of an assignment edge, process "XYz" resource "XYz"
///     "XYz <- XYz"
///
/// You need to process edges[] one edge at a time, and run a deadlock
/// detection after each edge. As soon as you detect a deadlock, your function
/// needs to stop processing edges and return an instance of Result structure
/// with 'index' set to the index that caused the deadlock, and 'procs' set
/// to contain names of processes that are in the deadlock.
///
/// To indicate no deadlock was detected after processing all edges, you must
/// return Result with index=-1 and empty procs.


// Main function to detect deadlock
Result detect_deadlock(const std::vector<std::string> &edges) {
    //initializing the result struct.
    Result result;
    result.edge_index = -1;
    //initializing the graph
    Graph graph;
    //vector to store the split strings
    std::vector<std::string> e;
    //unordered sets for the resources and the processes
    std::unordered_set<std::string> pSet;
    std::unordered_set<std::string> rSet;
    //for loop to go through each edge and add that to the graph
    for(int i =0; i < static_cast<int>(edges.size()); i++){
        //adding the the nodes to e
        e = split(edges[i]);
        //adding the nodes to the resources and processes set
        pSet.insert(e[0]);
        rSet.insert(e[2]);
        //if a duplicate processes or resource exists, add a symbol to differentiate it.
        if(pSet.find(e[2]) != pSet.end()){
            e[2] = e[2]+"$";
        }
        if(rSet.find(e[0])!= rSet.end()){
            e[0] = e[0]+"#";
        }

        //inserts the key with a default-constructed value if it doesn't exist
        graph.out_counts[e[0]];
        graph.out_counts[e[2]];

        if(e[1] == "->"){
            
            //adding the nodes that point towards the current node e[2] in the adjecency list
            graph.adj_list[e[2]].emplace_back(e[0]);
            //updating the out counts
            graph.out_counts[e[0]]+=1;
            
        }

        else {
            
            //adding the nodes that point towards the current node e[0] in the adjecency list
            graph.adj_list[e[0]].emplace_back(e[2]);
            //updating the out counts
            graph.out_counts[e[2]]+=1;
            
        }

        //copying the out counts map onto out
        std::unordered_map<std::string, int> out = graph.out_counts;
        //initializing zeroes vector
        std::vector<std::string> zeros;

        //going through the out map
        for(const auto& node : out){
            //if the out count of the current node is 0, adding that node to the zeroes vector
            if(node.second == 0){
                zeros.emplace_back(node.first);
            }
        }

        //toposort
        while(!zeros.empty()){
            //remove one entry from zeroes.
            std::string n = zeros.back();
            zeros.pop_back();
            //going through the nodes in the adjecency list
            for(std::string n2: graph.adj_list[n]){
                //decreasing the out count of the current node
                out[n2]--;
                //adding the node back to zeroes if the out count is zero
                if(out[n2]==0){
                    zeros.emplace_back(n2);
                }
            }
        }

        //going through the out mapo
        for(const auto& node : out){
            //adding the node to dl_procs if its a robot (process) and has out count > 0
            if(node.second > 0){
                if( pSet.find(node.first) != pSet.end()){
                    result.dl_procs.emplace_back(node.first);
                }
            }
        }

        
        //at the end of the loop, updating the result index and returning the result if dl_procs is not empty
        if(!result.dl_procs.empty()){
            result.edge_index = i;
            return result;
        }

    }
    
    //returning the result otherwise
    return result;

}