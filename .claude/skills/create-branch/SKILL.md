---
name: create-branch
description: GitFlowに従ってブランチを作成。「ブランチを作って」「Issue着手」「#42に着手」「このIssueをやる」「タスクを始める」「作業開始」「着手する」「対応する」「取り掛かる」「GitFlowで」「hotfixで」「featureで」などと言われた時に使用。
---

# ブランチ作成スキル（worktree方式）

worktreeを使ってfeature/hotfixブランチを作成する。メインリポジトリ（keyball/）は常にdevelopブランチを維持する。

---

## worktree構成

```
~/git/
├── keyball/                         # developブランチ（常にdevelopを維持）
├── keyball-feature-{issue番号}/     # featureブランチ用worktree
└── keyball-hotfix-{説明}/           # hotfixブランチ用worktree
```

---

## 実行手順

### Step 1: ブランチ種別を確認

ユーザーに確認：
- **feature**: Issue対応、新機能、タスク → Issue番号が必要
- **hotfix**: 軽微な修正、緊急対応 → Issue番号不要

### Step 2: 必要情報を収集

**featureの場合:**
- Issue番号（必須）
- 短い説明（英語、ケバブケース推奨）

**hotfixの場合:**
- 短い説明（英語、ケバブケース推奨）

### Step 3: developブランチを最新化

```bash
cd /Users/masatomix/git/keyball
git checkout develop
git pull origin develop
```

### Step 4: worktreeを作成

**featureブランチの場合:**
```bash
git worktree add -b feature/{issue番号}-{説明} ../keyball-feature-{issue番号} develop
```

例:
```bash
git worktree add -b feature/42-add-user-auth ../keyball-feature-42 develop
```

**hotfixブランチの場合:**
```bash
git worktree add -b hotfix/{説明} ../keyball-hotfix-{説明} develop
```

例:
```bash
git worktree add -b hotfix/fix-typo ../keyball-hotfix-fix-typo develop
```

### Step 5: 完了案内

作成完了後、以下を案内：

```
worktreeを作成しました:
- ブランチ: feature/{issue番号}-{説明}
- パス: /Users/masatomix/git/keyball-feature-{issue番号}

作業を開始するには:
  cd /Users/masatomix/git/keyball-feature-{issue番号}

作業完了後のクリーンアップ:
  cd /Users/masatomix/git/keyball
  git worktree remove ../keyball-feature-{issue番号}
  git branch -D feature/{issue番号}-{説明}
  git push origin --delete feature/{issue番号}-{説明}
  git pull origin develop
```

---

## 注意事項

- メインリポジトリ（/Users/masatomix/git/keyball）では直接作業しない
- worktree内で作業・コミット・プッシュを行う
- PRマージ後は必ずworktreeを削除する
- PRのベースブランチは `develop` を指定する
- 既存のworktreeがある場合は `git worktree list` で確認

---

## 参考コマンド

```bash
# worktree一覧を確認
git worktree list

# worktreeを削除
git worktree remove ../keyball-feature-{issue番号}

# 強制削除（未コミットの変更がある場合）
git worktree remove --force ../keyball-feature-{issue番号}

# リモートブランチの削除
git push origin --delete feature/{issue番号}-{説明}
```
