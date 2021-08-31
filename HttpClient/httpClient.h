#include <string>

using namespace std;

namespace SE
{
   class HttpClient
   {
      public:
        string request(const char* url);
   };
}