#include "stdafx.h"
#include "DeathBlock.h"
#include "Player.h"
#include "MainCamera.h"
#include "Key.h"
#include "Background.h"
#include "Game.h"

bool DeathBlock::Start() {

	m_player = FindGO<Player>("player");
	m_key = FindGO<Key>("key");
	m_backGround = FindGO<BackGround>("background");
	m_game = FindGO<Game>("game");
	m_skinModelRender->SetPosition(m_pos);

	m_skinModelRender->SetScale(m_sca);

	m_death = NewGO<Effect>(0);
	m_death->Init(u"Assets/effect/death.efk");
	m_death->SetScale({ 100.0f,100.0f,100.0f });

	m_skinModelRender->SetScale(m_sca);
	auto mainCamera = FindGO<MainCamera>("maincamera");
	mainCamera->changeRotCameraEvent.push_back([&]() {
		Quaternion m_rotZ;
		m_rotZ.SetRotationDeg(Vector3::AxisZ, -2.0f);
		m_rotZ.Apply(m_ligData.m_directionLigData[0].Dir);
		});

	m_ghostPos = m_pos;
	m_ghostPos.x += 50.0f * m_sca.x;
	m_ghostPos.y += 50.0f * m_sca.y;

	m_ghostPos.z -= 200.0f;
	m_ghostBox.CreateBox(
		m_ghostPos,	//第一引数は座標。
		Quaternion::Identity,		//第二引数は回転クォータニオン。
		{ 100.0f * m_sca.x, 100.0f * m_sca.y, 400.0f * m_sca.z}	//第三引数はボックスのサイズ。
	);

	m_skinModelRender->UpdateWorldMatrix();
	return true;
}

DeathBlock::~DeathBlock() {
	DeleteGO(m_skinModelRender);
}

void DeathBlock::Update() {

	if (m_moveFlg) {
		static bool move = false;
		if (!move) {
			Vector3 length = m_movePos[1] - m_pos;
			length.Normalize();
			m_pos += length;
			m_ghostPos += length;
			if (m_pos.x >= m_movePos[1].x) {
				move = true;
			}
		}
		else {
			Vector3 length = m_movePos[0] - m_pos;
			length.Normalize();
			m_pos += length;
			m_ghostPos += length;
			if (m_pos.x <= m_movePos[0].x) {
				move = false;
			}
		}
		m_skinModelRender->SetPosition(m_pos);
		m_ghostBox.SetPosition(m_ghostPos);
	}
	Vector3 effPos;


	PhysicsWorld::GetInstance()->ContactTest(*m_player->GetRigidBody(), [&](const btCollisionObject& contactObject) {
		m_ligData.uvNoiseOffset += 0.01f;
		float t;
		m_ligData.uvNoiseOffset = modf(m_ligData.uvNoiseOffset, &t);
		if (m_ghostBox.IsSelf(contactObject) == true) {

			//m_ghostObjectとぶつかった
			//m_pointLig->SetActiveFlag(true);	//ポイントライトをつける。
			//m_ghostBox.SetPosition({ 700.0f,405.0f,0.0f });
			m_hitPlayer = true;
			if (m_player != nullptr) {
				effPos = m_player->GetPosition();
			}
			//if (m_player->GetKeyFlg()) {
			//	m_player->SetPosition(m_key->GetKeyPos());
			//}
		}
		});


	if (m_hitPlayer && !m_player->GetTreasureFlg())
	{
		//死ぬエフェクト再生と効果音
		if (m_player->Getrespawn() == false) {
			Effect* m_death = NewGO<Effect>(0);
			m_death->Init(u"Assets/effect/death.efk");
			m_death->SetScale({ 100.0f,100.0f,100.0f });
			m_player->Setrespawn(true);
			m_death->SetPosition(m_player->GetPosition());
			m_deathActiveState = m_player->DeactivatePlayerModel();
			m_death->Play();
			m_deathFlg = true;

			SoundManager::GetInstance()->Play(SE_Death);

			/*m_timer++;
			if (m_timer == 60) {
				g_engine->SetGameState(GameState::State_Game);
				m_timer = 0;*/
		}
		m_timer++;
		if (m_timer >= 90)
		{
			SoundManager::GetInstance()->Play(SE_ReStart);
			m_player->Setrespawn(false);
			m_timer = 0;
			m_backGround->SetStart(true);
			m_hitPlayer = false;
			m_respawnEfk = false;

		}
		else if (m_timer >= 80) {

			if (m_player->GetKeyFlg()) {
				m_key = FindGO<Key>("key");
				m_player->SetPosition(m_key->GetKeyPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
			}
			else {
				m_player->SetPosition(m_player->GetStartPos());
				m_player->ActivatePlayerModel(m_deathActiveState);
				m_deathFlg = false;
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
			m_player->SetPosition(m_player->GetPosition());
		}
		m_player->ClearPower();

		if (m_efkRespawn != nullptr) {
			m_efkRespawn->SetPosition(m_player->GetPosition());
		}
		//g_engine->SetGameState(GameState::State_Dead);
	}
}

