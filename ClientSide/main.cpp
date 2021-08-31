#include "../HttpClient/httpClient.h"

int main()
{
   httpClient client;
   string command;
   
   for (;;)
   {
      cout << "You can insert following commands: " << endl;
      cout << "1: /start" << endl;
      cout << "2: /stop" << endl;
      
      cin >> command;

      if (command.compare(0, 1, "1", 0, 1) == 0 )
      {
        string query;
        string response;
        
        // http request to server (start 1234 listener)
        response = client.request("localhost:1234/start");

        // show server response
        cout << response;

        // wait for user query
        cin >> query;

        // send search query to server
        response = client.request("localhost:1234/" + query);
        
        // show search result
        cout << response;
      }

      else if (command.compare(0, 1, "2", 0, 1) == 0 )
      {
          // http requesst for stoping server (1234 port listener)
          client.request("localhost:1234/stop");

          // loop interruption
          break;
      }
   }

}   




