/**  inputgate.cc  *************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman






changes log
when      who       what
4.28.99   Dan       Creation
5.2.99    Dan       Changed   Contructor arguments.
5.3.99    Dan       Added     Debug level.
5.4.99    Dan       Added     Preformace time points.

*******************************************************************************/


#include "../../lib/string/string.h"
#include "../../lib/log/log.h"
#include "../../sserver/dataobjects/input.h"
#include "../gate/inputgate.h"
#include "../directors/queueDirector.h"

extern log_o log;


inputgate_o::inputgate_o(const thread_o& thread,
                           server_o& server,
                           queue_o<input_o>& queue): thread_o(thread)  {
    Server          = &server;
    InputQueue      = &queue;
    NumberAdvanced  = 0;
}

inputgate_o::~inputgate_o()  {}

void inputgate_o::tendgate()  {
int x;
    string_o    message;
    input_o*    input;
    unsigned long qa;


    while(1)  {
        input = new input_o();

        if(::log.debug(301))  {
            (message = "") << *this << "waiting for connect " << NumberAdvanced << '.';
            ::log << message;
        }

        input->setSocket(Server->accept());
        if(Server->error() != ERROR_OK)  {
            (message = "") << *this << *(error_o*)this;
message<<"E0??????";
            ::log.error(message);
        }
        else  {

            if(::log.debug(309))  {
                input->reset();
            }

            //input->setIpAddress(Server->clientIp());
            input->setPriority(0);


            if(::log.debug(302))  {
                (message = "") << *this << "message:\n`";
                message << input->message() << "'";
                ::log << message;
            }

            qa = InputQueue->put(input);

            if(::log.debug(309))  {
                input->adjust();
                (message = "") << *this << "t8: " << *(time_o*)input;
                ::log << message;
            }

            if(::log.debug(301))  {
                (message = "") << *this << "input object placed " << qa;
                message << " in " << InputQueue->cardinality();
                ::log << message;
                (message = "") << *this << "finished connect " << NumberAdvanced << '.';
                ::log << message;
            }

            NumberAdvanced++;

        }
    }
}


/******************************************************************************/
