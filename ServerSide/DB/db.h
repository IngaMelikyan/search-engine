#include <string>

using namespace std;

namespace SE
{
   class DB
    {
        public:
            bool create(string dbPath);
            bool insert(string dbPath, string title, string description);
            bool search(string dbPath, string query);
    };
}

