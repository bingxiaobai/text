#pragma once
#ifndef player_h
#define player_h

class player
{
public:
	int level;		//���Ƶȼ�
	int sum_point;		//���Ƶ�����
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
	int suit;   //��ɫ
	int point;     //����
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
	int straight = 0;			//˳��
	int flush = 0;			//ͬ��
	int pair = 0;				//����
	int same_point = 0;		//ͬ��
	int ordinary = 0;			//����
	int draw = 0;				//ƽ��
	int player1_win = 0;	//1P��ʤ
	int player2_win = 0;	//2P��ʤ
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
