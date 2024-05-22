#include <Novice.h>

const char kWindowTitle[] = "LE2D_21_マエノ_タカノリ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	int map[15][11] = {
		{1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,3,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,1},
		{1,0,0,0,0,1,0,0,0,0,1},
		{1,0,0,0,1,0,1,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,2,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1} };

	//0.空白　1.ブロック　2.プレイヤー　3.対象地点 

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

	int playerposX = 0;
	int playerposY = 0;
	int goalposX = 0;
	int goalposy = 0;

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
				if (map[i][j] == 2) { playerposX = j; playerposY = i; }
				if (map[i][j] == 3) { goalposX = j; goalposy = i; }
			}
		}

		//移動AI
		if (moovAI == 1) {

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
		Novice::ScreenPrintf(0, 0, "timer %d", timer);
		Novice::ScreenPrintf(0, 20, "posX %d", playerposX);
		Novice::ScreenPrintf(0, 40, "posY %d", playerposY);

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
