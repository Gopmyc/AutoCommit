<a id="readme-top"></a>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![project\_license][license-shield]][license-url]
[![Email][email-shield]][email-url]

<br />
<div align="center">
	<a href="https://github.com/Gopmyc/AutoCommit">
		<img src="auto_commit_logo.png" alt="Logo" width="80" height="80">
	</a>

<h3 align="center">AutoCommit</h3>

<p align="center">
	A deterministic Git commit generator written in C.<br />
	Automatically analyzes modified files, applies explicit rule-based logic, builds semantic commit messages (with emoji support), and optionally updates project versioning.
	<br /><br />
	Predictable, auditable, and designed for real automation workflows.
	<br />
	<br />
	<a href="https://github.com/Gopmyc/AutoCommit"><strong>Explore the source »</strong></a>
	<br />
	<br />
	<a href="https://github.com/Gopmyc/AutoCommit/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
	·
	<a href="https://github.com/Gopmyc/AutoCommit/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
</p>
</div>

---

## About The Project

`AutoCommit` is a low-level command-line utility that automates Git commit creation based on detected file changes and explicit configuration rules.

It does **not** rely on AI, heuristics, or diff-based intent inference. Every commit message is the result of deterministic logic implemented in C and driven by a JSON configuration.

The goal is simple: produce **high-signal, reproducible commit history** suitable for humans and automation alike.

### What AutoCommit Is (and Is Not)

AutoCommit **does not**:

* infer intent from code diffs
* inspect function-level changes
* guess features or business logic

Instead, it:

* analyzes the Git working tree
* detects added, modified, deleted, and renamed files
* matches file paths against explicit rules
* generates semantic commit messages based on those rules

If you value determinism, predictability, and clarity over magic, AutoCommit fits.

### Key Features

* 📂 Smart detection of file changes via Git
* 🧠 JSON-driven rule system
* ✨ Semantic commit messages with optional emojis
* 🔢 Optional automatic version increment (`VERSION` file)
* 🛡️ Safe mode (dry-run, no commit)
* 🚫 `--no-version` mode
* ⚡ Written in pure C (fast, portable, minimal dependencies)

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Why This Exists

In many workflows, commits are either:

* manually written but inconsistent
* automated but meaningless

Typical noise looks like:

```
update file
fix stuff
modified x.c
```

AutoCommit targets the middle ground:

* zero manual effort
* no loss of semantic clarity

---

## How It Works (Technical Overview)

1. `git status` is parsed to identify file changes

2. Each file is classified (add / modify / delete / rename)

3. Paths are matched against rules defined in `commit_config.json`

4. Rules emit:

   * a commit tag (`feat`, `refactor`, `docs`, `chore`, …)
   * an optional emoji
   * a human-readable description

5. A single aggregated commit message is produced and applied

All logic lives in explicit C headers and source files to keep behavior transparent and auditable.

---

## Commit Message Examples

### Example Output

```
 feat (<scope>): ✨ add configurable commit rules
 refactor (<scope>): ♻️ simplify versioning logic
 docs (<scope>): 📚 update usage documentation
```

### Mixed Changes

```
 refactor (<scope>): ♻️ restructure core processing logic
 chore (<scope>): 📦 update project configuration
```

Emoji usage is optional and fully controlled by configuration.

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Configuration

AutoCommit behavior is driven by a JSON configuration file.

Example `commit_config.json`:

```json
[
  {
    "path": "docs/",
    "actions": {
      "add":    { "tag": "docs", "emoji": "📚", "desc": "add documentation" },
      "modify": { "tag": "docs", "emoji": "📚", "desc": "update documentation" },
      "delete": { "tag": "docs", "emoji": "🗑️", "desc": "remove documentation" },
      "rename": { "tag": "docs", "emoji": "🔄", "desc": "rename documentation" }
    }
  },
  {
    "path": "srcs/core/",
    "actions": {
      "add":    { "tag": "feat", "emoji": "✨", "desc": "add core functionality" },
      "modify": { "tag": "refactor", "emoji": "♻️", "desc": "refactor core logic" }
    }
  }
]
```

Rules are evaluated top-down. The first matching rule applies.

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Built With

* ![C](https://img.shields.io/badge/C-00599C?style=for-the-badge\&logo=c\&logoColor=white)

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Getting Started

### Prerequisites

* Git
* Make
* GCC or Clang
* POSIX-compatible environment (Linux, macOS, WSL, MSYS2)

---

### Installation (POSIX / Linux / macOS)

```bash
git clone https://github.com/Gopmyc/AutoCommit.git
cd AutoCommit
make
```

---

### Installation (Windows with MSYS2 + CMake)

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make mingw-w64-x86_64-cmake git

git clone https://github.com/Gopmyc/AutoCommit.git
cd AutoCommit
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
```

---

## Usage

```bash
./auto_commit
./auto_commit --safe
./auto_commit --no-version
```

AutoCommit will:

1. detect modified files
2. match them against rules
3. generate a semantic commit message
4. optionally update the version
5. execute the Git commit

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Limitations (By Design)

AutoCommit intentionally does **not**:

* inspect diff hunks
* understand function-level intent
* infer business logic
* split commits automatically

Multiple unrelated changes in the same directory will be grouped.

This trade-off favors determinism and simplicity.

---

## Roadmap

* Regex / glob-based rules
* Git hook integration
* Improved rule conflict detection
* Multi-commit output support

<p align="right"><a href="#readme-top">🔝</a></p>

---

## License

Distributed under the MIT License.
See `LICENSE` for details.

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Contact

**Gopmyc**
📧 [gopmyc.pro@gmail.com](mailto:gopmyc.pro@gmail.com)
🔗 [https://github.com/Gopmyc/AutoCommit](https://github.com/Gopmyc/AutoCommit)

<p align="right"><a href="#readme-top">🔝</a></p>

[contributors-shield]: https://img.shields.io/github/contributors/Gopmyc/AutoCommit.svg?style=for-the-badge
[contributors-url]: https://github.com/Gopmyc/AutoCommit/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/Gopmyc/AutoCommit.svg?style=for-the-badge
[forks-url]: https://github.com/Gopmyc/AutoCommit/network/members
[stars-shield]: https://img.shields.io/github/stars/Gopmyc/AutoCommit.svg?style=for-the-badge
[stars-url]: https://github.com/Gopmyc/AutoCommit/stargazers
[issues-shield]: https://img.shields.io/github/issues/Gopmyc/AutoCommit.svg?style=for-the-badge
[issues-url]: https://github.com/Gopmyc/AutoCommit/issues
[license-shield]: https://img.shields.io/github/license/Gopmyc/AutoCommit.svg?style=for-the-badge
[license-url]: https://github.com/Gopmyc/AutoCommit/blob/main/LICENSE
[email-shield]: https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white
[email-url]: mailto:gopmyc.pro@gmail.com
