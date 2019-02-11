#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, const char *argv[])
{
  using namespace std;
  ifstream input(argv[1], ios::binary);
  if (!input.is_open())
  {
    std::cerr << "Unable to open input file: \"" << argv[1] << endl;
    exit(-1);
  }
  ofstream output(argv[2]);
  if (!output.is_open())
  {
    std::cerr << "Unable to open output file: \"" << argv[2] << endl;
    exit(-1);
  } 
  output << "static const unsigned char assetData[] = {" << endl;
  unsigned int counter = 0;
  const char bin2hexLookUp[] = "0123456789abcdef"; 
  char current;
  while (input.get(current))
  {
    if (counter == 0)
      output << "  ";
    unsigned char currentAsUnsigned = static_cast<unsigned char>(current);
    output << "0x" << bin2hexLookUp[currentAsUnsigned >> 4] 
                   << bin2hexLookUp[currentAsUnsigned & 0x0f] << ", ";
    ++counter;
    if ((counter % 10) == 0)
      output << endl << "  "; 
  }
  output << "};";
  output.close();
  input.close();
}
