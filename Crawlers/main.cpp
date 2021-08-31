#include "WatchCrawler/crawler.h"
#include <string>
#include <iostream>

using namespace SE;
using namespace std;

int main()
{
    Crawler crawler;
    crawler.traversal();
}   

// compiling string: g++ main.cpp watchcrawler/crawler.cpp ../httpclient/httpclient.cpp -lcurl ../serverside/db/db.cpp -l sqlite3

