/**  workThread_o.cc  **********************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman




changes log
when       who       what
4.28.99    Dan       Creation
5.2.99     Dan       Changed   constuctor arguments.
5.4.99     Dan       Added     performace time points.

*******************************************************************************/



#include "string_o.h"
#include "log_o.h"
#include "queue_o.h"
#include "sendrecv_o.h"
#include "workThread_o.h"
#include "carapace_o.h"

extern  log_o       log;
extern  carapace_o  carapace;

workThread_o::workThread_o(const thread_o& thread,
                           queue_o<input_o>& inputqueue,
                           queue_o<output_o>& outputqueue): thread_o(thread)  {
    InputQueue      = &inputqueue;
    OutputQueue     = &outputqueue;
    NumberAdvanced  = 0;
}

workThread_o::~workThread_o()  {}

int workThread_o::workLoop()  {
    int             err;
int msgsize;
    string_o        message;
    unsigned int    ca;
    unsigned int    nbn;
    unsigned int    retry;
    sendrecv_o      sendrecv;
    input_o*        input;
    output_o*       output;

    while(1)  {
        if((*(error_o*)this) != ERROR_OK)  return error();

        if(::log.debug(112))  {
            (message = "") << *(thread_o*)this << "waiting for job " << NumberAdvanced << '.';
            ::log << message;
        }

        input = InputQueue->get();

        if(input)  {

            output = new output_o(input);

//            yeild();
            nbn = 0;
            retry = 999999L;
            while(nbn == 0 && retry-- > 1)  {
                yeild();
                yeild();
                nbn = sendrecv.recv(input->socket(),input->message());
            }
            if(retry <= 1)  {
                (message = "") << *(thread_o*)this << "retries exhausted, null message.";
                ::log.error(message);
            }
            while(nbn > 0)  {
                yeild();
                nbn = sendrecv.recv(input->socket(),input->message());
            }

if(input->message().contains("************"))  {
input->setState(CLIENT_STATE_12STAR_PROTOCOL);
    msgsize = input->message().stoi();
            if(::log.debug(112))  {
                (message = "") << *(thread_o*)this << "12*protocol rep size ";
                message << msgsize << ".";
                ::log << message;
            }
    input->message().upcut("************");
    while(input->message().length() < msgsize)  {
                yeild();
                nbn = sendrecv.recv(input->socket(),input->message());
    }
}






            if(::log.debug(119))  {
                input->adjust();
                (message = "") << *(thread_o*)this << "t9: " << *(time_o*)input;
                ::log << message;
            }


            if(::log.debug(112))  {
                (message = "") << *(thread_o*)this << "msg size ";
                message << input->message().length() << ".";
                ::log << message;
            }

            if(::log.debug(113))  {
                (message = "") << *(thread_o*)this << "sending job " << NumberAdvanced << " to carapace.";
                ::log << message;
            }

            err = carapace.process(*input,*output);
            if(err)  {
                *(error_o*)this = err;
                (message = "") << *(thread_o*)this << "carapace reports ";
                message << err << ".";
                ::log << message;
            }

            if(::log.debug(113))  {
                (message = "") << *(thread_o*)this << "carapace completed job " << NumberAdvanced << '.';
                ::log << message;
            }


/*
if(output->state() == OUTPUT_STATE_12STAR_PROTOCOL)  {
    msgsize = output->message().length();
    output->Message.reverse();
    output->Message << "************";
    message = "";
    message << msgsize;
    message.reverse();
    output->Message << message;
    output->Message.reverse();
}
*/


            ca = OutputQueue->put(output);


            if(::log.debug(119))  {
                input->adjust();
                (message = "") << *(thread_o*)this << "t10: " << *(time_o*)input;
                ::log << message;
            }

            if(::log.debug(112))  {
                (message = "") << *(thread_o*)this << "job " << NumberAdvanced;
                message << " output queued at " << ca << ".";
                ::log << message;
            }


            delete input;


            if(::log.debug(112))  {
                (message = "") << *(thread_o*)this << "finshed job " << NumberAdvanced << '.';
                ::log << message;
            }

            NumberAdvanced++;

        }
    }
    return 0;
}

int workThread_o::doWork()  {
    int      err;
    string_o message;

    if(::log.debug(111))  {
        (message = "") << *(thread_o*)this << "work loop starting.";
        ::log << message;
    }

    err = workLoop();

    if(err)  {
        (message = "") << *(thread_o*)this;
        message << "work loop terminating, error " << err << ".";
        ::log << message;
    }

    if(::log.debug(111))  {
        (message = "") << *(thread_o*)this << "work loop terminating.";
        ::log << message;
    }

    return err;
}


/******************************************************************************/
