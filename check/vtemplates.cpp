
#include <iostream>

template< typename First, typename ...Params >
void f( First first, Params... other )
{
    std::cout << first << "\n";
    f( other... );
}

template< >
void f( )
{
    return;
}

int main( )
{
    f( 1, "Hello", 3.14 );
    return 0;
}
