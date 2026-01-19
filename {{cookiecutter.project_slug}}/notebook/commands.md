# コマンドチートシート

注意: cookiecutter後の `cd` を忘れずに!

---

## 0. 前提

- CMake >= 3.24
- C++23 対応コンパイラ（MSVC / clang / gcc）
- SDL3（必要なら vcpkg 等で導入）

---

## 1. CMake: Configure（生成）

### Debug 生成（おすすめ）
```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

### Release 生成
```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

### Ninja を使う場合（入っているなら速い）
```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```

---

## 2. Build（ビルド）

### Debug ビルド
```powershell
cmake --build build --config Debug
```

### Release ビルド
```powershell
cmake --build build --config Release
```

※ `--config` は Visual Studio 系のマルチコンフィグ環境で必要。  
※ Linux/macOS（Makefile/Ninja など）では `--config` は不要な場合が多い。

---

## 3. Run（実行）

### ビルド済み実行ファイルの実行（Windows例）
```powershell
.\build\bin\{{cookiecutter.project_slug}}.exe
```

### CMake から実行（ターゲット実行）
```powershell
cmake --build build --target {{cookiecutter.project_slug}} --config Debug
.\build\bin\{{cookiecutter.project_slug}}.exe
```

---

## 4. Clean（クリーン）

### ビルド成果物を全消し（確実）
```powershell
Remove-Item -Recurse -Force build
```

### もう一度生成し直す
```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

---

## 5. Tests（テスト）

### テストをビルド
```powershell
cmake --build build --config Debug
```

### CTest 実行
```powershell
ctest --test-dir build -C Debug
```

### 詳細出力（失敗時の原因が見やすい）
```powershell
ctest --test-dir build -C Debug --output-on-failure
```

---

## 6. Install（任意）

インストール設定を書いた場合のみ利用。

```powershell
cmake --install build --config Release
```

---

## 7. Git 基本操作

### 初期化（テンプレ使用直後など）
```powershell
git init
```

### 状態確認
```powershell
git status
```

### 差分確認
```powershell
git diff
```

### 追加（ステージング）
```powershell
git add .
```

### コミット
```powershell
git commit -m "init project"
```

### ブランチ確認
```powershell
git branch
```

### 新ブランチ作成 & 移動
```powershell
git switch -c feature/my-feature
```

### ブランチ切り替え
```powershell
git switch main
```

### リモート追加（GitHubなど）
```powershell
git remote add origin <YOUR_REPO_URL>
```

### push（初回）
```powershell
git push -u origin main
```

### pull（更新を取得）
```powershell
git pull
```

---

## 8. よくある運用コマンドセット（おすすめ）

### 開発開始（Debug）
```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
.\build\bin\{{cookiecutter.project_slug}}.exe
```

### リリース用（Release）
```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
.\build\bin\{{cookiecutter.project_slug}}.exe
```

### すべてやり直す
```powershell
Remove-Item -Recurse -Force build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```