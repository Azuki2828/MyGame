#pragma once
class Result;
class Game;
class SaveData	: public IGameObject
{
public:
	void Save();
	void Load();

	typedef struct {
		int maxscore;	//最高記録を保存
	}SaveData_t;

	SaveData_t Data;
	Game* game = nullptr;		//まだGameはない
	Result* m_result = nullptr;	//まだResultはない
};

