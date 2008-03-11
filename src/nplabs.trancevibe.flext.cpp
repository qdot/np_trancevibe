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

class tv:
	// inherit from basic flext class
	public flext_base
{
	// obligatory flext header (class name,base class name)
	FLEXT_HEADER(tv,flext_base)
 
public:
	// constructor
	tv()
	{
		trancevibe_open(&m_vibe,0);
		// define inlets:
		// first inlet must always be of type anything (or signal for dsp objects)
		AddInInt();  // add one inlet for any message
		
		// register methods
		FLEXT_ADDMETHOD(0,m_int);  // register method (for float messages) "m_float" for inlet 0
	} 

	~tv()
	{
		trancevibe_close(m_vibe);
	}

	
protected:
	trancevibe m_vibe;
	void m_int(int input)  // method for float values
	{
		int result;
		trancevibe_set_speed(m_vibe, input, 100);
	}

private:
	FLEXT_CALLBACK_1(m_int,int)  // callback for method "m_float" (with one float argument)
};
// instantiate the class
FLEXT_NEW("tv",tv)



