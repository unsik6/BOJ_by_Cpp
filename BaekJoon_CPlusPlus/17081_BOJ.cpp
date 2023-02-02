// 17081 RPG Extreme
// 그냥 게임 하나 만드는 거임. 문제 정의 너무 길어서 생략

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

// map
int N, M;
char map[101][101];
void printMap()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			cout << map[r][c];
		}
		cout << '\n';
	}
}
int RCToOffset(int _r, int _c) { return _r * M + _c; }
pair<int, int> OffsetToRC(int _offset) { return {_offset / M, _offset % M}; }

// input of character
int moveCnt;
char moveSeq[5001];	// last of input will be \0.

// gameover
#define NOT_OVER 0
#define KILL_BOSS 1
#define PLAYER_KILLED 2
#define CMD_OVER 3

// accType
#define HR 1
#define RE 2
#define CO 3
#define EX 4
#define DX 5
#define HU 6
#define CU 7

class EQUIP
{
public:
	char type;
	int accType;	// 1HR, 2RE, 3CO, 4EX, 5DX, 6HU, 7CU
	int addValue;

	EQUIP(char _t = ' ', int _accT = 0, int _value = 0) : type(_t), accType(_accT), addValue(_value) {}
};

class MONSTER
{
public:
	bool isBoss;
	string name;
	int atk, def, max_HP, cur_HP, exp;

	MONSTER() : isBoss(false), name(""), atk(0), def(0), max_HP(0), cur_HP(0), exp(0) {}
	MONSTER(int _r, int _c, string _name, int _atk, int _def, int _maxHP, int _exp)
	{
		isBoss = (map[_r][_c] == 'M' ? true : false);
		name = _name;
		atk = _atk;
		def = _def;
		max_HP = _maxHP;
		cur_HP = max_HP;
		exp = _exp;
	}

	bool getDamage(int _d)
	{
		cur_HP -= _d;
		if (cur_HP <= 0)
		{
			cur_HP = 0;
			return true;
		}
		else return false;
	}
};

// classes
class PLAYER
{
public:
	int first_r, first_c;
	int r, c;

	int max_HP, cur_HP, atk, def;
	int cur_atk, cur_def;
	int curLvl;
	int curExp;

	EQUIP weapon;
	EQUIP armor;
	vector<EQUIP> accs;

	PLAYER();
	void resetCurStats();
	void increaseExp(int _e);
	bool getDamage(int _d);
	bool HaveTheAcc(int _accT);
	bool isFullAcc();

	int r_move[4]{ 0, 0, -1, 1 };
	int c_move[4]{ -1, 1, 0 ,0 };
	void move(char _dir);
};

class MANAGER
{
public: 
	int turn = 0;
	int gameState = 0;
	string killerName = "";

private:
	int monsCnt;
	unordered_map<int, MONSTER> monsters;

	int boxesCnt;
	unordered_map<int, EQUIP> boxes;

public:
	MANAGER();	
	void createMonster(int _r, int _c, string _name, int _atk, int _def, int _maxHP, int _exp);

	int getMonsCnt() const { return monsCnt; }
	void increaseMonsCnt() { monsCnt++; }

	void createBox(int _r, int _c, char _t);

	int getBoxesCnt() const { return boxesCnt; }
	void increaseBoxesCnt() { boxesCnt++; }

	EQUIP openTheBox(int _r, int _c);

	void battle(int _r, int _c, bool _isHR, bool _isRE, bool _isCO, bool _isEX, bool _isDX, bool _isHU);
};

// global manager is only one.
MANAGER gameManager;

// Player is only one
PLAYER player;

PLAYER::PLAYER()
{
	first_r = first_c = r = c = 0;
	max_HP = cur_HP = 20;
	cur_atk = atk = cur_def = def = 2;
	curLvl = 1;
	curExp = 0;
}

void PLAYER::resetCurStats()
{
	cur_atk = atk + weapon.addValue;
	cur_def = def + armor.addValue;
}

void PLAYER::increaseExp(int _e)
{
	curExp += _e;

	// level up
	if (curExp >= 5 * curLvl)
	{
		max_HP += 5; cur_HP = max_HP;
		atk += 2; def += 2;
		curLvl++;
		curExp = 0;

		resetCurStats();
	}
}

bool PLAYER::getDamage(int _d)
{
	cur_HP -= _d;
	if (cur_HP <= 0)
	{
		cur_HP = 0;
		return true;
	}
	else return false;
}

