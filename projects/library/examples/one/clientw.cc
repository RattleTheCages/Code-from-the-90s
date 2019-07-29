/**  client1.cc  ***************************************************************

*******************************************************************************/

#include "../../lib/string/string.h"        // Include a minimal set of objects
#include "../../lib/log/log.h"              // from the 
#include "../../sserver/telenet/client.h"   

log_o   log;        // All objects that do error reporting send the report to
                    // this global log object.  The log object is thread-safe
                    // and prevents one message from cutting off another message
                    // during concurrent thread error reports.  This log can
                    // also be used during debugging and to log non-error
                    // occurances.

                    // Create the starting point, main function.

int main(int argc,char* argv[])  {
    int       rcode;
    string_o  rstring;
    string_o  sstring;
    client_o  client;                   // Instantiate the client object.

    rcode = client.connect("www.wunderground.com",80);

    if(rcode)  {                        // Check the error state.
        cerr << "client reports error " << rcode << endl;
        return rcode;
    }

//sstring << "GET /cgi-bin/findweather/getForecast?query=80112 HTTP/1.0\n";
sstring << "GET / HTTP/1.0\n";
sstring << "Connection: Keep-Alive\n";
sstring << "User-Agent: Mozilla/4.61 [en] (Win95; I)\n";
sstring << "Host: www.infomechanics.com\n";
sstring << "Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, image/png, */*\n";
sstring << "Accept-Encoding: gzip\n";
sstring << "Accept-Language: en\n";
sstring << "Accept-Charset: iso-8859-1,*,utf-8\n";
sstring << "\n";


    cout << "sending: " << sstring << endl;

    client.send(sstring);


    client.recv(rstring);               // Receive the reply!
    cout << "recving: " << rstring << endl;


    client.disconnect();                // Disconnect from the server.
    return 0;
}

/******************************************************************************/
