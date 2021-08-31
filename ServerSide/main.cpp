
#include "Server/httplib.h"
#include "DB/db.h"

using namespace httplib;

int main(void)
{
    Server svr;
    Db db;

    svr.Get("/start", [](const Request& req, Response& res) {
      res.set_content("You can type search query here: ", "text/plain");
    });

    svr.Get("/search?query", [](const Request& req, Response& res) {
      if (req.has_header("Content-Length")) {
          // get search query by http
          auto query = req.matches[2];

          // run search by query in DB
          string responce = db.search(query)

          // build response
          res.set_content(response, "text/plain");
      }
    });

    svr.Get("/stop", [&](const Request& req, Response& res) {
      svr.stop();
    });

    svr.listen("localhost", 1234);
}