bool PLAYER::HaveTheAcc(int _accT)
{
	for (int i = 0; i < accs.size(); i++)
	{
		if (accs[i].accType == _accT)
			return true;
	}
	return false;
}

bool PLAYER::isFullAcc()
{
	if (accs.size() >= 4)
		return true;
	else return false;
}

void PLAYER::move(char _dir)
{
	int dir;
	if (_dir == 'L') dir = 0;
	else if (_dir == 'R') dir = 1;
	else if (_dir == 'U') dir = 2;
	else if (_dir == 'D') dir = 3;
	else return;

	int nextR = r + r_move[dir];
	int nextC = c + c_move[dir];
	if (nextR <= 0 || nextR > N || nextC <= 0 || nextC > M)
	{
		nextR = r;
		nextC = c;
	}
	if (map[nextR][nextC] == '#')
	{
		nextR = r;
		nextC = c;
	}

	char nextObj = map[nextR][nextC];

	if (nextObj == '.')
	{
		r = nextR; c = nextC;
	}
	else if (nextObj == 'B')
	{
		EQUIP getItem = gameManager.openTheBox(nextR, nextC);
		if (getItem.type == 'W')
			weapon = getItem;
		else if (getItem.type == 'A')
			armor = getItem;
		else
		{
			if (!HaveTheAcc(getItem.accType) && !isFullAcc())
			{
				accs.push_back(getItem);
			}
		}
		resetCurStats();
		r = nextR; c = nextC;
	}
	else if (nextObj == '^')
	{
		int damage;
		if (HaveTheAcc(DX))
			damage = 1;
		else damage = 5;

		bool playerDie = getDamage(damage);

		if (playerDie)
		{
			if (HaveTheAcc(RE))
			{
				for (int i = 0; i < player.accs.size(); i++)
					if (player.accs[i].accType == RE)
						player.accs.erase(player.accs.begin() + i);
				player.r = player.first_r; player.c = player.first_c;
				player.cur_HP = player.max_HP;
			}
			else {
				gameManager.gameState = PLAYER_KILLED;
				gameManager.killerName = "SPIKE TRAP";
			}
		}
		else
		{
			r = nextR; c = nextC;
		}
	}
	else
	{
		gameManager.battle(nextR, nextC, HaveTheAcc(HR), HaveTheAcc(RE), HaveTheAcc(CO), HaveTheAcc(EX), HaveTheAcc(DX), HaveTheAcc(HU));
	}
}

MANAGER::MANAGER()
{
	monsCnt = 0;
	boxesCnt = 0;
}

void MANAGER::createMonster(int _r, int _c, string _name, int _atk, int _def, int _maxHP, int _exp)
{
	MONSTER mon(_r, _c, _name, _atk, _def, _maxHP, _exp);
	monsters[RCToOffset(_r, _c)] = mon;
}

void MANAGER::createBox(int _r, int _c, char _t)
{
	EQUIP acc;
	if (_t == 'O')
	{
		string inputAccType;
		cin >> inputAccType;
		int accType;
		if (inputAccType == "HR")
			accType = HR;
		else if (inputAccType == "RE")
			accType = RE;
		else if (inputAccType == "CO")
			accType = CO;
		else if (inputAccType == "EX")
			accType = EX;
		else if (inputAccType == "DX")
			accType = DX;
		else if (inputAccType == "HU")
			accType = HU;
		else if (inputAccType == "CU")
			accType = CU;
		else accType = 0;

		EQUIP acc2(_t, accType);
		acc = acc2;
	}
	else
	{
		int value;
		cin >> value;
		EQUIP acc2(_t, 0, value);
		acc = acc2;
	}

	boxes[RCToOffset(_r, _c)] = acc;
}

EQUIP MANAGER::openTheBox(int _r, int _c)
{
	EQUIP item = boxes[RCToOffset(_r, _c)];
	boxes.erase(RCToOffset(_r, _c));
	map[_r][_c] = '.';
	return item;
}

