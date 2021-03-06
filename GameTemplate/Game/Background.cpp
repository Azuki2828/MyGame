#include "stdafx.h"
#include "Background.h"
#include "Magnet.h"
#include "Key.h"
#include "GameLevel2D.h"
#include "Game.h"
#include "Player.h"
#include "TreasureBox.h"
#include "DeathBlock.h"
#include "Seesaw.h"

namespace {
	const int STAGE_NUM = 4;
	Vector3 stageStartPos[STAGE_NUM] = {
		{ 300.0f,1200.0f,-300.0f },
		{ 300.0f,300.0f,-300.0f },
		{ 300.0f,1300.0f,-300.0f },
		{ 300.0f,1900.0f,-300.0f }
	};
}

bool BackGround::Start()
{
	const char* stageFilePath[] = {
		"Assets/level/stage01_treasure.tkl",
		"Assets/level/stage02_treasure.tkl",
		"Assets/level/stage03_treasure.tkl",
		"Assets/level/stage04_treasure.tkl"
	};
	m_game = FindGO<Game>("game");
	m_player = FindGO<Player>("player");

	m_stageNum = m_game->GetStageNum();


	/*const char* MagnetName[] = {
		"Magnet_N_01",
		"Magnet_N_02",
		"Magnet_N_03",
		"Magnet_N_04",
		"Magnet_N_05",
		"Magnet_N_06",
		"Magnet_N_move_01",
		"Magnet_Nplus_01",
		"Magnet_S_01",
		"Magnet_S_02",
		"Magnet_S_03",
		"Magnet_Splus_01",
		"MagnetHoge",
	};*/

	//ゲーム画面のUI表示
	m_level2D = NewGO<GameLevel2D>(1,"gamescreenlevel2d");

	//背景画像を初期化。
	m_spriteRender = NewGO<SpriteRender>(0);
	m_spriteRender->SetPosition(Vector3::Zero);
	m_spriteRender->Init("Assets/image/eheheNS03.dds", 1300.0f, 750.0f);


	LevelInit(stageFilePath[m_stageNum - 1]);
	m_deathPosY = -500.0f;
	//switch (m_stageNum) {
	//case 1:
	//	//これがlevelのLoadの基盤。
	//	//特定のオブジェクトを指定する（ここでいうフック）場合は、名前検索する。
	//	m_level.Init("Assets/level/stage01_treasure.tkl", [&](LevelObjectData& objData) {


	//		//return true;が自分で生成。return false;がパソコンが生成してくれる。
	//		//falseだと生成勝手にしてくれるけど、位置変えたりとかいじれない！！

	//		m_deathPosY = -500.0f;		//state02では-500.0fで死ぬ！

	//		if (objData.EqualObjectName(L"Key_after") == true) {
	//			if (m_key == nullptr) {
	//				m_key = NewGO<Key>(0, "key");
	//			}
	//			m_key->InitKey("Key_after");
	//			m_key->SetKeyPos(objData.position);
	//			m_key->SetScaleKey(objData.scale);
	//			m_key->SetTriggerBox(objData.position);
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"KeyBox") == true) {
	//			if (m_key == nullptr) {
	//				m_key = NewGO<Key>(0, "key");
	//			}
	//			m_key->InitDoor("KeyBox");
	//			m_key->SetDoorPos(objData.position);


	//			m_key->SetScaleDoor(objData.scale);
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"TreasureBox") == true) {

	//			Effect* treasure = nullptr;
	//			treasure = NewGO<Effect>(0);
	//			treasure->Init(u"Assets/effect/treasure_4.efk");
	//			treasure->SetScale({ 80.0f,80.0f,80.0f });
	//			Vector3 effPos = objData.position;
	//			effPos += { 50.0f, -150.0f, 60.0f };
	//			treasure->SetPosition(effPos);
	//			//treasure->Update();
	//			treasure->Play();

	//			m_treasureBox = NewGO<TreasureBox>(0, "treasureBox");
	//			Vector3 pos = objData.position;
	//			pos.x -= 75.0f;
	//			pos.z -= 50.0f;
	//			m_treasureBox->SetPosition(pos);
	//			m_treasureBox->SetRotation(objData.rotation);
	//			Vector3 sca = objData.scale;
	//			sca.x = 2.5f;
	//			sca.y = 2.5f;
	//			sca.z = 2.5f;
	//			m_treasureBox->SetScale(sca);

	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_100") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N100_100");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_100") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_100");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 150.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_-200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N100_-200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetRotation(objData.rotation);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 150.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N-100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N-100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S-100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S-100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 150.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S-100_-200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S-100_-200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_-200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_-200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"DeathBlock") == true) {
	//		m_deathBlock.push_back(NewGO<DeathBlock>(0));
	//		m_deathBlock[deathBlockNum]->Init("DeathBlock");
	//		m_deathBlock[deathBlockNum]->SetPosition(objData.position);
	//		m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//		m_deathBlock[deathBlockNum]->SetStartPos({ 300.0f,1200.0f,-300.0f });
	//		m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//		deathBlockNum++;
	//		return true;
	//		}
	//		

	//		return false;//levelのオブジェクトをそのままロード。
	//	});

	//	m_player->SetPosition({ 300.0f,1200.0f,-300.0f });
	//	m_player->SetStartPos({ 300.0f,1200.0f,-300.0f });
	//	break;
	//case 2:
	//	m_level.Init("Assets/level/stage02_treasure.tkl", [&](LevelObjectData& objData) {


	//		//return true;が自分で生成。return false;がパソコンが生成してくれる。
	//		//falseだと生成勝手にしてくれるけど、位置変えたりとかいじれない！！

	//		m_deathPosY = -500.0f;		//state02では-500.0fで死ぬ！

	//		if (objData.EqualObjectName(L"Key_after") == true) {
	//			if (m_key == nullptr) {
	//				m_key = NewGO<Key>(0, "key");
	//			}
	//			m_key->InitKey("Key_after");
	//			m_key->SetKeyPos(objData.position);
	//			m_key->SetScaleKey(objData.scale);
	//			m_key->SetTriggerBox(objData.position);
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"KeyBox") == true) {
	//			if (m_key == nullptr) {
	//				m_key = NewGO<Key>(0, "key");
	//			}
	//			m_key->InitDoor("KeyBox");
	//			m_key->SetDoorPos(objData.position);

	//			m_key->SetScaleDoor(objData.scale);
	//			
	//			Effect* treasure = nullptr;
	//			treasure = NewGO<Effect>(0);
	//			treasure->Init(u"Assets/effect/treasure_4.efk");
	//			treasure->SetScale({ 80.0f,80.0f,80.0f });
	//			Vector3 effPos = objData.position;
	//			effPos += { 200.0f, -150.0f, -200.0f };
	//			treasure->SetPosition(effPos);
	//			//treasure->Update();
	//			treasure->Play();
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"TreasureBox") == true) {

	//			m_treasureBox = NewGO<TreasureBox>(0, "treasureBox");
	//			Vector3 pos = objData.position;
	//			pos.x -= 75.0f;
	//			pos.z -= 50.0f;
	//			m_treasureBox->SetPosition(pos);
	//			m_treasureBox->SetRotation(objData.rotation);
	//			Vector3 sca = objData.scale;
	//			sca.x = 2.5f;
	//			sca.y = 2.5f;
	//			sca.z = 2.5f;
	//			m_treasureBox->SetScale(sca);
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_100") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N100_100");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_100") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_100");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 150.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N-100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N-100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_-200triangle") == true) {
	//		m_magnet.push_back(*(m_magnet.end() - 1));
	//		m_magnet[sampleNum] = NewGO<Magnet>(0);
	//		m_magnet[sampleNum]->SetState_N();
	//		m_magnet[sampleNum]->Init("Magnet_N100_-200triangle");
	//		m_magnet[sampleNum]->SetPosition(objData.position);
	//		m_magnet[sampleNum]->SetRotation(objData.rotation);
	//		Vector3 m_magPos = objData.position;
	//		m_magPos.x += 50.0f;
	//		m_magPos.y -= 50.0f;
	//		m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//		m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//		sampleNum++;
	//		return true;
	//			}
	//		else if (objData.EqualObjectName(L"Magnet_S-100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S-100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S-100_-200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S-100_-200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_-200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_-200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"DeathBlock") == true) {
	//		m_deathBlock.push_back(NewGO<DeathBlock>(0));
	//		m_deathBlock[deathBlockNum]->Init("DeathBlock");
	//		m_deathBlock[deathBlockNum]->SetPosition(objData.position);
	//		m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//		m_deathBlock[deathBlockNum]->SetStartPos({ 300.0f,300.0f,-300.0f });
	//		m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//		deathBlockNum++;
	//		return true;
	//		}

	//		return false;//levelのオブジェクトをそのままロード。
	//		});
	//		m_player->SetPosition({ 300.0f,300.0f,-300.0f });
	//		m_player->SetStartPos({ 300.0f,300.0f,-300.0f });
	//	break;
	//case 3:

	//	m_level.Init("Assets/level/stage03_treasure.tkl", [&](LevelObjectData& objData) {


	//		//return true;が自分で生成。return false;がパソコンが生成してくれる。
	//		//falseだと生成勝手にしてくれるけど、位置変えたりとかいじれない！！

	//		m_deathPosY = -500.0f;		//state02では-500.0fで死ぬ！

	//		if (objData.EqualObjectName(L"Key_after") == true) {
	//			if (m_key == nullptr) {
	//				m_key = NewGO<Key>(0, "key");
	//			}
	//			m_key->InitKey("Key_after");
	//			m_key->SetKeyPos(objData.position);
	//			m_key->SetScaleKey(objData.scale);
	//			m_key->SetTriggerBox(objData.position);
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"KeyBox") == true) {
	//			if (m_key == nullptr) {
	//				m_key = NewGO<Key>(0, "key");
	//			}
	//			m_key->InitDoor("KeyBox");
	//			m_key->SetDoorPos(objData.position);

	//			m_key->SetScaleDoor(objData.scale);

	//			Effect* treasure = nullptr;
	//			treasure = NewGO<Effect>(0);
	//			treasure->Init(u"Assets/effect/treasure_4.efk");
	//			treasure->SetScale({ 80.0f,80.0f,80.0f });
	//			Vector3 effPos = objData.position;
	//			effPos += { 200.0f, -150.0f, -200.0f };
	//			treasure->SetPosition(effPos);
	//			//treasure->Update();
	//			treasure->Play();
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"TreasureBox") == true) {

	//			m_treasureBox = NewGO<TreasureBox>(0, "treasureBox");
	//			Vector3 pos = objData.position;
	//			pos.x -= 75.0f;
	//			pos.z -= 50.0f;
	//			m_treasureBox->SetPosition(pos);
	//			m_treasureBox->SetRotation(objData.rotation);
	//			Vector3 sca = objData.scale;
	//			sca.x = 2.5f;
	//			sca.y = 2.5f;
	//			sca.z = 2.5f;
	//			m_treasureBox->SetScale(sca);
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_100") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N100_100");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_100") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_100");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 150.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N-100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_N();
	//			m_magnet[sampleNum]->Init("Magnet_N-100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_N100_-200triangle") == true) {
	//		m_magnet.push_back(*(m_magnet.end() - 1));
	//		m_magnet[sampleNum] = NewGO<Magnet>(0);
	//		m_magnet[sampleNum]->SetState_N();
	//		m_magnet[sampleNum]->Init("Magnet_N100_-200triangle");
	//		m_magnet[sampleNum]->SetPosition(objData.position);
	//		m_magnet[sampleNum]->SetRotation(objData.rotation);
	//		Vector3 m_magPos = objData.position;
	//		m_magPos.x += 50.0f;
	//		m_magPos.y -= 50.0f;
	//		m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//		m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//		sampleNum++;
	//		return true;
	//			}
	//		else if (objData.EqualObjectName(L"Magnet_S-100_200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S-100_200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S-100_-200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S-100_-200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y += 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"Magnet_S100_-200triangle") == true) {
	//			m_magnet.push_back(*(m_magnet.end() - 1));
	//			m_magnet[sampleNum] = NewGO<Magnet>(0);
	//			m_magnet[sampleNum]->SetState_S();
	//			m_magnet[sampleNum]->Init("Magnet_S100_-200triangle");
	//			m_magnet[sampleNum]->SetPosition(objData.position);
	//			Vector3 m_magPos = objData.position;
	//			m_magPos.x += 50.0f;
	//			m_magPos.y -= 50.0f;
	//			m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//			m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//			sampleNum++;
	//			return true;
	//		}
	//		else if (objData.EqualObjectName(L"DeathBlock") == true) {
	//		m_deathBlock.push_back(NewGO<DeathBlock>(0));
	//		m_deathBlock[deathBlockNum]->Init("DeathBlock");
	//		m_deathBlock[deathBlockNum]->SetPosition(objData.position);
	//		m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//		m_deathBlock[deathBlockNum]->SetStartPos({ 300.0f,1300.0f,-300.0f });
	//		m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//		deathBlockNum++;
	//		return true;
	//		}

	//		return false;//levelのオブジェクトをそのままロード。
	//	});

	//		m_player->SetPosition({ 300.0f,1300.0f,-300.0f });
	//		m_player->SetStartPos({ 300.0f,1300.0f,-300.0f });
	//	break;
	//case 4:

	//		m_level.Init("Assets/level/stage04_treasure.tkl", [&](LevelObjectData& objData) {


	//			//return true;が自分で生成。return false;がパソコンが生成してくれる。
	//			//falseだと生成勝手にしてくれるけど、位置変えたりとかいじれない！！

	//			m_deathPosY = -500.0f;		//state02では-500.0fで死ぬ！

	//			if (objData.EqualObjectName(L"Key_after") == true) {
	//				if (m_key == nullptr) {
	//					m_key = NewGO<Key>(0, "key");
	//				}
	//				m_key->InitKey("Key_after");
	//				m_key->SetKeyPos(objData.position);
	//				m_key->SetScaleKey(objData.scale);
	//				m_key->SetTriggerBox(objData.position);
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"KeyBox") == true) {
	//				if (m_key == nullptr) {
	//					m_key = NewGO<Key>(0, "key");
	//				}
	//				m_key->InitDoor("KeyBox");
	//				m_key->SetDoorPos(objData.position);

	//				m_key->SetScaleDoor(objData.scale);

	//				Effect* treasure = nullptr;
	//				treasure = NewGO<Effect>(0);
	//				treasure->Init(u"Assets/effect/treasure_4.efk");
	//				treasure->SetScale({ 80.0f,80.0f,80.0f });
	//				Vector3 effPos = objData.position;
	//				effPos += { 200.0f, -150.0f, -200.0f };
	//				treasure->SetPosition(effPos);
	//				//treasure->Update();
	//				treasure->Play();
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"TreasureBox") == true) {

	//				m_treasureBox = NewGO<TreasureBox>(0, "treasureBox");
	//				Vector3 pos = objData.position;
	//				pos.x -= 75.0f;
	//				pos.z -= 50.0f;
	//				m_treasureBox->SetPosition(pos);
	//				m_treasureBox->SetRotation(objData.rotation);
	//				Vector3 sca = objData.scale;
	//				sca.x = 2.5f;
	//				sca.y = 2.5f;
	//				sca.z = 2.5f;
	//				m_treasureBox->SetScale(sca);
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_N100_100") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_N();
	//				m_magnet[sampleNum]->Init("Magnet_N100_100");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				Vector3 m_magPos = objData.position;
	//				m_magPos.x += 50.0f;
	//				m_magPos.y += 50.0f;
	//				m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_S100_100") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_S();
	//				m_magnet[sampleNum]->Init("Magnet_S100_100");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				Vector3 m_magPos = objData.position;
	//				m_magPos.x += 50.0f;
	//				m_magPos.y += 50.0f;
	//				m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_N100_200triangle") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_N();
	//				m_magnet[sampleNum]->Init("Magnet_N100_200triangle");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_S100_200triangle") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_S();
	//				m_magnet[sampleNum]->Init("Magnet_S100_200triangle");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				Vector3 m_magPos = objData.position;
	//				m_magPos.x += 150.0f;
	//				m_magPos.y -= 50.0f;
	//				m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_N-100_200triangle") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_N();
	//				m_magnet[sampleNum]->Init("Magnet_N-100_200triangle");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_N100_-200triangle") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_N();
	//				m_magnet[sampleNum]->Init("Magnet_N100_-200triangle");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				Vector3 m_magPos = objData.position;
	//				m_magPos.x += 50.0f;
	//				m_magPos.y += 50.0f;
	//				m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_S-100_200triangle") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_S();
	//				m_magnet[sampleNum]->Init("Magnet_S-100_200triangle");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_S-100_-200triangle") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_S();
	//				m_magnet[sampleNum]->Init("Magnet_S-100_-200triangle");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				Vector3 m_magPos = objData.position;
	//				m_magPos.x += 50.0f;
	//				m_magPos.y += 50.0f;
	//				m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"Magnet_S100_-200triangle") == true) {
	//				m_magnet.push_back(*(m_magnet.end() - 1));
	//				m_magnet[sampleNum] = NewGO<Magnet>(0);
	//				m_magnet[sampleNum]->SetState_S();
	//				m_magnet[sampleNum]->Init("Magnet_S100_-200triangle");
	//				m_magnet[sampleNum]->SetPosition(objData.position);
	//				m_magnet[sampleNum]->SetRotation(objData.rotation);
	//				Vector3 m_magPos = objData.position;
	//				m_magPos.x += 50.0f;
	//				m_magPos.y -= 50.0f;
	//				m_magnet[sampleNum]->SetMagnetPosition(m_magPos);
	//				m_magnet[sampleNum]->SetMagnetNum(sampleNum);
	//				sampleNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"DeathBlock") == true) {
	//				m_deathBlock.push_back(NewGO<DeathBlock>(0));
	//				m_deathBlock[deathBlockNum]->Init("DeathBlock");
	//				m_deathBlock[deathBlockNum]->SetPosition(objData.position);
	//				m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//				switch (m_stageNum) {
	//				case 1:
	//					break;
	//				case 2:
	//					break;
	//				case 3:
	//					break;
	//				case 4:
	//					break;
	//				}
	//				m_deathBlock[deathBlockNum]->SetStartPos({ 300.0f,1900.0f,-300.0f });
	//				m_deathBlock[deathBlockNum]->SetScale(objData.scale);
	//				deathBlockNum++;
	//				return true;
	//			}
	//			else if (objData.EqualObjectName(L"seesaw") == true) {
	//			m_seesaw.push_back(NewGO<Seesaw>(0));
	//			//m_seesaw[seesawNum] = NewGO<Seesaw>(0);
	//			m_seesaw[seesawNum]->SetPosition(objData.position);
	//			m_seesaw[seesawNum]->SetRotation(objData.rotation);
	//			m_seesaw[seesawNum]->Init("seesaw");
	//			m_seesaw[seesawNum]->StartRot(objData.rotation);
	//			seesawNum++;
	//			//m_seesaw->SetScale(objData.scale);
	//			//m_seesaw->SetStartPos({ 300.0f,1300.0f,-300.0f });
	//			//m_seesaw->SetScale(objData.scale);
	//			return true;
	//			}

	//			return false;//levelのオブジェクトをそのままロード。
	//			});

	//		m_player->SetPosition({ 300.0f,1900.0f,-300.0f });
	//		m_player->SetStartPos({ 300.0f,1900.0f,-300.0f });
	//		break;

	//}

	//BGM再生。

	SoundManager::GetInstance()->Play(BGM_Game);

	//ModelInitData initData;
	//initData.m_tkmFilePath = "Assets/modelData/bg/bg.tkm";
	///シェーダーファイルのファイルパスを指定する。
	//initData.m_fxFilePath = "Assets/shader/model.fx";
	///頂点シェーダーのエントリーポイント
	//initData.m_vsEntryPointFunc = "VSMain";
	//m_model.Init(initData);
	//
	///メッシュコライダーを作成。
	//m_physicsStaticObject.CreateFromModel(m_model, m_model.GetWorldMatrix());
	return true;
}


