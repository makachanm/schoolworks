#include <stdio.h>

struct linux_class{
	int index;
	char level;
	float weight;
} x= {232, 'A', 2.0};

int main(){
	struct linux_class y = {500, 'B', 2.1};
	struct linux_class ori;

	printf("%d, %c, %f\n", x.index, x.level, x.weight);
	printf("%d, %c, %f\n", y.index, y.level, y.weight);
	printf("%d, %c, %f\n", ori.index, ori.level, ori.weight);
	
}
