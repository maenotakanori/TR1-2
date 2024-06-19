#include <Novice.h>
#include<time.h>

const char kWindowTitle[] = "LE2D_21_マエノ_タカノリ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int map[15][11] = {
		{1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,2,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1} };

	//0.空白　1.ブロック　2.プレイヤー　3.目的地 

	int mapNumber[15][11] = {
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0} };
	int mapDebug = 0;

	int blocksize = 32;
	int blockposx = 480;
	int blockposy = 120;

	int moovW = 0;
	int moovA = 0;
	int moovS = 0;
	int moovD = 0;

	int timer = 10;
	int timerON = 0;

	int moovAI = 0;

	int playerPosX = 0;
	int playerPosY = 0;
	int goalPosX = 0;
	int goalPosY = 0;
	srand((unsigned int)time(nullptr));
	int randPosX = rand() % 9;
	int randPosY = rand() % 13;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		//移動
		if (keys[DIK_W]) { moovW = 1; timerON = 1; }
		if (keys[DIK_A]) { moovA = 1; timerON = 1; }
		if (keys[DIK_S]) { moovS = 1; timerON = 1; }
		if (keys[DIK_D]) { moovD = 1; timerON = 1; }
		if (keys[DIK_SPACE]) { moovAI = 1; }
		if(keys[DIK_Q]){ mapDebug = 1; }
		else { mapDebug = 0; }
		if (keys[DIK_E] && timerON == 0	) {
			timerON = 1;
			
			randPosX = rand() % 9;
			randPosY = rand() % 13;
			if (randPosX == 0) { randPosX = 9; }
			if (randPosY == 0) { randPosY = 13; }

			map[randPosY][randPosX] = 3;
		}

		if (timerON == 1) { timer--; }
		if (timer <= 0) { timerON = 0; timer = 10; }


		if (moovW == 1 && timerON == 0) {
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 11; j++) {
					if (map[i][j] == 2 && map[i - 1][j] != 1) {
						map[i - 1][j] = 2; map[i][j] = 0;
						moovW = 0;
						break;
					}
				}
			}
		}
		if (moovA == 1 && timerON == 0) {
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 11; j++) {
					if (map[i][j] == 2 && map[i][j - 1] != 1) {
						map[i][j - 1] = 2; map[i][j] = 0;
						moovA = 0;
						break;
					}
				}
			}
		}
		if (moovS == 1 && timerON == 0) {
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 11; j++) {
					if (map[i][j] == 2 && map[i + 1][j] != 1) {
						map[i + 1][j] = 2; map[i][j] = 0;
						moovS = 0;
						i = 99;
						break;
					}
				}
			}
		}
		if (moovD == 1 && timerON == 0) {
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 11; j++) {
					if (map[i][j] == 2 && map[i][j + 1] != 1) {
						map[i][j + 1] = 2; map[i][j] = 0;
						moovD = 0;
						break;
					}
				}
			}
		}

		//ポジション
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 11; j++) {
				if (map[i][j] == 2) { playerPosX = j; playerPosY = i; }
				if (map[i][j] == 3) { goalPosX = j; goalPosY = i; }
			}
		}

		//ルート調査
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 11; j++) {
				if (map[i][j] == 3) {
					mapNumber[i][j] = 1;
				}
				for (int mapCount = 1; mapCount < 20; mapCount++) {
					if (mapNumber[i][j] == mapCount) {
						if (map[i - 1][j] == 0 && mapNumber[i - 1][j] == 0 || map[i - 1][j] == 2 && mapNumber[i - 1][j] == 0) { mapNumber[i - 1][j] = mapCount + 1; }
						if (map[i][j - 1] == 0 && mapNumber[i][j - 1] == 0 || map[i][j - 1] == 2 && mapNumber[i][j - 1] == 0) { mapNumber[i][j - 1] = mapCount + 1; }
						if (map[i + 1][j] == 0 && mapNumber[i + 1][j] == 0 || map[i + 1][j] == 2 && mapNumber[i + 1][j] == 0) { mapNumber[i + 1][j] = mapCount + 1; }
						if (map[i][j + 1] == 0 && mapNumber[i][j + 1] == 0 || map[i][j + 1] == 2 && mapNumber[i][j + 1] == 0) { mapNumber[i][j + 1] = mapCount + 1; }
					}
				}
			}
		}



		//移動AI
		if (moovAI == 1) {
			if (mapNumber[playerPosY][playerPosX] > mapNumber[playerPosY + 1][playerPosX]){ moovW = 1; timerON = 1; }
			if (mapNumber[playerPosY][playerPosX] > mapNumber[playerPosY][playerPosX - 1]) { moovA = 1; timerON = 1; }
			if (mapNumber[playerPosY][playerPosX] > mapNumber[playerPosY + 1][playerPosX]) { moovS = 1; timerON = 1; }
			if (mapNumber[playerPosY][playerPosX] > mapNumber[playerPosY][playerPosX + 1]) { moovD = 1; timerON = 1; }
		}

		if (playerPosX == goalPosX && playerPosY == goalPosY) {
			moovAI = 0;
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 11; j++) {
					mapNumber[i][j] = 0;
				}
			}
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//マップ描画
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 11; j++) {
				if (map[i][j] == 0) { Novice::DrawBox(j * blocksize + blockposx, i * blocksize + blockposy, blocksize, blocksize, 0.0f, WHITE, kFillModeWireFrame); }
				if (map[i][j] == 1) { Novice::DrawBox(j * blocksize + blockposx, i * blocksize + blockposy, blocksize, blocksize, 0.0f, BLACK, kFillModeSolid); }
				if (map[i][j] == 2) { Novice::DrawBox(j * blocksize + blockposx, i * blocksize + blockposy, blocksize, blocksize, 0.0f, BLUE, kFillModeSolid); }
				if (map[i][j] == 3) { Novice::DrawBox(j * blocksize + blockposx, i * blocksize + blockposy, blocksize, blocksize, 0.0f, RED, kFillModeSolid); }
			}
		}

		//デバッグ
		Novice::ScreenPrintf(0, 0, "posX %d", playerPosX);
		Novice::ScreenPrintf(0, 20, "posY %d", playerPosY);
		Novice::ScreenPrintf(0, 100, "moovW %d", moovW);
		Novice::ScreenPrintf(0, 120, "moovA %d", moovA);
		Novice::ScreenPrintf(0, 140, "moovS %d", moovS);
		Novice::ScreenPrintf(0, 160, "moovD %d", moovD);

		if (mapDebug == 1) {
			for (int i = 0; i < 15; i++) {
				for (int j = 0; j < 11; j++) {
					for (int mapCount = 1; mapCount < 20; mapCount++) {
						if (mapNumber[i][j] == mapCount) {
							Novice::ScreenPrintf(j* blocksize + blockposx + 12, i* blocksize + blockposy + 8, "%d", mapCount);
							Novice::DrawBox(j * blocksize + blockposx, i * blocksize + blockposy, blocksize, blocksize, 0.0f, BLUE, kFillModeWireFrame);
						}
						
						
					}
				}
			}
		}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