BackGround::~BackGround()
{
	//背景削除。
	DeleteGO(m_spriteRender);
	for (int i = 0; i < m_magnet.size(); i++) {
		DeleteGO(m_magnet[i]);
	}
	for (int i = 0; i < m_seesaw.size(); i++) {
		DeleteGO(m_seesaw[i]);
	}
	for (int i = 0; i < m_deathBlock.size(); i++) {
		DeleteGO(m_deathBlock[i]);
	}
	//タイム削除。
	DeleteGO(m_fontRender);
	DeleteGO(m_key);
	DeleteGO(m_player);
	m_player = nullptr;
	DeleteGO(m_treasureBox);
	DeleteGO(m_level2D);
}


void BackGround::Update()
{
	if (m_seesawFlg) {
		for (int i = 0; i < m_seesaw.size(); i++) {
			m_seesaw[i]->SetStart();
		}
		m_seesawFlg = false;
	}
	//static int sampleNum = 0;
	//Vector3 pos = m_magnet[sampleNum]->GetPosition();
	//if (g_pad[0]->IsTrigger(enButtonA)) {
	//	m_magnet[sampleNum]->SetPosition({ pos.x,pos.y,pos.z - 100.0f });
	//	sampleNum++;
	//}
}

void BackGround::LevelInit(const char* filePath) {

	int magnetNum = 0;
	int seesawNum = 0;
	int deathBlockNum = 0;

	m_level.Init(filePath, [&](LevelObjectData& objData) {


		//return true;が自分で生成。return false;がパソコンが生成してくれる。
		//falseだと生成勝手にしてくれるけど、位置変えたりとかいじれない！！

		m_deathPosY = -500.0f;		//state02では-500.0fで死ぬ！

		if (objData.EqualObjectName(L"Key_after") == true) {
			if (m_key == nullptr) {
				m_key = NewGO<Key>(0, "key");
			}
			m_key->InitKey("Key_after");
			m_key->SetKeyPos(objData.position);
			m_key->SetScaleKey(objData.scale);
			m_key->SetTriggerBox(objData.position);
			return true;
		}
		else if (objData.EqualObjectName(L"KeyBox") == true) {
			if (m_key == nullptr) {
				m_key = NewGO<Key>(0, "key");
			}
			m_key->InitDoor("KeyBox");
			m_key->SetDoorPos(objData.position);

			m_key->SetScaleDoor(objData.scale);

			Effect* treasure = nullptr;
			treasure = NewGO<Effect>(0);
			treasure->Init(u"Assets/effect/treasure_4.efk");
			treasure->SetScale({ 80.0f,80.0f,80.0f });
			Vector3 effPos = objData.position;
			effPos += { 200.0f, -150.0f, -200.0f };
			treasure->SetPosition(effPos);
			//treasure->Update();
			treasure->Play();
			return true;
		}
		else if (objData.EqualObjectName(L"TreasureBox") == true) {

			m_treasureBox = NewGO<TreasureBox>(0, "treasureBox");
			Vector3 pos = objData.position;
			pos.x -= 75.0f;
			pos.z -= 50.0f;
			m_treasureBox->SetPosition(pos);
			m_treasureBox->SetRotation(objData.rotation);
			Vector3 sca = objData.scale;
			sca.x = 2.5f;
			sca.y = 2.5f;
			sca.z = 2.5f;
			m_treasureBox->SetScale(sca);
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N100_100") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_N();
			m_magnet[magnetNum]->Init("Magnet_N100_100");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 50.0f;
			m_magPos.y += 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S100_100") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_S();
			m_magnet[magnetNum]->Init("Magnet_S100_100");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 50.0f;
			m_magPos.y += 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N100_200triangle") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_N();
			m_magnet[magnetNum]->Init("Magnet_N100_200triangle");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 150.0f;
			m_magPos.y -= 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S100_200triangle") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_S();
			m_magnet[magnetNum]->Init("Magnet_S100_200triangle");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 150.0f;
			m_magPos.y -= 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N-100_200triangle") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_N();
			m_magnet[magnetNum]->Init("Magnet_N-100_200triangle");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 150.0f;
			m_magPos.y -= 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_N100_-200triangle") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_N();
			m_magnet[magnetNum]->Init("Magnet_N100_-200triangle");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 50.0f;
			m_magPos.y += 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S-100_200triangle") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_S();
			m_magnet[magnetNum]->Init("Magnet_S-100_200triangle");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 150.0f;
			m_magPos.y -= 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S-100_-200triangle") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_S();
			m_magnet[magnetNum]->Init("Magnet_S-100_-200triangle");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 50.0f;
			m_magPos.y += 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"Magnet_S100_-200triangle") == true) {
			m_magnet.push_back(NewGO<Magnet>(0));
			m_magnet[magnetNum]->SetState_S();
			m_magnet[magnetNum]->Init("Magnet_S100_-200triangle");
			m_magnet[magnetNum]->SetPosition(objData.position);
			m_magnet[magnetNum]->SetRotation(objData.rotation);
			Vector3 m_magPos = objData.position;
			m_magPos.x += 50.0f;
			m_magPos.y -= 50.0f;
			m_magnet[magnetNum]->SetMagnetPosition(m_magPos);
			m_magnet[magnetNum]->SetMagnetNum(magnetNum);
			magnetNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"DeathBlock") == true) {
			m_deathBlock.push_back(NewGO<DeathBlock>(0));
			m_deathBlock[deathBlockNum]->Init("DeathBlock");
			m_deathBlock[deathBlockNum]->SetPosition(objData.position);
			m_deathBlock[deathBlockNum]->SetScale(objData.scale);
			m_deathBlock[deathBlockNum]->SetStartPos(stageStartPos[m_stageNum - 1]);
			m_deathBlock[deathBlockNum]->SetScale(objData.scale);
			deathBlockNum++;
			return true;
		}
		else if (objData.EqualObjectName(L"seesaw") == true) {
			m_seesaw.push_back(NewGO<Seesaw>(0));
			//m_seesaw[seesawNum] = NewGO<Seesaw>(0);
			m_seesaw[seesawNum]->SetPosition(objData.position);
			m_seesaw[seesawNum]->SetRotation(objData.rotation);
			m_seesaw[seesawNum]->Init("seesaw");
			m_seesaw[seesawNum]->StartRot(objData.rotation);
			seesawNum++;
			//m_seesaw->SetScale(objData.scale);
			//m_seesaw->SetStartPos({ 300.0f,1300.0f,-300.0f });
			//m_seesaw->SetScale(objData.scale);
			return true;
		}

		return false;//levelのオブジェクトをそのままロード。
		});
		m_player->SetPosition(stageStartPos[m_stageNum - 1]);
		m_player->SetStartPos(stageStartPos[m_stageNum - 1]);
}


void BackGround::Render(RenderContext& rc)
{
	m_level.Draw(rc);
	m_model.Draw(rc);
}