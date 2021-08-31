#include "httpClient.h"
#include <stdio.h>
#include <curl/curl.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace SE;
using namespace std;


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
   ((std::string*)userp)->append((char*)contents, size * nmemb);
   return size * nmemb;
}


string HttpClient::request(const char* url)
{
   CURL *curl;
   CURLcode res;
   string readBuffer;

   curl = curl_easy_init();
  
   if(curl) 
   {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
      res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
   }

   return readBuffer;
}









