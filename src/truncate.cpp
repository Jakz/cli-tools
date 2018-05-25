#include <cstdlib>
#include <cstdio>

#include <string>
#include <iostream>

using namespace std;

using u64 = uint64_t;
using byte = uint8_t;

constexpr u64 BUFFER_SIZE = 1 << 24;
constexpr bool verbose = true;
constexpr bool absolute = false;

int main(int argc, const char* argv[])
{
  std::string inName = argv[1];
  u64 start = std::stoull(argv[2]);
  u64 end = std::stoull(argv[3]);
  
  size_t dot = inName.find_last_of(".");
  std::string outName = inName.substr(0, dot) + "-out." + inName.substr(dot+1);
  
  FILE* in = fopen(inName.c_str(), "rb");
  FILE* out = fopen(outName.c_str(), "wb");
  byte* buffer = new byte[BUFFER_SIZE];
  
  if (!in) { std::cerr << "Error opening input file." << std::endl; return -1; }
  if (!out) { std::cerr << "Error opening output file." << std::endl; return -1; }
  if (!buffer) { std::cerr << "Error allocating buffer." << std::endl; return -1; }
  
  if (in && out && buffer)
  {
    fseek(in, start, SEEK_SET);
    u64 progress = absolute ? (end - start) : (end);
    
    if (verbose)
      std::cout << "Extracting " << progress << " bytes." << std::endl;
    
    while (progress > 0)
    {
      u64 step = std::min(progress, BUFFER_SIZE);
      fread(buffer, 1, step, in);
      fwrite(buffer, 1, step, out);
      
      progress -= step;
    }
    
    delete [] buffer;
    fclose(in);
    fclose(out);
  }
  
  return 0;
}