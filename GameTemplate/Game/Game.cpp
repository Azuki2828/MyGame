#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "GameTime.h"
#include "MainCamera.h"
#include "Key.h"
#include "GameTime.h"
#include "SaveData.h"
#include "ResultScene.h"
#include "TreasureBox.h"

bool Game::Start() {



	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	m_gameStartTime = 3.0f * g_graphicsEngine->GetGraphicTime();
	PhysicsWorld::GetInstance()->SetGravity({ 0, -300, 0 });
	g_camera3D->SetUp({ 0.0f,1.0f,0.0f });

	//セーブを追加
	m_saveData = NewGO<SaveData>(0, "savedata");
	//m_savedata->FileSave();
	m_saveData->Load();

	//float a = m_resulttime;
	//m_ghostBox.CreateBox(
	//	{ 500.0f, 405.0f, 0.0f },	//第一引数は座標。
	//	Quaternion::Identity,		//第二引数は回転クォータニオン。
	//	{ 200.0f, 200.0f, 750.0f }	//第三引数はボックスのサイズ。
	//);

	//m_dirLight = NewGO<DirectionLight>(0, "backGroundLight");
	//m_dirLight->SetLigDirection(0.0f, 1.0f, 0.0f);
	//m_dirLight->SetLigColor();
	//カメラを生成。
	m_camera = NewGO<MainCamera>(0, "maincamera");
	//プレイヤーを生成。
	m_player = NewGO<Player>(0, "player");
	//地形を生成。
	m_backGround = NewGO<BackGround>(0, "background");
	//フォントレンダーを生成
	m_fontRender = NewGO<FontRender>(2);
	//時間経過を表示
	m_fontRender->Init(L"Time", { -500.0f,310.0f });	//場所
	m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });	//白色
	m_fontRender->SetShadowParam(true, 1.0f, Vector4::Black);

	//pivotが使えないからコメントアウトしています。
	//m_fontRender->SetPivot({ 1.0f, 0.0f });				//中心を右側に

	//m_recordfontRender = NewGO<FontRender>(2);
	//wchar_t text[64];
	//swprintf_s(text, L"%2.1f", m_saveData->Data.record);
	//m_recordfontRender->Init(text);
	//m_recordfontRender->SetText(text);
	//m_recordfontRender->SetPosition({ 500.0f, 300.0f });

	return true;
}

Game::~Game()
{
	DeleteGO(m_saveData);
	//DeleteGO(m_dirLight);
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_camera);
	DeleteGO(m_fontRender);
	/*if (m_effect != nullptr) {
		DeleteGO(m_effect);
	}*/
}

