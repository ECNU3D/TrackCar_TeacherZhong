#include "stm32f10x.h"

#ifndef _VAR_H_
#define	_VAR_H_
//定义一个类，里面存放经纬度数组

extern u8 heartok;//是否发送心跳数组的数据

extern u16 beat;
extern double seitatest;
extern u8 pathen;

extern double seita;

extern double head2,pitch2,roll2;

extern u8 coord[50];
extern u8 package[70];//存放三个坐标的数组

extern u8 pathrecord[1024];//存放所有的预设路径的坐标
extern double pathrecord1[1024];//存放所有的预设路径的坐标

extern u16 count;

// extern double speed;
extern u8 speeden;

extern double gaussx;
extern double gaussy;

extern u8 rotateok;

extern u8 rotateok1;
extern u8 pathok;
extern u16 pathlen;

extern u8 comd1[5];//同时读取三个角度
extern u8 comd2[5];//校准命令
extern u8 comd3[6];//设置波特率命令 ,9600
extern u8 comd4[6];//设置模块地址命令,0x10
extern u8 comd5[6];//自动应答模式

extern u8 *command1;//同时读取三个角度
extern u8 *command2;//校准命令
extern u8 *command3;//设置波特率命令 ,9600
extern u8 *command4;//设置模块地址命令,0x10
extern u8 *command5;//自动应答模式

extern u8 *ps;

typedef struct 
{
		u8 LAT[16];
		u8 LNG[16];
		double *latitude;
		double *longitude;
		
}tTuoqiu;//经纬度结构体

extern double latitude3;
extern double longitude3;

extern tTuoqiu tuoqiu1;
extern tTuoqiu *ptuoqiu;

typedef struct 
{
		double *gaosix;//未经平滑的高斯坐标
		double *gaosiy;
		double *gaosix1;//经过平滑以后的高斯坐标
		double *gaosiy1;
		
}gaosiplain;//平面坐标结构体

extern double gaosix3;
extern double gaosiy3;
extern double gaosix4;
extern double gaosiy4;

extern gaosiplain gaosiplain1;
extern gaosiplain *gaosi;

#endif

// extern u8 LAT,LNG;//定义两个指针指向存放经纬度的内存地址
// extern double f1[100];
// extern double X;
// extern double Y;

// extern double longitude2;
// extern double latitude2;

// extern double *X2;
// extern double *Y2;

// extern double px;
// extern double py;
// extern u8 anglewide;
// extern u8 seitaok;
// extern u8 testcoord0[10];
// extern u8 testcoord1[10];
// extern u8 testcoord2[10];
// extern u8 testcoord3[10];
// extern double testcoord4[10];
// extern u8 receivepackage[70];//存放接收到的打包好的数据
// extern double heading;
// extern double roll;
// extern double pitch;
// extern u8 orderen;
// extern u16 jp;
// extern u8 *order7;//加速命令
// extern u8 *order8;//减速命令
// extern u8 *order6;//减速命令
// extern u8 *order1;//加速命令
// extern u8 *order2;//减速命令

// extern u8 *order3;//加速命令
// extern u8 *order4;//减速命令

// extern u8 *order5;//加速命令


// extern u8 *stop;//停止命令

// extern u8 *right;//右转命令
// extern u8 *left;//左转命令

// extern u8 *orgright;//原地右转
// extern u8 *orgleft;//原地左转



// extern u8 *back;//后退命令

// extern u8 *emergency;

// extern u8 *remote;

// extern u8 *path;