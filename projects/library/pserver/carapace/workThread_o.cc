/**  workThread_o.cc  **********************************************************

    12.31.1999  Performance Server Library v2.000


    Work Thread.




changes log
when       who       what
4.28.99    Dan       Creation
5.2.99     Dan       Changed   constuctor arguments.
5.4.99     Dan       Added     performace time points.





                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/



#include "string_o"
#include "log_o"
#include "queue_o"
#include "sendrecv_o"
#include "workThread_o"
#include "carapace_o"

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

            nbn = 0;
            retry = 999999L;
            while(nbn == 0 && retry-- > 1)  {
                yeild();
                nbn = sendrecv.recv(input->socket(),input->message());
            }
            if(retry <= 1)  {
                (message = "") << *(thread_o*)this << "Retries exhausted, null message.";
                ::log.error(message);
            }
            while(nbn > 0)  {
                yeild();
                nbn = sendrecv.recv(input->socket(),input->message());
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

            err = carapace.process(*input, *output);
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
        (message = "") << *(thread_o*)this << "Work loop starting.";
        ::log << message;
    }

    err = workLoop();

    if(err)  {
        (message = "") << *(thread_o*)this;
        message << "Work loop terminating, error " << err << ".";
        ::log << message;
    }

    if(::log.debug(111))  {
        (message = "") << *(thread_o*)this << "Work loop terminating.";
        ::log << message;
    }

    return err;
}


/******************************************************************************/
