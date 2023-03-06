#ifndef _defines_h_
#define _defines_h_

#ifndef UNICODE
#define UNICODE
#endif

//To becouse pRenderTarget->GetSize returns unexpected %rad register under gcc compiler
//But workaround doesnt work (but im still keeping for unreliable behaviour yay)
#ifndef WIDL_EXPLICIT_AGGREGATE_RETURNS
#define WIDL_EXPLICIT_AGGREGATE_RETURNS 
#endif

#endif