void MANAGER::battle(int _r, int _c, bool _isHR, bool _isRE, bool _isCO, bool _isEX, bool _isDX, bool _isHU)
{
	int turn = 0;
	bool victory = false;
	MONSTER mon = monsters[RCToOffset(_r, _c)];

	if (mon.isBoss && _isHU)
		player.cur_HP = player.max_HP;

	while (true)
	{
		// player turn
		if (turn % 2 == 0)
		{
			int damage = 1;
			if (turn / 2 == 0 && _isCO)
			{
				int multiple = (_isDX ? 3 : 2);
				damage = max(damage, multiple * player.cur_atk - mon.def);
			}
			else damage = max(damage, player.cur_atk - mon.def);

			if (mon.getDamage(damage))
			{
				victory = true;
				break;
			}
		}
		// monster turn
		else
		{
			int damage = 1;
			if (turn / 2 == 0 && mon.isBoss && _isHU)
			{
				damage = 0;
			}
			else damage = max(damage, mon.atk - player.cur_def);

			if (player.getDamage(damage))
			{
				victory = false;
				break;
			}
		}
		turn++;
	}

	if (victory)
	{
		monsters.erase(RCToOffset(_r, _c));
		map[_r][_c] = '.';
		if (mon.isBoss)
			gameState = KILL_BOSS;

		// 정산
		if (_isHR)
		{
			player.cur_HP += 3;
			if (player.max_HP < player.cur_HP)
				player.cur_HP = player.max_HP;
		}
		int getEXP = (_isEX ? (int)(mon.exp * 1.2) : mon.exp);
		player.increaseExp(getEXP);
		player.r = _r; player.c = _c;
	}
	else
	{
		if (_isRE)
		{
			for (int i = 0; i < player.accs.size(); i++)
				if (player.accs[i].accType == RE)
					player.accs.erase(player.accs.begin() + i);
			player.r = player.first_r; player.c = player.first_c;
			player.cur_HP = player.max_HP;
		}
		else
		{
			gameState = PLAYER_KILLED;
			killerName = mon.name;
		}
	}
}

void inputMap()
{
	cin >> N >> M;

	for (int r = 1; r <= N; r++)
	{
		char inputRow[101];
		cin >> inputRow;
		for (int c = 1; c <= M; c++)
		{
			map[r][c] = inputRow[c - 1];
			if (map[r][c] == 'M' || map[r][c] == '&')
				gameManager.increaseMonsCnt();
			else if (map[r][c] == 'B')
				gameManager.increaseBoxesCnt();
			else if (map[r][c] == '@')
			{
				player.r = player.first_r = r; player.c = player.first_c = c;
				map[r][c] = '.';
			}
		}
	}
}

void setMoveSeq()
{
	cin >> moveSeq;
}

void setMons()
{
	int cnt = gameManager.getMonsCnt();
	while (cnt > 0)
	{
		int r, c, w, a, h, e;
		string name;
		cin >> r >> c >> name >> w >> a >> h >> e;
		gameManager.createMonster(r, c, name, w, a, h, e);
		cnt--;
	}
}

void setBox()
{
	int cnt = gameManager.getBoxesCnt();
	while (cnt > 0)
	{
		int r, c; char t;
		cin >> r >> c >> t;
		gameManager.createBox(r, c, t);
		cnt--;
	}
}

void setGame()
{
	inputMap();
	setMoveSeq();
	setMons();
	setBox();
}

void output()
{
	if (gameManager.gameState != PLAYER_KILLED)
		map[player.r][player.c] = '@';
	printMap();
	cout << "Passed Turns : " << gameManager.turn << '\n';
	cout << "LV : " << player.curLvl << '\n';
	cout << "HP : " << player.cur_HP << '/' << player.max_HP << '\n';
	cout << "ATT : " << player.atk << '+' << player.weapon.addValue << '\n';
	cout << "DEF : " << player.def << '+' << player.armor.addValue << '\n';
	cout << "EXP : " << player.curExp << '/' << player.curLvl * 5 << '\n';
	if (gameManager.gameState == KILL_BOSS)
		cout << "YOU WIN!";
	else if (gameManager.gameState == PLAYER_KILLED)
		cout << "YOU HAVE BEEN KILLED BY " << gameManager.killerName << "..";
	else
		cout << "Press any key to continue.";
}

void runFrame()
{
	int seqIdx = 0;
	while (true)
	{
		if (moveSeq[seqIdx + 1] == '\0')
			gameManager.gameState = CMD_OVER;

		player.move(moveSeq[seqIdx]);
		gameManager.turn++;
		if (gameManager.gameState != 0)
			break;

		
		seqIdx++;

		// check
		/*cout << '\n';
		cout << "TURN : " << gameManager.turn << '\n';
		char tmp = map[player.r][player.c];
		map[player.r][player.c] = '@';
		printMap();
		map[player.r][player.c] = tmp;
		cout << '\n';*/
	}
	output();
}

int main()
{
	setGame();
	runFrame();

	return 0;
}