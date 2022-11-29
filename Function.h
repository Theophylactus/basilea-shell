#pragma once

#include "Param_data.h"
#include "Arglist.h"

/* The function superclass. Used to polymorphically handle all the different function classes */
class Function {
private:
	/* Used only in Function::prepare_params() as a manifest of how the arguments shall be like */
	static const Params_data params_data;
	
protected:
	static void prepare_params(Arglist* args, const Params_data& params_data);
	
public:
	static const Function* instance_of(const std::string& func_name);
	
	/*static constexpr size_t return_type;*/
	
	virtual std::string run(Arglist& args) const { return ""; };
};

/* The definition of the following classes are in the functions/ directory. */

#define FUNC_SUPER public Function { static const Params_data params_data; std::string run(Arglist& args) const; };

class Compute :    FUNC_SUPER
class Corrupt :    FUNC_SUPER
class Download :   FUNC_SUPER
class Echo :       FUNC_SUPER
class Integral :   FUNC_SUPER
class Litaniae :   FUNC_SUPER
class Plot :       FUNC_SUPER
class Random :     FUNC_SUPER // TODO allow for Random to return different amount of decimal digits based on the args
class Read :       FUNC_SUPER
class Scp :        FUNC_SUPER
class Scriptor :   FUNC_SUPER
class Set : public Function {
public:
	static void replace_vars_by_vals(std::string* source); /* This function class needs this exceptional method to retrieve the value of the stored variables */
	static const Params_data params_data;
	std::string run(Arglist& args) const;
};
class Shell_exec : FUNC_SUPER
class Wait :       FUNC_SUPER
class Write :      FUNC_SUPER

#undef FUNC_SUPER

