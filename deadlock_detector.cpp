// this is the ONLY file you should edit and submit to D2L

#include "deadlock_detector.h"
#include "common.h"
#include <iostream>

/// this is the function you need to (re)implement
///
/// parameter edges[] contains a list of request- and assignment- edges
///   example of a request edge, process "p1" resource "r1"
///     "p1 -> r1"
///   example of an assignment edge, process "XYz" resource "XYz"
///     "XYz <- XYz"
///
/// You need to process edges[] one edge at a time, and run a deadlock
/// detection after each edge. As soon as you detect a deadlock, your function
/// needs to stop processing edges and return an instance of Result structure
/// with edge_index set to the index that caused the deadlock, and dl_procs set
/// to contain with names of processes that are in the deadlock.
///
/// To indicate no deadlock was detected after processing all edges, you must
/// return Result with edge_index = -1 and empty dl_procs[].
///

struct FastGraph {
    std::vector<std::vector<int>> adj_list;
    std::vector<int> out_counts;
} ;
Result detect_deadlock(const std::vector<std::string> & edges)
{
    // let's try to guess the results :)
    Result result;
    FastGraph graph;
    Word2Int conversion;
    std::vector<std::string> int2word;
  
    for(int i =0; i<(int)edges.size();i++){
        std::vector<std::string> splitted_tokens;
        splitted_tokens = split(edges.at(i));
        splitted_tokens.at(0).append("#");
        int n1 = conversion.get(splitted_tokens.at(0));
        int n2 = conversion.get(splitted_tokens.at(2));
        int n3 = std::max(n2,n1);

        
        if((long)graph.adj_list.size()<n3+1){
           
            graph.out_counts.resize(n3+1);
            graph.adj_list.resize(n3+1);
            int2word.resize(n3+1);
            int2word.at(n1) = splitted_tokens.at(0);
            int2word.at(n2) = splitted_tokens.at(2);
        }
        
        if(splitted_tokens.at(1).compare("->")==0){
            graph.adj_list.at(n2).push_back(n1);
            graph.out_counts.at(n1)++;

        }else{
            graph.adj_list.at(n1).push_back(n2);
            graph.out_counts.at(n2)++;              
        }
        std::vector<int> out = graph.out_counts;
        std::vector<int> zeros;
        for(int i=0; i<(long)out.size();i++){
            if(out.at(i)==0) zeros.push_back(i);
        }
        while(!zeros.empty()){ 
            int n = zeros.back();
            zeros.pop_back();
            for( auto & node : graph.adj_list.at(n) ){
                out.at(node)--;
                if(out.at(node)==0) zeros.push_back(node);
            }
        }
        for(int i=0; i<(long)out.size();i++){
            if(out.at(i)>0 && int2word.at(i).back()=='#'){
                std::string process = int2word.at(i);
                process.resize(process.size()-1);
                result.dl_procs.push_back(process);
            }
        }
        if(!result.dl_procs.empty()){
            result.edge_index = i;
            return result;
        }
     
    }
    result.edge_index = -1;
    return result;
}