void Game::Update() {

	//カメラのスクロールが終わってプレイヤーの視点になる。且つ、ワンショット再生させるためのフラグ。
	if (m_camera->GetCameraScrollFlg() == false && m_startSoundflg == true) {

		SoundManager::GetInstance()->Play(SE_CountDown);

		m_countDownSprite = true;
		m_startSoundflg = false;
	}

	//カウントダウンが鳴りだしたら、
	if (m_countDownSprite == true) {
		//カウントダウンスプライトを表示。
		switch (m_countDownTimer) {
		 case 0:
			//「3」表示
			 HUD::GetHUD()->Init("Assets/image/3.dds", 1000.0f, 1000.0f);
			 HUD::GetHUD()->SetPosition(0, { 0.0f,0.0f,0.0f });
			//m_sprite[0] = NewGO<SpriteRender>(3);
			//m_sprite[0]->SetPosition({ 0.0f,0.0f,0.0f });
			//m_sprite[0]->Init("Assets/image/3.dds", 1000.0f, 1000.0f);

			break;

		 case 60:
			//「3」削除。
			//DeleteGO(m_sprite[0]);
			 HUD::GetHUD()->Deactivate(0);

			//「2」表示
			HUD::GetHUD()->Init("Assets/image/2.dds", 1000.0f, 1000.0f);
			HUD::GetHUD()->SetPosition(1, { 0.0f,0.0f,0.0f });
			//m_sprite[1] = NewGO<SpriteRender>(3);
			//m_sprite[1]->SetPosition({ 0.0f,0.0f,0.0f });
			//m_sprite[1]->Init("Assets/image/2.dds", 1000.0f, 1000.0f);

			break;

		 case 120:
			//「2」削除。
			//DeleteGO(m_sprite[1]);
			 HUD::GetHUD()->Deactivate(1);

			//「1」表示
			HUD::GetHUD()->Init("Assets/image/1.dds", 1000.0f, 1000.0f);
			HUD::GetHUD()->SetPosition(2, { 0.0f,0.0f,0.0f });
			//m_sprite[2] = NewGO<SpriteRender>(3);
			//m_sprite[2]->SetPosition({ 0.0f,0.0f,0.0f });
			//m_sprite[2]->Init("Assets/image/1.dds", 1000.0f, 1000.0f);

			break;

		 case 180:
			//「1」削除。
			//DeleteGO(m_sprite[2]);
			 HUD::GetHUD()->Deactivate(2);
			 m_gameStartFlg = true;
			//「GO!!」表示
			HUD::GetHUD()->Init("Assets/image/GO.dds", 1000.0f, 1000.0f);
			HUD::GetHUD()->SetPosition(3, { 0.0f,0.0f,0.0f });
			//m_sprite[3] = NewGO<SpriteRender>(3);
			//m_sprite[3]->SetPosition({ 0.0f,0.0f,0.0f });
			//m_sprite[3]->Init("Assets/image/GO.dds", 1000.0f, 1000.0f);

			break;

		 case 300:
			//「GO!!」削除。
			//DeleteGO(m_sprite[3]);
			 HUD::GetHUD()->Deactivate(3);

			 m_countDownSprite = false;

			break;
		}

		m_countDownTimer++;

	}

	wchar_t text1[64];

	////スタートの効果音が鳴り終わったら
	//if (m_startSoundflg == false) {
	//	m_timer += GameTime::GameTimeFunc().GetFrameDeltaTime();		//タイム計測開始のためのタイム
	//}
	if (m_gameStartFlg && !m_player->GetTreasureFlg()) {
		m_time += GameTime::GameTimeFunc().GetFrameDeltaTime();
	}


		//スイッチ文で使いたいのでキャスト。
		switch (static_cast<int>(m_time)) {
		
		case 10:

			m_fontRender->SetPosition({ -520.0f,310.0f });	//場所
			m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });	//白色

			break;

		//100秒経過したら、
		case 100:

			m_fontRender->SetPosition({ -540.0f,310.0f });	//場所
			m_fontRender->SetColor({ 1.0f,1.0f,1.0f,1.0f });	//白色

			break;
		}
		//タイム文字表示
		swprintf_s(text1, L"%2.1f", m_time);
		m_fontRender->SetText(text1);


	if (m_player->GetTreasureFlg() == true) {			//ゴールしたら計測終了

		m_resultSceneTime += GameTime().GameTimeFunc().GetFrameDeltaTime();

		if (m_resultScene == nullptr && m_resultSceneTime >= 3.0f) {
			//BGMを削除。
			SoundManager::GetInstance()->Release(BGM_GameUpTempo);

			//ゲームクリアのサウンドを再生。
			SoundManager::GetInstance()->Play(SE_GameClear);
			m_resultScene = NewGO<ResultScene>(0, "resultscene");
			m_resultScene->SetStageNum(m_stageNum);
		}
	}

	if (m_hitPlayer)
	{
		//死ぬエフェクト再生と効果音
		if (m_player->Getrespawn() == false) {
			m_playerPos = m_player->GetPosition();
			Effect* m_death = NewGO<Effect>(0);
			m_death->Init(u"Assets/effect/death.efk");
			m_death->SetScale({ 100.0f,100.0f,100.0f });
			m_player->Setrespawn(true);
			m_death->SetPosition(m_playerPos);
			m_deathActiveState = m_player->DeactivatePlayerModel();
			m_death->Play();
			deathFlg = true;

			SoundManager::GetInstance()->Play(SE_Death);

			/*m_timer++;
			if (m_timer == 60) {
				g_engine->SetGameState(GameState::State_Game);
				m_timer = 0;*/
		}
		m_playerTimer++;
		if (m_playerTimer >= 90)
		{
			SoundManager::GetInstance()->Play(SE_ReStart);
			m_player->Setrespawn(false);
			m_playerTimer = 0;
			m_backGround->SetStart(true);
			m_hitPlayer = false;
			m_respawnEfk = false;

		}
		else if (m_playerTimer >= 80) {

			if (m_player->GetKeyFlg()) {
				m_key = FindGO<Key>("key");
				m_player->SetPosition(m_key->GetKeyPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				deathFlg = false;
			}
			else {
				m_player->SetPosition(m_player->GetStartPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				deathFlg = false;
			}
			//m_hitPlayer = false;
			if (!m_respawnEfk) {
				m_efkRespawn = NewGO<Effect>(0);
				m_efkRespawn->Init(u"Assets/effect/respawn.efk");
				m_efkRespawn->SetScale({ 100.0f,100.0f,100.0f });
				Vector3 effPos = m_player->GetPosition();
				m_efkRespawn->SetPosition(effPos);
				//treasure->Update();
				m_efkRespawn->Play();
				m_respawnEfk = true;
			}
		}
		else {
			m_player->SetPosition(m_playerPos);
		}
		m_player->ClearPower();

		if (m_efkRespawn != nullptr) {
			m_efkRespawn->SetPosition(m_player->GetPosition());
		}
		//g_engine->SetGameState(GameState::State_Dead);
	}

	//if (m_treasureBox != nullptr) {
	//	if (static_cast<int>(m_time) % 14 == 0 && !m_treasureFlg) {
	//		m_treasureBox = FindGO<TreasureBox>("treasureBox");
	//		m_effect = nullptr;
	//		m_effect = NewGO<Effect>(0);
	//		m_effect->Init(u"Assets/effect/treasure_4.efk");
	//		m_effect->SetScale({ 80.0f,80.0f,80.0f });
	//		Vector3 effPos = m_treasureBox->GetPosition();
	//		effPos += { 50.0f, -150.0f, 0.0f };
	//		m_effect->SetPosition(effPos);
	//		//treasure->Update();
	//		m_effect->Play();
	//		m_treasureFlg = true;

	//	}
	//	else if (static_cast<int>(m_time) % 15 == 1) {
	//		m_treasureFlg = false;
	//	}
	//}

	///デバック用のコマンド。
	//if (g_pad[0]->IsTrigger(enButtonX)) {
	//	NewGO<ResultScene>(0, "resultscene");
	//}

}