/*
 * Implementation file for Trancevibrator Max/Pd External
 *
 * Copyright (c) 2005-2008 Kyle Machulis/Nonpolynomial Labs <kyle@nonpolynomial.com>
 *
 * More info on Nonpolynomial Labs @ http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libtrancevibe/
 *
 * Example code from flext tutorials. http://www.parasitaere-kapazitaeten.net/ext/flext/
 */

// include flext header
#include <flext.h>
#include <trancevibe.h>

// check for appropriate flext version
#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif


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
		AddInAnything("Command Input");		
		AddInInt("Speed Input");
		AddOutBang("Bangs on successful connection/command");
		
		FLEXT_ADDMETHOD(0, trancevibe_anything);
		FLEXT_ADDMETHOD(1, set_speed);
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
	int mSpeed;

	void trancevibe_anything(const t_symbol *msg,int argc,t_atom *argv)
	{
		
		
		if(!strcmp(msg->s_name, "open"))
		{
			int ret;
			if(mTranceVibe)
			{
				trancevibe_close(mTranceVibe);
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
			ToOutBang(0);
		}
		else if (!strcmp(msg->s_name, "timeout"))
		{
			if(argc == 1)
			{
				mTimeout = GetInt(argv[0]);
				ToOutBang(0);
			}
			else
			{
				post("Timeout requires 1 argument (timeout in milliseconds)");
			}
		}
		else if (!strcmp(msg->s_name, "close"))
		{
			close();
			ToOutBang(0);
		}
		else if (!strcmp(msg->s_name, "bang"))
		{
			if(mTranceVibe)
			{
				trancevibe_speed(mSpeed);
				ToOutBang(0);
			}
			else
			{
				post("Not connected to trancevibe");
			}
		}
		else 
		{
			post("Not a valid np_trancevibe message: %s", msg->s_name);
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

	void set_speed(int speed)
	{
		mSpeed = speed;
	}
	
	void trancevibe_speed(int input) 
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
	FLEXT_CALLBACK_I(set_speed)
};

FLEXT_NEW("np_trancevibe", np_trancevibe)



