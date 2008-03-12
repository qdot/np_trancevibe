/* 
flext tutorial - simple 1 

Copyright (c) 2002,2003 Thomas Grill (xovo@gmx.net)
For information on usage and redistribution, and for a DISCLAIMER OF ALL
WARRANTIES, see the file, "license.txt," in this distribution.  

-------------------------------------------------------------------------

This is an example of a simple object doing a float inversion
*/

// include flext header
#include <flext.h>
#include <trancevibe.h>

// check for appropriate flext version
#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif


// define the class that stands for a pd/Max object
// Attention: the class name must be the same as the object name!! (without an eventual ~)
// Special names are possible with the usage of libraries (see the lib1 tutorial example)

class np_trancevibe:
	// inherit from basic flext class
	public flext_base
{
	// obligatory flext header (class name,base class name)
	FLEXT_HEADER(np_trancevibe,flext_base)
 
public:
	// constructor
	np_trancevibe() :
	mTranceVibe(NULL),
		mTimeout(10)
	{
		// define inlets:
		// first inlet must always be of type anything (or signal for dsp objects)
		AddInAnything("Command Input");
		
		AddInInt("Speed Input");  // add one inlet for any message

		AddOutBang("Bangs on successful connection/command");
		
		// register methods
		FLEXT_ADDMETHOD(0, trancevibe_anything);
		FLEXT_ADDMETHOD(1, trancevibe_speed);
	} 

	virtual ~np_trancevibe()
	{
		if(mTranceVibe)
		{
			close();
		}
	}
	
protected:
	trancevibe mTranceVibe;
	int mTimeout;

	void trancevibe_anything(const t_symbol *msg,int argc,t_atom *argv)
	{
		
		if(!strcmp(msg->s_name, "open"))
		{
			int ret;
			if(mTranceVibe)
			{
			}
			if(argc == 1)
			{
				post("Opening %d", GetInt(argv[0]));
				ret = trancevibe_open(&mTranceVibe, GetInt(argv[0]));
			}
			else
			{
				post("Opening default");
				ret = trancevibe_open(&mTranceVibe, 0);
			}
			if(ret >= 0)
			{
				ToOutBang(0);
			}
			else
			{
				post("Cannot connect to trancevibe");
			}
		}
		else if (!strcmp(msg->s_name, "count"))
		{
			post("Trancevibes Connected to System: %d", trancevibe_get_count());
		}
		else if (!strcmp(msg->s_name, "timeout"))
		{
			if(argc == 1)
			{
				mTimeout = GetInt(argv[0]);
			}
			else
			{
				post("Timeout requires 1 argument (timeout in milliseconds)");
			}
		}
		else if (!strcmp(msg->s_name, "close"))
		{
			close();
		}
		else
		{
			post("Not a valid message: %s", msg->s_name);
		}
	}

	void close()
	{
		if(mTranceVibe)
		{
			trancevibe_set_speed(mTranceVibe, 0, mTimeout);
			trancevibe_close(mTranceVibe);
			mTranceVibe = NULL;
		}
	}
	
	void trancevibe_speed(int input)  // method for float values
	{
		int result;
		if(!mTranceVibe)
		{
			post("Trancevibe not connected");
		}
		if(input > 255 || input < 0)
		{
			if(input > 255) input = 255;
			else if (input < 0) input = 0;
			post("Speed input must be between 0 and 255");
		}
		trancevibe_set_speed(mTranceVibe, input, mTimeout);
	}

private:
	FLEXT_CALLBACK_A(trancevibe_anything)
	FLEXT_CALLBACK_I(trancevibe_speed)
};
// instantiate the class
FLEXT_NEW("np_trancevibe", np_trancevibe)



