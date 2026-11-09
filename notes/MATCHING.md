# Matching techniques

Compiler idioms and source forms that fix near-misses in this ROM, each with the
function it worked on and the compiler (2.0/sp2p2 unless stated otherwise).

## Branches and stores

- A global address loaded in both arms of a conditional (`cmp r0, #0; ldrlt r1, =g;
  rsblt r0, r0, #0; ldrge r1, =g; str r0, [r1, #x]`) comes from a store written in
  each branch, `if (v < 0) g.f = -v; else g.f = v;`; `if (v < 0) v = -v; g.f = v;`
  loads the address once before the `cmp` (57 % -> 100 %, `func_02040c98`,
  `func_02040cb4`).

## Registers

- A repeated subexpression written out instead of kept in a local: in
  `func_02040cd0` the original loads `fade->target` into r1 and sets the division
  arguments `r0 = 16` before `r1 = range`; with a local `range = 16 - fade->target`
  the load goes to r0 and the arguments are set in the other order (99.75 %).
  Writing `(16 / (16 - fade->target)) * ((fade->frame * (16 - fade->target)) /
  fade->duration)` gives 100 %. Declaration order of the locals also moved this
  function from 98.66 % to 99.75 % (`target, level, done, dir, finished`; found by
  a script over the permutations).

## Data addressing

- A file's static scalars are addressed from one base: the pool holds the address
  of the first one and the code reads `[base, #offset]`. A source that declares them
  `extern` one by one loads each address instead. Describe the block as one
  `extern struct` named after the base symbol, members at the offsets the code reads
  (`OS_GetTick`, the thread functions at `data_020cbcc0`, the NitroSystem sound
  locks at `data_020ddab8`, stream player and command blocks; library units written
  with `lib_unit_gen.py --source`).
- A load of `T+0`, where dsd put a symbol `T` inside an object `S`, matches a source
  that writes `S.member` (`S+N`) once `relocs.txt` says `to:S add:N` (24 loads in
  the library units).
- Two pool entries for one address come from two distinct symbols (khdays'
  `data_02047370_budget` in `GfxQueue_Configure`; `SDK_OVERLAY_DIGEST` and
  `SDK_OVERLAY_DIGEST_END` in `FS_StartOverlay`), or from a function's `static`
  variable (`NNS_SndArcLoadWaveArcTable`): mwcc does not merge them. One symbol, or a
  file-level `extern`, gives one entry.
- Scheduling around a volatile register read depends on whether the stored variable
  can alias it: a store to a variable that the file defines (a `static`, or khdays'
  definitions) moves after the read; a store to an `extern` stays before it
  (`OS_InitLock` with a constant lock address, `CTRDGi_InitModuleInfo`,
  `SND_RecvCommandReply`). These need the unit to define its data (own `.bss`).
- A value the linker defines (`SDK_IRQ_STACKSIZE`, `SDK_SYS_STACKSIZE`,
  `SDK_SECTION_ARENA_DTCM_START`) keeps a runtime test the constant would fold
  (`OS_GetInitArenaHi`, `OSi_InitStackChecker`): the source must name a symbol, which
  `relocs.txt` cannot express (dsd has no absolute symbols), so the original word has
  no relocation.

Beyond these, read the sibling project's notes,
`E:\Projets\Dev\ts2-castaway\notes\MATCHING.md` (mwccarm 2.0, ARM code). A technique
from there is recorded here only once it has worked on a function of this ROM, with
the function and the compiler it was tried with: this game may use another compiler,
other flags and much more Thumb code.
