/*
 * Implementation file for Trancevibrator Max/MSP External
 *
 * Copyright (c) 2005-2008 Kyle Machulis/Nonpolynomial Labs <kyle@nonpolynomial.com>
 *
 * More info on Nonpolynomial Labs @ http://www.nonpolynomial.com
 *
 * Sourceforge project @ http://www.sourceforge.net/projects/libtrancevibe/
 *
 * This library is covered by the MIT license, read LICENSE for details.
 */

#include "ext.h"
#include "trancevibe.h"

#define MAXSIZE 256

typedef struct _max_trancevibe
{
	struct object m_ob;
	t_atom m_args[MAXSIZE];
	trancevibe tv;
	unsigned char speed;
	unsigned int timeout;
	void *m_confirm;
} t_max_trancevibe;

void *max_trancevibe_class;

void *max_trancevibe_new(t_symbol *s, short ac, t_atom *av);

void max_trancevibe_anything(t_max_trancevibe* x, t_symbol *msg, short argc, t_atom *argv);
void max_trancevibe_speed(t_max_trancevibe* x, long t);
void max_trancevibe_assist(t_max_trancevibe *x, void *b, long m, long a, char *s);
void max_trancevibe_bang(t_max_trancevibe *x);

void main()
{
	setup((t_messlist **)&max_trancevibe_class, (method)max_trancevibe_new,0L, (short)sizeof(t_max_trancevibe), 0L, A_GIMME, 0);
	addbang((method)max_trancevibe_bang);
	addinx((method)max_trancevibe_speed,1);
	addmess((method)max_trancevibe_anything, "anything", A_GIMME, 0);
	addmess((method)max_trancevibe_assist,"assist", A_CANT, 0);
}

void *max_trancevibe_new(t_symbol *s, short ac, t_atom *av)
{
	t_max_trancevibe *x;
	x = (t_max_trancevibe *)newobject(max_trancevibe_class);
	x->speed = 0;
	x->tv = NULL;
	intin(x, 1);
#ifdef WIN32
	x->timeout = 10;
#else 
	x->timeout = 1;
#endif
	x->m_confirm = bangout(x);
	return x;
}

void max_trancevibe_anything(t_max_trancevibe* x, t_symbol *msg, short argc, t_atom *argv)
{
	if(!strcmp(msg->s_name, "open"))
	{
		int ret;
		if(argc == 1)
		{
			ret = trancevibe_open(&(x->tv), argv[0].a_w.w_long);
		}
		else
		{
			ret = trancevibe_open(&(x->tv), 0);
		}
		if(!ret)
		{
			outlet_bang(x->m_confirm);
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
			x->timeout = argv[0].a_w.w_long;
		}
		else
		{
			post("Timeout requires 1 argument (timeout in milliseconds)");
		}
	}
	else if (!strcmp(msg->s_name, "close"))
	{
		if(x->tv)
		{
			if(!trancevibe_set_speed(x->tv, 0, x->timeout)) outlet_bang(x->m_confirm);
			trancevibe_close(x->tv);
			x->tv = NULL;
			outlet_bang(x->m_confirm);
		}
	}
	else
	{
		post("Not a valid message: %s", msg->s_name);
	}
}

void max_trancevibe_bang(t_max_trancevibe* x)
{
	if(!(x->tv))
	{
		post("Trancevibe not connected");
		return;
	}
	if(!trancevibe_set_speed(x->tv, x->speed, x->timeout)) outlet_bang(x->m_confirm);
}

void max_trancevibe_speed(t_max_trancevibe* x, long t)
{
	if(t > 255)
	{
		t = 255;
		post("Clamping trancevibe speed value to 255");
	}
	x->speed = t;
}

void max_trancevibe_assist(t_max_trancevibe *x, void *b, long m, long a, char *s)
{
	if (m==ASSIST_INLET) {
		switch (a) {
			case 0:
				sprintf(s, "Command Input");
			case 1:
				sprintf(s, "Speed Input");
		}
	}
	else {
		sprintf(s,"Bangs on successful connection");
	}
}
