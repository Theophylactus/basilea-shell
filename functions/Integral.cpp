#include "../Function.h"
#include "../extra.h"
#include <stdexcept>
#include <stdlib.h>

using std::string;

const Params_data Integral::params_data = {
											Param_data("function", typeid(const char*)),
											Param_data("x-start", typeid(long double)),
											Param_data("x-end", typeid(long double))
											};

/* Defined in Compute.cpp - we're borrowing this function here for internal usage */
long double compute(string expresion);

inline double trapezoid_area(double f_side_len, double s_side_len, double height) {
	return (f_side_len + s_side_len) * height / 2;
}

inline double compute_f_on_x(const std::string& func, long double x) {
	return compute(extra::replace_all(func, "x", std::to_string(x)));
}

/* This method of numeric integration works by doing the sum of trapezoids comprehended within the area that the function 
 * makes between the X axis and its line. These trapezoids have a height (or width, in this case) of 0.0001. 
                                                 .                                                  
                                                .O                                                  
                                                .d.                                                 
                                                 ,                                                  
                        .,:OKooocl.              ,                                                  
                    .oN0l;':l''':0kc             ,                                                  
                ;xooc,o,''':l''''l'o0'           ,                                                  
           ',:lolk,'''o,''':l''''l'',kl.         ,                                                  
      '.,cl0O,'''l''''o,''':l''''l''';XO         ,                                                  
 .;::cKx;''cc''''l''''o,''':l''''l''''lkl        ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l,0:       ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l',K.      ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l'':O      ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l'''dc     ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l''''O.    ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l''''kN.   ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l'''',N'   ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l'''',xk   ,                                                  
      c,'''cc''''l''''o,''':l''''l''''l'''',lx,  ,                                              .o  
      c,'''cc''''l''''o,''':l''''l''''l'''',l;O  ,                                             .x   
      c,'''cc''''l''''o,''':l''''l''''l'''',l'k, ,                                            .k    
      c,'''cc''''l''''o,''':l''''l''''l'''',l';O ,                                           .x     
      c,'''cc''''l''''o,''':l''''l''''l'''',l''k,,                                          .x      
      c,'''cc''''l''''o,''':l''''l''''l'''',l'';k,                                         cX'      
      c,'''cc''''l''''o,''':l''''l''''l'''',l'''ko                                         Od       
      c,'''cc''''l''''o,''':l''''l''''l'''',l'''dX'                                       kcc       
      c,'''cc''''l''''o,''':l''''l''''l'''',l''',X,                                      k:,c       
      c,'''cc''''l''''o,''':l''''l''''l'''',l''''kO                                     x:',c       
      c,'''cc''''l''''o,''':l''''l''''l'''',l''''oO;                                  'kc'',c       
      c,'''cc''''l''''o,''':l''''l''''l'''',l''''l;O                                 .WO''',c       
      c,'''cc''''l''''o,''':l''''l''''l'''',l''''l'x;                               .kdc''',c       
      c,'''cc''''l''''o,''':l''''l''''l'''',l''''l',O                              .k;cc''',c       
  ....;,''';;'''':'''':,''';;'''':'''':,''',:''''o''xd:;,,,,:,,,,:,,,,:;,,,;:,,,,:ck;';;''',;..'xl' 
                                                 ,   0o,''''l''''l''''l:''',l''',kk                 
                                                 ,   :X,''''l''''l''''l:''',l'''dK;                 
                                                 ,   .Wd''''l''''l''''l:''',l''ld                   
                                                 ,    :0''''l''''l''''l:''',l'oo                    
                                                 ,     od'''l''''l''''l:''',dk:                     
                                                 ,      0c''l''''l''''l:'''xW;                      
                                                 ,      .K;'l''''l''''l:''lx'                       
                                                 ,       'K;l''''l''''l:,x:                         
                                                 ,        '0k''''l''''oxx.                          
                                                 ,         l0O:''l'',dXx                            
                                                 ,           'dkx0xxd'                              
                                                 ,              .:.                                 
                                                 ,                                                  
*/

string Integral::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	string function = args.next();
	if(function.find('x') == string::npos)
		throw std::runtime_error("La función dada no parece contener la variable x. Procure proporcionarla en minúsculas (x).");
		
	long double from = compute(args.next());
	long double to = compute(args.next());
	if(from > to)
		throw std::runtime_error("La coordenada x de inicio es mayor a la del fin.");
	
	long double result = 0;
	
	for(long double x = from; x <= to; x += 0.0001) {
		result += trapezoid_area(compute_f_on_x(function, x), compute_f_on_x(function, x + 0.0001), 0.0001);
	}
	
	return std::to_string(result);
}
