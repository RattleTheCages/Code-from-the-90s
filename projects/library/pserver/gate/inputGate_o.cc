/**  inputGate_o.cc  ***********************************************************

    12.31.1999  Performance Server Library v2.000


    Input Gate Implementation.




changes log
when      who       what
4.28.99   Dan       Creation
5.2.99    Dan       Changed   Contructor arguments.
5.3.99    Dan       Added     Debug level.
5.4.99    Dan       Added     Preformace time points.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "log_o"
#include "input_o"
#include "string_o"
#include "inputGate_o"
#include "queueDirector_o"

extern log_o log;


inputGate_o::inputGate_o(const thread_o& thread,
                           server_o& server,
                           queue_o<input_o>& queue): thread_o(thread)  {
    Server          = &server;
    InputQueue      = &queue;
    NumberAdvanced  = 0;
}

inputGate_o::~inputGate_o()  {}

void inputGate_o::tendgate()  {
    string_o    message;
    input_o*    input;
    unsigned long qa;


    while(1)  {
        input = new input_o();

        if(::log.debug(301))  {
            (message = "") << *this << "Waiting for connect " << NumberAdvanced << '.';
            ::log << message;
        }

        input->setSocket(Server->accept());
        if(Server->error() != ERROR_OK)  {
            (message = "") << *this << *(error_o*)this;
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
                (message = "") << *this << "Finished connect " << NumberAdvanced << '.';
                ::log << message;
            }

            NumberAdvanced++;

        }
    }
}


/******************************************************************************/
