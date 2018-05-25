#include <cstdlib>
#include <cstdio>

#include <string>
#include <iostream>

using namespace std;

using u64 = uint64_t;
using byte = uint8_t;

constexpr u64 BUFFER_SIZE = 1 << 24;
constexpr bool verbose = true;

int main(int argc, const char* argv[])
{
  if (argc < 3)
    std::cout << "\tConcatenate files." << std::endl << "\tUsage: concat outfile infiles..." << std::endl;
  
  byte* buffer = new byte[BUFFER_SIZE];
  FILE* out = fopen(argv[1], "wb");
  u64 total = 0;
  
  if (buffer && out)
  {
    for (int i = 1 + 1; i < argc; ++i)
    {
      FILE* in = fopen(argv[i], "rb");
      
      if (in)
      {
        while (true)
        {
          u64 count = fread(buffer, 1, BUFFER_SIZE, in);
        
          if (count == 0)
            break;
          
          total += count;
          fwrite(buffer, 1, count, out);
        }
        
        fclose(in);
      }

    }
    
    if (verbose)
      std::cout << "Written " << total << " bytes." << std::endl;
  }

  delete [] buffer;
  fclose(out);
  
  return 0;
}