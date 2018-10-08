#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "player_h.h"			//包含类player,hand_card和win 其中player类是负责储存玩家手牌的等级和点数和的
								//hand_card类是用来记录玩家手牌的花色和单张点数的
								//win类是用来记录玩家在循环N次中通过各种方式获胜的次数和1P与2P获胜次数的
#define random(a,b)(rand()%(b-a+1)+a)
using namespace std;

int winner_level = 0;		//赢家的等级（同花，顺子，同点，对子，杂牌）

win wy;		//创建对象wy储存获胜方式和获胜次数

vector<player> game_player;		//创建一个player类的向量来储存等级和点数和

vector<hand_card> player_card;	//创建一个hand_card类的向量来储存手牌

int deal_card()        //发牌
{
	int suit[6];
	int singel_point[6];
	for (int i = 0; i < 6; i++)        //发牌
	{
		suit[i] = random(1, 4);					//通过随机数生成手牌的花色    四种花色分别用1,2,3,4代替
		singel_point[i] = random(2, 14);		//通过随机数生成手牌的点数
	}
	for (int i = 0;i<6; i++)			//去除重复的手牌
	{
		for (int j = i+1; j < 6; j++)
		{
			if (suit[i] == suit[j] && singel_point[i] == singel_point[j])		//检测是否有相同的手牌
			{
				suit[j] = random(1, 4);					//如果有则重新通过随机数生成新的花色与点数
				singel_point[j] = random(2, 14);
				i = 0;				//将上一循环清零重新检测
				break;
			}
		}
	}
	for (int i = 0, temp = 0, flag = 0; i < 3; i++)     //1P手牌排序
	{
		for (int j = i+1; j < 3; j++)
		{
			if (singel_point[i] < singel_point[j])		//排序同时交换花色
			{
				temp = singel_point[i];
				singel_point[i] = singel_point[j];
				singel_point[j] = temp;
				flag = suit[i];
				suit[i] = suit[j];
				suit[j] = flag;
			}
		}
	}
	for (int i = 0; i < 3; i++)    //1P返回数组
	{
		player_card.push_back(hand_card(suit[i], singel_point[i]));
	}
	for (int i = 3, temp = 0, flag = 0; i < 6; i++)         //2P手牌排序
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (singel_point[i] < singel_point[j])		//排序同时交换花色
			{
				temp = singel_point[i];
				singel_point[i] = singel_point[j];
				singel_point[j] = temp;
				flag = suit[i];
				suit[i] = suit[j];
				suit[j] = flag;
			}
		}
	}
	for (int i = 3; i < 6; i++)        //2p返回数组
	{
		player_card.push_back(hand_card(suit[i], singel_point[i]));
	}
	for (int i = 0; i < 6; i++)				//将随机生成的手牌的花色和点数归零
	{
		suit[i] = 0;
		singel_point[i] = 0;
	}
	return 0;
}

int calculate(vector<hand_card> player_card)         //计算等级和点数   
{
	vector<int> sum_point;
	int lv = 0;		//等级
	int sum = 0;		//点数和
	for (int i = 0; i < 3; i++)
	{
		sum += player_card[i].point;       //求1p点数和
	}
	sum_point.push_back(sum);
	sum = 0;
	for (int i = 3; i < 6; i++)
	{
		sum += player_card[i].point;       //求2p点数和
	}
	sum_point.push_back(sum);
	if (player_card[0].suit == player_card[1].suit&&player_card[1].suit == player_card[2].suit)  //1p同花
	{
		lv = 5;
		game_player.push_back(player(lv, sum_point[0]));//返回值
	}
	else if ((player_card[0].point - 1) == (player_card[1].point) && (player_card[1].point - 1) == (player_card[2].point))//1p顺子
	{
		lv = 4;
		game_player.push_back(player(lv, sum_point[0]));
	}
	else if (player_card[0].point == player_card[1].point && player_card[1].point == player_card[2].point)//1p同点
	{
		lv = 3;
		game_player.push_back(player(lv, sum_point[0]));
	}
	else if (player_card[0].point == player_card[1].point || player_card[1].point == player_card[2].point) //1p对子
	{
		lv = 2;
		game_player.push_back(player(lv, sum_point[0]));
	}
	else						//1p杂牌
	{
		lv = 1;
		game_player.push_back(player(lv, sum_point[0]));
	}

	if (player_card[3].suit == player_card[4].suit&&player_card[4].suit == player_card[5].suit)  //2p同花
	{
		lv = 5;
		game_player.push_back(player(lv, sum_point[1]));//返回值
	}
	else if ((player_card[3].point - 1) == (player_card[4].point) && (player_card[4].point - 1) == (player_card[5].point))//2p顺子
	{
		lv = 4;
		game_player.push_back(player(lv, sum_point[1]));
	}
	else if (player_card[3].point == player_card[4].point && player_card[4].point == player_card[5].point)//2p同点
	{
		lv = 3;
		game_player.push_back(player(lv, sum_point[1]));
	}
	else if (player_card[3].point == player_card[4].point || player_card[4].point == player_card[5].point) //2p对子
	{
		lv = 2;
		game_player.push_back(player(lv, sum_point[1]));
	}
	else						//2p杂牌
	{
		lv = 1;
		game_player.push_back(player(lv, sum_point[1]));
	}
	return 0;
}

