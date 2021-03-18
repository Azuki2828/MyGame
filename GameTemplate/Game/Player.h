#pragma once

class DirectionLight;

class Player : public IGameObject
{
public:
	bool Start() override;
	void Update() override;
	~Player();

	//現在のステートを取得する関数。
	const int GetPlayerState()const { return pState; }

	//現在の座標を取得する関数。
	const Vector3 GetPosition()const { return m_charaCon.GetPosition(); }

	//外部から力を受け取る関数。
	//pow：力の大きさ
	void ReceivePower(Vector3 pow)const { m_movePower += pow; }

	//プレイヤーの磁極を変換する関数。
	void ChangeState();

	void Render(RenderContext& rc)override;

private:
	/// <summary>
	/// アニメーションクリップ。
	/// </summary>
	enum EnAnimationClip {
		enAnimClip_Idle,
		enAnimClip_Run,
		enAnimClip_Num,
	};

	/// <summary>
	/// 磁極。
	/// </summary>
	typedef enum {
		State_N,
		State_S,
	}Player_State;

	/// <summary>
	/// プレイヤーの登録番号。
	/// </summary>
	enum EnPlayer {
		enPlayer_0,
		enPlayer_1,
		enPlayer_Num
	};
	//プレイヤーのステート。
	Player_State pState = State_N;

	Model m_model;										//モデル表示処理。
	ModelInitData initData;								//モデルのデータ。
	Animation m_animation;								//アニメション再生処理。
	AnimationClip m_animationClips[enAnimClip_Num];		//アニメーションクリップ。
	Skeleton m_skeleton;								//スケルトン。
	CharacterController m_charaCon;						//キャラコン。

	DirectionLight* m_dirLight = nullptr;				//ディレクションライト。
	Vector3 m_pos = { 300.0f,300.0f,0.0f };				//初期座標。
	//Vector3 m_pos = { 1500.0f,2800.0f,0.0f };
	//Vector3 m_pos = { 1500.0f,2800.0f,20.0f };
	mutable Vector3 m_movePower;						//動く力。

	SkinModelRender* m_skinModelRender[enPlayer_Num] = { nullptr };
	Font m_font;

	Quaternion m_rotation;
	//正面を向かせる変数
	float rot = 180.0f;
	//正面を向かせる変数に合成させるボールの転がりの変数
	Quaternion m_rotation1;
	float rot1 = 0.0f;

	bool RespornFlag = false;
	int RespornCount = 0;

	bool PushBFlag = true;
	int PushBCount = 0;
};