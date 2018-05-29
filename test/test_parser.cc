#define PARSER_TEST_MODULE
#include "Parser.hpp"
#include "Vector.hpp"
#include "NN.hpp"

template <typename T>
constexpr void print_comment(T p_comment)
{
	std::cout << p_comment << "\n";
	std::cout.flush();
}

int main()
{
	const char* pos = "../../data/mnist_train.csv";

	laobject::Vector<laobject::Vector<type> > inputs(60000);
	laobject::Vector<laobject::Vector<type> > outputs(60000);

	print_comment<const char*>("Opening file...");
	print_comment<const char*>(pos);

	hand_number::fillFromFile(pos, inputs, outputs, 28, 28, 10);

	

	std::ifstream file(pos);
	unsigned line_count = 0;

	std::string line;
	while(std::getline(file,line))
		++line_count;

	std::cout<<"Line count: "<<line_count<<"\n";

	return 0;	
}