/*
                                                .;;.                           .;;.                                                
                                                 '',:.                        ';''.                                                
                                                    .:;   .                 .o'                                                    
                                                     cc  .o.            ;;  .k.                                                    
                                                     cc .:o.            ;l;..k.                                                    
                              .......               .ll.::.              'o',k,                ......                              
                           .;;;,,,,ckc;;.          .kxdo;.                'cdxxc           .;;oo;;,;,;;;.                          
                         .o'.       ..'oo;       .:oddolc::l:.        'oc::loddol'       .oo:..       ..:;                         
                        .,:.            co'    .;o:;;:'    'lk:.    'od:.   .:;;;lc.    .:k.            ';'                        
                        co;.            .:kl' 'lc.           'oc   .k:.          .;o:..:do'             .ck.                       
                       .lxo'             .kkdcc.                    .              .;cokkc             .:dk,                       
                      .oxo;l:.           .kko;                                       .ckkc            ,o:ckd;                      
                   .;,;c,,c',:''''        .oc                                         .k;.       .''';:.;;.::';'                   
                .;;;,.   .:,'.            'oc        ....;dddddddddddddddl....        .k:.             ';'    .,;,.                
                           .'.           .k:.     .;;oxxxxk:''''''''''''okxxxxc;;.     'oc             '                           
                                         .k.   ;cclllo:....              ...'oolllcc.   cc                                         
              ...                       .:k;..ldo:.                              'cdd;..oo'                        ...             
              .cl;,.                    cxdddx;'.                                  ''ldodxk.                   .;;:o;.             
                ..;cc.                'loddo:.                                        'loddo:.               .;cc...               
                    'cc'           .;oxodo;.                                            .cxddkc.           .;o;.                   
                    ..,c;;c.    ..:dxxdo'                                                 .:odxxo'..   .,:;:;'.                    
                   .::;'';ddc''od:odoxc           ..                            .           .kddxllk:';ddl'',::'                   
                       '';ddc'''. ;dx:.           ;l;.                        .:o.           'ldo. ''';ddl''.                      
                        ,cc.    .cddo.            ;oo.         ......         ;oo.            ;dxl,    .;cc.                       
                       .c;     .;dl'              ;oo.       ';::::::,.       ;oo.             .:ol.     .o;.                      
                      .o,.     :xk.               ;oc:'     'o.      ;:.    .;clo.               cxd'     .c;                      
                     .;o.    .dxd:.               ;; ;;    cc         .k.   .o..o.               'lkd;     ;c.                     
                     ;c.     .dxc                 ;; ;l;.  cc         .k.  .:o..o.                .kd;     .;o.                    
            ,;.             .lxd;                .:;  'o..o'           .:; ;:. .o'                .oxd;      .       .c.           
            .:o.        ..  'dk.                .o:.  .o..k.            cc ;;  .;l;                 cx:   '         ;l;.           
             .o:.     .:,.  'dk.                .o.   .o:ck.            co,l;    :;                 cx:   ';'     .;l;             
               :;   .c:.   .:oc.                .o.     cc.              ,x'     :;                 ,ll.    'o;.  .o'              
               ;l;:lk:.    ;xc                  .o.     cc               .k.     :;                  .xo.    'od:;:o.              
                'oxl.      ;xc                  .o.     cdc.            ,ok.     :;                  .xo.      ,kd:.               
                .oxc       ;xc                 .;o.     cxo.            ;dk.     ;c.                 .xo.      .kd;                
                .oxc       ;xc                 ;c.      cxxl::::::::::::oxk.     .;o.                .xo.      .kd;                
                 .lc       ;xc                 ;;       cl.cc.........'d',k.      .o.                .xo.      .k,                 
                  cc       ;xc                 ;;     .;,. ;;         .o..;;.     .o.                .xo.      .k.                 
                   'o'     ;xc                ;c,     .k.  ,cc.      ,cc.  cc     .cc.               .xo.    .::.                  
                   .:dc    .ll'               :.      .k.   .o.      ;;    cc       :.              .:o;.   .kl'                   
          .;,,;,;;;. cd:.   'dk.            .;l.      .k.   .o:.   .;l;    cc       ::.             cx:    'lk..;;;,,,,,.          
           .......;:;:ld'   'dk.            .o.       .k.    .:;   .o'     cc        :;             cx:   .coc;;c.......           
                      .;lc. 'dk:.          .,o.       .k.     ;;   .o.     cc        ;c.           'ox: .;d:.                      
                        .'c:,:dxc          :c.        .k.     ,c; ':c.     cc        .,o'         .kxl,;c;.                        
                           .cooxo'       .d:.         .k.      .o.;;       cc         .;l;       .:kdol;.                          
                            .;odxk.     .:o.           ';'     .o.;;     .:,.           ;l;.     cxddc.                            
                             .codx,   .cc,.             cc     .ccc,     .k.             .cc;.  .lxol,                             
                               .:dxo.cl;.               cc       :.      .k.               .:o;;kdl;.                              
                                .odxx;.                 ..       .        '                  .lxdd;                                
                                .coddo;                                                     .oddol,                                
                                  ;c'lo;.                                                  .cx:;o.                                 
 .';,,,;;.      .:::::::.         ;:..'do:.                                              'lo:..'o.        .,::::::,.     .;;,,,,;. 
.;.      .,.  ';'       ''        .:o;,;ldx:.                                          'ldo:,'cl;.       .:.      .:,. .''       ..
          .o..k.                   .oxc .;odo:                                       'cddc. .kd;                    cc ;;          
           .::.                    .oxl.  .;ccll:.                                'lllcc.   ,kd;                     'o'           
            cc                    .;oclk.     'ldx:'''.                      ''''ldo:.     cd:lc'                    .k.           
            cc                   .lxo..ol,     ...:llddcccc.............;ccclkoll,..     .co; ;dk,                   .k.           
            ';'                .:klco.  co'          .;;;cxxxxxxxxxxxxxxxo;;;;.         .:k.  ;l:do'                .,:.           
             .kl'           .::do',,.   .:kl'             ................            .:do'   .';,:kl:,           .:dc             
              .:l:l:....:l::l:..  ;;      .:oo.                                      :oo'      .o. ..'l::co'...'occo'              
                  '::::::'        ;;        .:d:''                               .''dl'        .o.       .:::::::.                 
                                  ..          .':kl:::'                     .::::do''           .                                  
                                                 ......                      ......                                                
                                                 
                                                                               
               ___     _______   __  __    _    ____  ___    _      ____  _   _ ____  ___ ____ ____ ___ __  __    _    _ 
              / \ \   / / ____| |  \/  |  / \  |  _ \|_ _|  / \    |  _ \| | | |  _ \|_ _/ ___/ ___|_ _|  \/  |  / \  | |
             / _ \ \ / /|  _|   | |\/| | / _ \ | |_) || |  / _ \   | |_) | | | | |_) || |\___ \___ \| || |\/| | / _ \ | |
            / ___ \ V / | |___  | |  | |/ ___ \|  _ < | | / ___ \  |  __/| |_| |  _ < | | ___) |__) | || |  | |/ ___ \|_|
           /_/   \_\_/  |_____| |_|  |_/_/   \_\_| \_\___/_/   \_\ |_|    \___/|_| \_\___|____/____/___|_|  |_/_/   \_(_)
                                                                                                              

*/
