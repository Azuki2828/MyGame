#pragma once

class Player;

class Magnet : public IGameObject
{
public:
	bool Start() override final;
	void Update() override final;
	void SetState_N(bool plusflg = false) {
		mState = State_N;
		if (plusflg) {
			plusFlg = true;
		}
	}
	void SetState_S(bool plusflg = false) {
		mState = State_S; 
		if (plusflg) {
			plusFlg = true;
		}
	}
	void SetPosition(Vector3 pos) { m_pos = pos; }
	void Init(const char* magnetName)
	{
		char filePathtkm[256];

		sprintf(filePathtkm, "Assets/modelData/tkm/%s.tkm", magnetName);
		m_skinModelRender = NewGO<SkinModelRender>(0);
		m_skinModelRender->SetFileNametkm(filePathtkm);
		m_skinModelRender->Init(true, false);
	}
private:

	//プレイヤーに力を与える関数。
	void SetMagnetPower()const;

	bool plusFlg = false;
	mutable Vector3 m_length;
	Vector3 m_pos;

	typedef enum {
		State_N,
		State_S,
		State_Nplus,
		State_Splus,
	}Magnet_State;

	Magnet_State mState;

	Player* m_player = nullptr;

	SkinModelRender* m_skinModelRender = nullptr;
	PhysicsStaticObject m_physicsStaticObject;
};

