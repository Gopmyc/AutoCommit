
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
	An autonomous Git commit generator written in C.
	Automatically analyses modified files, infers commit type from customizable rules, builds semantic commit messages, and updates project versioning.
	<br /><br />
	Configurable, fast, and designed for real automation workflows.
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

`AutoCommit` is a command-line utility that automates Git commit creation based on detected file changes.
It loads rules from a JSON configuration (via `cJSON`), determines commit type, generates semantic commit messages, and optionally increments the project version.

Designed for developers who want consistent commit history without thinking about wording or categories.

### Key Features

* 📂 Smart detection of modified, added, deleted, and renamed files
* 🧠 JSON-driven commit rules
* ✨ Automatic semantic commit formatting
* 🔢 Version auto-increment (`VERSION` file)
* 🛡️ Safe mode for debugging without committing
* 🚫 Optional `--no-version` mode

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Built With

* ![C](https://img.shields.io/badge/C-00599C?style=for-the-badge\&logo=c\&logoColor=white)

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Getting Started

This section explains how to build and use the tool locally.

### Prerequisites

You’ll need:

* `gcc` or `clang`
* Make
* Git
* A POSIX-compatible environment

### Installation

1. Clone the repo:

   ```bash
   git clone https://github.com/Gopmyc/AutoCommit.git
   cd AutoCommit
   ```

2. Build the program:

   ```bash
   make
   ```

3. Ensure `commit_config.json` exists at the project root.
   If you use the default one, you’re ready to go.

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Usage

### Basic usage

```bash
./auto_commit
```

### Debug (dry-run)

```bash
./auto_commit --safe
```

### Disable version updates

```bash
./auto_commit --no-version
```

### Combined

```bash
./auto_commit --safe --no-version
```

AutoCommit will:

1. Detect modified files through `git status`
2. Match each file against rules in `commit_config.json`
3. Generate a semantic commit message
4. Optionally increment and save the version
5. Execute the corresponding Git commands

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Roadmap

* [x] JSON-driven rule system
* [x] Auto-versioning
* [x] Safe mode
* [x] Modular internal architecture
* [ ] Windows support (cross-platform commits)
* [ ] Rule overrides via CLI
* [ ] Extended rule matching (regex, glob patterns)
* [ ] Multi-file commit batching

Feature suggestions are welcome via the Issues tab.

<p align="right"><a href="#readme-top">🔝</a></p>

---

## Contributing

Contributions are welcome.

1. Fork the repo
2. Create your branch (`git checkout -b feature/NewFeature`)
3. Commit your changes (`git commit -m 'Add NewFeature'`)
4. Push (`git push origin feature/NewFeature`)
5. Create a Pull Request

### Contributors

<a href="https://github.com/Gopmyc/AutoCommit/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=Gopmyc/AutoCommit" />
</a>

<p align="right"><a href="#readme-top">🔝</a></p>

---

## License

Distributed under the MIT License.
See [`LICENSE`](https://github.com/Gopmyc/AutoCommit/blob/main/LICENSE) for details.

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
