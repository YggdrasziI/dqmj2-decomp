# Matching techniques

Compiler idioms and source forms that fix near-misses in this ROM, each with the
function it worked on and the compiler (2.0/sp2p2 unless stated otherwise).

## Branches and stores

- A global address loaded in both arms of a conditional (`cmp r0, #0; ldrlt r1, =g;
  rsblt r0, r0, #0; ldrge r1, =g; str r0, [r1, #x]`) comes from a store written in
  each branch, `if (v < 0) g.f = -v; else g.f = v;`; `if (v < 0) v = -v; g.f = v;`
  loads the address once before the `cmp` (57 % -> 100 %, `func_02040c98`,
  `func_02040cb4`).

- A `>= 0` test on a `u16` field that the original keeps (`ldrh; cmp r0, #0; blt`):
  write `(int)field >= 0`; a bare `field >= 0` is folded away (`func_020411c4`,
  87 % -> 100 %).
- `if (f() == 0) { ... } else { ret = 1; }` puts the `ret = 1` block after the
  main path, as in the original; the inverted test gives `movne` early
  (`func_020410ec`, `func_020412fc`).
- A store of a call result in one branch and of a constant in the other, with the
  constant store conditionalized (`ldrne; movne; strneb; bne`): write the call
  branch first, `if (!f()) g.x = h(); else g.x = 0;` (`func_02042e88`, 95 % ->
  100 %).
- A `u8` function that masks only the result of a comparison (`movgt; movle; and
  r0, r0, #0xff`): write that return as `a > b ? 1 : 0`; a bare `a > b` and the
  `if` forms drop the `and`, a ternary returning other constants adds one
  (`func_02042db8`, 94.2 % -> 100 %).
- Stack arrays and structs take their slots in reverse declaration order: the
  last declared gets the lowest offset (`func_02043938` buffers, `func_02043a4c`
  matrix and vectors).

## Registers

- A repeated subexpression written out instead of kept in a local: in
  `func_02040cd0` the original loads `fade->target` into r1 and sets the division
  arguments `r0 = 16` before `r1 = range`; with a local `range = 16 - fade->target`
  the load goes to r0 and the arguments are set in the other order (99.75 %).
  Writing `(16 / (16 - fade->target)) * ((fade->frame * (16 - fade->target)) /
  fade->duration)` gives 100 %. Declaration order of the locals also moved this
  function from 98.66 % to 99.75 % (`target, level, done, dir, finished`; found by
  a script over the permutations).

- A loop over a global table whose base stays in a register across calls: read
  it through a local pointer (`UnkAnimRes *tbl = data_020df48c;`); indexing the
  global reloads the pool word after each call (`func_02041244`, `func_020412a0`).
  The order of the locals then fixes the registers (permutation script).
- A `u16` local set from a field load stays merged with the load's virtual
  register, so its declaration place has no effect on its color: declare it
  `int` and the declaration order applies again (`func_02042950`, `int id;`
  between `i` and `n`, 98.4 % -> 100 %). `python tools/mwcc_sched.py <src>
  <symbol> --colors` prints the coloring order (higher virtual register first).

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
- Two pool entries for one address come from two distinct symbols
  (`SDK_OVERLAY_DIGEST` and `SDK_OVERLAY_DIGEST_END` in `FS_StartOverlay`), from a
  function's `static` variable (`NNS_SndArcLoadWaveArcTable`), or from a struct that
  the file defines with `= {0}`: the member stores go through one word, the address
  passed to a callee through the other (`GfxQueue_Configure`, 100 %; an `extern` or
  an uninitialised definition gives one entry, 82 %). One `extern` symbol gives one
  entry. Same fix in `func_ov005_021cd6ec` (96.12 % -> 100 %); there the `int` just
  before the object must stay `extern`, or mwcc reaches the object from it (+4).
- Scheduling around a volatile register read depends on how the stored variable is
  declared; each case was found by trying the forms:
  - `SND_RecvCommandReply`: the file defines its nine scalars at file level with
    `= 0`. mwcc puts them in `.bss` and reaches them from the `.bss` section symbol;
    without `= 0` they become commons, each loaded from its own pool word. objdiff
    maps the section-symbol relocation to the symbol at that offset (100 %), while
    `lib_unit_gen.py --source` reports "check after renames failed" on it. The unit
    owns that `.bss` (`delinks.txt`, symbols sized in `symbols.txt`).
  - `CTRDGi_InitModuleInfo`: only a function `static` moves the store after the read
    (100 %); a global, a file `static` or an `extern` give 98.16 %. Its address is
    also used by three other units, so it stays without a source (`notes/SPLITS.md`).
  - `OS_InitLock`: a constant lock address (0x027FFFF0) schedules the stores
    differently; an `extern` symbol matches, defined by the link (below).
- String literals and file data: each literal gets its own `.data` section
  (alignment 1) and the link places them 4-byte aligned, in source order; literals
  of a table initializer come out in reverse order of appearance. Named `char[]`
  arrays come out in reverse declaration order: the ROM's L, S, M strings of
  `data_020c6a14` are declared M, S, L (`unit_02041090.cpp`; checked by the link).
  Give each string symbol its exact length in `symbols.txt` (`kind:data(byte[10])`),
  otherwise dsd counts the padding and objdiff scores `.data` below 100 %; rename
  literals to the object's `@<n>` names (`local`) printed by `check symbols`.
- A symbol that dsd placed inside an object (`data_020df025` = `data_020defec` +
  0x39) is removed and its load becomes `to:0x020defec add:0x39` in `relocs.txt`.
- A function `static` is a local symbol `name$N` in the object. In `symbols.txt` it
  is written `name$N ... local` (dsd's `check symbols` compares the part before `$`);
  dsd rejects a relocation from another unit to a local symbol.

- Data inside code (constants read pc-relative by hand-written ARM) is written as
  an `asm` function of `dcd` words (`.word` is rejected); mwcc keeps `asm` functions
  in source order, so the block placed first lands before the function
  (`DGTi_Hash2ProcessBlock`).

## Link-defined values

- A value that the SDK's link script defines (`SDK_IRQ_STACKSIZE`,
  `SDK_SYS_STACKSIZE`, `SDK_SECTION_ARENA_DTCM_START`, `SDK_OVERLAY_DIGEST[_END]`)
  keeps a runtime test that a constant would fold, so the source names a symbol.
  `tools/lcf_keep.py` defines it (`ABSOLUTE_SYMBOLS`, value read from the literal
  pool). `relocs.txt` cannot express such a symbol (dsd has no absolute symbols), so
  the original word has no relocation; objdiff still scores the function 100 % and
  the ROM check proves the bytes (`OSi_InitStackChecker`, `OS_GetInitArenaHi`,
  `FS_StartOverlay`, and the lock word of `OS_InitLock`).
- A symbol defined this way is not seen by dsd's `check symbols` (it is in no module
  section): it cannot stand for a `symbols.txt` entry.

Beyond these, read the sibling project's notes,
`E:\Projets\Dev\ts2-castaway\notes\MATCHING.md` (mwccarm 2.0, ARM code). A technique
from there is recorded here only once it has worked on a function of this ROM, with
the function and the compiler it was tried with: this game may use another compiler,
other flags and much more Thumb code.
