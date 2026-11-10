Dragon Quest Monsters: Joker 2 (Nintendo DS)
============================================

> [!IMPORTANT]
> AI Disclosure:
> AI was used for the following tasks:
> - Writing commentary (primarily translating into English and formatting).
> - Documenting and citing the various sources used in the project (see PROVENANCE.md, REFERENCE.md, and more generally the files contained within the "notes" directory).
> - Writing code (C, C++, Python, etc.—I used it as a tool) and reviewing my own work (yes, some code was written by AI, but it was verified by a human; I didn't simply type "Claude, decompile this for me").

A work-in-progress matching decompilation of Dragon Quest Monsters: Joker 2 for the
Nintendo DS, built with [ds-decomp](https://github.com/AetiasHax/ds-decomp).

> [!NOTE]
> No port to PC or other platforms is planned for the time being, but should that change, the link will appear here

This repository does **not** contain any game assets or assembly whatsoever. An existing
copy of the game is required.

It builds the following versions:

Name | Description       | SHA1 Hash of input ROM(s)
---- | ----------------- | ------------------------------------------
jpn  | Japan Revision 0 (`CJRJ`) | `fa7da80d6ba30d1cdaa43a157a5851a97f9e97ea`
eur  | Europe Revision 0 (`CJRP`), not supported yet | `513ac63c7d67211007da6ba7050b179dfafb362a`

The default version is `jpn`, i.e. the Japan Revision 0 ROM.

Progress
========

| Release | Game code | Progress |
|---|---|---|
| Dragon Quest Monsters: Joker 2 (Japan) | `CJRJ` | [![Fuzzy](progress/jpn/fuzzy.svg)](notes/PROGRESS.md) [![Perfect](progress/jpn/perfect.svg)](notes/PROGRESS.md) [![Linked](progress/jpn/linked.svg)](notes/PROGRESS.md) |
| Dragon Quest Monsters: Joker 2 (Europe) | `CJRP` | not supported yet |

[![Progress card](progress/jpn/card.svg)](notes/PROGRESS.md)

- **Fuzzy**: objdiff fuzzy match score over all code.
- **Perfect**: code that matches byte for byte.
- **Linked**: code built from source (`complete` files of `delinks.txt`).

The badges and the card are drawn from the objdiff report by
`tools/progress_badges.py`. After a build, `python tools/progress_badges.py --record`
redraws `progress/jpn/` and adds the current commit to `progress/jpn/history.csv`.

Dependencies
============

- [Python](https://www.python.org/downloads/) 3.10+ in `%PATH%`, then
  `pip install -r tools/requirements.txt`.
- [ninja](https://github.com/ninja-build/ninja/releases) in `%PATH%`
  (`pip install ninja` works too).
- On Windows use native tooling; WSL or msys2 are not required. On Linux,
  [wibo](https://github.com/decompals/wibo) is downloaded to run the compiler.

dsd, objdiff-cli and the mwccarm compilers are downloaded by the first `ninja` run.

Building
========

1. Copy the ROM to `extract/baserom_dqmj2_jpn.nds`
   (SHA-1 `fa7da80d6ba30d1cdaa43a157a5851a97f9e97ea`).
2. Optional: copy your own `arm7_bios.bin` to the repository root to check the
   original ROM SHA-1 (without it the secure area is not encrypted, see `SPEC.md`).
3. Run:

   ```
   python tools/configure.py
   ninja
   ```

   The first `ninja` only downloads the tools and reruns `configure.py`; run `ninja`
   again. A build ends with `build\jpn\dqmj2_jpn.nds: OK`.

Diffing
=======

`ninja objdiff` writes `objdiff.json`; open the repository folder in
[objdiff](https://github.com/encounter/objdiff). `ninja report` writes
`build/jpn/report.json`.

Documentation
=============

- `SPEC.md`: target ROM, toolchain, acceptance criteria, naming.
- `notes/`: compiler evidence, region map, matching techniques, references and
  provenance of reused code, progress log.
