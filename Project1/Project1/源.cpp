#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "player_h.h"			//������player,hand_card��win ����player���Ǹ��𴢴�������Ƶĵȼ��͵����͵�
								//hand_card����������¼������ƵĻ�ɫ�͵��ŵ�����
								//win����������¼�����ѭ��N����ͨ�����ַ�ʽ��ʤ�Ĵ�����1P��2P��ʤ������
#define random(a,b)(rand()%(b-a+1)+a)
using namespace std;

int winner_level = 0;		//Ӯ�ҵĵȼ���ͬ����˳�ӣ�ͬ�㣬���ӣ����ƣ�

win wy;		//��������wy�����ʤ��ʽ�ͻ�ʤ����

vector<player> game_player;		//����һ��player�������������ȼ��͵�����

vector<hand_card> player_card;	//����һ��hand_card�����������������

int deal_card()        //����
{
	int suit[6];
	int singel_point[6];
	for (int i = 0; i < 6; i++)        //����
	{
		suit[i] = random(1, 4);					//ͨ��������������ƵĻ�ɫ    ���ֻ�ɫ�ֱ���1,2,3,4����
		singel_point[i] = random(2, 14);		//ͨ��������������Ƶĵ���
	}
	for (int i = 0;i<6; i++)			//ȥ���ظ�������
	{
		for (int j = i+1; j < 6; j++)
		{
			if (suit[i] == suit[j] && singel_point[i] == singel_point[j])		//����Ƿ�����ͬ������
			{
				suit[j] = random(1, 4);					//�����������ͨ������������µĻ�ɫ�����
				singel_point[j] = random(2, 14);
				i = 0;				//����һѭ���������¼��
				break;
			}
		}
	}
	for (int i = 0, temp = 0, flag = 0; i < 3; i++)     //1P��������
	{
		for (int j = i+1; j < 3; j++)
		{
			if (singel_point[i] < singel_point[j])		//����ͬʱ������ɫ
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
	for (int i = 0; i < 3; i++)    //1P��������
	{
		player_card.push_back(hand_card(suit[i], singel_point[i]));
	}
	for (int i = 3, temp = 0, flag = 0; i < 6; i++)         //2P��������
	{
		for (int j = i + 1; j < 6; j++)
		{
			if (singel_point[i] < singel_point[j])		//����ͬʱ������ɫ
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
	for (int i = 3; i < 6; i++)        //2p��������
	{
		player_card.push_back(hand_card(suit[i], singel_point[i]));
	}
	for (int i = 0; i < 6; i++)				//��������ɵ����ƵĻ�ɫ�͵�������
	{
		suit[i] = 0;
		singel_point[i] = 0;
	}
	return 0;
}

int calculate(vector<hand_card> player_card)         //����ȼ��͵���   
{
	vector<int> sum_point;
	int lv = 0;		//�ȼ�
	int sum = 0;		//������
	for (int i = 0; i < 3; i++)
	{
		sum += player_card[i].point;       //��1p������
	}
	sum_point.push_back(sum);
	sum = 0;
	for (int i = 3; i < 6; i++)
	{
		sum += player_card[i].point;       //��2p������
	}
	sum_point.push_back(sum);
	if (player_card[0].suit == player_card[1].suit&&player_card[1].suit == player_card[2].suit)  //1pͬ��
	{
		lv = 5;
		game_player.push_back(player(lv, sum_point[0]));//����ֵ
	}
	else if ((player_card[0].point - 1) == (player_card[1].point) && (player_card[1].point - 1) == (player_card[2].point))//1p˳��
	{
		lv = 4;
		game_player.push_back(player(lv, sum_point[0]));
	}
	else if (player_card[0].point == player_card[1].point && player_card[1].point == player_card[2].point)//1pͬ��
	{
		lv = 3;
		game_player.push_back(player(lv, sum_point[0]));
	}
	else if (player_card[0].point == player_card[1].point || player_card[1].point == player_card[2].point) //1p����
	{
		lv = 2;
		game_player.push_back(player(lv, sum_point[0]));
	}
	else						//1p����
	{
		lv = 1;
		game_player.push_back(player(lv, sum_point[0]));
	}

	if (player_card[3].suit == player_card[4].suit&&player_card[4].suit == player_card[5].suit)  //2pͬ��
	{
		lv = 5;
		game_player.push_back(player(lv, sum_point[1]));//����ֵ
	}
	else if ((player_card[3].point - 1) == (player_card[4].point) && (player_card[4].point - 1) == (player_card[5].point))//2p˳��
	{
		lv = 4;
		game_player.push_back(player(lv, sum_point[1]));
	}
	else if (player_card[3].point == player_card[4].point && player_card[4].point == player_card[5].point)//2pͬ��
	{
		lv = 3;
		game_player.push_back(player(lv, sum_point[1]));
	}
	else if (player_card[3].point == player_card[4].point || player_card[4].point == player_card[5].point) //2p����
	{
		lv = 2;
		game_player.push_back(player(lv, sum_point[1]));
	}
	else						//2p����
	{
		lv = 1;
		game_player.push_back(player(lv, sum_point[1]));
	}
	return 0;
}

int winner(vector<player> game_player)      //�ж������˭��Ӯ��
{
	
	if (game_player[0].level > game_player[1].level)   //���Ƚ��еȼ��ж�
	{
		winner_level = game_player[0].level;
		wy.player1_win++;
		cout << "Ӯ����1P��";
	}
	else if (game_player[1].level > game_player[0].level)
	{
		winner_level = game_player[1].level;
		wy.player2_win++;
		cout << "Ӯ����2P��";
	}
	else if (game_player[0].sum_point > game_player[1].sum_point)      //��ν��е����ж�
	{
		winner_level = game_player[0].level;
		wy.player1_win++;
		cout << "Ӯ����1P��";
	}
	else if (game_player[1].sum_point > game_player[0].sum_point)
	{
		winner_level = game_player[1].level;
		wy.player2_win++;
		cout << "Ӯ����2P��";
	}
	else if (game_player[0].level == game_player[1].level&&game_player[0].sum_point == game_player[1].sum_point)	//ƽ���ж�
	{
		winner_level = 6;
		cout << "ƽ��";
	}
	else			//����״�����б���
	{
		cout << "error!";
		system("pause");
	}
	return 0;
}

int output(vector<hand_card> player_card)//���ÿ����ҵ�����
{
	cout << "1P������Ϊ��";
	for (int i = 0; i < 3; i++)        //���1P������
	{
		if (player_card[i].suit == 1)				//�жϻ�ɫΪ����
		{
			cout << "����" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 2)			//�жϻ�ɫΪ����
		{
			cout << "����" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 3)			//�жϻ�ɫΪ��Ƭ
		{
			cout << "��Ƭ" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 4)			//�жϻ�ɫΪ÷��
		{
			cout << "÷��" << player_card[i].point << " ";
		}
		else			//����״�����б���
		{
			cout << "error!";
			system("pause");
		}
	}
	cout << endl;
	cout << "2P������Ϊ��";
	for (int i = 3; i < 6; i++)        //���2P������
	{
		if (player_card[i].suit == 1)				//�жϻ�ɫΪ����
		{
			cout << "����" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 2)			//�жϻ�ɫΪ����
		{
			cout << "����" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 3)			//�жϻ�ɫΪ��Ƭ
		{
			cout << "��Ƭ" << player_card[i].point << " ";
		}
		else if (player_card[i].suit == 4)			//�жϻ�ɫΪ÷��
		{
			cout << "÷��" << player_card[i].point << " ";
		}
		else			//����״�����б���
		{
			cout << "error!";
			system("pause");
		}
	}
	cout << endl;
	return 0;
}

int winner_way()		//�����ʤ�ķ�ʽ
{
	if (winner_level == 5)			//ͬ��
	{
		cout << "��ͬ����" << endl;
	}
	else if (winner_level == 4)		//˳��
	{
		cout << "��˳�ӣ�" << endl;
	}
	else if (winner_level == 3)		//ͬ��
	{
		cout << "��ͬ�㣡" << endl;
	}
	else if (winner_level == 2)		//����
	{
		cout << "�Ƕ��ӣ�" << endl;
	}
	else if (winner_level == 1)		//����
	{
		cout << "�����ƣ�" << endl;
	}
	else if (winner_level == 6)		//ƽ��
	{
		cout << endl;
	}
	else			//����״�����б���
	{
		cout << "error!";
		system("pause");
	}
	cout << endl;
	return 0;
}

int statistics()			//ͳ�Ƹ�����ʽ�л�ʤ�Ĵ���
{
	if (winner_level == 5)		//ͬ����ʤ
	{
		wy.flush++;
	}
	else if (winner_level == 4)		//˳�ӻ�ʤ
	{
		wy.straight++;
	}
	else if (winner_level == 3)		//ͬ���ʤ
	{
		wy.same_point++;
	}
	else if (winner_level == 2)		//���ӻ�ʤ
	{
		wy.pair++;
	}
	else if (winner_level == 1)		//���ƻ�ʤ
	{
		wy.ordinary++;
	}
	else if (winner_level == 6)		//ƽ��
	{
		wy.draw++;
	}
	else			//����״�����б���
	{
		cout << "error!";
		system("pause");
	}
	return 0;
}	


double winrate(double win_times,double sum_times)		//����ʤ�ʣ���ʤ�������ܴ�����
{
	return (win_times / sum_times) * 100;
}

int main()
{
	double n;		//ѭ������n
	char st;
	srand((unsigned)time(0));        //��������
	cout << "������ѭ���Ĵ�����" ;
	while (cin >> st)		//��������Ƿ�Ϊ����  ����������������
	{
		if (st >= 48 && st <= 57)			//�ж��ַ��Ƿ���0-9������
		{
			cin.putback(st);			//����������0-9���־ͽ�����ַ��Ż���������
			cin >> n;					//���������е����ֶ���ѭ������n��
			break;
		}
		cout << "���������֣�";
	}
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		deal_card();		//����
		output(player_card);			//�������
		calculate(player_card);			//�������Ƶȼ��͵�����
		winner(game_player);			//�ж������˭��Ӯ��
		winner_way();				//�ж������Ӯ�һ�ʤ�ķ�ʽ
		statistics();				//����ʤ��ʽͳ�Ƶ�win_way����
		player_card.clear();			//�����һ�ֵ�����
		game_player.clear();			//�����һ�ֵ����Ƶȼ��͵�����
		winner_level = 0;			//�����һ�ֵĻ�ʤ��ʽ
	}
	cout << "˳�ӻ�ʤ" << wy.straight << "��" << "ʤ��Ϊ"<<winrate(wy.straight,n)<<"%"<<endl;
	cout << "���ӻ�ʤ" << wy.pair << "��" << "ʤ��Ϊ" << winrate(wy.pair, n) <<"%"<< endl;
	cout << "ͬ����ʤ" << wy.flush << "��" << "ʤ��Ϊ" << winrate(wy.flush, n) <<"%"<< endl;
	cout << "ͬ���ʤ" << wy.same_point << "��" << "ʤ��Ϊ" << winrate(wy.same_point, n) <<"%"<< endl;
	cout << "���ƻ�ʤ" << wy.ordinary << "��" << "ʤ��Ϊ" << winrate(wy.ordinary, n) <<"%"<< endl;
	cout << "1P��ʤ�ĸ���Ϊ" << winrate(wy.player1_win, n) << "% 2P��ʤ�ĸ���Ϊ" << winrate(wy.player2_win, n) << "% ";
	cout << "ƽ�ִ���Ϊ��" << wy.draw << "��" << endl;
	system("pause");
	return 0;
}
