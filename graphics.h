#ifndef USER_INTERFACE
#define USER_INTERFACE

#define H_LINE 196
#define V_LINE 179
#define DR_CORNER 217
#define UL_CORNER 218
#define UR_CORNER 191
#define DL_CORNER 192
#define CROSS_LINE 197
#define LEFT_CROSS 195
#define RIGHT_CROSS 180
#define SEGMENT 45

#define WIDTH 25

void br(){
	char c = H_LINE;
	for(int i=0;i<WIDTH;i++)
		cout<<c;
	cout<<endl;
}

#endif //USER_INTERFACE