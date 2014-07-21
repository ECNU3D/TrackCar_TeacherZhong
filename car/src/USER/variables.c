#include "variables.h"
#include "stm32f10x.h"
#include "stdint.h"

u8 heartok=0;//是否发送心跳数组的数据

u16 beat=0;
double seitatest=0;

u8 pathen=0;

double seita;

double head2,pitch2,roll2;

u8 coord[50];
u8 package[70]={0};//存放三个坐标的数组以及电源剩余电量

u8 pathrecord[1024];//存放所有的预设路径的坐标
double pathrecord1[1024];//存放所有的预设路径的坐标

u16 count;

// double speed=0;
u8 speeden=0;

u8 rotateok=0;

u8 rotateok1=0;
u8 pathok=0;

u16 pathlen=0;

u8 comd1[5]={0x68,0x04,0x00,0x04,0x08};//同时读取三个角度
u8 comd2[5]={0x68,0x04,0x00,0x08,0x0c};//校准命令
u8 comd3[6]={0x68,0x05,0x00,0x0b,0x02,0x12};//设置波特率命令 ,9600
u8 comd4[6]={0x68,0x05,0x00,0x0f,0x10,0x15};//设置模块地址命令,0x10
u8 comd5[6]={0x68,0x05,0x00,0x0c,0x01,0x12};//自动应答模式

u8 *command1=comd1;//同时读取三个角度
u8 *command2=comd2;//校准命令
u8 *command3=comd3;//设置波特率命令 ,9600
u8 *command4=comd4;//设置模块地址命令,0x10
u8 *command5=comd5;//自动应答模式

u8 *ps;

double latitude3=0;
double longitude3=0;

tTuoqiu tuoqiu1;
tTuoqiu *ptuoqiu=&tuoqiu1;

double gaosix3=0;
double gaosiy3=0;
double gaosix4=0;
double gaosiy4=0;

gaosiplain gaosiplain1;
gaosiplain *gaosi=&gaosiplain1;



// tTuoqiu ptuoqiu=&tuoqiu1;
// tTuoqiu tuoqiu1=
// {
// 	.LAT={0,1},
// 	.LNG={0,1},
// 	.latitude=&latitude3,
// 	.longitude=&longitude3
// };
// u8 LAT,LNG;//定义两个指针指向存放经纬度的内存地址
// double f1[100];
// double X;
// double Y;

// double longitude2;
// double latitude2;

// double gaussx;
// double gaussy;


// double *X2;
// double *Y2;

// double px=0;
// double py=0;
// u8 anglewide=10;
// u8 seitaok=0;
// u8 testcoord0[10];
// u8 testcoord1[10];
// u8 testcoord2[10];
// u8 testcoord3[10];
// double testcoord4[10];
// u8 receivepackage[70];//存放接收到的打包好的数据
// double heading;
// double roll;
// double pitch;
// u8 orderen=0;
// u16 jp=0;
// u8 *order7="4fast";//加速命令
// u8 *order8="4slow";//减速命令
// u8 *order6="6fast";//减速命令


// u8 *order1="1fast";//加速命令
// u8 *order2="2fast";//减速命令

// u8 *order3="3fast";//加速命令
// u8 *order4="4fast";//减速命令

// u8 *order5="5fast";//加速命令

// u8 *stop="stop";//停止命令

// u8 *right="right";//右转命令
// u8 *left="left";//左转命令

// u8 *orgright="orgright";//原地右转
// u8 *orgleft="orgleft";//原地左转

// u8 *back="back";//后退命令

// u8 *emergency="instanthalt";

// u8 *remote="ARQ";

// u8 *path="P";