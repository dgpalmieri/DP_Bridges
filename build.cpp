// build.cpp
// Dylan Palmieri
// 2020-11-14
// Dynamic Programming solution for the bridge problem from Homework 2

#include<algorithm>
#include<vector>
#include "build.hpp"

int bridges_recurse( const size_t & west, const size_t & east,
                     std::vector< std::vector< int > > bridges,
                     std::vector< int > & solved ){
    // Base case
    if ( bridges.size() == 1 && bridges[ 0 ].size() == 1 )
        return bridges[ 0 ][ 2 ];
}

int build( const size_t & west, const size_t & east,
           std::vector< std::vector< int > > bridges ){
    if ( bridges.empty() )
        return 0;
    std::sort( bridges.begin(), bridges.end() );
    std::vector<int> solved( bridges.size(), 0 );

    return bridges_recurse( west, east, bridges, solved );
}
