/**  outputGate_o.cc  **********************************************************

    12.31.1999  Performance Server Library v2.000





changes log
when      who       what
5.3.99    Dan       Creation
5.4.99    Dan       Added     Preformace time points.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "string_o"
#include "log_o"
#include "output_o"
#include "outputGate_o"
#include "queueDirector_o"


extern log_o log;


outputGate_o::outputGate_o(const thread_o& thread,
                           queue_o<output_o>& queue): thread_o(thread)  {
    OutputQueue     = &queue;
    NumberAdvanced  = 0;
}

outputGate_o::~outputGate_o()  {}

void outputGate_o::tendgate()  {
    long int    x;
    long int    sent;
    long int    messageLength; 
    string_o    message;
    sendrecv_o  sendrecv;
    output_o*   output;


    while(2)  {

        if(::log.debug(311))  {
            (message = "") << *this << "waiting for output " << NumberAdvanced << '.';
            ::log << message;
        }

        output = OutputQueue->get();

        if(output)  {

            if(::log.debug(319))  {
                output->adjust();
                (message = "") << *this << "t11: " << *(time_o*)output;
                ::log << message;
            }

            if(::log.debug(312))  {
                (message = "") << *this << "message:\n`";
                message << output->message() << "'";
                ::log << message;
            }


            messageLength = output->message().length();
            message = output->message();
            sent = 0;

/*
            while(messageLength > sent)  {
                x = sendrecv.send(output->socket(),message);
                if(sendrecv.error() != ERROR_OK)  break;
                if(x > 0)  sent = sent + x;
                if(messageLength == sent)  break;
                message.upcut((int)x);
                thread_o::yeild();
            }
*/


            x = sendrecv.send(output->socket(),output->message());
          

            thread_o::yeild();
            (void)sendrecv.close(output->socket());


            if(::log.debug(319))  {
                output->adjust();
                (message = "") << *this << "t12: " << *(time_o*)output;
                ::log << message;
            }

            delete output;

            if(::log.debug(311))  {
                (message = "") << *this << "completed output " << NumberAdvanced << '.';
                ::log << message;
            }

            NumberAdvanced++;

        }
    }
}


/******************************************************************************/
