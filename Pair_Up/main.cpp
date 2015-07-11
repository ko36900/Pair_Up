//------------READ-ME--------------------------------------------
//���nedOPT�ĵط���ζ����Ҫ�Ż�
//���+�ĵط���ζ����Ҫ���

//Update7-7: ����ȷ������������� Piece.type		(0��6]    match to six different piece basic type
//			 ���ⷽ�飺			Piece.specType	[0��6]	  match to seven different piece addition type
//			specType:			
/*
* 0.ori-ԭʼ����-ʲô������		
* 1.line-������
* 2.row-������		
* 3.box-����3*3	
* 4.same_color-����ͬɫ
* 5.unclear-��������	
* 6.death-ֱ������
*/

//Update7-7:Please add getter and setter for your class :D
//Update7-7:Please change your function name to match main function as possible~ 
//Update7-8:��Map����������һ���������ȡ�������������
//Update7-8:Map���м�ɾ��Ԫ�غ� ���еĵ�������ʧЧ����ע����ѭ�����ؽ��µ�����
//Update7-8:-��Ч��Ϣ-Map����ʹ�����Ͻ�Ϊ����ԭ��
//Update7-8:Map���и���Ϊʹ�����½�Ϊ����ԭ��
//Update7-8:��Ϸ���ڴ�СΪ1476*1016
//Update7-9:ÿ��Piece��С:100*100����Ч����:98*98��Map�����С:900*900������ԭ��λ��:(x_map_LT,y_map_LT)������ԭ��λ��:(x_map_LB,y_map_LB)		
//			ÿ��[x][y]piece�����λ�ã�
//Update7-9:ͬ������ ͳһ�������� ����Ƿ�-is ���-pair ����-clear �Ƿְ壨���а�-leaderboard ��-piece ͼ-map ����-score ����-make �ж�����-flag
//			�ɵģ�ԭʼ��-ori �µ�-new
//			gameMode�µĺ������ "g_" ǰ׺��learboardMode�µĺ������ "l_" ǰ׺
//Update7-9:����ȫ��ʹ�ô��δ���
//Update7-10:��ͣ������ť����:(85 802)(327 802)
#define YAGE //ע�����EGEģʽ
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
//�ӿں����б�
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
	//����6*5=30��Ƥ�� (6�ַ���ÿ����5�����ⷽ�飩
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