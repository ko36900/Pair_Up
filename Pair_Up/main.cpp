//------------READ-ME--------------------------------------------
//标记nedOPT的地方意味着需要优化
//标记+的地方意味着需要添加

//Update7-7: 现已确定方块的属性是 Piece.type		(0，6]    match to six different piece basic type
//			 特殊方块：			Piece.specType	[0，6]	  match to seven different piece addition type
//			specType:			
/*
* 0.ori-原始方块-什么都不做		
* 1.line-消除列
* 2.row-消除行		
* 3.box-消除3*3	
* 4.same_color-消除同色
* 5.unclear-不可消除	
* 6.death-直接死亡
*/

//Update7-7:Please add getter and setter for your class :D
//Update7-7:Please change your function name to match main function as possible~ 
//Update7-8:对Map类请求：增添一个数据域读取消除方块的总数
//Update7-8:Map在中间删除元素后 其中的迭代器会失效，请注意在循环里重建新迭代器
//Update7-8:-无效信息-Map队列使用左上角为坐标原点
//Update7-8:Map队列更新为使用左下角为坐标原点
//Update7-8:游戏窗口大小为1476*1016
//Update7-9:每个Piece大小:100*100，有效区域:98*98，Map区域大小:900*900，左上原点位置:(x_map_LT,y_map_LT)，左下原点位置:(x_map_LB,y_map_LB)		
//			每块[x][y]piece坐标的位置：
//Update7-9:同名请求： 统一函数命名 检查是否-is 配对-pair 消除-clear 记分板（排行榜）-leaderboard 块-piece 图-map 分数-score 创造-make 判定旗帜-flag
//			旧的，原始的-ori 新的-new
//			gameMode下的函数请加 "g_" 前缀，learboardMode下的函数请加 "l_" 前缀
//Update7-9:坐标全部使用传参处理
//Update7-10:暂停继续按钮坐标:(85 802)(327 802)
#define YAGE //注释则打开EGE模式
#ifdef YAGE
#include "yage.h"
#else
#include "graphics.h"
#endif 

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <ctime>
#include "leaderboardMode.h"
#include "Map.h"
#include "Piece.h"
#include "Global.h"
#include "Button.h"
#include "gameMode.h"
#include "optionMode.h"
//接口函数列表
//g_makeMap();
//g_isDead();
//g_playerMove();			
//g_checkPair(oriMap);
//g_pairUp();
//g_setMap();
//g_replenishMap();

void resource(Option);
void resourceSkin_yage(int);
void resourceSkin_ege(int);
int gameMode();
int leaderboardMode();//+
int optionMode();//+
int exitMode();
int init(void);
void meun(int);
//
int start_yage()
{
	return 1;
}
int main(int argc, char*argv[])
{

	init();

#ifdef YAGE
	while (start_yage())
		meun(start_yage());
	yage_quit();
#else
	while (start_ege())
		meun(start_ege());
#endif
	return 0;
}

int init(void)
{
	srand((unsigned)time(0));
	yage_init(Global::x_scr, Global::y_scr);
	return 0;
}

//NEED TO FIX:
//CONDITION WILL ALWAYS BE 1 IT CAUSE INFINITY LOOP
void meun(int playerChoose)
{
	int condition = 1;

		switch (playerChoose)
		{
		case 1:
			condition = gameMode();
			//start game
			break;
		case 2:
			//open record mode
			condition = leaderboardMode();
			break;
		case 3:
			//option
			condition = optionMode();
			break;
		case 4:
			//exit program
			condition = exitMode();
			break;
		default:
			condition = 1;
			break;
		}
}

int gameMode()
{
	g_game();
	return 1;
}

int leaderboardMode()
{	
	l_leaderboard();
	return 1;
}

int optionMode()
{	
	o_option();
	return 1;
}

int exitMode()
{
	return 0;
}

void resource(Option option)
{
#ifdef YAGE
	struct yage_canvas *Background = yage_canvas_load_image("Bk.png");
	resourceSkin_yage(option.getSkin());
#else
	resourceSkin_ege(option.getSkin());
#endif

}

//Only Yage
void resourceSkin_yage(int skin)
{
	std::vector<struct yage_canvas *> pieceSkin;
	std::string temp;
	std::stringstream ss;
	//加载6*5=30张皮肤 (6种方块每个有5种特殊方块）
	for (int i = 1; i != 7; ++i)
		for (int j = 0; j != 7; ++j)
		{
			ss << "Skin" << skin << "_Piece_" << i << "_" << j << ".png";
			ss >> temp;
			ss.clear();
			std::cout << temp << std::endl;
			pieceSkin.push_back(yage_canvas_load_image(temp.c_str()));
		}
		ss << "Skin" << skin << "_Piece_Special_1";
		ss >> temp;
		ss.clear();
		struct yage_canvas *specPiece1 = yage_canvas_load_image(temp.c_str());
		ss << "Skin" << skin << "_Piece_Special_2";
		ss >> temp;
		ss.clear();
		struct yage_canvas *specPiece2 = yage_canvas_load_image(temp.c_str());

}