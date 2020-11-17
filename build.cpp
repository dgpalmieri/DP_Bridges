// build.cpp
// Dylan Palmieri
// 2020-11-14
// Dynamic Programming solution for the bridge problem from Homework 2

#include<algorithm> // for std::sort, std::max
#include<vector>    // for std::vector
#include<utility>   // for std::pair
#include<tuple>     // for std::forware_as_tuple
#include "build.hpp"

#include<iostream>
using std::cout;
using std::endl;

using Bridge = std::vector< int >;

int bridges_recurse( const int & index, const std::vector< Bridge > & bridges,
                     std::vector< int > & memo,
                     const std::pair< int, int > & nextAvailibleCities ){
    if ( index >= bridges.size() )
        return 0;

    int maxToll = 0;
    auto cities = std::make_pair( bridges[ index ][ 0 ],
                                  bridges[ index ][ 1 ] );

    if ( cities.first >= nextAvailibleCities.first &&
         cities.second >= nextAvailibleCities.second ){
        if (memo[ index ] != 0)
            maxToll = memo[ index ];
        else {
            auto temp = bridges[ index ][ 2 ] +
                        bridges_recurse( index+1, bridges, memo,
                                         { cities.first+1, cities.second+1 } );
            maxToll = std::max( temp, maxToll );
            memo[ index ] = maxToll;
        }
    }

    auto temp = bridges_recurse( index+1, bridges, memo,
                                 { nextAvailibleCities.first, nextAvailibleCities.second } );
    maxToll = std::max( temp, maxToll );

    return maxToll;
}

void sort_bridges( std::vector< Bridge > & bridges ){
    std::sort( bridges.begin(), bridges.end(),
               []( const Bridge & a, const Bridge & b ){
        return std::forward_as_tuple(a[0], a[1], -a[2]) <
               std::forward_as_tuple(b[0], b[1], -b[2]);
            } );

    int west = -1, east = -1;

    auto it = std::remove_if(bridges.begin(), bridges.end(),
        [&](const auto & bridge)
        {
            auto value = bridge[0] == west && bridge[1] == east;
            west = bridge[0];
            east = bridge[1];
            return value;
        });

    bridges.erase(it, bridges.end());
}

int build( const size_t & west, const size_t & east,
           std::vector< Bridge > bridges ){
    if ( bridges.empty() ){
        return 0;
    }

    sort_bridges( bridges );

    std::vector<int> memo( bridges.size(), 0 );

    return bridges_recurse( 0, bridges, memo, { -1, -1 } );
}
