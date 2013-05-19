#include <vector>

template< typename T >
bool Interleave(std::vector<T> First, int FirstCount, std::vector<T> Second, int SecondCount, std::vector<T>& out) {
	if( First.size() * SecondCount != Second.size() * FirstCount
		|| First.size() % FirstCount != 0
		|| Second.size() %SecondCount != 0
	)
		return false;

	out.clear();
	int Items = First.size() / FirstCount;
	for( int i = 0; i < Items; ++i ) {
		out.insert( out.end(), First.begin() + i * FirstCount, First.begin() + (i+1) * FirstCount);
		out.insert( out.end(), Second.begin() + i * SecondCount, Second.begin() + (i+1) * SecondCount);
	}
	return true;
}
