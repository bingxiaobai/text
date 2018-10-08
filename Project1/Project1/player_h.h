#pragma once
#ifndef player_h
#define player_h

class player
{
public:
	int level;		//手牌等级
	int sum_point;		//手牌点数和
	player(int lv, int pt);
	~player();

private:

};

player::player(int lv, int pt) :level(lv), sum_point(pt)
{
}

player::~player()
{
}

class hand_card
{
public:
	int suit;   //花色
	int point;     //点数
	hand_card(int st, int pt);
	~hand_card();

private:

};

hand_card::hand_card(int st, int pt) :suit(st), point(pt)
{
}

hand_card::~hand_card()
{
}

class win
{
public:
	int straight = 0;			//顺子
	int flush = 0;			//同花
	int pair = 0;				//对子
	int same_point = 0;		//同点
	int ordinary = 0;			//杂牌
	int draw = 0;				//平局
	int player1_win = 0;	//1P获胜
	int player2_win = 0;	//2P获胜
	win();
	~win();

private:

};

win::win()
{
}

win::~win()
{
}
#endif // !player
