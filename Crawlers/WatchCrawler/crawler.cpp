#include "crawler.h"
#include <iostream>
#include <string.h>
#ifdef _WINDOWS
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif
#include <time.h>
#include <stdlib.h>
#include <random>
#include <ctype.h>
#include <stdio.h>

using namespace SE;
using namespace std;

void Crawler::traversal()
{
   srand(time(NULL));

   string titles = "";
   string descriptions = "";
   string url;
   int x = 1;
   int y = 75;
   int r;

   // remove old SQLith storage
   remove(this->dbPath.c_str());

   // create a new SQLite storage
   this->db.create(this->dbPath);

   // traversal all URLs and add data to SQLite
   for(int i = 1; ; i ++)
   {
      // generate next url
      url = "https://www.watchcollector.com.au/buy-a-watch/results";
      url = url + to_string(x) + "-" + to_string(i * y);
      x += 75;

      // to do request
      string html = request(url.c_str());

      // output some  info about ongoing work
      cout << "get data from... " + url << endl;

      // extract data if content was recived
      if( is_content(html) )
      {
         titles += getTitles(html);
         descriptions += getDescriptions(html); 
      }

      // interrupt loop if no recived content
      else 
      {
         break;
      }

      insertToDb(titles, descriptions);

      // delay 
      r = random(2, 4);
      Sleep(r * 1000);
   }
  
}

bool Crawler::insertToDb(string titles, string descriptions)
{

   string title = "";
   string descr = "";

   int titIndex = 0;
   int desIndex = 0;

   for (int i = 0; i < 75; i ++)
   {
      while(titles.compare(titIndex, 1, "\n", 0, 1) != 0)
      {
         title += titles[titIndex ++];
      }

      while(descriptions.compare(desIndex, 1, "\n", 0, 1) != 0)
      {
         descr += descriptions[desIndex ++];
      }

      this->db.insert(this->dbPath, title, descr);

      titIndex ++;
      desIndex ++;
      title = "";
      descr = "";
   }

   return true;
}


string Crawler::getTitles(string html)
{
   string title = "";
   int count = 0;

   const string className = "catProductTitle";
   const string less = "<";
   const string more = ">";
   const int length = html.length();
   

   for(int i = 0; i < length; i ++)
   {
      if(html.compare(i, 14, className, 0, 14) == 0)
      {
         count++;
      }

      if(count > 0 && html.compare(i, 1, more, 0, 1) == 0)
      {
         count++;
      }

      if(count == 3 && html.compare(i, 1, more, 0, 1) != 0)
      {

         if (html.compare(i, 1, less, 0, 1) == 0)
         {
            count = 0;
            title += "\n";

            continue;
         }

         title += html[i];
      }
   }  

   return title;
}


string Crawler::getDescriptions(string html)
{
   const int length = html.length();
   const string className = "product_s_desc";
   const string more  = ">";
   const string less  = "<";

   string desc  = "";
   int count = 0;

   for (int i = 0; i < length; i ++)
   {
      if (html.compare(i, 13, className, 0, 13) == 0)
      {
         count ++;
      }
      
      if (count > 0 && html.compare(i, 1, more, 0, 1) == 0)
      {
         count ++;
      }

      if (count == 2 && html.compare(i, 1, more, 0, 1) != 0)
      {
         if (html.compare(i, 1, less, 0, 1) == 0)
         {
            count = 0;
            desc = n_trim(desc);
            desc += "\n";

            continue;
         }

         desc += html[i];
      }
   }

   return desc;
}


bool Crawler::is_content(string html)
{
   string titles = getTitles(html);

   if (titles.length() > 0)
      return true;
   else 
      return false;
}


string Crawler::n_trim(const string& str)
{
   size_t first = str.find_first_not_of("\n");
   if (string::npos == first)
   {
      return str;
   }
   size_t last = str.find_last_not_of("\n");
   return str.substr(first, (last - first + 1));
}


int Crawler::random(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}