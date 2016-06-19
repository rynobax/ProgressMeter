#include "ProgressMeter.h"
#include <stdlib.h>

/* This is an example program that demonstrates use of the ProgressMeter */

void long_function(){
	int n = 0;
	for(int i=0;i<999999;i++){
		n = n + rand();
	}
}

int main(void){
	int count = 1500;
	ProgressMeter p = ProgressMeter(count, "Counting");
	for (int i = 0; i < count; ++i)
	{
		long_function();
		p.update();
	}
}
