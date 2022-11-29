/*
 1 In principio erat Verbum et Verbum erat apud Deum et Deus erat Verbum
 2 Hoc erat in principio apud Deum
 3 Omnia per ipsum facta sunt et sine ipso factum est nihil quod factum est
 4 In ipso vita erat et vita erat lux hominum
 5 Et lux in tenebris lucet et tenebrae eam non conprehenderunt
 */

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include "run_control.h"
//#include "calculus_BLSHGatewayHandler.h"

int main(int argc, const char* argv[]) {	
	srand(time(NULL));
	
	if(argc == 1) {
		std::cout << "Please specify the location of a script file\n";
		return 1;
	}
	
	std::ifstream command_file(argv[1]);
	if(!command_file) {
		std::cout << "Script file '" << argv[1] << "' not found.\n";
		return 2;
	}
	
	std::stringstream content;
	content << command_file.rdbuf();
	
	run_control(content.str());
	
	return 0;
}
/*
extern "C" {
	JNIEXPORT jstring JNICALL Java_calculus_BLSHGatewayHandler_runBLSH(JNIEnv* environment, jobject jobj, jstring j_script) {
		const char *script = (*env)->GetStringUTFChars(env, j_script, 0); 

		// process the string

		// Now we are done with str

		(*env)->ReleaseStringUTFChars(env, s, str);

		return env->NewString((const jchar*)retval.c_str(), (jsize)retval.length());
	}
}*/