int winner(vector<player> game_player)      //判定并输出谁是赢家
{
	
	if (game_player[0].level > game_player[1].level)   //优先进行等级判定
	{
		winner_level = game_player[0].level;
		wy.player1_win++;
		cout << "赢家是1P！";
	}
	else if (game_player[1].level > game_player[0].level)
	{
		winner_level = game_player[1].level;
		wy.player2_win++;
		cout << "赢家是2P！";
	}
	else if (game_player[0].sum_point > game_player[1].sum_point)      //其次进行点数判定
	{
		winner_level = game_player[0].level;
		wy.player1_win++;
		cout << "赢家是1P！";
	}
	else if (game_player[1].sum_point > game_player[0].sum_point)
	{
		winner_level = game_player[1].level;
		wy.player2_win++;
		cout << "赢家是2P！";
	}
	else if (game_player[0].level == game_player[1].level&&game_player[0].sum_point == game_player[1].sum_point)	//平局判定
	{
		winner_level = 6;
		cout << "平局";
	}
	else			//意外状况进行报错
	{
		cout << "error!";
		system("pause");
	}
	return 0;
}

int output(vector<hand_card> player_card)//输出每个玩家的手牌
{
	cout << "1P的手牌为：";
	for (int i = 0; i < 3; i++)        //输出1P的手牌
	{
		if (player_card[i].suit == 1)				//判断花色为红桃
		{
			cout << "红桃" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 2)			//判断花色为黑桃
		{
			cout << "黑桃" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 3)			//判断花色为方片
		{
			cout << "方片" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 4)			//判断花色为梅花
		{
			cout << "梅花" << player_card[i].point << " ";
		}
		else			//意外状况进行报错
		{
			cout << "error!";
			system("pause");
		}
	}
	cout << endl;
	cout << "2P的手牌为：";
	for (int i = 3; i < 6; i++)        //输出2P的手牌
	{
		if (player_card[i].suit == 1)				//判断花色为红桃
		{
			cout << "红桃" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 2)			//判断花色为黑桃
		{
			cout << "黑桃" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 3)			//判断花色为方片
		{
			cout << "方片" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 4)			//判断花色为梅花
		{
			cout << "梅花" << player_card[i].point << " ";
		}
		else			//意外状况进行报错
		{
			cout << "error!";
			system("pause");
		}
	}
	cout << endl;
	return 0;
}

int winner_way()		//输出获胜的方式
{
	if (winner_level == 5)			//同花
	{
		cout << "是同花！" << endl;
	}
	else if (winner_level == 4)		//顺子
	{
		cout << "是顺子！" << endl;
	}
	else if (winner_level == 3)		//同点
	{
		cout << "是同点！" << endl;
	}
	else if (winner_level == 2)		//对子
	{
		cout << "是对子！" << endl;
	}
	else if (winner_level == 1)		//杂牌
	{
		cout << "是杂牌！" << endl;
	}
	else if (winner_level == 6)		//平局
	{
		cout << endl;
	}
	else			//意外状况进行报错
	{
		cout << "error!";
		system("pause");
	}
	cout << endl;
	return 0;
}

int statistics()			//统计各个方式中获胜的次数
{
	if (winner_level == 5)		//同花获胜
	{
		wy.flush++;
	}
	else if (winner_level == 4)		//顺子获胜
	{
		wy.straight++;
	}
	else if (winner_level == 3)		//同点获胜
	{
		wy.same_point++;
	}
	else if (winner_level == 2)		//对子获胜
	{
		wy.pair++;
	}
	else if (winner_level == 1)		//杂牌获胜
	{
		wy.ordinary++;
	}
	else if (winner_level == 6)		//平局
	{
		wy.draw++;
	}
	else			//意外状况进行报错
	{
		cout << "error!";
		system("pause");
	}
	return 0;
}	


double winrate(double win_times,double sum_times)		//计算胜率（获胜次数，总次数）
{
	return (win_times / sum_times) * 100;
}

int main()
{
	double n;		//循环次数n
	char st;
	srand((unsigned)time(0));        //设置种子
	cout << "请输入循环的次数：" ;
	while (cin >> st)		//检测输入是否为数字  若不是则重新输入
	{
		if (st >= 48 && st <= 57)			//判定字符是否是0-9的数字
		{
			cin.putback(st);			//如果检测结果是0-9数字就将这个字符放回输入流中
			cin >> n;					//将输入流中的数字读入循环次数n中
			break;
		}
		cout << "请输入数字：";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		deal_card();		//发牌
		output(player_card);			//输出手牌
		calculate(player_card);			//计算手牌等级和点数和
		winner(game_player);			//判定并输出谁是赢家
		winner_way();				//判定并输出赢家获胜的方式
		statistics();				//将获胜方式统计到win_way类中
		player_card.clear();			//清除上一轮的手牌
		game_player.clear();			//清除上一轮的手牌等级和点数和
		winner_level = 0;			//清空上一轮的获胜方式
	}
	cout << "顺子获胜" << wy.straight << "次" << "胜率为"<<winrate(wy.straight,n)<<"%"<<endl;
	cout << "对子获胜" << wy.pair << "次" << "胜率为" << winrate(wy.pair, n) <<"%"<< endl;
	cout << "同花获胜" << wy.flush << "次" << "胜率为" << winrate(wy.flush, n) <<"%"<< endl;
	cout << "同点获胜" << wy.same_point << "次" << "胜率为" << winrate(wy.same_point, n) <<"%"<< endl;
	cout << "杂牌获胜" << wy.ordinary << "次" << "胜率为" << winrate(wy.ordinary, n) <<"%"<< endl;
	cout << "1P获胜的概率为" << winrate(wy.player1_win, n) << "% 2P获胜的概率为" << winrate(wy.player2_win, n) << "% ";
	cout << "平局次数为：" << wy.draw << "次" << endl;
	system("pause");
	return 0;
}
