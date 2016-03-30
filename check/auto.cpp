
#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

template< typename Container >
int count_zeros( Container c )
{
    int count = 0;

    for( auto it = c.begin( ); it != c.end( ); ++it ) {
        if( *it == 0 ) ++count;
    }
    return count;
}

int main( )
{
    auto i = 0L;

    // C++ 2011 allows natural initialization of sequence containers.
    // std::vector<int> vec = { 0, 1, 2, 3, 0 };
    // std::list<int> lst = { 1, 2, 3, 4, 5 };

    int initial_data1[] = { 0, 1, 2, 3, 0 };
    int initial_data2[] = { 1, 2, 3, 4, 5 };
    std::vector<int> vec( initial_data1, initial_data1 + 5 );
    std::list<int> lst( initial_data2, initial_data2 + 5 );


    // for( std::vector<int>::iterator it = vec.begin( ); it != vec.end( ); ++it ) { ...
    for( auto it = vec.begin( ); it != vec.end( ); ++it ) {
        std::cout << *it << "\n";
    }

    auto p = new std::vector<int>;
    delete p;

    std::cout << "Zeros in vector: " << count_zeros( vec ) << "\n";
    std::cout << "Zeros in list: " << count_zeros( lst ) << "\n";
    return EXIT_SUCCESS;
}
