#include "../../ServerSide/DB/db.h"
#include "../../HttpClient/httpClient.h"
#include <string>

using namespace std;

namespace SE
{
   class Crawler: public HttpClient
   {
      private:
         DB db;
         const string dbPath = "../ServerSide/DB/watch_data.db";

         string getTitles(string html);
         string getDescriptions(string html);
         string n_trim(const string& str);
         int random(int min, int max);
         bool is_content(string html);
         bool insertToDb(string titles, string descriptions);
         
      public:
         void traversal();
        
   };
}